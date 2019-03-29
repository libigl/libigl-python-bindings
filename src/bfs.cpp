#include <npe.h>
#include <typedefs.h>
#include <igl/bfs.h>

const char* ds_bfs = R"igl_Qu8mg5v7(
Construct an array indexing into a **directed** graph represented by an adjacency list using
breadth first search. I.e. the output is an array of vertices in breadth-first order.

Parameters
----------
A : #V list of adjacency lists  or #V by #V adjacency matrix
s : starting node (index into A)

Returns
-------
A tuple, (d, p) where:
 * d is a #V list of indices into rows of A in the order in which graph nodes are discovered
 * p is a #V list of indices of A of predecsors where -1 indicates root/not discovered. I.e.
   p[i] is the index of the vertex v which preceded d[i] in the breadth first traversal.
Note that together, (d, p) form a spanning tree of the input graph

See also
--------

Notes
-----

Examples
--------
>>> V, F, _ = igl.readOFF("test.off)
>>> A = igl.adjacency_matrix(V, F)
>>> d, p = igl.bfs(A, V[0])

)igl_Qu8mg5v7";

npe_function(bfs)
npe_doc(ds_bfs)
npe_arg(A, sparse_i32, sparse_i64)
npe_arg(s, int)
npe_begin_code()

  if (A.rows() != A.cols()) {
    std::string errmsg = std::string("Invalid Adjacency matrix. Must be a square sparse matrix. Got shape: (") +
                         std::to_string(A.rows()) + std::string(", ") + std::to_string(A.cols()) +
                         std::string(")");
    throw pybind11::value_error(errmsg);
  }
  if (A.rows() == 0 && A.cols() == 0) {
    throw pybind11::value_error("Invalid Adjacency matrix has shape 0x0.");
  }
  if (s < 0 || s >= A.rows()) {
    std::string errmsg = std::string("Invalid start index, must be between 0 and the number of rows of A (") +
                         std::to_string(A.rows()) + std::string("). Got s = ") + std::to_string(s);
    throw pybind11::index_error(errmsg);
  }
  EigenDense<npe_Scalar_A> d;
  EigenDense<npe_Scalar_A> p;
  igl::bfs(A, (size_t)s, d, p);
  return std::make_tuple(npe::move(d), npe::move(p));

npe_end_code()



