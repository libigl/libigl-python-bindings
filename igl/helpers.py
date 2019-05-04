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


# Enum definitions
MASSMATRIX_TYPE_BARYCENTRIC = 0
MASSMATRIX_TYPE_VORONOI = 1
MASSMATRIX_TYPE_FULL = 2

PER_VERTEX_NORMALS_WEIGHTING_TYPE_UNIFORM = 0
PER_VERTEX_NORMALS_WEIGHTING_TYPE_AREA = 1
PER_VERTEX_NORMALS_WEIGHTING_TYPE_ANGLE = 2


def check_dependencies(deps):
    available = [hasattr(igl, m) for m in deps]
    all_available = True
    for i, d in enumerate(available):
        if not d:
            all_available = False
            print("The libigl python bindings were compiled without %s support. Please recompile with the CMAKE flag LIBIGL_WITH_%s." %(deps[i], deps[i].upper()))

    if not all_available:
        sys.exit(-1)


def print_usage(key_dict):
    print("Usage:")
    for k in key_dict.keys():
        print("%s : %s" %(k, key_dict[k]))


def min_quad_with_fixed(q, b, bc, beq=np.array([]), bl=np.array([])):
    if bl.size == 0:
        bl = sparse.csc_matrix((q.shape[0], 1))
    else:
        bl = sparse.csc_matrix(bl)
    nr_const = bc.size + beq.shape[0]
    data_b = bc.tolist()
    data_b.extend(np.zeros(beq.shape[0]))
    row = list(range(bc.size))
    for i in range(bc.size, nr_const):
        row.extend([i, i])
    col = b.tolist()
    col.extend(beq.ravel())
    data_a = [1.0]*bc.size
    data_a.extend([1.0, -1.0]*beq.shape[0])
    data_a = np.array(data_a)
    data_b = np.array(data_b).reshape(len(data_b), 1)
    row = np.array(row)
    col = np.array(col)

    aeq = sparse.csc_matrix((data_a, (row, col)), shape=(nr_const, q.shape[0]))
    beq = sparse.csc_matrix(data_b)
    
    zo = sparse.csc_matrix(np.zeros((nr_const, nr_const)))
    aeqz = sparse.hstack([aeq, zo])
    tmp = sparse.hstack([q, aeq.T])
    d = sparse.vstack([tmp, aeqz]).tocsc()
    b = sparse.vstack([bl, beq]).tocsc()

    z = sparse.linalg.spsolve(d, -b)
    #from scikits.sparse.cholmod import cholesky
    #factor = cholesky(d)
    #z = factor(-b)

    return z[:-nr_const]
