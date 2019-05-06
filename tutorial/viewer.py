import igl
import scipy as sp
from scipy.sparse.linalg import spsolve
import numpy as np
import ipywidgets as widgets
from pythreejs import *
from IPython.display import display
import matplotlib.pyplot as plt
import numpy as np

# Helper functions
def get_colors(inp, colormap="viridis", normalize=True, vmin=None, vmax=None):
    colormap = plt.cm.get_cmap(colormap)
    if normalize:
        vmin=np.min(inp)
        vmax=np.max(inp)

    norm = plt.Normalize(vmin, vmax)
    return colormap(norm(inp))

class Viewer():
    def __init__(self, shading={}):
        self.update_shading(shading)
        #print("Viewer initialization")
        self.data = {}
        self.width = self.s["width"]
        self.height = self.s["height"]
        self.light = DirectionalLight(color='white', position=[0, 0, 1], intensity=0.6)
        self.cam = PerspectiveCamera(position=[0, 0, 1], lookAt=[0, 0, 0], fov=30, 
                                     aspect=self.width/self.height,
                                     children=[self.light])
        self.orbit = OrbitControls(controlling=self.cam)
        self.renderer = Renderer(camera=self.cam, scene = Scene(), controls=[self.orbit], 
                    width=self.width, height=self.height, antialias=self.s["antialias"])
        self.widgets = []
        
    def update_shading(self, shading):
        shad = {"flat":True, "wireframe":True, "wire_width": 0.03, "wire_color": "black",
                "width": 600, "height": 600, "antialias": True, "scale": 2.3, "side": 'DoubleSide',
                "colormap": "viridis", "normalize": [None, None], "background": "#ffffff",
                "line_width": 1.0, "line_color": "black", "bbox": False, 
                "point_color": "red", "point_size": 0.01, "coloring": "VertexColors"
               }
        for k in shading:
            shad[k] = shading[k]
        self.s = shad
    
    def gen_checkers(self, n_checkers_x, n_checkers_y, width=256, height=256): 
        # tex dims need to be power of two.
        array = np.ones((width, height, 3), dtype='float32')

        # width in texels of each checker
        checker_w = width / n_checkers_x
        checker_h = height / n_checkers_y

        for y in range(arr_h):
            for x in range(arr_w):
                color_key = int(x / checker_w) + int(y / checker_h)
                if color_key % 2 == 0:
                    array[x, y, :] = [ 1., 0.874, 0.0 ]
                else:
                    array[x, y, :] = [ 0., 0., 0. ]
        return array

    def set_mesh(self, v, f, c=None, uv=None, shading={}):
        self.update_shading(shading)

        self.scale = self.s["scale"] * (np.max(v) - np.min(v))
        mean = v.mean(0)# * self.scale
        mean = mean.tolist()
        self.orbit.target = mean
        self.cam.lookAt(mean)
        
        self.cam.position = [0, 0, self.scale]
        self.light.position = [0, 0, self.scale]
        
        v = v.astype("float32", copy=False)
        f = f.astype("uint16", copy=False).ravel()
        
        if type(c) == type(None):
            c = np.ones_like(v)
            c[:, 1] = 0.874
            c[:, 2] = 0.0
        else:
            normalize = self.s["normalize"][0] != None and self.s["normalize"][1] != None
            c = get_colors(c, self.s["colormap"], normalize=normalize, 
                       vmin=self.s["normalize"][0], vmax=self.s["normalize"][1])
            c = c.astype("float32", copy=False)
            c = c[:, :3]
            
        #ci = np.zeros((v.shape[0], 3))
        #for ii, fi in enumerate(f):
        #    for vi in fi:
        #        ci[vi] = c[ii]
        
        # = f.ravel()
        #print(ci.shape, f.shape, v.shape)
        if type(uv) == type(None):
            geometry = BufferGeometry(attributes=dict(
                position=BufferAttribute(v, normalized=False),
                index=BufferAttribute(f, normalized=False),
                color=BufferAttribute(c)
            ))
            self.material = MeshStandardMaterial(vertexColors=self.s["coloring"], 
                    reflectivity=1.0, side=self.s["side"], 
                    roughness=0.5, metalness=0.25, flatShading=self.s["flat"],
                    polygonOffset=True, polygonOffsetFactor= 1, polygonOffsetUnits=1)
        else:
            uv = (uv - np.min(uv)) / (np.max(uv) - np.min(uv))
            uv = uv.astype("float32", copy=False)
            geometry = BufferGeometry(attributes=dict(
                position=BufferAttribute(v, normalized=False),
                index=BufferAttribute(f, normalized=False),
                color=BufferAttribute(c),
                uv=BufferAttribute(uv)
            ))
            self.data_tex = DataTexture(data=self.gen_checkers(20, 20), format="RGBFormat", type="FloatType")
            self.material = MeshStandardMaterial(map=self.data_tex, reflectivity=1.0, side=self.s["side"], 
                    roughness=0.5, metalness=0.25, flatShading=self.s["flat"],
                    polygonOffset=True, polygonOffsetFactor= 1, polygonOffsetUnits=1)
        
        if self.s["coloring"] == "VertexColors":
            geometry.exec_three_obj_method('computeVertexNormals')
        else:
            geometry.exec_three_obj_method('computeFaceNormals')
        self.mesh = Mesh(geometry=geometry, material=self.material)
        
        #MeshLambertMaterial(vertexColors='VertexColors')
        if self.s["wireframe"]:
            self.geon = WireframeGeometry(self.mesh.geometry) # WireframeGeometry
            mat = LineBasicMaterial(color=self.s["wire_color"], linewidth=self.s["wire_width"])
            self.wireframe = LineSegments(self.geon, mat )
            self.mesh.add(self.wireframe)
        
        if self.s["bbox"]:
            self.add_bbox()

        self.scene = Scene(children=[self.mesh, self.cam, AmbientLight(intensity=0.5)], 
                           background=self.s["background"])#"#4c4c80"
        self.renderer.scene = self.scene

        self.orbit.exec_three_obj_method('update')
        self.cam.exec_three_obj_method('updateProjectionMatrix')
        

    def update_vertices(self, v):
        v = v.astype("float32", copy=False)
        self.mesh.geometry.attributes["position"].array = v
        #self.wireframe.attributes["position"].array = v # Wireframe updates?
        self.mesh.geometry.attributes["position"].needsUpdate = True
        self.mesh.geometry.verticesNeedUpdate = True
        self.mesh.geometry.elementsNeedUpdate = True
        self.update()
        
    def update_colors(self, c):
        normalize = self.s["normalize"][0] != None and self.s["normalize"][1] != None
        c = get_colors(c, self.s["colormap"], normalize=normalize, 
                   vmin=self.s["normalize"][0], vmax=self.s["normalize"][1])
        c = c.astype("float32", copy=False)
        c = c[:, :3]
        self.mesh.geometry.attributes["color"].array = c
        self.mesh.geometry.attributes["color"].needsUpdate = True
        self.mesh.geometry.verticesNeedUpdate = True
        self.mesh.geometry.elementsNeedUpdate = True
        self.update()
        
    def add_lines(self, beginning, ending, shading={}, update=True):#, colors):
        self.update_shading(shading)
        lines = np.hstack([beginning, ending])
        lines = lines.reshape((-1, 3))
        lines = lines.astype("float32", copy=False)
        g1 = BufferGeometry(attributes={
                'position': BufferAttribute(lines, normalized=False),
            },)

        #mat = LineBasicMaterial(color="black", linewidth=0.6)
        #linesgeom = Geometry(vertices=lines.tolist())#, colors = colors)# ['red', 'red', 'green', 'green', 'white', 'orange'])
        lines = LineSegments(geometry=g1,#linesgeom, 
             material=LineBasicMaterial(linewidth=self.s["line_width"], color=self.s["line_color"]))#,#vertexColors='VertexColors'), 
             #type='LinePieces')
        self.mesh.add(lines)
        #display(self.renderer)
        #self.renderer.exec_three_obj_method('update')
        if update:
            self.update()
            
    def add_bbox(self, shading={}, update=True):
        v = self.mesh.geometry.attributes["position"].array
        m = np.min(v, axis=0)
        M = np.max(v, axis=0)

        # Corners of the bounding box
        v_box = np.array([[m[0], m[1], m[2]], [M[0], m[1], m[2]], [M[0], M[1], m[2]], [m[0], M[1], m[2]],
                          [m[0], m[1], M[2]], [M[0], m[1], M[2]], [M[0], M[1], M[2]], [m[0], M[1], M[2]]])

        f_box = np.array([[0, 1], [1, 2], [2, 3], [3, 0], [4, 5], [5, 6], [6, 7], [7, 4],
                    [0, 4], [1, 5], [2, 6], [7, 3]], dtype=np.int)
        self.add_edges(v_box, f_box, shading, update)
        self.add_points(v_box, shading, update)

    def add_points(self, points, shading={}, update=True):
        self.update_shading(shading)
        points = points.astype("float32", copy=False)
        g2 = BufferGeometry(attributes={
                "position": BufferAttribute(points, normalized=False)})
        points = Points(geometry=g2, material=PointsMaterial(color=self.s["point_color"], 
                                                             size=self.s["point_size"]))
        self.mesh.add(points)
        if update:
            self.update()
    
    def add_edges(self, vertices, edges, shading={}, update=True):
        self.update_shading(shading)
        lines = np.zeros((edges.size, 3))
        cnt = 0
        for e in edges:
            lines[cnt, :] = vertices[e[0]]
            lines[cnt+1, :] = vertices[e[1]]
            cnt += 2
        lines = lines.astype("float32", copy=False)
        g1 = BufferGeometry(attributes={
                'position': BufferAttribute(lines, normalized=False),
            },)

        lines = LineSegments(geometry=g1,
             material=LineBasicMaterial(linewidth=self.s["line_width"], color=self.s["line_color"]))
        self.mesh.add(lines)
        if update:
            self.update()
    
    def update(self):
        self.mesh.exec_three_obj_method('update')
        self.orbit.exec_three_obj_method('update')
        self.cam.exec_three_obj_method('updateProjectionMatrix')
        self.scene.exec_three_obj_method('update')

    
    def add_arrows(self, arrow, length):#, colors):
        #mat = LineBasicMaterial(color="black", linewidth=0.6)
        #linesgeom = Geometry(vertices=lines)#, colors = colors)# ['red', 'red', 'green', 'green', 'white', 'orange'])
        #lines = LineSegments(geometry=linesgeom, 
             #material=LineBasicMaterial(linewidth=5, color="red"))#,#vertexColors='VertexColors'), 
             #type='LinePieces')
        arrowhelper = ArrowHelper(dir=arrow[1], origin=arrow[0], length=length);
        self.mesh.add(arrowhelper)

        
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
        display(self.renderer)
        for w in self.widgets:
            display(w)


def plot(v, f, c=None, uv=None, shading={}, plot=None, return_plot=False):
    if not plot:
        view = Viewer(shading)
    else:
        view = plot
    view.set_mesh(v, f, c, uv=uv, shading=shading)
    if not plot:
        view.launch()

    if return_plot:
        return view
