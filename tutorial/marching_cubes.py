import igl
import meshplot
meshplot.offline()

import numpy as np

import os
root_folder = os.getcwd()

v, f = igl.read_triangle_mesh(os.path.join(root_folder, "data", "armadillo.obj"))

#sample points on a 64x64x64 grid
n = 64
K = np.linspace( -1.0, 1.0, n)
pts = np.array([[x,y,z] for x in K for y in K for z in K])

S, _, _ = igl.signed_distance(pts, v, f, sign_type=igl.SIGNED_DISTANCE_TYPE_FAST_WINDING_NUMBER)

nV, nF = igl.marching_cubes(S, pts, n, n, n, 0.0)

meshplot.plot(nV, nF)


