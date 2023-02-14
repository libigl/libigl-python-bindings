import unittest
import os
import platform

import igl
import igl.triangle
import igl.copyleft.cgal
import numpy as np
import scipy as sp
import scipy.sparse as csc
import math
import sys
from git import Repo




DOUBLE_EPS = 1.0e-14
DOUBLE_EPS_SQ = 1.0e-28
FLOAT_EPS = 1.0e-7
FLOAT_EPS_SQ = 1.0e-14


class TestBasic(unittest.TestCase):

    def setUp(self):
        # This is called once for every sub-test.
        
        # Some global datastructures to use in the tests
        np.random.seed(42)
        # https://stackoverflow.com/a/45230996/148668
        self.test_data_path = os.path.join("./data","")
        if not os.path.isdir(self.test_data_path):
            Repo.clone_from("https://github.com/libigl/libigl-tests-data.git", self.test_data_path)

        self.v1, self.f1 = igl.read_triangle_mesh(
            os.path.join(self.test_data_path, "bunny_small.off"))
        self.v2, self.f2 = igl.read_triangle_mesh(
            os.path.join(self.test_data_path, "fertility.off"))

        self.v = np.random.rand(10, 3).astype(self.v1.dtype)
        self.t = np.random.rand(10, 4)
        self.f = np.random.randint(0, 10, size=(20, 3), dtype=self.f1.dtype)
        self.g = np.random.randint(0, 10, size=(20, 4), dtype="int32")

        self.default_int = np.array(range(2)).dtype
        self.default_float = np.zeros((2,2)).dtype

    def tearDown(self):
        vv1, ff1 = igl.read_triangle_mesh(
            os.path.join(self.test_data_path, "bunny_small.off"))
        vv2, ff2 = igl.read_triangle_mesh(
            os.path.join(self.test_data_path, "fertility.off"))
        self.assertTrue((vv1 == self.v1).all())
        self.assertTrue((ff1 == self.f1).all())

        self.assertTrue((vv2 == self.v2).all())
        self.assertTrue((ff2 == self.f2).all())

    def test_z_module(self):
        # Extract all implemented functions from the module
        funcs = []
        flist = ["helpers", "os", "print_usage",
                 "pyigl", "viewer", "check_dependencies"]
        for att in dir(igl):
            if str.istitle(att[0]) or att[:2] == "__" or att in flist:
                continue
            else:
                funcs.append(att)
        funcs = sorted(funcs)

        # Extract all tests from this file
        tests = []
        flist = ["test_module"]
        for att in dir(self):
            if not att.startswith("test") or att in flist:
                continue
            else:
                tests.append(att[5:])

        # Check that there are tests for all functions
        print("")
        for f in funcs:
            if f not in tests:
                if f == "igl" or f == "np" or f == "pyigl_classes" or f == "sparse" or f == "spsolve":
                    continue
                print("WARNING: Test for function %s missing." % f)
                #self.assertTrue(f in tests)

    # sparse matrix, no flag attribute
    def test_adjacency_matrix(self):
        a = igl.adjacency_matrix(self.f)
        b = igl.adjacency_matrix(self.f[:,:2]) # Test with edges only
        self.assertTrue(a.shape == (self.v.shape[0], self.v.shape[0]))
        self.assertTrue(b.shape == (self.v.shape[0], self.v.shape[0]))
        self.assertTrue(a.dtype == self.f.dtype)
        self.assertTrue(b.dtype == self.f.dtype)
        self.assertTrue(type(a) == csc.csc_matrix)
        self.assertTrue(type(b) == csc.csc_matrix)

    def test_avg_edge_length(self):
        l = igl.avg_edge_length(self.v1, self.f1)
        self.assertTrue(np.isclose(l, 0.004661094877063719))

    # sparse matrix
    def test_cotmatrix(self):
        l = igl.cotmatrix(self.v, self.f)
        self.assertTrue(l.shape == (self.v.shape[0], self.v.shape[0]))
        self.assertTrue(l.dtype == self.v.dtype)
        self.assertTrue(type(l) == csc.csc_matrix)

    def test_cotmatrix_intrinsic(self):
        el = igl.edge_lengths(self.v, self.f)
        l = igl.cotmatrix_intrinsic(el, self.f)
        self.assertTrue(l.shape == (self.v.shape[0], self.v.shape[0]))
        self.assertTrue(l.dtype == el.dtype)
        self.assertTrue(type(l) == csc.csc_matrix)

    def test_ears(self):
        ears, ears_opp = igl.ears(self.f1)
        self.assertTrue(ears.shape == ears_opp.shape)
        self.assertTrue(ears.dtype == self.f.dtype)
        self.assertTrue(ears_opp.dtype == self.f.dtype)
        self.assertTrue(ears.flags.c_contiguous)
        self.assertTrue(ears_opp.flags.c_contiguous)

    def test_gaussian_curvature(self):
        g = igl.gaussian_curvature(self.v, self.f)
        self.assertTrue(g.shape == (self.v.shape[0],))
        self.assertTrue(g.dtype == self.v.dtype)
        self.assertTrue(type(g) == np.ndarray)
        self.assertTrue(g.flags.c_contiguous)

    # sparse matrix, no flag attribute
    def test_grad_intrinsic(self):
        el = igl.edge_lengths(self.v, self.f)
        g = igl.grad_intrinsic(el, self.f)
        self.assertTrue(g.shape == (self.f.shape[0] * 2, self.v.shape[0]))
        self.assertTrue(type(g) == csc.csc_matrix)

    def test_grad(self):
        g = igl.grad(self.v, self.f)
        h = igl.grad(self.v, self.f, uniform=True)
        self.assertTrue(g.shape == (
            self.f.shape[0] * self.v.shape[1], self.v.shape[0]))
        self.assertTrue(h.shape == (
            self.f.shape[0] * self.v.shape[1], self.v.shape[0]))
        self.assertTrue(type(g) == type(h) == csc.csc_matrix)

    # sparse matrix, no flag attribute
    def test_massmatrix(self):
        a = igl.massmatrix(self.v, self.f)
        b = igl.massmatrix(
            self.v, self.f, type=igl.MASSMATRIX_TYPE_BARYCENTRIC)
        self.assertTrue(a.shape == (self.v.shape[0], self.v.shape[0]))
        self.assertTrue(b.shape == (self.v.shape[0], self.v.shape[0]))
        self.assertTrue(b.dtype == self.v.dtype)
        self.assertTrue(a.dtype == self.v.dtype)
        self.assertTrue(type(a) == type(b) == csc.csc_matrix)

    def test_massmatrix_intrinsic(self):
        el = igl.edge_lengths(self.v, self.f)
        a = igl.massmatrix_intrinsic(el, self.f)
        b = igl.massmatrix_intrinsic(
            el, self.f, type=igl.MASSMATRIX_TYPE_BARYCENTRIC)
        self.assertTrue(a.shape == (self.v.shape[0], self.v.shape[0]))
        self.assertTrue(b.shape == (self.v.shape[0], self.v.shape[0]))
        self.assertTrue(b.dtype == el.dtype)
        self.assertTrue(a.dtype == el.dtype)
        self.assertTrue(type(a) == type(b) == csc.csc_matrix)

    def test_principal_curvature(self):
        pd1, pd2, pv1, pv2 = igl.principal_curvature(self.v, self.f)
        qd1, qd2, qv1, qv2 = igl.principal_curvature(
            self.v, self.f, radius=7, use_k_ring=False)
        self.assertTrue(pd1.shape == qd1.shape == pd2.shape ==
                        qd2.shape == self.v.shape)
        self.assertTrue(pv1.shape == qv1.shape == pv2.shape ==
                        qv2.shape == (self.v.shape[0],))
        self.assertTrue(pd1.dtype == pd2.dtype ==
                        pv1.dtype == pv2.dtype == self.v.dtype)
        v = self.v.copy()

        pd1, pd2, pv1, pv2 = igl.principal_curvature(v, self.f)
        self.assertTrue(pd1.dtype == pd2.dtype ==
                        pv1.dtype == pv2.dtype == v.dtype)
        self.assertTrue(type(pd1) == type(pd2) == type(pv1)
                        == type(pv2) == np.ndarray)
        self.assertTrue(pd1.flags.c_contiguous)
        self.assertTrue(pd2.flags.c_contiguous)
        self.assertTrue(pv1.flags.c_contiguous)
        self.assertTrue(pv2.flags.c_contiguous)
        self.assertTrue(qd1.flags.c_contiguous)
        self.assertTrue(qd2.flags.c_contiguous)
        self.assertTrue(qv1.flags.c_contiguous)
        self.assertTrue(qv2.flags.c_contiguous)

    def test_read_obj(self):
        v, _, n, f, _, _ = igl.read_obj(self.test_data_path + "face.obj")
        self.assertTrue(type(v) == type(f) == type(n) == np.ndarray)
        self.assertTrue(v.shape == (25905, 3) and n.shape ==
                        (0, 0) and f.shape == (51712, 3))
        self.assertTrue(v.dtype == self.default_float)
        self.assertTrue(f.dtype == self.f.dtype)
        v, _, n, f, _, _ = igl.read_obj(
            self.test_data_path + "face.obj", dtype="float32")
        self.assertTrue(v.shape == (25905, 3) and n.shape ==
                        (0, 0) and f.shape == (51712, 3))
        self.assertTrue(v.dtype == np.float32)
        self.assertTrue(v.flags.c_contiguous)
        self.assertTrue(f.flags.c_contiguous)
        self.assertTrue(n.flags.c_contiguous)

    def test_read_off(self):
        v, f, n = igl.read_off(self.test_data_path + "bunny_small.off")
        self.assertTrue(type(v) == type(f) == type(n) == np.ndarray)
        self.assertTrue(v.shape == (3485, 3) and n.shape ==
                        (0, 0) and f.shape == (6966, 3))
        self.assertTrue(v.dtype == self.default_float)
        v, f, n = igl.read_off(
            self.test_data_path + "bunny_small.off", read_normals=False, dtype="float32")
        self.assertTrue(v.shape == (3485, 3) and n.shape ==
                        (0, 0) and f.shape == (6966, 3))
        self.assertTrue(v.dtype == np.float32)
        self.assertTrue(v.flags.c_contiguous)
        self.assertTrue(f.flags.c_contiguous)
        self.assertTrue(n.flags.c_contiguous)

    def test_read_mesh(self):
        v, t, f = igl.read_mesh(os.path.join(
            self.test_data_path, "octopus-low.mesh"))
        self.assertTrue(type(v) == type(t) == type(f) == np.ndarray)
        self.assertTrue(v.flags.c_contiguous)
        self.assertTrue(t.flags.c_contiguous)
        self.assertTrue(f.flags.c_contiguous)

        self.assertTrue(v.dtype == self.default_float)
        self.assertTrue(t.dtype == self.f1.dtype)
        self.assertTrue(f.dtype == self.f1.dtype)

    def test_read_triangle_mesh(self):
        v, f = igl.read_triangle_mesh(self.test_data_path + "octopus-low.mesh")
        #print(v.shape, f.shape)
        v, f = igl.read_triangle_mesh(self.test_data_path + "face.obj")
        #print(v.shape, f.shape)
        v, f = igl.read_triangle_mesh(self.test_data_path + "bunny_small.off")
        #print(v.shape, f.shape)
        self.assertTrue(f.dtype == self.f.dtype)
        self.assertTrue(v.flags.c_contiguous)
        self.assertTrue(f.flags.c_contiguous)

    def test_read_triangle_mesh_type_issue(self):
        v, f = igl.read_triangle_mesh(self.test_data_path + "face.obj")
        vs = np.array([0])
        vt = np.arange(v.shape[0])
        d = igl.exact_geodesic(v, f, vs, vt)
        self.assertTrue(d.dtype == v.dtype)

    # def test_triangulate(self):
    #     v = np.array([[0.0, 0.0], [1.0, 0.0], [1.0, 1.0], [0.0, 1.0]])
    #     e = np.array([[0, 1], [1, 2], [2, 3], [3, 0]], dtype="int32")
    #     h = np.array([[]])
    #     #print("v.dtype = %s, h.dtype = %s" % (v.dtype, h.dtype))
    #     v2, f2 = igl.triangulate(v, e, h, flags="a0.005qQ")
    #     self.assertTrue(v2.dtype == v.dtype)
    #     self.assertTrue(f2.dtype == e.dtype)
    #     self.assertTrue(type(v2) == type(f2) == np.ndarray)
    #     self.assertTrue(v2.flags.c_contiguous)
    #     self.assertTrue(f2.flags.c_contiguous)

    def test_write_obj(self):
        suc = igl.write_obj("test.obj", self.v, self.f)
        self.assertTrue(suc)
        self.assertTrue(os.path.isfile("test.obj"))

    def test_write_off(self):
        suc = igl.write_off("test.off", self.v, self.f, self.v)
        self.assertTrue(suc)
        self.assertTrue(os.path.isfile("test.off"))

    def test_adjacency_list(self):
        a = igl.adjacency_list(self.f1)
        self.assertEqual(len(a), self.v1.shape[0])

    # all are sparse matrices
    def test_arap_linear_block(self):
        kd = igl.arap_linear_block(self.v1, self.f1, d=2, energy=0)
        self.assertTrue(kd.shape[0] > 0)

    def test_arap_linear_block_elements(self):
        kd = igl.arap_linear_block_elements(self.v1, self.f1, d=2)
        self.assertTrue(kd.shape[0] > 0)

    def test_arap_linear_block_spokes(self):
        kd = igl.arap_linear_block_spokes(self.v1, self.f1, d=2)
        self.assertTrue(kd.shape[0] > 0)

    def test_arap_linear_block_spokes_and_rims(self):
        kd = igl.arap_linear_block_spokes_and_rims(self.v1, self.f1, d=2)
        self.assertTrue(kd.shape[0] > 0)

    def test_arap_rhs(self):
        k = igl.arap_rhs(self.v1, self.f1, d=2, energy=0)
        self.assertTrue(k.shape[0] > 0)

    def test_average_onto_faces(self):
        s = np.random.rand(self.f1.shape[0])
        sf = igl.average_onto_faces(self.f1, s)
        self.assertEqual(sf.shape[0], self.f1.shape[0])
        self.assertEqual(sf.dtype, s.dtype)

    def test_average_onto_vertices(self):
        s = np.random.rand(self.f1.shape[0], self.v1.shape[1])
        sv = igl.average_onto_vertices(self.v1, self.f1, s)
        self.assertEqual(sv.shape[0], self.v1.shape[0])
        self.assertEqual(sv.dtype, s.dtype)
        self.assertTrue(sv.flags.c_contiguous)

    def test_barycentric_coordinates(self):
        a, b, c = self.v1[self.f1[:, 0]
                          ], self.v1[self.f1[:, 1]], self.v1[self.f1[:, 2]]
        bc = igl.barycentric_coordinates_tri(a, a, b, c)
        self.assertEqual(bc.shape, a.shape)
        expected_bc = np.zeros(a.shape)
        expected_bc[:, 0] = np.ones(a.shape[0])
        self.assertTrue(np.linalg.norm(expected_bc-bc) < 1e-6)
        self.assertTrue(bc.flags.c_contiguous)

        d = 0.5*a + 0.5*c + np.array([0.1, 0.1, 0.1])
        bc = igl.barycentric_coordinates_tet(d, a, b, c, d)
        self.assertEqual(bc.shape, (a.shape[0], 4))
        self.assertTrue(bc.flags.c_contiguous)

    def test_barycentric_coordinates_tri(self):
        # tested in test_barycentric_coordinates
        pass

    def test_barycentric_coordinates_tet(self):
        # tested in test_barycentric_coordinates
        pass

    def test_vertex_components(self):
        a = igl.adjacency_matrix(self.f1)
        c, count = igl.vertex_components_from_adjacency_matrix(a)
        self.assertEqual(c.shape[0], self.v1.shape[0])
        self.assertTrue(c.flags.c_contiguous)

        c = igl.vertex_components(self.f1)
        self.assertEqual(c.shape[0], self.v1.shape[0])
        self.assertTrue(c.flags.c_contiguous)

    def test_facet_components(self):
        c = igl.facet_components(self.f1)
        self.assertEqual(c.shape, (self.f1.shape[0],))
        self.assertTrue(np.array_equal(c, np.zeros_like(c)))
        self.assertTrue(c.flags.c_contiguous)

    def test_bfs(self):
        a = igl.adjacency_matrix(self.f1)
        p, d = igl.bfs(a, 0)
        self.assertEqual(p.shape, (self.v1.shape[0],))
        self.assertEqual(p.shape, (self.v1.shape[0],))

        try:
            p, d, = igl.bfs(a, -1)
            self.assertTrue(False)
        except IndexError as e:
            pass

        a = csc.csc_matrix(np.zeros([0, 0]), dtype=np.int32)
        try:
            p, d, = igl.bfs(a, 0)
            self.assertTrue(False)
        except ValueError as e:
            pass

        a = csc.csc_matrix(np.zeros([10, 11]), dtype=np.int32)
        try:
            p, d, = igl.bfs(a, 0)
            self.assertTrue(False)
        except ValueError as e:
            pass

        a = csc.csc_matrix(np.zeros([10, 10]), dtype=np.int32)
        p, d, = igl.bfs(a, 0)
        self.assertEqual(p.shape, ())
        self.assertTrue(np.array_equal(d, -np.ones(10)))
        self.assertTrue(p.flags.c_contiguous)

    def test_bfs_orient(self):
        ff, c = igl.bfs_orient(self.f1)
        self.assertEqual(ff.shape, self.f1.shape)
        self.assertEqual(c.shape, (self.f1.shape[0],))
        self.assertTrue(np.array_equal(self.f1, ff))
        self.assertTrue(ff.flags.c_contiguous)
        self.assertTrue(c.flags.c_contiguous)

    def test_oriented_facets(self):
        e = igl.oriented_facets(self.f1)
        self.assertTrue(e.shape[0] > self.f1.shape[0])
        self.assertTrue(0 <= np.max(e) < self.v1.shape[0])
        self.assertTrue(e.flags.c_contiguous)

    # sparse matrix, no flag attribute
    def test_orientable_patches(self):
        c, a = igl.orientable_patches(self.f1)

        self.assertTrue(np.array_equal(c, np.zeros(self.f1.shape[0])))
        self.assertEqual(a.shape, (self.f1.shape[0], self.f1.shape[0]))

    def test_edge_topology(self):
        ev, fe, ef = igl.edge_topology(self.v1, self.f1)
        self.assertEqual(fe.shape, self.f1.shape)
        self.assertEqual(ef.shape, (ev.shape[0], 2))
        self.assertEqual(np.max(ev), self.v1.shape[0] - 1)
        self.assertEqual(np.min(ef), 0)
        self.assertTrue(fe.flags.c_contiguous)
        self.assertTrue(ef.flags.c_contiguous)
        self.assertTrue(ev.flags.c_contiguous)

    def test_edges(self):
        e = igl.edges(self.f1)
        self.assertTrue(e.shape[0] > self.f1.shape[0])
        self.assertEqual(e.shape[1], 2)
        self.assertTrue(e.flags.c_contiguous)

    def test_bone_parents(self):
        e = igl.edges(self.f1)
        res = igl.bone_parents(e)
        self.assertEqual(res.shape[0], e.shape[0])
        self.assertTrue(e.flags.c_contiguous)

    def test_sort_angles(self):
        r = igl.sort_angles(self.v)
        self.assertTrue(r.dtype == self.f.dtype)
        self.assertEqual(r.shape[0], self.v.shape[0])
        self.assertTrue(r.flags.c_contiguous)

    def test_circumradius(self):
        r = igl.circumradius(self.v, self.f)
        self.assertTrue(r.dtype == self.v.dtype)
        self.assertEqual(r.shape[0], self.f.shape[0])
        self.assertTrue(r.flags.c_contiguous)

    def test_quad_planarity(self):
        p = igl.quad_planarity(self.v, self.g)
        self.assertTrue(p.dtype == self.v.dtype)
        self.assertEqual(p.shape[0], self.g.shape[0])
        self.assertTrue(p.flags.c_contiguous)

    def test_collapse_small_triangles(self):
        ff = igl.collapse_small_triangles(self.v, self.f, 0.5)
        self.assertEqual(ff.shape[1], self.f.shape[1])
        self.assertTrue(ff.flags.c_contiguous)

    def test_bounding_box(self):
        bv, bf = igl.bounding_box(self.v)
        self.assertEqual(bv.shape[1], self.v.shape[1])
        self.assertEqual(bf.shape[1], self.v.shape[1])
        self.assertTrue(bv.flags.c_contiguous)
        self.assertTrue(bf.flags.c_contiguous)

    def test_per_face_normals(self):
        n = igl.per_face_normals(self.v2, self.f2, self.v2)

        self.assertEqual(n.dtype, self.v2.dtype)
        self.assertEqual(n.shape[0], self.f2.shape[0])
        self.assertEqual(n.shape[1], 3)
        self.assertTrue(n.flags.c_contiguous)

    def test_ambient_occlusion(self):
        n = igl.per_vertex_normals(self.v2, self.f2)
        s = igl.ambient_occlusion(self.v2, self.f2, self.v2, n, 2)

        self.assertEqual(s.dtype, self.v1.dtype)
        self.assertEqual(len(s.shape), 1)
        self.assertTrue(s.flags.c_contiguous)

    def test_write_triangle_mesh(self):
        ok = igl.write_triangle_mesh("out.obj", self.v, self.f)
        self.assertTrue(ok)
        self.assertTrue(os.path.isfile("out.obj"))

    def test_barycenter(self):
        bc = igl.barycenter(self.v, self.f)
        self.assertEqual(bc.dtype, self.v.dtype)
        self.assertEqual(bc.shape[0], self.f.shape[0])
        self.assertEqual(bc.shape[1], 3)
        self.assertTrue(bc.flags.c_contiguous)

    def test_read_dmat(self):
        # TODO: maybe a vector
        mat = igl.read_dmat(self.test_data_path + "decimated-knight-selection.dmat")
        self.assertEqual(mat.dtype, "float64")
        self.assertTrue(mat.flags.c_contiguous)

    # sparse matrix, no flag attribute
    def test_vector_area_matrix(self):
        a = igl.vector_area_matrix(self.f)
        self.assertEqual(a.dtype, "float64")
        self.assertEqual(a.shape[0], a.shape[1])
        self.assertEqual(a.shape[0], self.v.shape[0]*2)

    # def test_tetrahedralize(self):
    #     status, tv, tt, tf = igl.tetrahedralize(self.v2, self.f2)

    #     self.assertEqual(status, 0)
    #     self.assertEqual(tv.dtype, self.v1.dtype)
    #     self.assertEqual(tt.dtype, self.f1.dtype)
    #     self.assertEqual(tf.dtype, self.f1.dtype)

    #     self.assertEqual(tv.shape[1], 3)
    #     self.assertEqual(tf.shape[1], 3)
    #     self.assertEqual(tt.shape[1], 4)
    #     self.assertTrue(tv.flags.c_contiguous)
    #     self.assertTrue(tt.flags.c_contiguous)
    #     self.assertTrue(tf.flags.c_contiguous)

    def test_hausdorff(self):
        dist = igl.hausdorff(self.v, self.f, self.v1, self.f1)
        # print(dist)

    def test_isolines(self):
        func = np.random.rand(self.v1.shape[0], 1)
        iso_v, iso_e = igl.isolines(self.v1, self.f1, func, 10)

        self.assertEqual(iso_v.dtype, func.dtype)
        self.assertEqual(iso_e.dtype, self.f1.dtype)
        self.assertEqual(iso_e.shape[1], 2)
        self.assertTrue(iso_v.flags.c_contiguous)
        self.assertTrue(iso_e.flags.c_contiguous)

    def test_unproject_ray(self):
        pos = np.random.rand(2, 1)
        model = np.random.rand(4, 4)
        proj = np.random.rand(4, 4)
        viewport = np.random.rand(4, 1)
        source, direction = igl.unproject_ray(pos, model, proj, viewport)
        self.assertEqual(source.dtype, self.v.dtype)
        self.assertEqual(direction.dtype, self.v.dtype)
        self.assertEqual(len(source.shape), 1)
        self.assertTrue(source.flags.c_contiguous)

    def test_winding_number(self):
        s = igl.winding_number(self.v1, self.f1, self.v)

        self.assertEqual(s.shape[0], self.v.shape[0])

    def test_winding_number_for_point(self):
        p = np.zeros((1, 3))
        s = igl.winding_number_for_point(self.v1, self.f1, p)

    def test_unproject(self):
        model = np.array([[1., 0, 0, 0], [0, 1, 0, 0],
                          [0, 0, 1, 0], [0, 0, 0, 1]])
        proj = np.array([[1., 0, 0, 0], [0, 1, 0, 0],
                         [0, 0, 1, 0], [0, 0, 0, 1]])
        viewport = np.array([1., 1, 1, 1])
        scene = igl.unproject(self.v, model, proj, viewport)

        self.assertEqual(scene.dtype, self.v.dtype)
        self.assertEqual(scene.shape[0], self.v.shape[0])
        self.assertEqual(scene.shape[1], 3)
        self.assertTrue(scene.flags.c_contiguous)

    def test_upsample(self):
        nv, nf = igl.upsample(self.v1, self.f1)

        self.assertEqual(nv.dtype, self.v1.dtype)
        self.assertEqual(nf.dtype, self.f1.dtype)

        self.assertEqual(nv.shape[1], self.v1.shape[1])
        self.assertEqual(nf.shape[1], self.f1.shape[1])
        self.assertTrue(nv.flags.c_contiguous)
        self.assertTrue(nf.flags.c_contiguous)

    def test_random_points_on_mesh(self):
        n = 10
        b, fi = igl.random_points_on_mesh(n, self.v1, self.f1)

        self.assertEqual(b.dtype, self.v1.dtype)
        self.assertEqual(fi.dtype, self.f1.dtype)

        self.assertEqual(b.shape[0], n)
        self.assertEqual(b.shape[1], 3)
        self.assertEqual(fi.shape[0], n)
        self.assertTrue(b.flags.c_contiguous)
        self.assertTrue(fi.flags.c_contiguous)

    def test_boundary_loop(self):
        l = igl.boundary_loop(self.f)
        self.assertEqual(len(l.shape), 1)
        self.assertEqual(l.dtype, self.f.dtype)
        self.assertTrue(l.flags.c_contiguous)

    def test_all_boundary_loop(self):
        l = igl.all_boundary_loop(self.f)
        self.assertEqual(type(l), type([]))
        self.assertTrue(len(l) > 0)

    def test_bounding_box_diagonal(self):
        length = igl.bounding_box_diagonal(self.v1)
        self.assertEqual(type(length), float)

    def test_boundary_facets(self):
        b = igl.boundary_facets(self.f1)
        self.assertEqual(b.dtype, self.f1.dtype)
        self.assertTrue(b.shape[1] == 3 or b.shape[1] == 2)
        self.assertTrue(b.flags.c_contiguous)

    def test_connect_boundary_to_infinity(self):
        fo = igl.connect_boundary_to_infinity(self.f1)
        self.assertEqual(fo.dtype, self.f1.dtype)
        self.assertEqual(fo.shape[1], 3)
        self.assertTrue(fo.flags.c_contiguous)

    def test_connect_boundary_to_infinity_face(self):
        vof, fof = igl.connect_boundary_to_infinity_face(self.v1, self.f1)
        self.assertEqual(fof.dtype, self.f1.dtype)
        self.assertEqual(fof.shape[1], 3)
        self.assertEqual(vof.dtype, self.v1.dtype)
        self.assertEqual(vof.shape[1], 3)
        self.assertTrue(vof.flags.c_contiguous)
        self.assertTrue(fof.flags.c_contiguous)

    def test_connect_boundary_to_infinity_index(self):
        foi = igl.connect_boundary_to_infinity_index(self.f1, 0)
        self.assertEqual(foi.dtype, self.f1.dtype)
        self.assertEqual(foi.shape[1], 3)
        self.assertTrue(foi.flags.c_contiguous)

    def test_cotmatrix_entries(self):
        c = igl.cotmatrix_entries(self.v1, self.f1)
        self.assertEqual(c.dtype, self.v1.dtype)
        self.assertEqual(c.shape[0], self.f1.shape[0])
        self.assertTrue(c.shape[1] == 3 or c.shape[1] == 6)
        self.assertTrue(c.flags.c_contiguous)

    # sparse matrix, no flag attribute
    def test_crouzeix_raviart_cotmatrix(self):
        l, e, emap = igl.crouzeix_raviart_cotmatrix(self.v1, self.f1)
        self.assertEqual(l.dtype, self.v1.dtype)
        self.assertEqual(l.shape[0], e.shape[0])
        self.assertEqual(l.shape[1], e.shape[0])
        self.assertTrue(e.shape[1] == 2 or e.shape[1] == 3)
        self.assertTrue(emap.shape[0] == 3*self.f1.shape[0]
                        or emap.shape[0] == 4*self.f1.shape[0])
        self.assertTrue(e.flags.c_contiguous)
        self.assertTrue(emap.flags.c_contiguous)
        l2 = igl.crouzeix_raviart_cotmatrix_known_e(self.v1, self.f1, e, emap)
        self.assertEqual(l2.dtype, l.dtype)
        self.assertEqual(l2.shape, l.shape)

    def test_crouzeix_raviart_cotmatrix_known_e(self):
        pass

    def test_crouzeix_raviart_massmatrix(self):
        m, e, emap = igl.crouzeix_raviart_massmatrix(self.v1, self.f1)
        self.assertEqual(m.dtype, self.v1.dtype)
        self.assertEqual(m.shape[0], e.shape[0])
        self.assertEqual(m.shape[1], e.shape[0])
        self.assertTrue(e.shape[1] == 2 or e.shape[1] == 3)
        self.assertTrue(emap.shape[0] == 3*self.f1.shape[0]
                        or emap.shape[0] == 4*self.f1.shape[0])
        self.assertTrue(e.flags.c_contiguous)
        self.assertTrue(emap.flags.c_contiguous)
        m2 = igl.crouzeix_raviart_massmatrix_known_e(self.v1, self.f1, e, emap)
        self.assertEqual(m2.dtype, m.dtype)
        self.assertEqual(m2.shape, m.shape)

    def test_crouzeix_raviart_massmatrix_known_e(self):
        pass

    def test_cylinder(self):
        v, f = igl.cylinder(100, 100)
        self.assertEqual(v.dtype, self.v.dtype)
        self.assertEqual(f.dtype, self.f.dtype)
        self.assertEqual(v.shape[1], 3)
        self.assertEqual(f.shape[1], 3)
        self.assertTrue(v.flags.c_contiguous)
        self.assertTrue(f.flags.c_contiguous)

    def test_decimate(self):
        success, u, g, j, i = igl.decimate(self.v1, self.f1, 100)
        self.assertEqual(u.shape[1], self.v1.shape[1])
        self.assertEqual(g.shape[1], 3)
        self.assertEqual(j.shape[0], g.shape[0])
        self.assertTrue(len(j.shape) == len(i.shape) and len(i.shape) == 1)
        self.assertEqual(type(success), bool)
        self.assertTrue(u.dtype == self.v.dtype)
        self.assertTrue(g.dtype == j.dtype and j.dtype ==
                        i.dtype and i.dtype == self.f.dtype)
        self.assertTrue(u.flags.c_contiguous)
        self.assertTrue(g.flags.c_contiguous)
        self.assertTrue(j.flags.c_contiguous)
        self.assertTrue(i.flags.c_contiguous)

    def test_dihedral_angles(self):
        t = np.random.randint(0, 10, size=(10, 4))
        theta, cos_theta = igl.dihedral_angles(self.v, t)
        self.assertEqual(theta.dtype, self.v.dtype)
        self.assertEqual(cos_theta.dtype, self.v.dtype)
        self.assertTrue(
            theta.shape == cos_theta.shape and cos_theta.shape == (self.t.shape[0], 6))
        self.assertTrue(theta.flags.c_contiguous)
        self.assertTrue(cos_theta.flags.c_contiguous)

    def test_dihedral_angles_intrinsic(self):
        # intrinsic function of dihedral_angles
        pass

    def test_directed_edge_parents(self):
        e = np.random.randint(0, 10, size=(10, 2))
        p = igl.directed_edge_parents(e)
        self.assertEqual(p.dtype, e.dtype)
        self.assertEqual(p.shape[0], e.shape[0])
        self.assertEqual(len(p.shape), 1)
        self.assertTrue(p.flags.c_contiguous)

    def test_doublearea(self):
        a = igl.doublearea(self.v1, self.f1)
        self.assertEqual(a.shape[0], self.f1.shape[0])
        self.assertEqual(a.dtype, self.v1.dtype)
        self.assertTrue(a.flags.c_contiguous)

    def test_euler_characteristic(self):
        eu = igl.euler_characteristic(self.f1)
        self.assertEqual(type(eu), int)

    def test_euler_characteristic_complete(self):
        eu = igl.euler_characteristic_complete(self.v1, self.f1)
        self.assertEqual(type(eu), int)

    def test_fit_plane(self):
        n, c = igl.fit_plane(self.v1)
        self.assertTrue(n.dtype == c.dtype == self.v1.dtype)
        self.assertTrue(n.shape == c.shape == (3,))
        self.assertTrue(n.flags.c_contiguous)
        self.assertTrue(c.flags.c_contiguous)

    def test_internal_angles(self):
        k = igl.internal_angles(self.v1, self.f1)
        self.assertEqual(k.dtype, self.v1.dtype)
        self.assertEqual(k.shape, self.f1.shape)
        self.assertTrue(k.flags.c_contiguous)

    def test_is_edge_manifold(self):
        is_m = igl.is_edge_manifold(self.f1)
        self.assertEqual(type(is_m), bool)

    def test_map_vertices_to_circle(self):
        bnd = np.random.randint(0, self.v1.shape[0], size=(100, 1))
        uv = igl.map_vertices_to_circle(self.v1, bnd)
        self.assertEqual(uv.dtype, self.v1.dtype)
        self.assertEqual(uv.shape, (bnd.shape[0], 2))
        self.assertTrue(uv.flags.c_contiguous)

    def test_marching_cubes(self):
        #test empty level set.
        n = 50
        emptyField = np.zeros((n*n*n,1))
        K = np.linspace( -1.0, 1.0, n)
        pts = np.array([[x,y,z] for x in K for y in K for z in K])
        V,F = igl.marching_cubes(emptyField, pts, n, n, n, 0.0)
        self.assertEqual(V.shape, (0, 3))
        self.assertEqual(F.shape, (0, 3))

        #test marching over a sphere
        sphereField = np.linalg.norm(pts, axis=1) - 1
        V,F = igl.marching_cubes(sphereField, pts, n, n, n, 0.0)

        self.assertTrue(V.dtype == pts.dtype)
        self.assertTrue(F.dtype == self.default_int)

        self.assertNotEqual(V.shape, (0,3))
        self.assertNotEqual(F.shape, (0,3))
        self.assertTrue(F.flags.c_contiguous)
        self.assertTrue(F.flags.c_contiguous)

    def test_per_vertex_normals(self):
        n = igl.per_vertex_normals(self.v1, self.f1, 0)
        self.assertEqual(n.shape, (self.v1.shape[0], 3))
        self.assertEqual(n.dtype, self.v1.dtype)
        self.assertTrue(n.flags.c_contiguous)

    def test_per_corner_normals(self):
        n = igl.per_corner_normals(self.v1, self.f1, 80)
        self.assertEqual(n.shape, (self.f1.shape[0]*3, 3))
        self.assertEqual(n.dtype, self.v1.dtype)
        self.assertTrue(n.flags.c_contiguous)

    def test_per_vertex_attribute_smoothing(self):
        aout = igl.per_vertex_attribute_smoothing(self.v1, self.f1)
        self.assertEqual(aout.shape, self.v1.shape)
        self.assertTrue(aout.flags.c_contiguous)

    def test_piecewise_constant_winding_number(self):
        is_w = igl.piecewise_constant_winding_number(self.f1)
        self.assertEqual(type(is_w), bool)

    def test_procrustes(self):
        s, r, t = igl.procrustes(self.v1, self.v1, True, True)
        self.assertEqual(type(s), float)
        self.assertTrue(r.dtype == t.dtype == self.v1.dtype)

    def test_qslim(self):
        success, u, g, j, i = igl.qslim(self.v1, self.f1, 100)
        self.assertEqual(u.dtype, self.v1.dtype)
        self.assertTrue(g.dtype == j.dtype == i.dtype == self.f1.dtype)
        self.assertEqual(u.shape[1], self.v1.shape[1])
        self.assertEqual(g.shape[1], 3)
        self.assertTrue(j.shape[0] > 0 and i.shape[0] > 0)
        self.assertTrue(u.flags.c_contiguous)
        self.assertTrue(g.flags.c_contiguous)
        self.assertTrue(j.flags.c_contiguous)
        self.assertTrue(i.flags.c_contiguous)

    def test_per_edge_normals(self):
        fn = np.random.rand(self.f1.shape[0], 3)
        n, e, emap = igl.per_edge_normals(self.v1, self.f1, 0, fn)
        self.assertEqual(e.shape[1], 2)
        # incorrect documentation saying emap and e have the same number of rows
        #self.assertEqual(e.shape[0], emap.shape[0])
        self.assertTrue(n.flags.c_contiguous)
        self.assertTrue(e.flags.c_contiguous)
        self.assertTrue(emap.flags.c_contiguous)

    def test_remove_duplicate_vertices(self):
        epsilon = 1e-6
        sv, svi, svj, sf = igl.remove_duplicate_vertices(
            self.v1, self.f1, epsilon)
        self.assertTrue(sv.dtype == self.v1.dtype)
        self.assertTrue(svi.dtype == svj.dtype == sf.dtype == self.f1.dtype)
        self.assertEqual(sv.shape[1], self.v1.shape[1])
        self.assertTrue(len(svi.shape) == len(svj.shape) == 1)
        self.assertTrue(sv.flags.c_contiguous)
        self.assertTrue(svi.flags.c_contiguous)
        self.assertTrue(svj.flags.c_contiguous)
        self.assertTrue(sf.flags.c_contiguous)

    def test_remove_duplicates(self):
        epsilon = 1e-6
        nv, nf = igl.remove_duplicates(self.v1, self.f1, epsilon)
        self.assertEqual(nv.dtype, self.v1.dtype)
        self.assertEqual(nf.dtype, self.f1.dtype)
        self.assertTrue(nv.shape[0] > 0 and nv.shape[1] > 0)
        self.assertTrue(nf.shape[0] > 0)
        self.assertTrue(nv.flags.c_contiguous)
        self.assertTrue(nf.flags.c_contiguous)

    def test_remove_unreferenced(self):
        nv, nf, i, j = igl.remove_unreferenced(self.v1, self.f1)
        self.assertEqual(nv.shape[1], self.v1.shape[1])
        self.assertEqual(nf.shape[1], self.f1.shape[1])
        self.assertEqual(i.shape[0], self.v1.shape[0])
        self.assertEqual(nv.dtype, self.v1.dtype)
        self.assertTrue(nf.dtype == i.dtype == j.dtype == self.f1.dtype)
        self.assertTrue(nv.flags.c_contiguous)
        self.assertTrue(nf.flags.c_contiguous)
        self.assertTrue(i.flags.c_contiguous)
        self.assertTrue(j.flags.c_contiguous)

    def test_resolve_duplicated_faces(self):
        f2, j = igl.resolve_duplicated_faces(self.f1)
        self.assertTrue(f2.dtype == self.f1.dtype == j.dtype)
        self.assertEqual(self.f1.shape[1], f2.shape[1])
        self.assertEqual(f2.shape[0], j.shape[0])
        self.assertTrue(f2.flags.c_contiguous)
        self.assertTrue(j.flags.c_contiguous)

    def test_shape_diameter_function(self):
        s = igl.shape_diameter_function(
            self.v1, self.f1, self.v1, self.v1, 100)
        self.assertEqual(s.shape[0], self.v1.shape[0])
        self.assertEqual(s.dtype, self.v1.dtype)
        self.assertTrue(s.flags.c_contiguous)

    def test_triangle_triangle_adjacency(self):
        tt, tti = igl.triangle_triangle_adjacency(self.f1)
        self.assertTrue(tt.shape == tti.shape == (self.f1.shape[0], 3))
        self.assertTrue(tt.dtype == tti.dtype == self.f1.dtype)
        self.assertTrue(tt.flags.c_contiguous)
        self.assertTrue(tti.flags.c_contiguous)

    def test_uniformly_sample_two_manifold_at_vertices(self):
        s = igl.uniformly_sample_two_manifold_at_vertices(self.v1, 100, 1.0)
        self.assertEqual(s.dtype, self.f1.dtype)
        self.assertTrue(s.shape[0] > 0)
        self.assertTrue(s.flags.c_contiguous)

    def test_uniformly_sample_two_manifold_internal(self):
        # internal function tested in test_uniformly_sample_two_manifold
        pass

    def test_unproject_in_mesh(self):
        pos = np.array([10., 10.])
        eye = np.eye(4)
        viewport = np.array([0., 0., 100., 100.])
        obj, hits = igl.unproject_in_mesh(
            pos, eye, eye, viewport, self.v1, self.f1)

        self.assertTrue(obj.flags.c_contiguous)
        self.assertTrue(obj.dtype == self.v1.dtype)

    def test_unproject_onto_mesh(self):
        pos = np.array([10., 10.])
        eye = np.eye(4)
        viewport = np.array([0., 0., 100., 100.])
        ok, fid, bc = igl.unproject_onto_mesh(
            pos, eye, eye, viewport, self.v1, self.f1)

        self.assertTrue(type(ok) == bool)
        self.assertTrue(bc.flags.c_contiguous)
        self.assertTrue(bc.dtype == self.v1.dtype)

    def test_vertex_components_from_adjacency_matrix(self):
        # tested in test_vertex_components
        pass

    def test_vertex_triangle_adjacency(self):
        vf, ni = igl.vertex_triangle_adjacency(self.f1, self.v1.shape[0])
        self.assertEqual(vf.shape[0], 3*self.f1.shape[0])
        self.assertTrue(len(vf.shape) == len(ni.shape) == 1)
        self.assertEqual(ni.shape[0], self.v1.shape[0]+1)
        self.assertTrue(vf.flags.c_contiguous)
        self.assertTrue(ni.flags.c_contiguous)

    def test_tet_tet_adjacency(self):
        tet = np.array([[0, 1, 2, 3], [4, 5, 6, 7]])
        tt, tti = igl.tet_tet_adjacency(tet)

        self.assertEqual(tt.shape, tet.shape)
        self.assertEqual(tti.shape, tet.shape)
        self.assertEqual(tti.dtype, tet.dtype)
        self.assertTrue(tt.flags.c_contiguous)
        self.assertTrue(tti.flags.c_contiguous)

    def test_arap1(self):
        v, f, _ = igl.read_off(os.path.join(self.test_data_path, "camelhead.off"))
        b = igl.boundary_loop(f)
        thetas = np.linspace(0, 2 * np.pi, len(b))[:, np.newaxis]
        bc = np.concatenate([np.cos(thetas), np.sin(
            thetas), np.zeros_like(thetas)], axis=1)
        uv_initial_guess = igl.harmonic(v, f, b, bc, 1)

        v2d = v[:, :2].copy()
        arap1 = igl.ARAP(v2d, f, 2, b)
        vp1 = arap1.solve(bc[:, :2], uv_initial_guess[:, :2])
        self.assertEqual(vp1.shape[0], v.shape[0])
        self.assertTrue(vp1.flags.c_contiguous)

        arap2 = igl.ARAP(v, f, 3, b)
        vp2 = arap2.solve(bc, uv_initial_guess)
        self.assertEqual(vp2.shape[0], v.shape[0])
        self.assertTrue(vp2.flags.c_contiguous)

    def test_arap2(self):
        num_b = 100

        thetas = np.linspace(0, 2 * np.pi, num_b)[:, np.newaxis]
        r = thetas / (2 * np.pi)
        boundary = np.concatenate(
            [r * np.cos(thetas), np.sin(thetas), np.zeros([num_b, 1])], axis=1)
        edges = np.array([(i, (i + 1) % boundary.shape[0])
                          for i in range(boundary.shape[0])])
        v = np.load(os.path.join(self.test_data_path, "test_arap2_v.npy"))
        f = np.load(os.path.join(self.test_data_path, "test_arap2_f.npy"))
        v = np.concatenate([v, np.zeros([v.shape[0], 1])], axis=1)
        b = igl.boundary_loop(f)

        thetas = np.linspace(0, 2 * np.pi, len(b))[:, np.newaxis]
        circle_b = np.concatenate(
            [np.cos(thetas), np.sin(thetas), np.zeros([len(b), 1])], axis=1)

        v0 = igl.harmonic(v, f, b, circle_b, 1)
        arap = igl.ARAP(v, f, 2, b)

        v2 = arap.solve(circle_b[:, :2], v0[:, :2])
        self.assertEqual(v2.shape[0], v0.shape[0])
        self.assertTrue(v2.flags.c_contiguous)

    def test_arap3(self):
        v, f = igl.read_triangle_mesh(
            os.path.join(self.test_data_path, "camelhead.off"))

        # Find the open boundary
        bnd = igl.boundary_loop(f)

        # Map the boundary to a circle, preserving edge proportions
        bnd_uv = igl.map_vertices_to_circle(v, bnd)

        # Harmonic parametrization for the internal vertices
        uv = igl.harmonic(v, f, bnd, bnd_uv, 1)

        arap = igl.ARAP(v, f, 2, np.zeros((0)))
        uva = arap.solve(np.zeros((0, 0)), uv)

    def test_arap4(self):
        v, f = igl.read_triangle_mesh(
            os.path.join(self.test_data_path, "camelhead.off"))
        b = igl.boundary_loop(f)
        thetas = np.linspace(0, 2 * np.pi, len(b))[:, np.newaxis]
        bc = np.concatenate([np.cos(thetas), np.sin(
            thetas), np.zeros_like(thetas)], axis=1)
        uv_initial_guess = igl.harmonic(v, f, b, bc, 1)

        arap = igl.ARAP(v, f, 3, b, igl.ARAP_ENERGY_TYPE_SPOKES)
        uva = arap.solve(bc, uv_initial_guess)

    def test_slim(self):
        v, f, _ = igl.read_off(os.path.join(self.test_data_path, "camelhead.off"))
        b = igl.boundary_loop(f)
        thetas = np.linspace(0, 2 * np.pi, len(b))[:, np.newaxis]
        bc = np.concatenate([np.cos(thetas), np.sin(
            thetas), np.zeros_like(thetas)], axis=1)
        uv_initial_guess = igl.harmonic(v, f, b, bc, 1)

        slim = igl.SLIM(
            v, f, uv_initial_guess[:, :2], b, bc[:, :2], igl.SLIM_ENERGY_TYPE_ARAP, 0.0)
        slim.solve(1)
        v2 = slim.vertices()
        self.assertEqual(v2.shape[0], v.shape[0])
        self.assertTrue(v2.flags.c_contiguous)

    def test_bbw(self):
        V, T, F = igl.read_mesh(os.path.join(self.test_data_path, "hand.mesh"))
        C, BE, _, _, _, _ = igl.read_tgf(
            os.path.join(self.test_data_path, "hand.tgf"))

        ok, b, bc = igl.boundary_conditions(V, T, C, np.array(
            [], dtype=T.dtype), BE, np.array([], dtype=T.dtype))

        self.assertTrue(b.flags.c_contiguous)
        self.assertTrue(bc.flags.c_contiguous)
        self.assertTrue(b.dtype == T.dtype)
        self.assertTrue(bc.dtype == V.dtype)

        bbw = igl.BBW(0, 2)
        W = bbw.solve(V, T, b, bc)
        self.assertTrue(W.dtype == V.dtype)
        self.assertTrue(W.flags.c_contiguous)

    def test_shapeup(self):
        VQC, FQC, _ = igl.read_off(os.path.join(
            self.test_data_path, "halftunnel.off"))
        array_of_fours = np.ones((FQC.shape[0], 1), dtype="int32")*4

        E = np.zeros((FQC.shape[0]*FQC.shape[1], 2), dtype="int32")
        E[:, 0] = np.concatenate((FQC[:, 0], FQC[:, 1], FQC[:, 2], FQC[:, 3]))
        E[:, 1] = np.concatenate((FQC[:, 1], FQC[:, 2], FQC[:, 3], FQC[:, 0]))

        b = np.array([0])
        wShape = np.ones((FQC.shape[0], 1))
        wSmooth = np.ones((E.shape[0], 1))

        shapeup = igl.shapeup(VQC, array_of_fours, FQC, E,
                              b, wShape, wSmooth, maxIterations=3)

        bc = VQC[0, :]
        func = 'regular_face_projection'
        P = shapeup.solve(bc, VQC, local_projection=func)

        self.assertTrue(P.flags.c_contiguous)
        self.assertTrue(P.dtype == VQC.dtype)

    def test_boundary_conditions(self):
        # tested in test bbw
        pass

    def test_harmonic(self):
        # tested in test_slim, test_arap2, and test_arap1
        pass

    def test_harmonic_integrated(self):
        Q = igl.harmonic_integrated(self.v1, self.f1, 1)
        self.assertTrue(Q.dtype == self.v1.dtype)

    def test_harmonic_uniform_laplacian(self):
        b = np.array([0, 10])
        bc = np.array([
            [0, 0], [10., 10.]])
        W = igl.harmonic_uniform_laplacian(self.f1, b, bc, 1)

        self.assertTrue(W.dtype == self.v1.dtype)
        self.assertTrue(W.flags.c_contiguous)

    def test_harmonic_integrated_from_laplacian_and_mass(self):
        l = igl.cotmatrix(self.v1, self.f1)
        m = igl.massmatrix(self.v1, self.f1, igl.MASSMATRIX_TYPE_VORONOI)

        Q = igl.harmonic_integrated_from_laplacian_and_mass(l, m, 1)
        self.assertTrue(Q.dtype == self.v1.dtype)

    # deal with igl::PerEdgeNormalsWeightingType
    # def test_per_edge_normals(self):
    #    fn = np.random.rand(self.f1.shape[0], 3)
    #    n, e, emap = igl.per_edge_normals(self.v1, self.f1, 0, fn)

    def test_lscm(self):
        b = np.array([1, 2, 3])
        # print(b.dtype)
        bc = np.array([
            [1., 0],
            [1, 1],
            [2, 2]])
        success, uv = igl.lscm(self.v1, self.f1, b, bc)
        self.assertEqual(type(success), bool)
        self.assertEqual(uv.dtype, self.v1.dtype)
        self.assertEqual(uv.shape, (self.v1.shape[0], 2))
        self.assertTrue(uv.flags.c_contiguous)

    def test_is_irregular_vertex(self):
        is_i = igl.is_irregular_vertex(self.v1, self.f1)
        self.assertEqual(type(is_i[0]), bool)

    def test_harmonic(self):
        l = igl.cotmatrix(self.v1, self.f1)
        m = igl.massmatrix(self.v1, self.f1, igl.MASSMATRIX_TYPE_VORONOI)
        b = np.array([1, 2, 10, 7])
        bc = self.v1[b, :]
        k = 1
        w = igl.harmonic_from_laplacian_and_mass(l, m, b, bc, k)
        self.assertTrue(w.flags.c_contiguous)

    def test_harmonic_from_laplacian_and_mass(self):
        # tested in test_harmonic
        pass

    # this test is creating a matrix which is not spd and an assertion fails...
    # def test_bijective_composite_harmonic_mapping(self):
    #     v, f = igl.read_triangle_mesh(os.path.join(self.test_data_path, "circle.obj"))
    #     f = np.array(f[:, [0, 2, 1]])
    #     v = np.array(v[:, 0:2])
    #     b = np.array([943, 1356]
    #     bc = np.array([
    #         [0, 0],
    #         [10., 10.]
    #     ])

    #     ok, u = igl.bijective_composite_harmonic_mapping(v, f, b, bc)

    #     self.assertTrue(u.flags.c_contiguous)
    #     self.assertTrue(u.dtype == v1.dtype)
    #     self.assertTrue(type(ok) == bool)

    def test_exact_geodesic(self):
        vs = np.array([0])
        vt = np.arange(self.v1.shape[0])

        d = igl.exact_geodesic(self.v1, self.f1, vs, vt)
        self.assertEqual(d.dtype, self.v1.dtype)
        self.assertTrue(d.flags.c_contiguous)

    def test_heat_geodesic(self):
        vs = np.array([0])
        d = igl.heat_geodesic(self.v1, self.f1, 1.0, vs)
        # TODO: Should this not return distances for all sources?
        self.assertEqual(d.dtype, self.v1.dtype)
        self.assertTrue(d.flags.c_contiguous)

    def test_cut_mesh(self):
        cuts = np.random.randint(0, 2, size=self.f1.shape, dtype=self.f1.dtype)
        vcut, fcut = igl.cut_mesh(self.v1, self.f1, cuts)

        self.assertTrue(vcut.flags.c_contiguous)
        self.assertTrue(fcut.flags.c_contiguous)

        self.assertTrue(vcut.dtype == self.v1.dtype)
        self.assertTrue(vcut.shape[1] == 3)
        self.assertTrue(vcut.shape[0] >= self.v1.shape[0])
        self.assertTrue(fcut.dtype == self.f1.dtype)
        self.assertTrue(fcut.shape[1] == 3)
        self.assertTrue(fcut.shape[0] == self.f1.shape[0])

    def test_cut_mesh_from_singularities(self):
        mismatch = np.random.randint(
            0, 10, size=self.f1.shape, dtype=self.f1.dtype)
        seams = igl.cut_mesh_from_singularities(self.v1, self.f1, mismatch)
        self.assertEqual(seams.shape, (self.f1.shape[0], 3))
        self.assertEqual(seams.dtype, bool)
        self.assertTrue(seams.flags.c_contiguous)

    # def test_BBW(self):
    #    BBW = igl.BBW()
    #    w = BBW.solve(self.v1, self.f1, self.bc, self.b0)

    def test_loop_subdivision_matrix(self):
        S, nf = igl.loop_subdivision_matrix(len(self.v1), self.f1)
        self.assertEqual(nf.dtype, self.f1.dtype)
        self.assertEqual(nf.shape[1], self.f1.shape[1])
        self.assertTrue(nf.flags.c_contiguous)

    def test_loop(self):
        nv, nf = igl.loop(self.v1, self.f1)
        self.assertEqual(nv.dtype, self.v1.dtype)
        self.assertEqual(nv.shape[1], self.v1.shape[1])
        self.assertEqual(nf.dtype, self.f1.dtype)
        self.assertEqual(nf.shape[1], self.f1.shape[1])
        self.assertTrue(nv.flags.c_contiguous)
        self.assertTrue(nf.flags.c_contiguous)

    def test_segments_intersect(self):
        p = np.float32([0, 0, 0])
        r = np.float32([1, 2, 3])
        q = np.float32([5, 5, 5])
        s = np.float32([3, 2, 1])
        is_intersect, t, u, eps = igl.segments_intersect(p, r, q, s)
        self.assertEqual(type(is_intersect), bool)
        self.assertEqual(type(t), float)
        self.assertEqual(type(u), float)

    def test_hessian_energy(self):
        q = igl.hessian_energy(self.v1, self.f1)
        self.assertEqual(q.dtype, self.v1.dtype)
        self.assertEqual(q.shape, (self.v1.shape[0], self.v1.shape[0]))

    def test_signed_distance(self):
        min_v = np.min(self.v1, axis=0)
        max_v = np.max(self.v1, axis=0)
        n = 16
        g = np.mgrid[min_v[0]:max_v[0]:complex(
            n), min_v[1]:max_v[1]:complex(n), min_v[2]:max_v[2]:complex(n)]
        p = np.vstack(list(map(np.ravel, g))).T
        # test default type
        s, i, c = igl.signed_distance(p, self.v1, self.f1)

        self.assertEqual(s.shape[0], p.shape[0])
        self.assertEqual(i.shape[0], p.shape[0])
        self.assertEqual(c.shape, p.shape)

        signTypes = [
            igl.SIGNED_DISTANCE_TYPE_PSEUDONORMAL,
            igl.SIGNED_DISTANCE_TYPE_WINDING_NUMBER,
            igl.SIGNED_DISTANCE_TYPE_DEFAULT,
            igl.SIGNED_DISTANCE_TYPE_UNSIGNED,
            igl.SIGNED_DISTANCE_TYPE_FAST_WINDING_NUMBER
        ]

        # test each specific type.
        for signType in signTypes:
            s, i, c = igl.signed_distance(
                p, self.v1, self.f1, sign_type=signType)
            self.assertEqual(s.shape[0], p.shape[0])
            self.assertEqual(i.shape[0], p.shape[0])
            self.assertEqual(c.shape, p.shape)
            self.assertTrue(s.flags.c_contiguous)
            self.assertTrue(i.flags.c_contiguous)
            self.assertTrue(c.flags.c_contiguous)

            self.assertTrue(s.dtype == self.v1.dtype)
            self.assertTrue(c.dtype == self.v1.dtype)
            self.assertTrue(i.dtype == self.f1.dtype)

        # test return_normals, default changes to psuedonormal
        s, i, c, n = igl.signed_distance(
            p, self.v1, self.f1, return_normals=True)
        self.assertEqual(n.shape, p.shape)
        self.assertTrue(n.flags.c_contiguous)
        self.assertTrue(n.dtype == self.v1.dtype)

        # ensure error raised when trying param other than pseudonormal for normals
        with self.assertRaises(ValueError):
            igl.signed_distance(
                p, self.v1, self.f1, sign_type=igl.SIGNED_DISTANCE_TYPE_WINDING_NUMBER, return_normals=True)

        # ensure error raise when invalid param given
        with self.assertRaises(ValueError):
            igl.signed_distance(p, self.v1, self.f1, sign_type=345)

    def test_offset_surface(self):
        sv, sf, gv, side, so = igl.offset_surface(
            self.v1, self.f1, 1, 10, igl.SIGNED_DISTANCE_TYPE_DEFAULT)
        self.assertTrue(sv.dtype == self.v1.dtype)
        self.assertTrue(sf.dtype == self.f1.dtype)

        self.assertTrue(gv.dtype == self.v1.dtype)
        self.assertTrue(side.dtype == self.f1.dtype)
        self.assertTrue(so.dtype == self.f1.dtype)

        self.assertTrue(sv.shape[1] == 3)
        self.assertTrue(sf.shape[1] == 3)
        self.assertTrue(gv.shape[1] == 3)

        self.assertTrue(gv.shape[0] == so.shape[0])

    def test_biharmonic_coordinates(self):
        w = igl.biharmonic_coordinates(self.v1, self.f1, [[0]])

        self.assertTrue(w.flags.c_contiguous)
        self.assertTrue(w.dtype == self.v1.dtype)

    # std::function in python
    # def test_flip_avoid_line_search(self):
    #    pass

    def test_min_quad_with_fixed(self):
        v, f = igl.read_triangle_mesh(
            os.path.join(self.test_data_path, "cheburashka.off"))

        # Two fixed points: Left hand, left foot should have values 1 and -1
        b = np.array([4331, 5957])
        bc = np.array([1., -1.])
        B = np.zeros((v.shape[0], 1))

        # Construct Laplacian and mass matrix
        L = igl.cotmatrix(v, f)
        M = igl.massmatrix(v, f, igl.MASSMATRIX_TYPE_VORONOI)
        Minv = sp.sparse.diags(1 / M.diagonal())

        # Bi-Laplacian
        Q = L.dot(Minv.dot(L))

        # Solve with only equality constraints
        Aeq = sp.sparse.csc_matrix((0, 0))
        Beq = np.array([])
        ok, z1 = igl.min_quad_with_fixed(Q, B, b, bc, Aeq, Beq, True)
        self.assertTrue(z1.flags.c_contiguous)
        self.assertTrue(z1.dtype == B.dtype)
        self.assertTrue(ok)

    def test_marching_tets(self):
        TV = np.array([
            [0., 0., 0.],
            [1., 0., 0.],
            [0., 1., 0.],
            [0., 0., 1.],
            [0., 0., -1.]
        ])
        TT = np.array([[0, 1, 2, 3], [0, 1, 2, 4]])
        S = np.array([0., 1., 1., 1., 1.])

        v, f, j, bc = igl.marching_tets(TV, TT, S, 0.5)

        self.assertTrue(v.flags.c_contiguous)
        self.assertTrue(f.flags.c_contiguous)
        self.assertTrue(j.flags.c_contiguous)

        self.assertTrue(v.dtype == TV.dtype)
        self.assertTrue(v.shape[0] >= 3)
        self.assertTrue(v.shape[1] == 3)

        self.assertTrue(f.dtype == TT.dtype)
        self.assertTrue(f.shape[1] == 3)

        self.assertTrue(j.dtype == TT.dtype)
        self.assertTrue(j.shape[0] == f.shape[0])

        self.assertTrue(bc.dtype == TV.dtype)
        self.assertTrue(bc.shape[0] == v.shape[0])
        self.assertTrue(bc.shape[1] == TV.shape[0])

    def test_read_tgf(self):
        filename = os.path.join(self.test_data_path, "hand.tgf")
        tf = np.array([1.])
        ti = np.array([1])

        V, E, P, BE, CE, PE = igl.read_tgf(filename)

        self.assertTrue(V.flags.c_contiguous)
        self.assertTrue(E.flags.c_contiguous)
        self.assertTrue(P.flags.c_contiguous)
        self.assertTrue(BE.flags.c_contiguous)
        self.assertTrue(CE.flags.c_contiguous)
        self.assertTrue(PE.flags.c_contiguous)

        self.assertTrue(V.dtype == tf.dtype)
        self.assertTrue(E.dtype == ti.dtype)
        self.assertTrue(P.dtype == ti.dtype)
        self.assertTrue(BE.dtype == ti.dtype)
        self.assertTrue(CE.dtype == ti.dtype)
        self.assertTrue(PE.dtype == ti.dtype)

    def test_deform_skeleton(self):
        hand_file = os.path.join(self.test_data_path, "hand.tgf")
        C, BE, _, _, _, _ = igl.read_tgf(hand_file)

        T = np.zeros((BE.shape[0]*4, 3))
        I = np.eye(3)
        for i in range(0, T.shape[0], 4):
            T[i:i+3, :] = I

        CT, BET = igl.deform_skeleton(C, BE, T)
        self.assertTrue(CT.flags.c_contiguous)
        self.assertTrue(BET.flags.c_contiguous)

        self.assertTrue(CT.dtype == C.dtype)
        self.assertTrue(BET.dtype == BE.dtype)

    def test_edge_lengths(self):
        l = igl.edge_lengths(self.v1, self.f1)

        self.assertTrue(l.flags.c_contiguous)
        self.assertTrue(l.dtype == self.v1.dtype)
        self.assertTrue(l.shape == self.f1.shape)

    def test_planarize_quad_mesh(self):
        v, f, _ = igl.read_off(os.path.join(
            self.test_data_path, "inspired_mesh_quads_Conjugate.off"))
        out = igl.planarize_quad_mesh(v, f, 1, 1e-2)

        self.assertTrue(out.dtype == v.dtype)
        self.assertTrue(out.flags.c_contiguous)

    def test_local_basis(self):
        b1, b2, b3 = igl.local_basis(self.v1, self.f1)
        self.assertTrue(b1.flags.c_contiguous)
        self.assertTrue(b2.flags.c_contiguous)
        self.assertTrue(b3.flags.c_contiguous)

        self.assertTrue(b1.dtype == self.v1.dtype)
        self.assertTrue(b2.dtype == self.v1.dtype)
        self.assertTrue(b3.dtype == self.v1.dtype)

        self.assertTrue(b1.shape == self.f1.shape)
        self.assertTrue(b2.shape == self.f1.shape)
        self.assertTrue(b3.shape == self.f1.shape)

    def test_cross_fields(self):
        V, F = igl.read_triangle_mesh(
            os.path.join(self.test_data_path, "3holes.off"))

        B = igl.barycenter(V, F)
        b = np.array([0])
        bc = np.array([[1., 0., 0.]])

        # if platform.system() == "Windows":
        X1 = np.load(os.path.join(self.test_data_path, "X1.npy"))
        S = np.load(os.path.join(self.test_data_path, "S.npy"))

        self.assertTrue(X1.flags.c_contiguous)
        self.assertTrue(S.flags.c_contiguous)
        self.assertTrue(X1.dtype == V.dtype)
        self.assertTrue(S.dtype == V.dtype)

        B1, B2, B3 = igl.local_basis(V, F)

        X2 = igl.rotate_vectors(X1, np.array([math.pi/2]), B1, B2)
        self.assertTrue(X2.flags.c_contiguous)
        self.assertTrue(X2.dtype == V.dtype)

        BIS1, BIS2 = igl.compute_frame_field_bisectors_no_basis(V, F, X1, X2)
        self.assertTrue(BIS1.flags.c_contiguous)
        self.assertTrue(BIS1.dtype == V.dtype)
        self.assertTrue(BIS2.flags.c_contiguous)
        self.assertTrue(BIS2.dtype == V.dtype)

        BIS1t, BIS2t = igl.compute_frame_field_bisectors(
            V, F, X1, X2, BIS1, BIS2)
        self.assertTrue(BIS1t.flags.c_contiguous)
        self.assertTrue(BIS1t.dtype == V.dtype)
        self.assertTrue(BIS2t.flags.c_contiguous)
        self.assertTrue(BIS2t.dtype == V.dtype)

        BIS1_combed, BIS2_combed = igl.comb_cross_field(V, F, BIS1, BIS2)
        self.assertTrue(BIS1_combed.flags.c_contiguous)
        self.assertTrue(BIS1_combed.dtype == V.dtype)
        self.assertTrue(BIS2_combed.flags.c_contiguous)
        self.assertTrue(BIS2_combed.dtype == V.dtype)

        BI_combed = igl.comb_line_field(V, F, BIS1)
        self.assertTrue(BI_combed.flags.c_contiguous)
        self.assertTrue(BI_combed.dtype == V.dtype)

        MMatch = igl.cross_field_mismatch(V, F, BIS1_combed, BIS2_combed, True)
        self.assertTrue(MMatch.flags.c_contiguous)
        self.assertTrue(MMatch.dtype == F.dtype)

        isSingularity, singularityIndex = igl.find_cross_field_singularities(
            V, F, MMatch)
        self.assertTrue(isSingularity.flags.c_contiguous)
        self.assertTrue(isSingularity.dtype == F.dtype)
        self.assertTrue(singularityIndex.flags.c_contiguous)
        self.assertTrue(singularityIndex.dtype == F.dtype)

        isSingularityt, singularityIndext = igl.find_cross_field_singularities_from_field(
            V, F, BIS1_combed, BIS2_combed)
        self.assertTrue(isSingularityt.flags.c_contiguous)
        self.assertTrue(isSingularityt.dtype == F.dtype)
        self.assertTrue(singularityIndext.flags.c_contiguous)
        self.assertTrue(singularityIndext.dtype == F.dtype)

        X1_combed, X2_combed = igl.comb_frame_field(
            V, F, X1, X2, BIS1_combed, BIS2_combed)
        self.assertTrue(X1_combed.flags.c_contiguous)
        self.assertTrue(X1_combed.dtype == V.dtype)
        self.assertTrue(X2_combed.flags.c_contiguous)
        self.assertTrue(X2_combed.dtype == V.dtype)

    def test_comb_cross_field(self):
        #tested in test_cross_fields
        pass

    def test_comb_frame_field(self):
        #tested in test_cross_fields
        pass

    def test_comb_line_field(self):
        #tested in test_cross_fields
        pass

    def test_compute_frame_field_bisectors(self):
        #tested in test_cross_fields
        pass

    def test_compute_frame_field_bisectors_no_basis(self):
        #tested in test_cross_fields
        pass

    def test_cross_field_mismatch(self):
        #tested in test_cross_fields
        pass

    def test_find_cross_field_singularities(self):
        #tested in test_cross_fields
        pass

    def test_find_cross_field_singularities_from_field(self):
        #tested in test_cross_fields
        pass

    def test_rotate_vectors(self):
        #tested in test_cross_fields
        pass

    def test_directed_edge_orientations(self):
        v = np.array([[0.0, 0.0, 0.], [1.0, 0.0, 0.],
                      [1.0, 1.0, 0.], [0.0, 1.0, 0.]])
        e = np.array([[0, 1], [1, 2], [2, 3], [3, 0]])

        q = igl.directed_edge_orientations(v, e)
        self.assertTrue(q.flags.c_contiguous)
        self.assertTrue(q.dtype == v.dtype)
        self.assertTrue(q.shape[0] == e.shape[0])
        self.assertTrue(q.shape[1] == 4)

    def test_lbs_matrix(self):
        V, _ = igl.read_triangle_mesh(os.path.join(self.test_data_path, "arm.obj"))
        W = igl.read_dmat(os.path.join(self.test_data_path, "arm-weights.dmat"))
        M = igl.lbs_matrix(V, W)
        self.assertTrue(M.flags.c_contiguous)
        self.assertTrue(M.dtype == V.dtype)
        self.assertTrue(M.shape[0] == V.shape[0])
        self.assertTrue(M.shape[1] == W.shape[1]*4)

    def test_direct_delta_mush(self):
        V, F = igl.read_triangle_mesh(os.path.join(self.test_data_path, "arm.obj"))
        W = igl.read_dmat(os.path.join(self.test_data_path, "arm-weights.dmat"))
        _, BE, _, _, _, _ = igl.read_tgf(os.path.join(self.test_data_path, "arm.tgf"))

        # Use same values as tutorial
        # https://github.com/libigl/libigl/blob/main/tutorial/408_DirectDeltaMush/main.cpp
        p = 20
        l = 3
        k = 1
        a = 0.8
        omega = igl.direct_delta_mush_precomputation(V, F,W, p, l, k, a)

        self.assertTrue(omega.shape[0] == V.shape[0])
        self.assertTrue(omega.shape[1] == BE.shape[0] * 10)
        self.assertTrue(omega.dtype == np.double)

        T = np.zeros((BE.shape[0]*4, 3))
        I = np.eye(3)
        for i in range(0, T.shape[0], 4):
            T[i:i+3, :] = I

        U = igl.direct_delta_mush(V, T, omega)

        self.assertTrue(U.shape[0] == V.shape[0])
        self.assertTrue(U.shape[1] == 3)
        self.assertTrue(U.dtype == np.double)
        self.assertFalse(np.isnan(U).any())
    
    def test_direct_delta_mush_precomputation(self):
        # covered in test_direct_delta_mush
        pass


    def test_point_mesh_squared_distance(self):
        dist, i, c = igl.point_mesh_squared_distance(
            np.array([0., 0., 0.]), self.v1, self.f1)

        self.assertTrue(dist.flags.c_contiguous)
        self.assertTrue(i.flags.c_contiguous)
        self.assertTrue(c.flags.c_contiguous)

        self.assertTrue(dist.dtype == self.v1.dtype)
        self.assertTrue(i.dtype == self.f1.dtype)
        self.assertTrue(c.dtype == self.v1.dtype)

        self.assertTrue(dist.shape == ())
        self.assertTrue(i.shape == ())
        self.assertTrue(c.shape == (3,))
        #########################
        dist, i, c = igl.point_mesh_squared_distance(
            np.array([[0., 0., 0.], [0., 0., 0.]]), self.v1, self.f1)

        self.assertTrue(dist.flags.c_contiguous)
        self.assertTrue(i.flags.c_contiguous)
        self.assertTrue(c.flags.c_contiguous)

        self.assertTrue(dist.dtype == self.v1.dtype)
        self.assertTrue(i.dtype == self.f1.dtype)
        self.assertTrue(c.dtype == self.v1.dtype)

        self.assertTrue(dist.shape[0] == 2)
        self.assertTrue(i.shape[0] == 2)
        self.assertTrue(c.shape[0] == 2)
        self.assertTrue(c.shape[1] == 3)

    def test_dual_quat_skinning(self):
        V, _ = igl.read_triangle_mesh(os.path.join(self.test_data_path, "arm.obj"))
        U = np.copy(V)
        W = igl.read_dmat(os.path.join(self.test_data_path, "arm-weights.dmat"))
        C, BE, _, _, _, _ = igl.read_tgf(
            os.path.join(self.test_data_path, "arm.tgf"))
        P = igl.directed_edge_parents(BE)
        rest_pose = igl.directed_edge_orientations(C, BE)

        M = igl.lbs_matrix(V, W)

        vQ, vT = igl.forward_kinematics(C, BE, P, rest_pose, np.array([]))
        self.assertTrue(vQ.flags.c_contiguous)
        self.assertTrue(vT.flags.c_contiguous)
        self.assertTrue(vQ.shape[1] == 4)
        self.assertTrue(vT.shape[1] == 3)
        self.assertTrue(vQ.shape[0] == BE.shape[0])
        self.assertTrue(vT.shape[0] == BE.shape[0])

        U = igl.dqs(V, W, vQ, vT)
        self.assertTrue(U.flags.c_contiguous)
        self.assertTrue(U.shape == V.shape)

    def test_dqs(self):
        # tested in test_dual_quat_skinning
        pass

    def test_forward_kinematics(self):
        # tested in test_dual_quat_skinning
        pass

    def test_active_set(self):
        V, F = igl.read_triangle_mesh(
            os.path.join(self.test_data_path, "cheburashka.off"))

        b = np.array([2556])
        bc = np.array([1.0])

        L = igl.cotmatrix(V, F)
        M = igl.massmatrix(V, F, igl.MASSMATRIX_TYPE_VORONOI)
        Minv = sp.sparse.csr_matrix(M)
        Minv.setdiag(1./M.diagonal())
        Q = L.T * (Minv * L)
        B = np.zeros((V.shape[0], 1))
        lx = np.zeros((V.shape[0], 1))
        ux = np.ones((V.shape[0], 1))

        Beq = np.array([0.08])
        Aeq = sp.sparse.csr_matrix(M.diagonal())

        Aieq = sp.sparse.csr_matrix((0, 0))
        Bieq = np.zeros((0, 0))

        status, Z = igl.active_set(
            Q, B, b, bc, Aeq, Beq, Aieq, Bieq, lx, ux, max_iter=5)

        self.assertTrue(status != 2)
        self.assertTrue(Z.shape[0] == Q.shape[0])
        self.assertTrue(Z.dtype == V.dtype)

    def test_face_occurrences(self):
        c = igl.face_occurrences(self.f)
        self.assertTrue(c.flags.c_contiguous)
        self.assertTrue(c.dtype == self.f.dtype)
        self.assertTrue(c.shape[0] == self.f.shape[0])

    def test_false_barycentric_subdivision(self):
        vd, fd = igl.false_barycentric_subdivision(self.v, self.f)
        self.assertTrue(vd.flags.c_contiguous)
        self.assertTrue(fd.flags.c_contiguous)

        self.assertTrue(vd.dtype == self.v.dtype)
        self.assertTrue(fd.dtype == self.f.dtype)

        self.assertTrue(vd.shape[0] == self.v.shape[0]+self.f.shape[0])
        self.assertTrue(vd.shape[1] == self.v.shape[1])
        self.assertTrue(fd.shape[1] == self.f.shape[1])
        self.assertTrue(fd.shape[0] == self.f.shape[0]*3)

    def test_flipped_triangles(self):
        flipped = igl.flipped_triangles(self.v[:, :2], self.f)
        self.assertTrue(flipped.flags.c_contiguous)
        self.assertTrue(flipped.dtype == self.f.dtype)
        self.assertTrue(len(flipped.shape) == 1)

    def test_inradius(self):
        r = igl.inradius(self.v, self.f)
        self.assertTrue(r.flags.c_contiguous)
        self.assertTrue(r.dtype == self.v.dtype)
        self.assertTrue(r.shape[0] == self.f.shape[0])
        self.assertTrue(len(r.shape) == 1)

    def test_is_border_vertex(self):
        res = igl.is_border_vertex(self.v, self.f)

        self.assertTrue(len(res) == self.v.shape[0])
        self.assertTrue(type(res) == list)
        self.assertTrue(type(res[0]) == bool)

    def test_extract_manifold_patches(self):
        n, p = igl.extract_manifold_patches(self.f2)
        self.assertTrue(p.flags.c_contiguous)
        self.assertTrue(p.dtype == self.f2.dtype)
        self.assertTrue(len(p.shape) == 1)
        self.assertTrue(p.shape[0] == self.f2.shape[0])
        self.assertTrue(type(n) == int)
        self.assertTrue(n == 1)

    def test_faces_first(self):
        RV, RF, IM = igl.faces_first(self.v, self.f)
        self.assertTrue(RV.flags.c_contiguous)
        self.assertTrue(RF.flags.c_contiguous)
        self.assertTrue(IM.flags.c_contiguous)

        self.assertTrue(RV.dtype == self.v.dtype)
        self.assertTrue(RF.dtype == self.f.dtype)
        self.assertTrue(IM.dtype == self.f.dtype)

        self.assertTrue(RV.shape[0] == self.v.shape[0])
        self.assertTrue(RF.shape[0] == self.f.shape[0])
        self.assertTrue(IM.shape[0] == self.v.shape[0])
        self.assertTrue(len(IM.shape) == 1)

    def test_is_intrinsic_delaunay(self):
        # Tested above
        pass

    def test_intrinsic_delaunay_triangulation(self):
        el = igl.edge_lengths(self.v1, self.f1)
        l, f = igl.intrinsic_delaunay_triangulation(el, self.f1)
        # print(l, f)
        self.assertTrue(f.flags.c_contiguous)
        self.assertTrue(f.dtype == self.f1.dtype)
        self.assertTrue(f.shape[1] == 3)

    def test_intrinsic_delaunay_triangulation_edges(self):
        el = igl.edge_lengths(self.v1, self.f1)
        l, f, e, u_e, emap, ue2e = igl.intrinsic_delaunay_triangulation_edges(
            el, self.f1)
        self.assertTrue(f.flags.c_contiguous)
        self.assertTrue(f.dtype == self.f.dtype)
        self.assertTrue(f.shape[1] == 3)

    def test_edges_to_path(self):
        e = igl.edges(self.f1)
        e = e[:1, :]
        i, j, k = igl.edges_to_path(e)

        self.assertTrue(i.flags.c_contiguous)
        self.assertTrue(j.flags.c_contiguous)
        self.assertTrue(k.flags.c_contiguous)

        self.assertTrue(i.dtype == e.dtype)
        self.assertTrue(j.dtype == e.dtype)
        self.assertTrue(k.dtype == e.dtype)

    def test_data_path_to_edges(self):
        v_indices = np.array(range(20))
        e1 = igl.path_to_edges(v_indices, False)
        e2 = igl.path_to_edges(v_indices, True)
        r2 = np.vstack([v_indices, np.array(range(1, 21))]).T
        r2[19, 1] = 0
        self.assertTrue(np.allclose(e2, r2))
        self.assertTrue(e1.flags.c_contiguous)
        self.assertTrue(e2.flags.c_contiguous)
        self.assertTrue(e1.dtype == v_indices.dtype)
        self.assertTrue(e2.dtype == v_indices.dtype)

    def test_exterior_edges(self):
        e = igl.exterior_edges(self.f1)

        self.assertTrue(e.flags.c_contiguous)
        self.assertTrue(e.dtype == self.f1.dtype)
        self.assertTrue(e.shape[1] == 2)

    def test_normal_derivative(self):
        d = igl.normal_derivative(self.v1, self.f1)

        self.assertTrue(d.shape == (self.f1.shape[0]*3, self.v1.shape[0]))
        self.assertTrue(d.dtype == self.v1.dtype)
        self.assertTrue(type(d) == csc.csc_matrix)

    def test_orient_outward(self):
        c, _ = igl.orientable_patches(self.f)
        ff, i = igl.orient_outward(self.v, self.f, c)

        self.assertTrue(ff.flags.c_contiguous)
        self.assertTrue(i.flags.c_contiguous)
        self.assertTrue(ff.dtype == self.f.dtype)
        self.assertTrue(i.dtype == self.f.dtype)
        self.assertTrue(ff.shape[0] == self.f.shape[0])
        self.assertTrue(ff.shape[1] == 3)
        self.assertTrue(len(i.shape) == 1)
        self.assertTrue(i.shape[0] == np.max(c)+1)

    def test_solid_angle(self):
        v0 = np.array(self.v1[self.f1[0, 0], :])
        v1 = np.array(self.v1[self.f1[0, 1], :])
        v2 = np.array(self.v1[self.f1[0, 2], :])
        p = np.array(self.v1[10, :])
        d = igl.solid_angle(v0, v1, v2, p)

    def test_simplify_polyhedron(self):
        v, f, j = igl.simplify_polyhedron(self.v1, self.f1)

        self.assertTrue(v.flags.c_contiguous)
        self.assertTrue(f.flags.c_contiguous)
        self.assertTrue(j.flags.c_contiguous)

        self.assertTrue(v.dtype == self.v1.dtype)
        self.assertTrue(f.dtype == self.f1.dtype)
        self.assertTrue(j.dtype == self.f1.dtype)

        self.assertTrue(v.shape[1] == self.v1.shape[1])
        self.assertTrue(f.shape[1] == self.f1.shape[1])
        self.assertTrue(len(j.shape) == 1)

    def test_unique_simplices(self):
        fa, ia, ic = igl.unique_simplices(self.f1)

        self.assertTrue(fa.flags.c_contiguous)
        self.assertTrue(ia.flags.c_contiguous)
        self.assertTrue(ic.flags.c_contiguous)

        self.assertTrue(fa.dtype == self.f1.dtype)
        self.assertTrue(ia.dtype == self.f1.dtype)
        self.assertTrue(ic.dtype == self.f1.dtype)

        self.assertTrue(fa.shape[1] == self.f1.shape[1])
        self.assertTrue(ia.shape[0] == ia.shape[0])
        self.assertTrue(ic.shape[0] == self.f1.shape[0])
        self.assertTrue(len(ic.shape) == 1)
        self.assertTrue(len(ia.shape) == 1)

    def test_swept_volume_bounding_box(self):
        def func(i, t): return (1-t) * \
            self.v1[self.f1[0, i], :] + t*self.v1[self.f1[1, i], :]

        bmin, bmax = igl.swept_volume_bounding_box(3, func, 3)
        self.assertTrue(bmin.flags.c_contiguous)
        self.assertTrue(bmax.flags.c_contiguous)

        self.assertTrue(bmin.dtype == self.v1.dtype)
        self.assertTrue(bmax.dtype == self.v1.dtype)

        self.assertTrue(bmin.shape == (3,))
        self.assertTrue(bmax.shape == (3,))

    def test_hessian(self):
        H = igl.hessian(self.v1, self.f1)
        self.assertTrue(H.dtype == self.v1.dtype)

    def test_snap_points(self):
        I, minD, VI = igl.snap_points(self.v1, self.v)

        self.assertTrue(I.flags.c_contiguous)
        self.assertTrue(minD.flags.c_contiguous)
        self.assertTrue(VI.flags.c_contiguous)

        self.assertTrue(I.dtype == self.f1.dtype)
        self.assertTrue(minD.dtype == self.v1.dtype)
        self.assertTrue(VI.dtype == self.v1.dtype)

        self.assertTrue(I.shape == (self.v1.shape[0], ))
        self.assertTrue(I.shape == (self.v1.shape[0], ))
        self.assertTrue(VI.shape == (self.v1.shape[0], 3))

    def test_ray_box_intersect(self):
        bmin = np.array([0., 0., 0.])
        bmax = np.array([1., 1., 1.])

        source = np.array([-1., -1, -1])
        dire = np.array([1., 1., 1.])

        hit, tmin, tmax = igl.ray_box_intersect(
            source, dire, bmin, bmax, 0, 100)

        self.assertTrue(hit)
        self.assertTrue(tmin > 0)
        self.assertTrue(tmax < 100)

    def test_ray_mesh_intersect(self):
        source = np.array([-1., -1, -1])
        dire = np.array([1., 1., 1.])

        hits = igl.ray_mesh_intersect(source, dire, self.v1, self.f1)

        self.assertTrue(len(hits) > 0)
        self.assertTrue(len(hits[0]) == 5)

    def test_ray_sphere_intersect(self):
        center = np.array([1., 1., 1.])

        source = np.array([-1., -1, -1])
        dire = np.array([1., 1., 1.])

        hits, tmin, tmax = igl.ray_sphere_intersect(
            source, dire, center, 1)

        self.assertTrue(hits == 2)

    def test_volume(self):
        v, t, f = igl.read_mesh(os.path.join(
            self.test_data_path, "octopus-low.mesh"))
        vol = igl.volume(v, t)
        self.assertTrue(vol.flags.c_contiguous)
        self.assertTrue(vol.dtype == v.dtype)
        self.assertTrue(len(vol.shape) == 1)
        self.assertTrue(vol.shape[0] == t.shape[0])

        a = v[t[:, 0], :]
        b = v[t[:, 1], :]
        c = v[t[:, 2], :]
        d = v[t[:, 3], :]

        vol = igl.volume_from_vertices(a, b, c, d)
        self.assertTrue(vol.flags.c_contiguous)
        self.assertTrue(vol.dtype == v.dtype)
        self.assertTrue(len(vol.shape) == 1)
        self.assertTrue(vol.shape[0] == a.shape[0])

        vol = igl.volume_single(a[0, :], b[0, :], c[0, :], d[0, :])

        l = igl.edge_lengths(v, t)
        vol = igl.volume_from_edges(l)
        self.assertTrue(vol.flags.c_contiguous)
        self.assertTrue(vol.dtype == v.dtype)
        self.assertTrue(len(vol.shape) == 1)
        self.assertTrue(vol.shape[0] == t.shape[0])

    def test_volume_from_edges(self):
        #tested in volume
        pass

    def test_volume_from_vertices(self):
        #tested in volume
        pass

    def test_volume_single(self):
        #tested in volume
        pass

    def test_mvc(self):
        pts = np.random.rand(10, 2)
        poly = np.array([[0., 0.], [1., 1.], [2., 2.], [0., 3.]])
        w = igl.mvc(pts, poly)

        self.assertTrue(w.flags.c_contiguous)
        self.assertTrue(w.dtype == pts.dtype)
        self.assertTrue(w.shape[0] == pts.shape[0])
        self.assertTrue(w.shape[1] == poly.shape[0])

    def test_all_pairs_distances(self):
        u = np.random.rand(10, 2)
        v = np.random.rand(5, 2)

        d = igl.all_pairs_distances(u, v, True)
        self.assertTrue(d.flags.c_contiguous)
        self.assertTrue(d.dtype == u.dtype)
        self.assertTrue(d.shape[0] == u.shape[0])
        self.assertTrue(d.shape[1] == v.shape[0])

    def test_line_segment_in_rectangle(self):
        s = np.array([0., 0.])
        d = np.array([10., 10.])

        A = np.array([1., 1.])
        B = np.array([2., 2.])

        inter = igl.line_segment_in_rectangle(s, d, A, B)
        self.assertTrue(inter)

    def test_look_at(self):
        eye = np.random.rand(3, 1)
        center = np.random.rand(3, 1)
        up = np.random.rand(3, 1)

        R = igl.look_at(eye, center, up)

        self.assertTrue(R.flags.c_contiguous)
        self.assertTrue(R.dtype == eye.dtype)
        self.assertTrue(R.shape[0] == 4)
        self.assertTrue(R.shape[1] == 4)

    def test_outer_vertex(self):
        v, a = igl.outer_vertex(
            self.v1, self.f1, np.zeros((1, 1), dtype=self.f1.dtype))

        self.assertTrue(a.flags.c_contiguous)
        self.assertTrue(a.dtype == self.f1.dtype)

    def test_outer_edge(self):
        v1, v2, a = igl.outer_edge(
            self.v1, self.f1, np.zeros((1, 1), dtype=self.f1.dtype))

        self.assertTrue(a.flags.c_contiguous)
        self.assertTrue(a.dtype == self.f1.dtype)

    def test_outer_facet(self):
        n = igl.per_face_normals(self.v1, self.f1, self.v1)
        index, flipped = igl.outer_facet(
            self.v1, self.f1, n, np.zeros((1, 1), dtype=self.f1.dtype))

    def test_partition(self):
        g, s, d = igl.partition(self.v1, 3)

        self.assertTrue(g.flags.c_contiguous)
        self.assertTrue(s.flags.c_contiguous)
        self.assertTrue(d.flags.c_contiguous)

        self.assertTrue(g.dtype == self.f1.dtype)
        self.assertTrue(s.dtype == self.f1.dtype)
        self.assertTrue(d.dtype == self.v1.dtype)

        self.assertTrue(g.shape[0] == self.v1.shape[0])
        self.assertTrue(s.shape[0] == 3)
        self.assertTrue(d.shape[0] == self.v1.shape[0])

        self.assertTrue(len(g.shape) == 1)
        self.assertTrue(len(s.shape) == 1)
        self.assertTrue(len(d.shape) == 1)

    def test_point_in_circle(self):
        inside = igl.point_in_circle(1, 2, 3, 4, 1)

    def test_point_simplex_squared_distance(self):
        dist, pt, bary = igl.point_simplex_squared_distance(
            np.array([3., 3, 1.]), self.v1, self.f1, 0)

        self.assertTrue(pt.flags.c_contiguous)
        self.assertTrue(bary.flags.c_contiguous)

        self.assertTrue(pt.dtype == self.v1.dtype)
        self.assertTrue(bary.dtype == self.v1.dtype)

        self.assertTrue(pt.shape[0] == 3)
        self.assertTrue(bary.shape[0] == 3)

    def test_polar_dec(self):
        A = np.random.rand(3, 3)

        r, t = igl.polar_dec(A)

        self.assertTrue(r.flags.c_contiguous)
        self.assertTrue(t.flags.c_contiguous)

        self.assertTrue(r.dtype == self.v1.dtype)
        self.assertTrue(t.dtype == self.v1.dtype)

        self.assertTrue(r.shape[0] == 3)
        self.assertTrue(t.shape[0] == 3)
        self.assertTrue(r.shape[1] == 3)
        self.assertTrue(t.shape[1] == 3)

    def test_project(self):
        model = np.random.rand(4, 4)
        proj = np.random.rand(4, 4)
        viewport = np.random.rand(4, 1)
        proj = igl.project(self.v, model, proj, viewport)
        self.assertEqual(proj.dtype, self.v.dtype)
        self.assertEqual(proj.shape, self.v.shape)
        self.assertTrue(proj.flags.c_contiguous)

    def test_project_isometrically_to_plane(self):
        U, UF, I = igl.project_isometrically_to_plane(self.v1, self.f1)

        self.assertEqual(U.dtype, self.v1.dtype)
        self.assertEqual(U.shape, (3*self.f1.shape[0], 2))
        self.assertTrue(U.flags.c_contiguous)

        self.assertEqual(UF.dtype, self.f1.dtype)
        self.assertEqual(UF.shape, self.f1.shape)
        self.assertTrue(UF.flags.c_contiguous)

        self.assertEqual(I.dtype, self.f1.dtype)
        self.assertEqual(I.shape, (self.v1.shape[0], 3*self.f1.shape[0]))
        self.assertTrue(type(I) == csc.csc_matrix)

    def test_project_to_line(self):
        pts = np.random.rand(10, 3)
        s = np.random.rand(1, 3)
        d = np.random.rand(1, 3)
        t, sqrt_d = igl.project_to_line(pts, s, d)

        self.assertTrue(t.flags.c_contiguous)
        self.assertTrue(t.dtype == pts.dtype)
        self.assertTrue(t.shape[0] == pts.shape[0])

        self.assertTrue(sqrt_d.flags.c_contiguous)
        self.assertTrue(sqrt_d.dtype == pts.dtype)
        self.assertTrue(sqrt_d.shape[0] == pts.shape[0])

    def test_project_to_line_segment(self):
        pts = np.random.rand(10, 3)
        s = np.random.rand(1, 3)
        d = np.random.rand(1, 3)
        t, sqrt_d = igl.project_to_line_segment(pts, s, d)

        self.assertTrue(t.flags.c_contiguous)
        self.assertTrue(t.dtype == pts.dtype)
        self.assertTrue(t.shape[0] == pts.shape[0])

        self.assertTrue(sqrt_d.flags.c_contiguous)
        self.assertTrue(sqrt_d.dtype == pts.dtype)
        self.assertTrue(sqrt_d.shape[0] == pts.shape[0])

    def test_ramer_douglas_peucker(self):
        pts = np.random.rand(10, 3)
        s, j, q = igl.ramer_douglas_peucker(pts, 1e-1)

        self.assertTrue(s.flags.c_contiguous)
        self.assertTrue(s.dtype == pts.dtype)
        self.assertTrue(s.shape[1] == pts.shape[1])

        self.assertTrue(j.flags.c_contiguous)
        self.assertTrue(j.dtype == self.f1.dtype)
        self.assertTrue(j.shape[0] == s.shape[0])

        self.assertTrue(q.flags.c_contiguous)
        self.assertTrue(q.dtype == pts.dtype)
        self.assertTrue(q.shape == pts.shape)

    def test_sample_edges(self):
        e = igl.edges(self.f1)
        s = igl.sample_edges(self.v1, e, 4)
        # print(e.shape, s.shape)

        self.assertTrue(s.flags.c_contiguous)
        self.assertTrue(s.dtype == self.v1.dtype)
        self.assertTrue(s.shape[0] < e.shape[0]*6)
        self.assertTrue(s.shape[1] == self.v1.shape[1])

    def test_read_msh(self):
        v, t = igl.read_msh(os.path.join(self.test_data_path, "car.msh"))
        self.assertTrue(type(v) == type(t) == np.ndarray)
        self.assertTrue(v.flags.c_contiguous)
        self.assertTrue(t.flags.c_contiguous)

        self.assertTrue(v.dtype == self.default_float)
        self.assertTrue(t.dtype == self.f1.dtype)

    def test_two_axis_valuator_fixed_up(self):
        down_quat = np.random.rand(4, 1)

        quat = igl.two_axis_valuator_fixed_up(
            20, 20, 1, down_quat, 10, 10, 9, 9)

        self.assertTrue(quat.flags.c_contiguous)
        self.assertTrue(quat.dtype == down_quat.dtype)
        self.assertTrue(quat.shape[0] == 4)

    def test_triangle_fan(self):
        _, f = igl.read_triangle_mesh(
            os.path.join(self.test_data_path, "camelhead.off"))
        e = igl.exterior_edges(self.f)
        cap = igl.triangle_fan(e)

        self.assertTrue(cap.flags.c_contiguous)
        self.assertTrue(cap.dtype == e.dtype)
        self.assertTrue(cap.shape[1] == 3)

    def test_triangles_from_strip(self):
        s = self.f[:, 0]
        f = igl.triangles_from_strip(s)

        self.assertTrue(f.flags.c_contiguous)
        self.assertTrue(f.dtype == self.f.dtype)
        self.assertTrue(f.shape[0] == self.f.shape[0]-2)
        self.assertTrue(f.shape[1] == 3)

    def test_signed_angle(self):
        a = np.random.rand(2, 1)
        b = np.random.rand(2, 1)
        p = np.random.rand(2, 1)

        angle = igl.signed_angle(a, b, p)

        a = np.random.rand(1, 2)
        b = np.random.rand(1, 2)
        p = np.random.rand(1, 2)

        angle = igl.signed_angle(a, b, p)

    def test_unique_edge_map(self):
        E, uE, EMAP, uE2E = igl.unique_edge_map(self.f1)

        self.assertTrue(E.flags.c_contiguous)
        self.assertTrue(uE.flags.c_contiguous)
        self.assertTrue(EMAP.flags.c_contiguous)

        self.assertTrue(E.dtype == self.f1.dtype)
        self.assertTrue(uE.dtype == self.f1.dtype)
        self.assertTrue(EMAP.dtype == self.f1.dtype)

        self.assertTrue(E.shape == (self.f1.shape[0]*3, 2))
        self.assertTrue(uE.shape[1] == 2)
        self.assertTrue(E.shape[0] == self.f1.shape[0]*3)

    def test_connected_components(self):
        a = igl.adjacency_matrix(self.f)
        comps, c, k = igl.connected_components(a)

        self.assertTrue(c.flags.c_contiguous)
        self.assertTrue(k.flags.c_contiguous)

        self.assertTrue(c.dtype == self.f1.dtype)
        self.assertTrue(k.dtype == self.f1.dtype)

        self.assertTrue(c.shape[0] == a.shape[0])

    def test_pso(self):
        def banana(x):
            x1 = x[0]
            x2 = x[1]
            return x1**4 - 2*x2*x1**2 + x2**2 + x1**2 - 2*x1 + 5

        lb = np.array([-3.0, -1.0])
        ub = np.array([2.0, 6.0])

        fopt, xopt = igl.pso(banana, lb, ub, max_iters=10, population=10)

        self.assertTrue(xopt.flags.c_contiguous)
        self.assertTrue(xopt.dtype == lb.dtype)
        self.assertTrue(xopt.shape == (2, ))

    def test_random_search(self):
        def banana(x):
            x1 = x[0]
            x2 = x[1]
            return x1**4 - 2*x2*x1**2 + x2**2 + x1**2 - 2*x1 + 5

        lb = np.array([-3.0, -1.0])
        ub = np.array([2.0, 6.0])

        fopt, xopt = igl.random_search(banana, lb, ub, iters=10)

        self.assertTrue(xopt.flags.c_contiguous)
        self.assertTrue(xopt.dtype == lb.dtype)
        self.assertTrue(xopt.shape == (2, ))

    def test_bijective_composite_harmonic_mapping(self):
        v, f, _ = igl.read_off(os.path.join(self.test_data_path, "camelhead.off"))
        b = igl.boundary_loop(f)
        thetas = np.linspace(0, 2 * np.pi, len(b))[:, np.newaxis]
        bc = np.concatenate([np.cos(thetas), np.sin(thetas)], axis=1)
        v2d = igl.harmonic(v, f, b, bc, 1)[:, :2]
        ret0, mapping0 = igl.bijective_composite_harmonic_mapping(
            v2d, f, b, bc)
        self.assertTrue(ret0)
        self.assertTrue(mapping0.flags.c_contiguous)
        self.assertTrue(mapping0.dtype == v2d.dtype)
        self.assertTrue(mapping0.shape == v2d.shape)

        ret1, mapping1 = igl.bijective_composite_harmonic_mapping_with_steps(
            v2d, f, b, bc, min_steps=1, max_steps=5, num_inner_iters=2, test_for_flips=True)
        self.assertTrue(ret1)
        self.assertTrue(mapping1.flags.c_contiguous)
        self.assertTrue(mapping1.dtype == v2d.dtype)
        self.assertTrue(mapping1.shape == v2d.shape)

        ret2, mapping2 = igl.bijective_composite_harmonic_mapping_with_steps(
            v2d, f, b, bc, min_steps=1, max_steps=5, num_inner_iters=2, test_for_flips=False)
        self.assertTrue(ret2)
        self.assertTrue(mapping2.flags.c_contiguous)
        self.assertTrue(mapping2.dtype == v2d.dtype)
        self.assertTrue(mapping2.shape == v2d.shape)

        self.assertTrue(np.allclose(mapping0, mapping1))

    def test_bijective_composite_harmonic_mapping_with_steps(self):
        # Tested above
        pass

    def test_extract_non_manifold_edge_curves(self):
        _ = igl.extract_non_manifold_edge_curves(self.f1, [])
        curves = igl.extract_non_manifold_edge_curves(self.f1, [range(10)])
        self.assertTrue(len(curves) == 1)
        self.assertTrue(curves[0][0] == 0)

    def test_intrinsic_delaunay_cotmatrix(self):
        l, l_int, f_int = igl.intrinsic_delaunay_cotmatrix(self.v1, self.f1)
        # print(l.shape, l_int.shape, f_int.shape)
        self.assertTrue(l.shape == (self.v1.shape[0], self.v1.shape[0]))
        self.assertTrue(l.dtype == self.v1.dtype)
        self.assertTrue(type(l) == csc.csc_matrix)

    def test_cut_to_disk(self):
        cuts = igl.cut_to_disk(self.f)
        self.assertTrue(len(cuts) == 9)

    def test_iterative_closest_point(self):
        r, t = igl.iterative_closest_point(
            self.v1, self.f1, self.v1, self.f1, 3, 20)
        self.assertEqual(r.shape, (3, 3))
        self.assertEqual(t.shape, (3,))
        self.assertTrue(r.flags.c_contiguous)
        self.assertTrue(t.flags.c_contiguous)
        self.assertTrue(r.dtype == t.dtype == self.v.dtype)

    def test_rigid_alignment(self):
        n = igl.per_vertex_normals(self.v1, self.f1)
        r, t = igl.rigid_alignment(self.v1, self.v1+1, n)
        self.assertTrue(np.allclose(r, np.eye(3)))
        self.assertTrue(np.allclose(t, np.ones(3)))
        self.assertEqual(r.shape, (3, 3))
        self.assertEqual(t.shape, (3,))
        self.assertTrue(r.flags.c_contiguous)
        self.assertTrue(t.flags.c_contiguous)
        self.assertTrue(r.dtype == t.dtype == self.v1.dtype)

    def test_sharp_edges(self):
        se, e, ue, emap, ue2e, sharp = igl.sharp_edges(
            self.v1, self.f1, np.pi*0.11)
        self.assertTrue(se.shape[1] == 2)
        self.assertTrue(ue.shape[1] == 2)
        self.assertTrue(emap.shape[0] == self.f1.shape[0]*3)
        self.assertTrue(se.shape[0] == len(sharp))
        self.assertTrue(se.flags.c_contiguous)
        self.assertTrue(e.flags.c_contiguous)
        self.assertTrue(ue.flags.c_contiguous)
        self.assertTrue(emap.flags.c_contiguous)

    def test_quad_grid(self):
        v, q, e = igl.quad_grid(3, 3)
        self.assertTrue(v.shape == (3*3, 2))
        self.assertTrue(q.shape == (2*2, 4))
        self.assertTrue(v.flags.c_contiguous)
        self.assertTrue(q.flags.c_contiguous)
        self.assertTrue(v.dtype == self.default_float)
        self.assertTrue(q.dtype == self.default_int)
        self.assertTrue(e.dtype == self.default_int)

    def test_sparse_voxel_grid(self):
        def sphere1(point):
            return np.sqrt(point[0]**2 + point[1]**2 + point[2]**2) - 1.0
        point = np.array([1.0, 0.0, 0.0])
        cs, cv, ci = igl.sparse_voxel_grid(point, sphere1, 1.0, 100)
        self.assertTrue(cv.flags.c_contiguous)
        self.assertTrue(cv.dtype == self.default_float)
        self.assertTrue(cv.shape == (len(cs), 3))
        self.assertTrue(ci.flags.c_contiguous)
        self.assertTrue(ci.dtype == self.default_int)
        self.assertTrue(ci.shape[1] == 8)

    def test_topological_hole_fill(self):
        f = self.f1
        b = np.array(range(10))
        h = [range(10, 20)]
        ff = igl.topological_hole_fill(f, b, h)
        self.assertTrue(ff.flags.c_contiguous)
        self.assertTrue(ff.shape[1] == 3)
        self.assertTrue(ff.dtype == f.dtype)
        self.assertTrue(ff.shape[0] != f.shape[0])

    def test_triangulated_grid(self):
        v, f = igl.triangulated_grid(10, 10)
        self.assertTrue(v.shape == (100, 2))
        self.assertTrue(f.shape == (162, 3))
        self.assertTrue(f.flags.c_contiguous)
        self.assertTrue(v.flags.c_contiguous)
        self.assertTrue(v.dtype == self.default_float)
        self.assertTrue(f.dtype == self.default_int)

    def test_unproject_on_line(self):
        pos = np.array([10., 10.])
        eye = np.eye(4)
        viewport = np.array([0., 0., 100., 100.])
        p = np.array([15.0, 20.0, 13.0])
        d = np.array([0.1, 0.2, 1.0])
        t, z = igl.unproject_on_line(pos, eye, viewport, p, d)

        self.assertTrue(z.flags.c_contiguous)
        self.assertTrue(z.shape == (3, ))
        self.assertTrue(z.dtype == pos.dtype)

    def test_unproject_on_plane(self):
        pos = np.array([10., 10.])
        eye = np.eye(4)
        viewport = np.array([0., 0., 100., 100.])
        p = np.array([1.0, 2.0, 3.0, 2.0])
        z = igl.unproject_on_plane(pos, eye, viewport, p)

        self.assertTrue(z.flags.c_contiguous)
        self.assertTrue(z.shape == (3, ))
        self.assertTrue(z.dtype == pos.dtype)

    def test_fast_winding_number_for_points(self):
        xs = np.linspace(-5.0, 5.0, 10)
        grid = np.meshgrid(xs, xs, xs, indexing='ij')
        grid = np.stack(grid).reshape(3, -1, order='F').T
        n = igl.per_vertex_normals(self.v1, self.f1)
        a = np.ones((n.shape[0], )) / n.shape[0]

        wn = igl.fast_winding_number_for_points(self.v1, n, a, grid)
        self.assertTrue(wn.flags.c_contiguous)
        self.assertTrue(wn.shape == (grid.shape[0], ))
        self.assertTrue(wn.dtype == self.v1.dtype)

    def test_fast_winding_number_for_meshes(self):
        xs = np.linspace(-5.0, 5.0, 10)
        grid = np.meshgrid(xs, xs, xs, indexing='ij')
        grid = np.stack(grid).reshape(3, -1, order='F').T

        wn = igl.fast_winding_number_for_meshes(self.v1, self.f1, grid)
        self.assertTrue(wn.flags.c_contiguous)
        self.assertTrue(wn.shape == (grid.shape[0], ))
        self.assertTrue(wn.dtype == self.v1.dtype)

    def test_flip_avoiding_line_search(self):
        def fun(v):
            return np.random.rand(1)

        energy, vr = igl.flip_avoiding_line_search(
            self.f1, self.v1[:, :2], self.v1[:, :2], fun, 10.0)
        self.assertTrue(vr.shape == (self.v1.shape[0], 2))
        self.assertTrue(vr.flags.c_contiguous)

    def test_edge_flaps(self):
        e, emap, ef, ei = igl.edge_flaps(self.f2)
        self.assertTrue(e.shape[1] == ef.shape[1] == ei.shape[1] == 2)
        self.assertTrue(e.shape[0] == ef.shape[0] == ei.shape[0])
        self.assertTrue(emap.shape[0] == self.f2.shape[0] * 3)
        self.assertTrue(np.min(e) >= 0 and np.max(e) < self.v2.shape[0])
        self.assertTrue(e.flags.c_contiguous)
        self.assertTrue(emap.flags.c_contiguous)
        self.assertTrue(ef.flags.c_contiguous)
        self.assertTrue(ei.flags.c_contiguous)
        self.assertTrue(e.dtype == emap.dtype ==
                        ef.dtype == ei.dtype == self.f2.dtype)

    def test_circulation(self):
        pass
        #e, emap, ef, ei = igl.edge_flaps(self.f2)
        #fac = igl.circulation(667, True, emap, ef, ei)
        # print(fac)

    def test_edge_collapse_is_valid(self):
        pass
        #e, emap, ef, ei = igl.edge_flaps(self.f2)
        #emap = emap.reshape(-1, 3)
        #val = igl.edge_collapse_is_valid(0, self.f2, e, emap, ef, ei)
        # print(val)

    def test_flip_edge(self):
        e, ue, emap, ue2e = igl.unique_edge_map(self.f1)
        f, e, ue, emap, ue2e = igl.flip_edge(self.f1, e, ue, emap, ue2e, 1)

        self.assertTrue(f.shape == self.f1.shape)
        self.assertTrue(e.shape[1] == ue.shape[1] ==
                        np.array(ue2e).shape[1] == 2)
        self.assertTrue(emap.shape[0] == self.f1.shape[0] * 3)

        self.assertTrue(np.min(e) >= 0 and np.max(e) < self.v2.shape[0])

        self.assertTrue(e.flags.c_contiguous)
        self.assertTrue(emap.flags.c_contiguous)
        self.assertTrue(ue.flags.c_contiguous)

        self.assertTrue(f.dtype == e.dtype == ue.dtype ==
                        emap.dtype == self.f1.dtype)
        self.assertTrue(np.array(ue2e).dtype == self.f1.dtype)

    def test_AABB(self):
        tree = igl.AABB_f64_3()
        tree.init(self.v1,self.f1)
        bc = igl.barycenter(self.v1,self.f1)
        sqrD = tree.squared_distance(self.v1,self.f1,bc)
        self.assertTrue(sqrD.shape[0] == bc.shape[0])
        self.assertTrue(np.max(sqrD) <= 1e-16)
        sqrD,I,C = tree.squared_distance(self.v1,self.f1,bc,return_index=True,return_closest_point=True)
        self.assertTrue(sqrD.shape[0] == bc.shape[0])
        self.assertTrue(I.shape[0] == bc.shape[0])
        self.assertTrue(C.shape == bc.shape)

    def test_in_element_3(self):
        V = np.array([ [0.,0,0], [1,0,0], [0,1,0], [0,0,1], [1,1,1]],dtype='float64')
        T = np.array([[0,1,2,3],[4,3,2,1]],dtype='int32')
        Q = np.array([[0.1,0.1,0.1],[0.9,0.9,0.9]],dtype='float64')
        tree = igl.AABB_f64_3()
        tree.init(V,T)
        I = igl.in_element_3(V,T,Q,tree)
        self.assertTrue(I.shape[0] == Q.shape[0])
        self.assertTrue(I[0] == 0)
        self.assertTrue(I[1] == 1)

    def test_in_element_2(self):
        V = np.array([ [0.,0], [1,0], [0,1], [1,1]],dtype='float64')
        F = np.array([[0,1,2],[2,1,3]],'int32')
        Q = np.array([[0.1,0.1],[0.9,0.9]],dtype='float64')
        tree = igl.AABB_f64_2()
        tree.init(V,F)
        I = igl.in_element_2(V,F,Q,tree)
        self.assertTrue(I.shape[0] == Q.shape[0])
        self.assertTrue(I[0] == 0)
        self.assertTrue(I[1] == 1)


    def test_triangulate(self):
        V = np.array([[0,0],[1,0],[1,1],[0,1]],dtype='float64')
        E = np.array([[0,1],[1,2],[2,3],[3,0]])
        V2,F2 = igl.triangle.triangulate(V,E,flags='Q')
        self.assertTrue(V2.shape == V.shape)
        self.assertTrue(F2.shape == (2,3))
        V = np.array([[0,0],[4,0],[0,4],[1,1],[1,2],[2,1]],dtype='float64')
        E = np.array([[0,1],[1,2],[2,0],[3,4],[4,5],[5,3]])
        H = np.array([[1.1,1.1]])
        # Markers can't be 0
        VM = 1+np.array(range(V.shape[0]))
        EM = 1+np.array(range(E.shape[0]))
        V2,F2,VM2,E2,EM2 = igl.triangle.triangulate(V,E,H,flags='Q',VM=VM,EM=EM)
        self.assertTrue(V2.shape == V.shape)
        self.assertTrue(F2.shape == (3*2,3))
        self.assertTrue(VM2.shape == VM.shape)
        self.assertTrue(E2.shape == E.shape)
        self.assertTrue(EM2.shape == EM.shape)


    # copyleft.cgal
    def test_convex_hull(self):
        V = np.array([[0,0,0],[1,0,0],[0,1,0],[0,0,1]],dtype="float64")
        F = igl.copyleft.cgal.convex_hull(V)
        F = np.sort(F)
        F = F[np.lexsort(F.T[::-1],axis=0)]
        F_gt = np.array([[0, 1, 2], [0, 1, 3], [0, 2, 3], [1, 2, 3]],dtype="int64")
        self.assertTrue((F == F_gt).all())

if __name__ == '__main__':
    unittest.main()
