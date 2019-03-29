# This file is part of libigl, a simple c++ geometry processing library.
#
# Copyright (C) 2017 Sebastian Koch <s.koch@tu-berlin.de> and Daniele Panozzo <daniele.panozzo@gmail.com>
#
# This Source Code Form is subject to the terms of the Mozilla Public License
# v. 2.0. If a copy of the MPL was not distributed with this file, You can
# obtain one at http://mozilla.org/MPL/2.0/.
import sys, os

# Add the igl library to the modules search path
sys.path.insert(0, os.getcwd() + "/../")
import pyigl as igl

#from shared import TUTORIAL_SHARED_PATH, check_dependencies

#dependencies = ["glfw"]
#check_dependencies(dependencies)

TUTORIAL_SHARED_PATH = ""

# Load a mesh in OFF format
V, F, _ = igl.read_off(TUTORIAL_SHARED_PATH + "beetle.off", read_normals=False)

# Plot the mesh
#viewer = igl.glfw.Viewer()
#viewer.data().set_mesh(V, F)
#viewer.launch()

from pythreejs import *
from IPython.display import display

vertices = [
    [0, 0, 0],
    [0, 0, 1],
    [0, 1, 0],
    [0, 1, 1],
    [1, 0, 0],
    [1, 0, 1],
    [1, 1, 0],
    [1, 1, 1]
]

faces = [
    [0, 1, 3],
    [0, 3, 2],
    [0, 2, 4],
    [2, 6, 4],
    [0, 4, 1],
    [1, 4, 5],
    [2, 3, 6],
    [3, 7, 6],
    [1, 5, 3],
    [3, 5, 7],
    [4, 6, 5],
    [5, 6, 7]
]

vertexcolors = ['#000000', '#0000ff', '#00ff00', '#ff0000',
                '#00ffff', '#ff00ff', '#ffff00', '#ffffff']

# Map the vertex colors into the 'color' slot of the faces
faces = [f + [None, [vertexcolors[i] for i in f]] for f in faces]

# Create the geometry:
cubeGeometry = Geometry(vertices=vertices,
    faces=faces,
    colors=vertexcolors)
# Calculate normals per face, for nice crisp edges:
cubeGeometry.exec_three_obj_method('computeFaceNormals')

# Create a mesh. Note that the material need to be told to use the vertex colors.
myobjectCube = Mesh(
    geometry=cubeGeometry,
    material=MeshLambertMaterial(vertexColors='VertexColors'),
    position=[-0.5, -0.5, -0.5],   # Center the cube
)

# Set up a scene and render it:
cCube = PerspectiveCamera(position=[3, 3, 3], fov=20,
                      children=[DirectionalLight(color='#ffffff', position=[-3, 5, 1], intensity=0.5)])
sceneCube = Scene(children=[myobjectCube, cCube, AmbientLight(color='#dddddd')])

rendererCube = Renderer(camera=cCube, background='black', background_opacity=1,
                        scene=sceneCube, controls=[OrbitControls(controlling=cCube)])

display(rendererCube)
