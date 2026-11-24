"""Check signed-distance precision dispatch and analytic geometry."""

import numpy as np
import pytest
import igl


def tetrahedron(dtype):
    vertices = np.array([[0, 0, 0], [1, 0, 0], [0, 1, 0], [0, 0, 1]], dtype=dtype)
    faces = np.array([[0, 1, 3], [0, 2, 1], [0, 3, 2], [1, 2, 3]], dtype=np.int64)
    return vertices, faces


@pytest.mark.parametrize("dtype", [np.float32, np.float64])
@pytest.mark.parametrize("index_dtype", [np.int32, np.int64])
@pytest.mark.parametrize("layout", ["C", "F", "strided"])
def test_signed_distance_precision(dtype, index_dtype, layout):
    """Preserve floating-point precision through face, edge, and vertex queries."""
    vertices, faces = tetrahedron(dtype)
    points = np.array([[0.125, 0.125, 0.125], [0.25, 0.25, -1],
                       [0.5, -1, -1], [-1, -1, -1]], dtype=dtype)
    if layout == "strided":
        vertices = np.repeat(vertices, 2, axis=1)[:, ::2]
        points = np.repeat(points, 2, axis=1)[:, ::2]
    else:
        vertices = np.array(vertices, order=layout)
        points = np.array(points, order=layout)
    faces = faces.astype(index_dtype)
    vertices.flags.writeable = False
    points.flags.writeable = False
    distance, indices, closest, normals = igl.signed_distance(
        points, vertices, faces, igl.SIGNED_DISTANCE_TYPE_PSEUDONORMAL
    )
    for output in [distance, closest, normals]:
        assert output.dtype == dtype
        assert np.isfinite(output).all()
    assert indices.dtype == np.int64
    np.testing.assert_allclose(distance, [-0.125, 1, np.sqrt(2), np.sqrt(3)],
                               rtol=8*np.finfo(dtype).eps)
    np.testing.assert_array_equal(np.sign(distance), [-1, 1, 1, 1])


@pytest.mark.parametrize("point_dtype,vertex_dtype", [
    (np.float32, np.float64), (np.float64, np.float32),
    (np.float16, np.float16),
])
def test_signed_distance_default_conversion(point_dtype, vertex_dtype):
    """Preserve double conversion for mixed and lower-precision arrays."""
    vertices, faces = tetrahedron(vertex_dtype)
    points = np.array([[0.125, 0.125, 0.125]], dtype=point_dtype)
    distance, _, closest, normals = igl.signed_distance(
        points, vertices, faces, sign_type=igl.SIGNED_DISTANCE_TYPE_PSEUDONORMAL
    )
    for output in [distance, closest, normals]:
        assert output.dtype == np.float64
    np.testing.assert_allclose(distance, [-0.125])


@pytest.mark.parametrize("dtype", [np.float32, np.float64])
@pytest.mark.parametrize("sign_type", [igl.SIGNED_DISTANCE_TYPE_DEFAULT,
    igl.SIGNED_DISTANCE_TYPE_WINDING_NUMBER, igl.SIGNED_DISTANCE_TYPE_FAST_WINDING_NUMBER,
    igl.SIGNED_DISTANCE_TYPE_UNSIGNED])
def test_signed_distance_methods(dtype, sign_type):
    """Keep every existing sign method callable for both precisions."""
    vertices, faces = tetrahedron(dtype)
    points = np.array([[0.125, 0.125, 0.125], [-0.125, -0.125, -0.125]], dtype=dtype)
    distance, _, closest, normals = igl.signed_distance(points, vertices, faces, sign_type)
    assert distance.dtype == closest.dtype == normals.dtype == dtype
    expected = [0.125 if sign_type == igl.SIGNED_DISTANCE_TYPE_UNSIGNED else -0.125, np.sqrt(3)/8]
    np.testing.assert_allclose(distance, expected, rtol=2e-6)


@pytest.mark.parametrize("dtype", [np.float32, np.float64])
def test_signed_distance_2d_and_bounds(dtype):
    """Handle 2D pseudonormals and finite query bounds in the requested precision."""
    vertices = np.array([[0, 0], [1, 0], [0, 1]], dtype=dtype)
    edges = np.array([[0, 1], [1, 2], [2, 0]], dtype=np.int64)
    points = np.array([[0.25, 0.25], [0.5, -1]], dtype=dtype)
    distance, _, _, _ = igl.signed_distance(points, vertices, edges,
        igl.SIGNED_DISTANCE_TYPE_PSEUDONORMAL, lower_bound=-0.5, upper_bound=0.5)
    assert distance.dtype == dtype
    np.testing.assert_allclose(distance[0], -0.25)
    assert np.isnan(distance[1])


def test_signed_distance_float_arithmetic():
    """Distinguish float arithmetic from double evaluation followed by a cast."""
    vertices, faces = tetrahedron(np.float32)
    points = np.array([[-0.1, -0.4, -0.7]], dtype=np.float32)
    distance, _, _, _ = igl.signed_distance(points, vertices, faces,
                                           igl.SIGNED_DISTANCE_TYPE_PSEUDONORMAL)
    expected = np.sqrt(np.sum(points[0]*points[0], dtype=np.float32))
    double_then_cast = np.float32(np.linalg.norm(points[0].astype(np.float64)))
    assert expected != double_then_cast
    np.testing.assert_array_equal(distance, [expected])
