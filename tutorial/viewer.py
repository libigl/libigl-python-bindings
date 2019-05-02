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
def get_colors(inp, colormap=plt.cm.viridis, normalize=True, vmin=None, vmax=None):
    if normalize:
        vmin=np.min(inp)
        vmax=np.max(inp)

    norm = plt.Normalize(vmin, vmax)
    return colormap(norm(inp))



class Viewer():
    def __init__(self):
        #print("Viewer initialization")
        self.data = {}
        self.width = 750
        self.height = 750
        self.light = DirectionalLight(color='white', position=[0, 0, 1], intensity=0.6)
        self.cam = PerspectiveCamera(position=[0, 0, 1], lookAt=[0, 0, 0], fov=30, aspect=self.width/self.height,
                        children=[self.light])
        self.orbit = OrbitControls(controlling=self.cam)
        self.renderer = Renderer(camera=self.cam, scene = Scene(), controls=[self.orbit], 
                    width=self.width, height=self.height, antialias=True)
        self.widgets = []
    
    def normalize_mesh(self, v):
        mi = np.min(v)
        ma = np.max(v)
        self.min = mi
        self.max = ma

        v = (v - mi) / ((ma - mi) * 2)
        mi = np.min(v)
        ma = np.max(v)
        mean = v.mean(0)
        v -= mean
        self.mean = mean
        return v

    def set_mesh(self, v, f, c=None, shading={"flat": True, "wireframe": True, "wire_width":0.03}):
        self.shading = shading
        #v = self.normalize_mesh(v)
        #ma = np.max(v)
        #mi = np.min(v)
        #vi = v/ ((ma - mi) * 2)
        self.scale =  2.3 * (np.max(v) - np.min(v))
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
            geometry = BufferGeometry(attributes=dict(
                position=BufferAttribute(v, normalized=False),
                index=BufferAttribute(f, normalized=False),
                color=BufferAttribute(c)
            ))
        else:
            c = c.astype("float32", copy=False)
            c = c[:, :3]
            geometry = BufferGeometry(attributes=dict(
                position=BufferAttribute(v, normalized=False),
                index=BufferAttribute(f, normalized=False),
                color=BufferAttribute(c),
            ))
        geometry.exec_three_obj_method('computeVertexNormals')
        self.mesh = Mesh(geometry=geometry, material=MeshStandardMaterial(vertexColors='VertexColors', reflectivity=1.0, 
                                                            #side='FrontSide', 
                                                            roughness=0.5, metalness=0.25, flatShading=self.shading["flat"],
                                                            polygonOffset=True, polygonOffsetFactor= 1,
                                                            polygonOffsetUnits=1))
#MeshLambertMaterial(vertexColors='VertexColors')
        if self.shading["wireframe"]:
            self.geon = WireframeGeometry(self.mesh.geometry) # WireframeGeometry
            mat = LineBasicMaterial(color="black", linewidth=self.shading["wire_width"])
            self.wireframe = LineSegments(self.geon, mat )
            self.mesh.add(self.wireframe)


        #self.mesh.scale = (scale, scale, scale)
        self.scene = Scene(children=[self.mesh, self.cam, AmbientLight(intensity=0.5)], background="#ffffff")#"#4c4c80"
        self.renderer.scene = self.scene
        #self.mesh.scale = (self.scale, self.scale, self.scale)
        #print(self.scale)
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

        
    def set_colors(self, c):
        c = c.astype("float32", copy=False)
        c = c[:, :3]
        self.mesh.geometry.attributes.get("color").array = c
        
    def add_lines(self, beginning, ending, shading={}, update=True):#, colors):
        shad = {"width":1, "color": "black"}
        for k in shading:
            shad[k] = shading[k]
        shading = shad
        lines = np.hstack([beginning, ending])
        lines = lines.reshape((-1, 3))
        #lines = (lines - self.min) / ((self.max - self.min) * 2)
        #lines -= self.mean
        lines = lines.astype("float32", copy=False)
        g1 = BufferGeometry(
            attributes={
                'position': BufferAttribute(lines, normalized=False),
            },
        )

        #mat = LineBasicMaterial(color="black", linewidth=0.6)
        #linesgeom = Geometry(vertices=lines.tolist())#, colors = colors)# ['red', 'red', 'green', 'green', 'white', 'orange'])
        lines = LineSegments(geometry=g1,#linesgeom, 
             material=LineBasicMaterial(linewidth=shading["width"], color=shading["color"]))#,#vertexColors='VertexColors'), 
             #type='LinePieces')
        self.mesh.add(lines)
        #display(self.renderer)
        #self.renderer.exec_three_obj_method('update')
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

        
    def add_widget(self, widget, callback):
        self.widgets.append(widget)
        widget.observe(callback, names='value')

    def add_dropdown(self, options, default, desc, cb):
        widget = widgets.Dropdown(options=options, value=default, description=desc)
        self.widgets.append(widget)
        widget.observe(cb, names="value")
        display(widget)

    def launch(self):
        display(self.renderer)
        for w in self.widgets:
            display(w)


def plot(v, f, c=None, shading={}, plot=None, return_plot=False):
    shad = {"flat":True, "wireframe":True, "wire_width": 0.03}
    for k in shading:
        shad[k] = shading[k]
    shading = shad
    if not plot:
        view = Viewer()
    else:
        view = plot
    if c is not None:
        c = get_colors(c, normalize=True)
    view.set_mesh(v, f, c, shading=shading)
    if not plot:
        view.launch()
    #view.cam.zoom = view.scale
    if return_plot:
        return view
