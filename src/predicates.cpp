#include <common.h>
#include <npe.h>
#include <typedefs.h>

#include <igl/predicates/predicates.h>

const char *ds_orient2d = R"igl_Qu8mg5v7(
Compute the orientation of the triangle formed by pa, pb, pc.

Parameters
----------
    pa, pb, pc  2D points.
Returns
-------

POSITIVE=1 if pa, pb, pc are counterclockwise oriented.
NEGATIVE=-1 if they are clockwise oriented.
COLLINEAR=0 if they are collinear.

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(orient2d)
npe_doc(ds_orient2d)

npe_arg(pa, dense_float, dense_double)
npe_arg(pb, npe_matches(pa))
npe_arg(pc, npe_matches(pa))
npe_begin_code()
    assert_size_equals(pa, 2, "pa");
    assert_size_equals(pb, 2, "pb");
    assert_size_equals(pc, 2, "pc");

    using Scalar = typename npe_Matrix_pa::Scalar;
    using MatType = Eigen::Matrix<Scalar, 2, 1>;

    Eigen::Map<MatType> tmp_pa(&pa(0, 0), pa.size());
    Eigen::Map<MatType> tmp_pb(&pb(0, 0), pb.size());
    Eigen::Map<MatType> tmp_pc(&pc(0, 0), pc.size());

    igl::predicates::exactinit();

    return int(igl::predicates::orient2d(tmp_pa, tmp_pb, tmp_pc));

npe_end_code()



const char *ds_orient3d = R"igl_Qu8mg5v7(

Compute the orientation of the tetrahedron formed by pa, pb, pc, pd.

Parameters
----------
pa, pb, pc, pd  3D points.

Returns
-------
POSITIVE=1 if pd is "below" the oriented plane formed by pa, pb and pc.
NEGATIVE=-1 if pd is "above" the plane.
COPLANAR=0 if pd is on the plane.

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(orient3d)
npe_doc(ds_orient3d)

npe_arg(pa, dense_float, dense_double)
npe_arg(pb, npe_matches(pa))
npe_arg(pc, npe_matches(pa))
npe_arg(pd, npe_matches(pa))
npe_begin_code()
    assert_size_equals(pa, 3, "pa");
    assert_size_equals(pb, 3, "pb");
    assert_size_equals(pc, 3, "pc");
    assert_size_equals(pd, 3, "pd");

    using Scalar = typename npe_Matrix_pa::Scalar;
    using MatType = Eigen::Matrix<Scalar, 3, 1>;

    Eigen::Map<MatType> pa_tmp(&pa(0, 0), pa.size());
    Eigen::Map<MatType> pb_tmp(&pb(0, 0), pb.size());
    Eigen::Map<MatType> pc_tmp(&pc(0, 0), pc.size());
    Eigen::Map<MatType> pd_tmp(&pd(0, 0), pd.size());

    igl::predicates::exactinit();
    return int(igl::predicates::orient3d(pa_tmp, pb_tmp, pc_tmp, pd_tmp));

npe_end_code()





const char *ds_incircle = R"igl_Qu8mg5v7(
Decide whether a point is inside/outside/on a circle.

Parameters
----------
pa, pb, pc  2D points that defines an oriented circle.
pd          2D query point.

Returns
-------
INSIDE=1 if pd is inside of the circle defined by pa, pb and pc.
OUSIDE=-1 if pd is outside of the circle.
COCIRCULAR=0 pd is exactly on the circle.

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(incircle)
npe_doc(ds_incircle)

npe_arg(pa, dense_float, dense_double)
npe_arg(pb, npe_matches(pa))
npe_arg(pc, npe_matches(pa))
npe_arg(pd, npe_matches(pa))
npe_begin_code()
    assert_size_equals(pa, 2, "pa");
    assert_size_equals(pb, 2, "pb");
    assert_size_equals(pc, 2, "pc");
    assert_size_equals(pd, 2, "pd");

    using Scalar = typename npe_Matrix_pa::Scalar;
    using MatType = Eigen::Matrix<Scalar, 2, 1>;

    Eigen::Map<MatType> pa_tmp(&pa(0, 0), pa.size());
    Eigen::Map<MatType> pb_tmp(&pb(0, 0), pb.size());
    Eigen::Map<MatType> pc_tmp(&pc(0, 0), pc.size());
    Eigen::Map<MatType> pd_tmp(&pd(0, 0), pd.size());

    igl::predicates::exactinit();
    return int(igl::predicates::incircle(pa_tmp, pb_tmp, pc_tmp, pd_tmp));

npe_end_code()



const char *ds_insphere = R"igl_Qu8mg5v7(

Decide whether a point is inside/outside/on a sphere.

Parameters
----------
pa, pb, pc, pd  3D points that defines an oriented sphere.
pe              3D query point.

Returns
-------

INSIDE=1 if pe is inside of the sphere defined by pa, pb, pc and pd.
OUSIDE=-1 if pe is outside of the sphere.
COSPHERICAL=0 pe is exactly on the sphere.

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(insphere)
npe_doc(ds_insphere)

npe_arg(pa, dense_float, dense_double)
npe_arg(pb, npe_matches(pa))
npe_arg(pc, npe_matches(pa))
npe_arg(pd, npe_matches(pa))
npe_arg(pe, npe_matches(pa))

npe_begin_code()
    assert_size_equals(pa, 3, "pa");
    assert_size_equals(pb, 3, "pb");
    assert_size_equals(pc, 3, "pc");
    assert_size_equals(pd, 3, "pd");
    assert_size_equals(pe, 3, "pe");

    using Scalar = typename npe_Matrix_pa::Scalar;
    using MatType = Eigen::Matrix<Scalar, 3, 1>;

    Eigen::Map<MatType> pa_tmp(&pa(0, 0), pa.size());
    Eigen::Map<MatType> pb_tmp(&pb(0, 0), pb.size());
    Eigen::Map<MatType> pc_tmp(&pc(0, 0), pc.size());
    Eigen::Map<MatType> pd_tmp(&pd(0, 0), pd.size());
    Eigen::Map<MatType> pe_tmp(&pe(0, 0), pe.size());

    igl::predicates::exactinit();
    return int(igl::predicates::insphere(pa_tmp, pb_tmp, pc_tmp, pd_tmp, pe_tmp));

npe_end_code()