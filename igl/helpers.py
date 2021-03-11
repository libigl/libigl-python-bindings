# This file is part of libigl, a simple c++ geometry processing library.
#
# Copyright (C) 2017 Sebastian Koch <s.koch@tu-berlin.de> and Daniele Panozzo <daniele.panozzo@gmail.com>
#
# This Source Code Form is subject to the terms of the Mozilla Public License
# v. 2.0. If a copy of the MPL was not distributed with this file, You can
# obtain one at http://mozilla.org/MPL/2.0/.
import os

import numpy as np
from scipy import sparse
from scipy.sparse.linalg import spsolve
import igl

# Enum definitions
MASSMATRIX_TYPE_BARYCENTRIC = 0
MASSMATRIX_TYPE_VORONOI = 1
MASSMATRIX_TYPE_FULL = 2

PER_VERTEX_NORMALS_WEIGHTING_TYPE_UNIFORM = 0
PER_VERTEX_NORMALS_WEIGHTING_TYPE_AREA = 1
PER_VERTEX_NORMALS_WEIGHTING_TYPE_ANGLE = 2

SLIM_ENERGY_TYPE_ARAP = 0
SLIM_ENERGY_TYPE_LOG_ARAP = 1
SLIM_ENERGY_TYPE_SYMMETRIC_DIRICHLET = 2
SLIM_ENERGY_TYPE_CONFORMAL = 3
SLIM_ENERGY_TYPE_EXP_CONFORMAL = 4
SLIM_ENERGY_TYPE_EXP_SYMMETRIC_DIRICHLET = 5

SIGNED_DISTANCE_TYPE_PSEUDONORMAL = 0           # Use fast pseudo-normal test [Bærentzen & Aanæs 2005]
SIGNED_DISTANCE_TYPE_WINDING_NUMBER = 1         # Use winding number [Jacobson, Kavan Sorking-Hornug 2013]
SIGNED_DISTANCE_TYPE_DEFAULT = 2
SIGNED_DISTANCE_TYPE_UNSIGNED = 3
SIGNED_DISTANCE_TYPE_FAST_WINDING_NUMBER = 4   # Use Fast winding number [Barill, Dickson, Schmidt, Levin, Jacobson 2018]

ARAP_ENERGY_TYPE_SPOKES = 0
ARAP_ENERGY_TYPE_SPOKES_AND_RIMS = 1
ARAP_ENERGY_TYPE_ELEMENTS = 2
ARAP_ENERGY_TYPE_DEFAULT = 3


def check_dependencies(deps):
    import sys
    available = [hasattr(igl, m) for m in deps]
    all_available = True
    for i, d in enumerate(available):
        if not d:
            all_available = False
            print("The libigl python bindings were compiled without %s support. "
                  "Please recompile with the CMAKE flag LIBIGL_WITH_%s." %(deps[i], deps[i].upper()))

    if not all_available:
        sys.exit(-1)


def print_usage(key_dict):
    print("Usage:")
    for k in key_dict.keys():
        print("%s : %s" %(k, key_dict[k]))
