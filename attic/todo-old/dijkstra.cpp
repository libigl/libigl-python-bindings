#include <npe.h>
#include <typedefs.h>






#include <igl/dijkstra_compute_paths.h>

const char* ds_dijkstra_compute_paths = R"igl_Qu8mg5v7(

Parameters
----------


Returns
-------


See also
--------


Notes
-----
None

Examples
--------

 Dijstra's algorithm for shortest paths, with multiple targets.
   Adapted from http:rosettacode.org/wiki/Dijkstra%27s_algorithm .
  
   Inputs:
     source           index of source vertex
     targets          target vector set
     VV               #V list of lists of incident vertices (adjacency list), e.g.
                      as returned by igl::adjacency_list
  
   Output:
     min_distance     #V by 1 list of the minimum distances from source to all vertices
     previous         #V by 1 list of the previous visited vertices (for each vertex) - used for backtracking
  
)igl_Qu8mg5v7";

npe_function(dijkstra_compute_paths)
npe_doc(ds_dijkstra_compute_paths)

npe_arg(source, IndexType &)
npe_arg(targets, std::set<IndexType> &)
npe_arg(vv, std::vector<std::vector<IndexType> > &)


npe_begin_code()

  EigenDense<npe_Scalar_> min_distance;
  EigenDense<npe_Scalar_> previous;
  igl::dijkstra_compute_paths(source, targets, vv, min_distance, previous);
  return std::make_tuple(npe::move(min_distance), npe::move(previous));

npe_end_code()
#include <igl/dijkstra_get_shortest_path_to.h>

const char* ds_dijkstra_get_shortest_path_to = R"igl_Qu8mg5v7(

Parameters
----------


Returns
-------


See also
--------


Notes
-----
None

Examples
--------

 Backtracking after Dijstra's algorithm, to find shortest path.
  
   Inputs:
     vertex           vertex to which we want the shortest path (from same source as above)
     previous         #V by 1 list of the previous visited vertices (for each vertex) - result of Dijkstra's algorithm
  
   Output:
     path             #P by 1 list of vertex indices in the shortest path from source to vertex
  
)igl_Qu8mg5v7";

npe_function(dijkstra_get_shortest_path_to)
npe_doc(ds_dijkstra_get_shortest_path_to)

npe_arg(vertex, IndexType &)
npe_arg(previous, dense_float, dense_double)


npe_begin_code()

  std::vector<IndexType> & path;
  igl::dijkstra_get_shortest_path_to(vertex, previous, path);
  return npe::move(path);

npe_end_code()


