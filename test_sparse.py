import igl
import time

V, F = igl.icosahedron()

max_iters = 10
for i in range(max_iters):
    A = igl.adjacency_matrix(F)
    n = A.shape[0]

    start = time.time()
    dims = igl.sparse_shape(A)
    t_shape = time.time() - start

    start = time.time()
    A2 = igl.sparse_noop(A)
    t_noop = time.time() - start

    print(f"{n} {t_shape:.6g} {t_noop:.6g}")

    if i != max_iters-1:
        V, F = igl.upsample(V, F)
