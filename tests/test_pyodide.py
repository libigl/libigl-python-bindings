"""Runtime and wheel-content regressions for the WebAssembly distribution."""

import ast
import importlib
from pathlib import Path
import sys

import numpy as np
import pytest


pytestmark = pytest.mark.skipif(sys.platform != "emscripten", reason="Pyodide wheel tests")


@pytest.mark.parametrize("module", [
    "igl.pyigl_core",
    "igl.copyleft.pyigl_copyleft_core",
    "igl.copyleft.cgal.pyigl_copyleft_cgal",
    "igl.copyleft.tetgen.pyigl_copyleft_tetgen",
    "igl.embree.pyigl_embree",
    "igl.triangle.pyigl_restricted_triangle",
    "igl.spectra.pyigl_spectra",
    "igl.predicates.pyigl_predicates",
    "igl.cycodebase.pyigl_cycodebase",
])
def test_module_and_stub_are_installed(module):
    extension = importlib.import_module(module)
    stub = Path(extension.__file__).with_name(module.rsplit(".", 1)[-1] + ".pyi")
    tree = ast.parse(stub.read_text())
    assert any(isinstance(node, (ast.FunctionDef, ast.ClassDef)) for node in tree.body)


def test_embree_ray_hits_and_misses():
    from igl.embree import EmbreeIntersector

    vertices = np.array([[0, 0, 0], [1, 0, 0], [0, 1, 0]], dtype=np.float64)
    faces = np.array([[0, 1, 2]], dtype=np.int64)
    intersector = EmbreeIntersector()
    intersector.init(vertices, faces)
    direction = np.array([0, 0, -1], dtype=np.float64)
    hit = intersector.intersectRay_first(np.array([0.25, 0.25, 1]), direction)
    assert hit == pytest.approx((0, 1, 0.25, 0.25))
    miss = intersector.intersectRay_first(np.array([2., 2., 1.]), direction)
    assert miss[0] == -1


@pytest.mark.parametrize("offset", [0.5, 2.0 ** -40])
@pytest.mark.parametrize("operation", ["union", "intersection", "difference"])
def test_cgal_boolean_volume_with_coplanar_faces(offset, operation):
    from igl.copyleft.cgal import mesh_boolean

    vertices = np.array([
        [0, 0, 0], [1, 0, 0], [1, 1, 0], [0, 1, 0],
        [0, 0, 1], [1, 0, 1], [1, 1, 1], [0, 1, 1],
    ], dtype=np.float64)
    faces = np.array([
        [0, 2, 1], [0, 3, 2], [4, 5, 6], [4, 6, 7],
        [0, 1, 5], [0, 5, 4], [1, 2, 6], [1, 6, 5],
        [2, 3, 7], [2, 7, 6], [3, 0, 4], [3, 4, 7],
    ], dtype=np.int64)
    shifted = vertices + np.array([offset, 0, 0])
    if offset == 0.5:
        result_vertices, result_faces, _ = mesh_boolean(
            vertices, faces, shifted, faces, operation,
        )
    else:
        result_vertices, result_faces, _ = mesh_boolean(
            vertices, faces, shifted, faces, type_str=operation,
        )
    triangles = result_vertices[result_faces]
    volume = np.einsum(
        "ij,ij->i", triangles[:, 0], np.cross(triangles[:, 1], triangles[:, 2]),
    ).sum() / 6
    expected = {"union": 1 + offset, "intersection": 1 - offset, "difference": offset}
    assert volume == pytest.approx(expected[operation], rel=1e-10, abs=1e-15)
