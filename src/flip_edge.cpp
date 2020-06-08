#include <npe.h>
#include <common.h>
#include <typedefs.h>

#include <pybind11/stl.h>

#include <igl/flip_edge.h>

const char* ds_flip_edge = R"igl_Qu8mg5v7(

Flip an edge in a triangle mesh.  The edge specified by uei must have
exactly two adjacent faces.  Violation will result in exception.
Another warning: edge flipping could convert manifold mesh into
non-manifold.

Parameters
----------
F         #F by 3 list of triangles.
E         #F*3 by 2 list of all of directed edges
uE        #uE by 2 list of unique undirected edges
EMAP      #F*3 list of indices into uE, mapping each directed edge to unique
          undirected edge
uE2E      #uE list of lists of indices into E of coexisting edges
ue        #index into uE the edge to be flipped.

Returns
-------

Updated   F, E, uE, EMAP and uE2E.


See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(flip_edge)
npe_doc(ds_flip_edge)

npe_arg(f, dense_longlong)
npe_arg(e, npe_matches(f))
npe_arg(u_e, npe_matches(f))
npe_arg(emap, npe_matches(f))
npe_arg(u_e2_e, std::vector<std::vector<typename EigenDenseInt::Scalar> >)
npe_arg(uei, size_t)

npe_begin_code()

    assert_valid_tri_mesh_faces(f);

    EigenDenseLike<npe_Matrix_f> f_copy = f;
    EigenDenseLike<npe_Matrix_f> e_copy = e;
    EigenDenseLike<npe_Matrix_f> u_e_copy = u_e;
    EigenDenseLike<npe_Matrix_f> emap_copy = emap;
    std::vector<std::vector<npe_Scalar_f> > u_e2_e_copy = u_e2_e;

    igl::flip_edge(f_copy, e_copy, u_e_copy, emap_copy, u_e2_e_copy, uei);
    return std::make_tuple(npe::move(f_copy), npe::move(e_copy), npe::move(u_e_copy), npe::move(emap_copy), \
           pybind11::detail::type_caster<decltype(u_e2_e_copy)>::cast(u_e2_e_copy, \
           pybind11::return_value_policy::move, pybind11::none()));

npe_end_code()
