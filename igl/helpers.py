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

    z = spsolve(d, -b)
    #from scikits.sparse.cholmod import cholesky
    #factor = cholesky(d)
    #z = factor(-b)

    return z[:-nr_const]


# Needs to be tested
def harmonic(v, f, b, bc, k):
    l = igl.cotmatrix(v, f)
    assert l.shape[0] == l.shape[1]
    if k > 1:
        m = igl.massmatrix(v, f, igl.MASSMATRIX_TYPE_DEFAULT)
        assert l.shape[0] == l.shape[1] == m.shape[0] == m.shape[1]
        assert sp.sparse.isdiag(m)

    def harmonic_sub(l, m, k):
        q = -l
        if k == 1:
            return q
        minv = sp.sparse.diags(1 / m.diagonal())
        for p in range(1, k):
            q = q.dot(minv).dot(-l)
        return q

    q = harmonic_sub(l, m, k)
    
    # Solve with equality and linear constraints
    vn = np.zeros_like(v)
    for i in range(v.shape[1]):
        bcw = bc[i]
        w = igl.min_quad_with_fixed(q, b, bcw)
        vn[:, i] = w
    
    return vn



def map_vertices_to_circle(v, bnd):

    map_ij = np.zeros(v.shape[0], dtype="int32")
    interior = []
    is_on_bnd = np.zeros(v.shape[0])

    for i in range(len(bnd)):
        is_on_bnd[bnd[i]] = 1
        map_ij[bnd[i]] = i

    is_on_bnd = is_on_bnd.astype("bool")
    for i in range(is_on_bnd.size):
        if not is_on_bnd[i]:
            map_ij[i] = len(interior)
            interior.append(i)

    length = np.zeros(len(bnd))
    length[0] = 0.0

    for i in range(1, len(bnd)):
        length[i] = length[i-1] + np.linalg.norm(v[bnd[i-1]] - v[bnd[i]])

    total = length[-1] + np.linalg.norm(v[bnd[0]] - v[bnd[-1]])

    uv = np.zeros((len(bnd), 2))
    for i in range(len(bnd)):
        frac = length[i] * 2.0 * np.pi / total
        uv[map_ij[bnd[i]]] = np.array([np.cos(frac), np.sin(frac)])

    return uv
