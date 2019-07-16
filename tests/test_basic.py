import unittest
import os

import igl
import numpy as np
import scipy.sparse.csc as csc
import math


DOUBLE_EPS = 1.0e-14
DOUBLE_EPS_SQ = 1.0e-28
FLOAT_EPS = 1.0e-7
FLOAT_EPS_SQ = 1.0e-14


class TestBasic(unittest.TestCase):

    def setUp(self):
        # Some global datastructures to use in the tests
        np.random.seed(42)
        self.test_path = os.path.join(os.path.dirname(
            os.path.realpath(__file__)), "../data/")
        self.v1, self.f1, self.n1 = igl.read_off(os.path.join(self.test_path, "bunny.off"))
        self.v2, self.f2, self.n2 = igl.read_off(os.path.join(self.test_path, "fertility.off"))

        self.v = np.random.rand(10, 3).astype(self.v1.dtype)
        self.t = np.random.rand(10, 4)
        self.f = np.random.randint(0, 10, size=(20, 3), dtype=self.f1.dtype)
        self.g = np.random.randint(0, 10, size=(20, 4), dtype="int32")

    def test_module(self):
        # Extract all implemented functions from the module
        funcs = []
        flist = ["helpers", "os", "print_usage", "pyigl", "viewer", "check_dependencies"]
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
        for f in funcs:
            if f not in tests:
                print("WARNING: Test for function %s missing."%f)
                #self.assertTrue(f in tests)

    def test_adjacency_matrix(self):
        a = igl.adjacency_matrix(self.f)
        self.assertTrue(a.shape == (self.v.shape[0], self.v.shape[0]))
        self.assertTrue(a.dtype == self.f.dtype)
        self.assertTrue(type(a) == csc.csc_matrix)

    def test_avg_edge_length(self):
        l = igl.avg_edge_length(self.v1, self.f1)
        self.assertTrue(np.isclose(l, 0.004661094877063719))

    def test_cotmatrix(self):
        l = igl.cotmatrix(self.v, self.f)
        self.assertTrue(l.shape == (self.v.shape[0], self.v.shape[0]))
        self.assertTrue(l.dtype == self.v.dtype)
        self.assertTrue(type(l) == csc.csc_matrix)

    def test_ear(self):
        ears, ears_opp = igl.ears(self.f1)
        self.assertTrue(ears.shape == ears_opp.shape)
        self.assertTrue(ears.dtype == self.f.dtype)
        self.assertTrue(ears_opp.dtype == self.f.dtype)

    def test_gaussian_curvature(self):
        g = igl.gaussian_curvature(self.v, self.f)
        self.assertTrue(g.shape == (self.v.shape[0],))
        self.assertTrue(g.dtype == self.v.dtype)
        self.assertTrue(type(g) == np.ndarray)

    def test_grad(self):
        g = igl.grad(self.v, self.f)
        h = igl.grad(self.v, self.f, uniform=True)
        self.assertTrue(g.shape == (self.f.shape[0] * self.v.shape[1], self.v.shape[0]))
        self.assertTrue(h.shape == (self.f.shape[0] * self.v.shape[1], self.v.shape[0]))
        self.assertTrue(type(g) == type(h) == csc.csc_matrix)

    def test_massmatrix(self):
        a = igl.massmatrix(self.v, self.f)
        b = igl.massmatrix(self.v, self.f, type=igl.MASSMATRIX_TYPE_BARYCENTRIC)
        self.assertTrue(a.shape == (self.v.shape[0], self.v.shape[0]))
        self.assertTrue(b.shape == (self.v.shape[0], self.v.shape[0]))
        self.assertTrue(b.dtype == np.float64)
        self.assertTrue(a.dtype == np.float64)
        self.assertTrue(type(a) == type(b) == csc.csc_matrix)

    def test_principal_curvature(self):
        pd1, pd2, pv1, pv2 = igl.principal_curvature(self.v, self.f)
        qd1, qd2, qv1, qv2 = igl.principal_curvature(self.v, self.f, radius=7, use_k_ring=False)
        self.assertTrue(pd1.shape == qd1.shape == pd2.shape == qd2.shape == self.v.shape)
        self.assertTrue(pv1.shape == qv1.shape == pv2.shape == qv2.shape == (self.v.shape[0],))
        self.assertTrue(pd1.dtype == pd2.dtype == pv1.dtype == pv2.dtype == np.float64)
        v = self.v.copy()
        v = v.astype(np.float32)
        pd1, pd2, pv1, pv2 = igl.principal_curvature(v, self.f)
        self.assertTrue(pd1.dtype == pd2.dtype == pv1.dtype == pv2.dtype == np.float32)
        self.assertTrue(type(pd1) == type(pd2) == type(pv1) == type(pv2) == np.ndarray)

    def test_read_obj(self):
        v, _, n, f, _, _ = igl.read_obj(self.test_path + "face.obj")
        self.assertTrue(type(v) == type(f) == type(n) == np.ndarray)
        self.assertTrue(v.shape == (25905, 3) and n.shape == (0, 0) and f.shape == (51712, 3))
        self.assertTrue(v.dtype == np.float64)
        v, _, n, f, _, _ = igl.read_obj(self.test_path + "face.obj", dtype="float32")
        self.assertTrue(v.shape == (25905, 3) and n.shape == (0, 0) and f.shape == (51712, 3))
        self.assertTrue(v.dtype == np.float32)

    def test_read_off(self):
        v, f, n = igl.read_off(self.test_path + "bunny.off")
        self.assertTrue(type(v) == type(f) == type(n) == np.ndarray)
        self.assertTrue(v.shape == (3485, 3) and n.shape == (0, 0) and f.shape == (6966, 3))
        self.assertTrue(v.dtype == np.float64)
        v, f, n = igl.read_off(self.test_path + "bunny.off", read_normals=False, dtype="float32")
        self.assertTrue(v.shape == (3485, 3) and n.shape == (0, 0) and f.shape == (6966, 3))
        self.assertTrue(v.dtype == np.float32)

    def test_read_triangle_mesh(self):
        v, f = igl.read_triangle_mesh(self.test_path + "octopus-low.mesh")
        print(v.shape, f.shape)
        v, f = igl.read_triangle_mesh(self.test_path + "face.obj")
        print(v.shape, f.shape)
        v, f = igl.read_triangle_mesh(self.test_path + "bunny.off")
        print(v.shape, f.shape)

    def test_triangulate(self):
        v = np.array([[0.0, 0.0], [1.0, 0.0], [1.0, 1.0], [0.0, 1.0]])
        e = np.array([[0, 1], [1, 2], [2, 3], [3, 0]], dtype="int32")
        h = np.array([[]])
        print("v.dtype = %s, h.dtype = %s" % (v.dtype, h.dtype))
        v2, f2 = igl.triangulate(v, e, h, flags="a0.005q")
        self.assertTrue(v2.dtype == v.dtype)
        self.assertTrue(type(v2) == type(f2) == np.ndarray)

    def test_write_obj(self):
        suc = igl.write_obj("test.obj", self.v, self.f)
        self.assertTrue(suc)
        self.assertTrue(os.path.isfile("test.obj"))

    def test_write_off(self):
        suc = igl.write_off("test.off", self.v, self.f,self.v)
        self.assertTrue(suc)
        self.assertTrue(os.path.isfile("test.off"))

    def test_adjacency_list(self):
        a = igl.adjacency_list(self.f1)
        self.assertEqual(len(a), self.v1.shape[0])

    def test_arap_linear_block(self):
        kd = igl.arap_linear_block(self.v1, self.f1, d=2, energy=0)
        self.assertTrue(kd.shape[0] > 0)
        kd = igl.arap_linear_block_elements(self.v1, self.f1, d=2)
        self.assertTrue(kd.shape[0] > 0)
        kd = igl.arap_linear_block_spokes(self.v1, self.f1, d=2)
        self.assertTrue(kd.shape[0] > 0)
        kd = igl.arap_linear_block_spokes_and_rims(self.v1, self.f1, d=2)
        self.assertTrue(kd.shape[0] > 0)

    def test_arap_rhs(self):
        k = igl.arap_rhs(self.v1, self.f1, d=2, energy=0)
        self.assertTrue(k.shape[0] > 0)

    # def test_average_onto_faces(self):
    #     s = np.random.rand(self.f1.shape[0])
    #     sf = igl.average_onto_faces(self.f1, s)
    #     self.assertEqual(sf.shape[0], self.f1.shape[0])

    def test_average_onto_vertices(self):
        s = np.random.rand(self.f1.shape[0])
        sv = igl.average_onto_vertices(self.v1, self.f1, s)
        self.assertEqual(sv.shape[0], self.v1.shape[0])

    def test_barycentric_coordinates(self):
        a, b, c = self.v1[self.f1[:, 0]], self.v1[self.f1[:, 1]], self.v1[self.f1[:, 2]]
        bc = igl.barycentric_coordinates_tri(a, a, b, c)
        self.assertEqual(bc.shape, a.shape)
        expected_bc = np.zeros(a.shape)
        expected_bc[:, 0] = np.ones(a.shape[0])
        self.assertTrue(np.linalg.norm(expected_bc-bc) < 1e-6)

        d = 0.5*a + 0.5*c + np.array([0.1, 0.1, 0.1])
        bc = igl.barycentric_coordinates_tet(d, a, b, c, d)
        self.assertEqual(bc.shape, (a.shape[0], 4))

    def test_vertex_components(self):
        a = igl.adjacency_matrix(self.f1)
        c, count = igl.vertex_components_from_adjacency_matrix(a)
        self.assertEqual(c.shape[0], self.v1.shape[0])

        c = igl.vertex_components(self.f1)
        self.assertEqual(c.shape[0], self.v1.shape[0])

    def test_face_components(self):
        c = igl.face_components(self.f1)
        self.assertEqual(c.shape, (self.f1.shape[0],))
        self.assertTrue(np.array_equal(c, np.zeros_like(c)))

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

        a = csc.csc_matrix(np.zeros([0, 0], dtype=np.int32))
        try:
            p, d, = igl.bfs(a, 0)
            self.assertTrue(False)
        except ValueError as e:
            pass

        a = csc.csc_matrix(np.zeros([10, 11], dtype=np.int32))
        try:
            p, d, = igl.bfs(a, 0)
            self.assertTrue(False)
        except ValueError as e:
            pass

        a = csc.csc_matrix(np.zeros([10, 10], dtype=np.int32))
        p, d, = igl.bfs(a, 0)
        self.assertEqual(p.shape, ())
        self.assertTrue(np.array_equal(d, -np.ones(10)))

    def test_bfs_orient(self):
        ff, c = igl.bfs_orient(self.f1)
        self.assertEqual(ff.shape, self.f1.shape)
        self.assertEqual(c.shape, (self.f1.shape[0],))
        self.assertTrue(np.array_equal(self.f1, ff))

    def test_oriented_facets(self):
        e = igl.oriented_facets(self.f1)
        self.assertTrue(e.shape[0] > self.f1.shape[0])
        self.assertTrue(0 <= np.max(e) < self.v1.shape[0])

    def test_orientable_patches(self):
        c, a = igl.orientable_patches(self.f1)

        self.assertTrue(np.array_equal(c, np.zeros(self.f1.shape[0])))
        self.assertEqual(a.shape, (self.f1.shape[0], self.f1.shape[0]))

    def test_edge_topology(self):
        ev, fe, ef = igl.edge_topology(self.v1, self.f1)
        self.assertEqual(fe.shape, self.f1.shape)
        self.assertEqual(ef.shape, (ev.shape[0],2))
        self.assertEqual(np.max(ev), self.v1.shape[0] - 1)
        self.assertEqual(np.min(ef), 0)

    def test_edges(self):
        e = igl.edges(self.f1)
        self.assertTrue(e.shape[0] > self.f1.shape[0])
        self.assertEqual(e.shape[1], 2)

    def test_bone_parents(self):
        e = igl.edges(self.f1)
        res = igl.bone_parents(e)
        self.assertEqual(res.shape[0], e.shape[0])

    def test_sort_angles(self):
        r = igl.sort_angles(self.v)
        self.assertTrue(r.dtype == self.f.dtype)
        self.assertEqual(r.shape[0], self.v.shape[0])

    def test_circumradius(self):
        r = igl.circumradius(self.v, self.f)
        self.assertTrue(r.dtype == self.v.dtype)
        self.assertEqual(r.shape[0], self.f.shape[0])

    def test_quad_planarity(self):
        p = igl.quad_planarity(self.v, self.g)
        self.assertTrue(p.dtype == self.v.dtype)
        self.assertEqual(p.shape[0], self.g.shape[0])

    # TODO: not completed
    def test_circulation(self):
        pass
        # emap ef, ei are missing
        # ret = igl.circulation(0, False, emap, ef, ei)
        # self.assertTrue(type(ret) == list)
        # self.assertTrue(type(ret[0]) == int)

    def test_collapse_small_triangles(self):
        ff = igl.collapse_small_triangles(self.v, self.f, 0.5)
        self.assertEqual(ff.shape[1], self.f.shape[1])

    def test_bounding_box(self):
        bv, bf = igl.bounding_box(self.v)
        self.assertEqual(bv.shape[1], self.v.shape[1])
        self.assertEqual(bf.shape[1], self.v.shape[1])

    def test_ambient_occlusion(self):
        pass
        #TODO: s is empty for some reason
        # p = -np.ones((1, 3), dtype=self.v1.dtype)
        # n = np.ones((1, 3), dtype=self.v1.dtype)*math.sqrt(3)

        # s = igl.ambient_occlusion(self.v1, self.f1, p, n, 2)
        # self.assertEqual(s.shape[0], 1)
        # self.assertEqual(s.dtype, self.v1.dtype)
        # self.assertEqual(len(s.shape), 1)

    def test_write_triangle_mesh(self):
        ok = igl.write_triangle_mesh("out.obj", self.v, self.f)
        self.assertEqual(ok, True)

    def test_barycenter(self):
        bc = igl.barycenter(self.v, self.f)
        self.assertEqual(bc.dtype, self.v.dtype)
        self.assertEqual(bc.shape[0], self.f.shape[0])
        self.assertEqual(bc.shape[1], 3)

    def test_read_dmat(self):
        mat = igl.read_dmat(self.test_path + "decimated-knight-selection.dmat")
        self.assertEqual(mat.dtype, "float64")

    def test_vector_area_matrix(self):
        a = igl.vector_area_matrix(self.f)
        self.assertEqual(a.dtype, self.f.dtype)
        self.assertEqual(a.shape[0], a.shape[1])
        self.assertEqual(a.shape[0], self.v.shape[0]*2)

    def test_tetrahedralize(self):
        status, tv, tt, tf = igl.tetrahedralize(self.v2, self.f2)

        self.assertEqual(status, 0)

        self.assertEqual(tv.dtype, self.v1.dtype)
        self.assertEqual(tt.dtype, self.f1.dtype)
        self.assertEqual(tf.dtype, self.f1.dtype)

        self.assertEqual(tv.shape[1], 3)
        self.assertEqual(tf.shape[1], 3)
        self.assertEqual(tt.shape[1], 4)

    def test_hausdorff(self):
        dist = igl.hausdorff(self.v, self.f, self.v1, self.f1)
        print(dist)

    def test_isolines(self):
        func = np.random.rand(self.v1.shape[0], 1)
        iso_v, iso_e = igl.isolines(self.v1, self.f1, func, 10)

        self.assertEqual(iso_v.dtype, func.dtype)
        self.assertEqual(iso_e.dtype, self.f1.dtype)
        self.assertEqual(iso_e.shape[1], 2)



    # boundary_conditions
    # bounding_box_diagonal
    #


if __name__ == '__main__':
    unittest.main()
