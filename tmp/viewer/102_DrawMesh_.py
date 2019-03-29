from pythreejs import *
import pyigl as igl

from IPython.display import display


class Viewer():
    def __init__(self):
        #print("Viewer initialization")
        self.data = {}

    def set_mesh(self, v, f):
        
        self.v = v.astype("float32", copy=False)
        self.f = f.astype("uint16", copy=False).ravel()

        self.geometry = BufferGeometry(attributes=dict(
            position=BufferAttribute(self.v, normalized=False),
            index=BufferAttribute(self.f, normalized=False)
            #color=BufferAttribute(vertexcolors),
        ))
        self.geometry.exec_three_obj_method('computeVertexNormals')
        self.mesh = Mesh(geometry=self.geometry, material=[MeshStandardMaterial(color='#ffdf00', reflectivity=1.0, 
                                                            side='FrontSide', 
                                                            roughness=0.5, metalness=0.25, flatShading=False,
                                                            polygonOffset=True, polygonOffsetFactor= 1,
                                                            polygonOffsetUnits=1)])

        geon = WireframeGeometry(self.mesh.geometry) # WireframeGeometry
        mat = LineBasicMaterial(color="black", linewidth=0.6)
        wireframe = LineSegments( geon, mat )
        self.mesh.add(wireframe)

        self.cam = PerspectiveCamera(position=[0, 0, 1], lookAt=[0, 0, 0],fov=30,
                        children=[DirectionalLight(color='white', position=[0, 0, 1], intensity=0.6)])
        self.scene = Scene(children=[self.mesh, self.cam, AmbientLight(intensity=0.5)], background="#4c4c80")

        self.renderer = Renderer(camera=self.cam, scene = self.scene, controls=[OrbitControls(controlling=self.cam)], 
                    width=600, height=600, antialias=True)

    def launch(self):
        display(self.renderer)
igl.Viewer = Viewer

import sys, os
import pyigl as igl

TUTORIAL_SHARED_PATH = ""

# Load a mesh in OFF format
v, f, _ = igl.read_off(TUTORIAL_SHARED_PATH + "bunny.off", read_normals=False)

# Plot the mesh
viewer = igl.Viewer()
viewer.set_mesh(v, f)
viewer.launch()
