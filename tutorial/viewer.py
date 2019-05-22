import numpy as np
import ipywidgets as widgets
from ipywidgets import HTML, Text, Output, VBox, HBox, interact
from pythreejs import *
from IPython.display import display
import matplotlib.pyplot as plt

# Helper functions
def get_colors(inp, colormap="viridis", normalize=True, vmin=None, vmax=None):
    colormap = plt.cm.get_cmap(colormap)
    if normalize:
        vmin=np.min(inp)
        vmax=np.max(inp)

    norm = plt.Normalize(vmin, vmax)
    return colormap(norm(inp))[:, :3]

def gen_checkers(n_checkers_x, n_checkers_y, width=256, height=256): 
    # tex dims need to be power of two.
    array = np.ones((width, height, 3), dtype='float32')

    # width in texels of each checker
    checker_w = width / n_checkers_x
    checker_h = height / n_checkers_y

    for y in range(height):
        for x in range(width):
            color_key = int(x / checker_w) + int(y / checker_h)
            if color_key % 2 == 0:
                array[x, y, :] = [ 1., 0.874, 0.0 ]
            else:
                array[x, y, :] = [ 0., 0., 0. ]
    return array

class Viewer():
    def __init__(self, settings):
        self.__update_settings(settings)
        self._light = DirectionalLight(color='white', position=[0, 0, 1], intensity=0.6)
        self._light2 = AmbientLight(intensity=0.5)
        self._cam = PerspectiveCamera(position=[0, 0, 1], lookAt=[0, 0, 0], fov=self.__s["fov"], 
                                     aspect=self.__s["width"]/self.__s["height"], children=[self._light])
        self._orbit = OrbitControls(controlling=self._cam)
        self._scene = Scene(children=[self._cam, self._light2], background=self.__s["background"])#"#4c4c80"
        self._renderer = Renderer(camera=self._cam, scene = self._scene, controls=[self._orbit], 
                    width=self.__s["width"], height=self.__s["height"], antialias=self.__s["antialias"])

        self.__widgets = []
        self.__objects = {}
        self.__cnt = 0
        
    def __get_shading(self, shading):
        shad = {"flat":True, "wireframe":True, "wire_width": 0.03, "wire_color": "black",
                "side": 'DoubleSide', "colormap": "viridis", "normalize": [None, None],
                "bbox": False, "roughness": 0.5, "metalness": 0.25, "reflectivity": 1.0, 
                "line_width": 1.0, "line_color": "black", "point_color": "red", "point_size": 0.01, 
                "text_color" : "red"
               }
        for k in shading:
            shad[k] = shading[k]
        return shad
        
    def __update_settings(self, settings={}):
        sett = {"width": 600, "height": 600, "antialias": True, "scale": 1.5, "background": "#ffffff", 
                "fov": 30}
        for k in settings:
            sett[k] = settings[k]
        self.__s = sett
        
    def __add_object(self, obj, parent=None):
        if not parent: # Object is added to global scene and objects dict
            self.__objects[self.__cnt] = obj
            self.__cnt += 1
            self._scene.add(obj["mesh"])
        else: # Object is added to parent object and NOT to objects dict
            parent.add(obj["mesh"])
            
        self.__update_view()
        return self.__cnt - 1
            
    
    def __add_line_geometry(self, lines, shading, obj=None):
        lines = lines.astype("float32", copy=False)
        mi = np.min(lines, axis=0)
        ma = np.max(lines, axis=0)
        geometry = BufferGeometry(attributes={'position': BufferAttribute(lines, normalized=False)})
        material = LineBasicMaterial(linewidth=shading["line_width"], color=shading["line_color"])
                    #, vertexColors='VertexColors'), 
        lines = LineSegments(geometry=geometry, material=material) #type='LinePieces')
        line_obj = {"geometry": geometry, "mesh": lines, "material": material, 
                    "max": ma, "min": mi, "type": "Lines", "wireframe": None}
        
        if obj:
            return self.__add_object(line_obj, obj), line_obj
        else:
            return self.__add_object(line_obj)
    
    def __update_view(self):
        if len(self.__objects) == 0:
            return
        ma = np.zeros((len(self.__objects), 3))
        mi = np.zeros((len(self.__objects), 3))
        for r, obj in enumerate(self.__objects):
            ma[r] = self.__objects[obj]["max"]
            mi[r] = self.__objects[obj]["min"]
        ma = np.max(ma, axis=0)
        mi = np.min(mi, axis=0)
        diag = np.linalg.norm(ma-mi)
        mean = ((ma - mi) / 2 + mi).tolist()
        scale = self.__s["scale"] * (diag)
        self._orbit.target = mean
        self._cam.lookAt(mean)
        self._cam.position = [mean[0], mean[1], mean[2]+scale]
        self._light.position = [mean[0], mean[1], mean[2]+scale]

        self._orbit.exec_three_obj_method('update')
        self._cam.exec_three_obj_method('updateProjectionMatrix')
 
    def __get_bbox(self, v):
        m = np.min(v, axis=0)
        M = np.max(v, axis=0)

        # Corners of the bounding box
        v_box = np.array([[m[0], m[1], m[2]], [M[0], m[1], m[2]], [M[0], M[1], m[2]], [m[0], M[1], m[2]],
                          [m[0], m[1], M[2]], [M[0], m[1], M[2]], [M[0], M[1], M[2]], [m[0], M[1], M[2]]])

        f_box = np.array([[0, 1], [1, 2], [2, 3], [3, 0], [4, 5], [5, 6], [6, 7], [7, 4],
                    [0, 4], [1, 5], [2, 6], [7, 3]], dtype=np.uint16)
        return v_box, f_box

    def __get_colors(self, v, f, c, sh):
        coloring = "VertexColors"
        if type(c) == type(None): # No color
            colors = np.ones_like(v)
            colors[:, 1] = 0.874
            colors[:, 2] = 0.0
            #print("No color")
        elif type(c) == np.ndarray and c.size == 3: # Single color
            colors = np.ones_like(v)
            colors[:, 0] = c[0]
            colors[:, 1] = c[1]
            colors[:, 2] = c[2]
            #print("Single colors")
        elif type(c) == np.ndarray and len(c.shape) == 2 and c.shape[1] == 3: # Color values for
            if c.shape[0] == f.shape[0]: # faces
                colors = np.hstack([c, c, c]).reshape((-1, 3))
                coloring = "FaceColors"
                #print("Face color values")
            if c.shape[0] == v.shape[0]: # vertices
                colors = c 
                #print("Vertex color values")
        elif type(c) == np.ndarray and c.size == f.shape[0]: # Function values for faces
            normalize = sh["normalize"][0] != None and sh["normalize"][1] != None
            cc = get_colors(c, sh["colormap"], normalize=normalize, 
                       vmin=sh["normalize"][0], vmax=sh["normalize"][1])
            #print(cc.shape)
            colors = np.hstack([cc, cc, cc]).reshape((-1, 3))
            coloring = "FaceColors"
            #print("Face function values")
        elif type(c) == np.ndarray and c.size == v.shape[0]: # Function values for vertices
            normalize = sh["normalize"][0] != None and sh["normalize"][1] != None
            colors = get_colors(c, sh["colormap"], normalize=normalize, 
                       vmin=sh["normalize"][0], vmax=sh["normalize"][1])
            #print("Vertex function values")
        else:
            print("Invalid color array given! Supported are numpy arrays.", type(c))

        return colors, coloring
    
    def add_mesh(self, v, f, c=None, uv=None, shading={}):
        sh = self.__get_shading(shading)
        mesh_obj = {}
        
        # Type adjustment vertices
        v = v.astype("float32", copy=False)
        
        # Color setup        
        colors, coloring = self.__get_colors(v, f, c, sh)
            
        # Type adjustment faces and colors
        c = colors.astype("float32", copy=False)
        
        # Material and geometry setup
        ba_dict = {"color": BufferAttribute(c)}
        if coloring == "FaceColors":
            verts = np.zeros((f.shape[0]*3, 3), dtype="float32")
            for ii in range(f.shape[0]):
                #print(ii*3, f[ii])
                verts[ii*3] = v[f[ii,0]]
                verts[ii*3+1] = v[f[ii,1]]
                verts[ii*3+2] = v[f[ii,2]]
            v = verts
        else:
            f = f.astype("uint16", copy=False).ravel()
            ba_dict["index"] = BufferAttribute(f, normalized=False)
        
        ba_dict["position"] = BufferAttribute(v, normalized=False)
        
        if type(uv) != type(None):
            uv = (uv - np.min(uv)) / (np.max(uv) - np.min(uv))
            tex = DataTexture(data=gen_checkers(20, 20), format="RGBFormat", type="FloatType")
            material = MeshStandardMaterial(map=tex, reflectivity=sh["reflectivity"], side=sh["side"], 
                    roughness=sh["roughness"], metalness=sh["metalness"], flatShading=sh["flat"],
                    polygonOffset=True, polygonOffsetFactor= 1, polygonOffsetUnits=5)
            ba_dict["uv"] = BufferAttribute(uv.astype("float32", copy=False))
        else:
            material = MeshStandardMaterial(vertexColors=coloring, reflectivity=sh["reflectivity"], 
                    side=sh["side"], roughness=sh["roughness"], metalness=sh["metalness"], 
                    flatShading=sh["flat"], 
                    polygonOffset=True, polygonOffsetFactor= 1, polygonOffsetUnits=5)

        geometry = BufferGeometry(attributes=ba_dict)
              
        if coloring == "VertexColors":
            geometry.exec_three_obj_method('computeVertexNormals')
        else:
            geometry.exec_three_obj_method('computeFaceNormals')
        
        # Mesh setup
        mesh = Mesh(geometry=geometry, material=material)
        
        # Wireframe setup
        mesh_obj["wireframe"] = None
        if sh["wireframe"]:
            wf_geometry = WireframeGeometry(mesh.geometry) # WireframeGeometry
            wf_material = LineBasicMaterial(color=sh["wire_color"], linewidth=sh["wire_width"])
            wireframe = LineSegments(wf_geometry, wf_material)
            mesh.add(wireframe)
            mesh_obj["wireframe"] = wireframe
        
        # Bounding box setup
        if sh["bbox"]:
            v_box, f_box = self.__get_bbox(v)
            _, bbox = self.add_edges(v_box, f_box, sh, mesh)
            mesh_obj["bbox"] = [bbox, v_box, f_box]
        
        # Object setup
        mesh_obj["max"] = np.max(v, axis=0)
        mesh_obj["min"] = np.min(v, axis=0)
        mesh_obj["geometry"] = geometry
        mesh_obj["mesh"] = mesh
        mesh_obj["material"] = material
        mesh_obj["type"] = "Mesh"
        mesh_obj["shading"] = sh
        mesh_obj["coloring"] = coloring
        mesh_obj["arrays"] = [v, f, c] # TODO replays with proper storage or remove if not needed
        
        return self.__add_object(mesh_obj)    

        
    def add_lines(self, beginning, ending, shading={}, obj=None):
        sh = self.__get_shading(shading)
        lines = np.hstack([beginning, ending])
        lines = lines.reshape((-1, 3))
        return self.__add_line_geometry(lines, sh, obj)
    
    def add_edges(self, vertices, edges, shading={}, obj=None):
        sh = self.__get_shading(shading)
        lines = np.zeros((edges.size, 3))
        cnt = 0
        for e in edges:
            lines[cnt, :] = vertices[e[0]]
            lines[cnt+1, :] = vertices[e[1]]
            cnt += 2
        return self.__add_line_geometry(lines, sh, obj)     

    def add_points(self, points, shading={}, obj=None):
        sh = self.__get_shading(shading)
        points = points.astype("float32", copy=False)
        mi = np.min(points, axis=0)
        ma = np.max(points, axis=0)
        geometry = BufferGeometry(attributes={"position": BufferAttribute(points, normalized=False)})
        material = PointsMaterial(color=sh["point_color"], size=sh["point_size"])
        points = Points(geometry=geometry, material=material)
        point_obj = {"geometry": geometry, "mesh": points, "material": material, 
            "max": ma, "min": mi, "type": "Points", "wireframe": None}
        
        if obj:
            return self.__add_object(point_obj, obj), point_obj
        else:
            return self.__add_object(point_obj)

    def remove_object(self, obj_id):
        if obj_id not in self.__objects:
            print("Invalid object id. Valid ids are: ", list(self.__objects.keys()))
            return
        self._scene.remove(self.__objects[obj_id]["mesh"])
        del self.__objects[obj_id]
        self.__update_view()
        
    def reset(self):
        for obj_id in list(self.__objects.keys()).copy():
            self._scene.remove(self.__objects[obj_id]["mesh"])
            del self.__objects[obj_id]
        self.__update_view()

    def update_object(self, oid=0, vertices=None, colors=None, faces=None):
        obj = self.__objects[oid]
        if type(vertices) != type(None):
            v = vertices.astype("float32", copy=False)
            obj["geometry"].attributes["position"].array = v
            #self.wireframe.attributes["position"].array = v # Wireframe updates?
            obj["geometry"].attributes["position"].needsUpdate = True
            obj["geometry"].exec_three_obj_method('computeVertexNormals')
        if type(colors) != type(None):
            colors, coloring = self.__get_colors(obj["arrays"][0], obj["arrays"][1], colors, obj["shading"])
            colors = colors.astype("float32", copy=False)
            obj["geometry"].attributes["color"].array = colors
            obj["geometry"].attributes["color"].needsUpdate = True
        if type(faces) != type(None):
            if obj["coloring"] == "FaceColors":
                print("Face updates are currently only possible in vertex color mode.")
                return
            f = faces.astype("uint16", copy=False).ravel()
            print(obj["geometry"].attributes)
            obj["geometry"].attributes["index"].array = f
            #self.wireframe.attributes["position"].array = v # Wireframe updates?
            obj["geometry"].attributes["index"].needsUpdate = True
            obj["geometry"].exec_three_obj_method('computeVertexNormals')
        #self.mesh.geometry.verticesNeedUpdate = True
        #self.mesh.geometry.elementsNeedUpdate = True
        #self.update()
    
    def update(self):
        self.mesh.exec_three_obj_method('update')
        self.orbit.exec_three_obj_method('update')
        self.cam.exec_three_obj_method('updateProjectionMatrix')
        self.scene.exec_three_obj_method('update')

        
    def add_text(self, text, shading={}):
        self.update_shading(shading)
        tt = TextTexture(string=text, color=self.s["text_color"])
        sm = SpriteMaterial(map=tt)
        self.text = Sprite(material=sm, scaleToTexture=True)    
        self.scene.add(self.text)
        
    #def add_widget(self, widget, callback):
    #    self.widgets.append(widget)
    #    widget.observe(callback, names='value')

    def add_dropdown(self, options, default, desc, cb):
        widget = widgets.Dropdown(options=options, value=default, description=desc)
        self.widgets.append(widget)
        widget.observe(cb, names="value")
        display(widget)
        
    def add_button(self, text, cb):
        button = widgets.Button(description=text)
        self.widgets.append(button)
        button.on_click(cb)
        display(button)

    def launch(self):
        display(self._renderer)
        for w in self.__widgets:
            display(w)

def plot(v, f, c=None, uv=None, shading={}, plot=None, return_plot=False):#, return_id=False):
    if not plot:
        view = Viewer(shading)
    else:
        view = plot
        view.reset()
    obj_id = view.add_mesh(v, f, c, uv=uv, shading=shading)
    if not plot:
        view.launch()

    #if return_plot and return_id:
    #    return view, obj_id
    if return_plot:# and not return_id:
        return view

def subplot(v, f, c=None, uv=None, shading={}, s=[1, 1, 0], data=None):
    shading["width"] = 400
    shading["height"] = 400
    view = Viewer(shading)
    view.add_mesh(v, f, c, uv=uv, shading=shading)
    if data == None:
        rows = []
    else:
        rows = data
    if s[0] != 1 or s[1] != 1:
        if data == None: # Intialize subplot array
            cnt = 0
            for r in range(s[0]):
                row = []
                for c in range(s[1]):
                    row.append(Output())
                    cnt += 1
                rows.append(row)
                
            for r in rows:
                display(HBox(r))

        out = rows[int(s[2]/s[1])][s[2]%s[1]]
        with out:
            display(view._renderer)
        rows[int(s[2]/s[1])][s[2]%s[1]] = view
    if data == None:
        return rows
