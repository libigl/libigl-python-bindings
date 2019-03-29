from pythreejs import *
from IPython.display import display

class Viewer():
    def __init__(self):
        #print("Viewer initialization")
        self.data = {}
        self.cam = PerspectiveCamera(position=[0, 0, 1], lookAt=[0, 0, 0],fov=30,
                        children=[DirectionalLight(color='white', position=[0, 0, 1], intensity=0.6)])
        self.renderer = Renderer(camera=self.cam, scene = Scene(), controls=[OrbitControls(controlling=self.cam)], 
                    width=600, height=600, antialias=False)
        self.widgets = []

    def set_mesh(self, v, f, c=None):
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
        self.mesh = Mesh(geometry=geometry, material=[MeshStandardMaterial(vertexColors='VertexColors', reflectivity=1.0, 
                                                            #side='FrontSide', 
                                                            roughness=0.5, metalness=0.25, flatShading=False,
                                                            polygonOffset=True, polygonOffsetFactor= 1,
                                                            polygonOffsetUnits=1)])
#MeshLambertMaterial(vertexColors='VertexColors')
        geon = WireframeGeometry(self.mesh.geometry) # WireframeGeometry
        mat = LineBasicMaterial(color="black", linewidth=0.6)
        wireframe = LineSegments( geon, mat )
        self.mesh.add(wireframe)

        self.scene = Scene(children=[self.mesh, self.cam, AmbientLight(intensity=0.5)], background="#4c4c80")
        self.renderer.scene = self.scene
        
    def set_colors(self, c):
        c = c.astype("float32", copy=False)
        c = c[:, :3]
        self.mesh.geometry.attributes.get("color").array = c
        
    def add_lines(self, lines):#, colors):
        #mat = LineBasicMaterial(color="black", linewidth=0.6)
        linesgeom = Geometry(vertices=lines)#, colors = colors)# ['red', 'red', 'green', 'green', 'white', 'orange'])
        lines = LineSegments(geometry=linesgeom, 
             material=LineBasicMaterial(linewidth=5, color="red"))#,#vertexColors='VertexColors'), 
             #type='LinePieces')
        self.mesh.add(lines)
    
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

    def launch(self):
        display(self.renderer)
        for w in self.widgets:
            display(w)

