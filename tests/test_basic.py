import unittest
import sys
import os

sys.path.insert(0, os.getcwd() + "/../")
import igl
import inspect
import numpy as np
import scipy.sparse.csr as csr
import scipy.sparse.csc as csc


class TestBasic(unittest.TestCase):

    def setUp(self):
        # Some global datastructures to use in the tests
        np.random.seed(42)
        self.v = np.random.rand(10, 3)
        self.t = np.random.rand(10, 4)
        self.f = np.random.randint(0, 10, size=(20, 3), dtype="int32")
        self.g = np.random.randint(0, 10, size=(20, 4), dtype="int32")
        self.v1, self.f1, self.n1 = igl.read_off(os.path.join(igl.TUTORIAL_PATH, "bunny.off"))

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

    def test_jet(self):
        c = igl.jet(np.random.rand(1000), True)
        self.assertTrue(len(c) == 1000)
        self.assertTrue(np.min(c) >= 0.0)
        self.assertTrue(np.max(c) <= 1.0)

    def test_massmatrix(self):
        a = igl.massmatrix(self.v, self.f)
        b = igl.massmatrix(self.v, self.f, type=igl.MASSMATRIX_TYPE_BARYCENTRIC)
        self.assertTrue(a.shape == (self.v.shape[0], self.v.shape[0]))
        self.assertTrue(b.shape == (self.v.shape[0], self.v.shape[0]))
        self.assertTrue(b.dtype == np.float64)
        self.assertTrue(a.dtype == np.float64)
        self.assertTrue(type(a) == type(b) == csc.csc_matrix)

    def test_parula(self):
        c = igl.parula(np.random.rand(1000), True)
        self.assertTrue(len(c) == 1000)
        self.assertTrue(np.min(c) >= 0.0)
        self.assertTrue(np.max(c) <= 1.0)

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
        v, _, n, f, _, _ = igl.read_obj(igl.TUTORIAL_PATH + "face.obj")
        self.assertTrue(type(v) == type(f) == type(n) == np.ndarray)
        self.assertTrue(v.shape == (25905, 3) and n.shape == (0, 0) and f.shape == (51712, 3))
        self.assertTrue(v.dtype == np.float64)
        v, _, n, f, _, _ = igl.read_obj(igl.TUTORIAL_PATH + "face.obj", dtype="float32")
        self.assertTrue(v.shape == (25905, 3) and n.shape == (0, 0) and f.shape == (51712, 3))
        self.assertTrue(v.dtype == np.float32)

    def test_read_off(self):
        v, f, n = igl.read_off(igl.TUTORIAL_PATH + "bunny.off")
        self.assertTrue(type(v) == type(f) == type(n) == np.ndarray)
        self.assertTrue(v.shape == (3485, 3) and n.shape == (0, 0) and f.shape == (6966, 3))
        self.assertTrue(v.dtype == np.float64)
        v, f, n = igl.read_off(igl.TUTORIAL_PATH + "bunny.off", read_normals=False, dtype="float32")
        self.assertTrue(v.shape == (3485, 3) and n.shape == (0, 0) and f.shape == (6966, 3))
        self.assertTrue(v.dtype == np.float32)

    def test_read_triangle_mesh(self):
        # TODO fix segfault problem
        pass
        #v, f = igl.read_triangle_mesh(igl.TUTORIAL_PATH + "bunny.mesh")
        #print(v.shape, f.shape)
        #v, f = igl.read_triangle_mesh(igl.TUTORIAL_PATH + "cube.obj")
        #print(v.shape, f.shape)
        #v, f = igl.read_triangle_mesh(igl.TUTORIAL_PATH + "beetle.off")
        #print(v.shape, f.shape)

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

    def test_average_onto_vertices(self):
        s = np.random.rand(self.f1.shape[0])
        sf = igl.average_onto_faces(self.f1, s)
        self.assertEqual(sf.shape[0], self.f1.shape[0])

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
        self.assertEqual(c.shape[0], self.f1.shape[0])

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

if __name__ == '__main__':
    unittest.main()
