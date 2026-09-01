# Changelog

All notable, user-facing changes to the `libigl` Python bindings are recorded
here. The project loosely follows [Semantic Versioning](https://semver.org) and
version numbers match the [PyPI releases](https://pypi.org/project/libigl/#history).

> Historical note: releases up to and including 2.6.2 were published to PyPI
> without matching git tags or GitHub releases (see #235). Starting with 2.6.3,
> pushing a version bump to `main` automatically creates the git tag, the GitHub
> release, and the PyPI upload together (#313). The 2.6.3 section below therefore
> folds in changes first shipped in the tag-less interim 2.6.2 release, i.e. it
> covers everything since the last tagged release, 2.6.1.

## 2.6.3 — 2026-08-31

### Added

New function bindings:

- **Distances & closest points:** `simplex_simplex_squared_distance`,
  `point_simplex_squared_distance`, `offset_surface`.
- **Rotations / ARAP:** `polar_svd3x3`, `fit_rotations`.
- **Quad meshes:** `quad_planarity`, `planarize_quad_mesh`, `quad_edges`.
- **Curves & mesh topology:** `ramer_douglas_peucker`, `path_to_edges`,
  `connect_boundary_to_infinity`, `smooth_corner_adjacency`,
  `per_face_normals_stable`, `resolve_duplicated_faces`, `vertex_components`,
  `is_vertex_manifold`, `is_intrinsic_delaunay`.
- **Remeshing:** `triangle.remesh_at_points`.
- **Winding numbers & distance fields:** `swept_volume`,
  `swept_volume_bounding_box`, `swept_volume_signed_distance`,
  point-cloud and pre-built-tree support for `fast_winding_number`,
  `lipschitz_octree`, `unique_sparse_voxel_corners`, and an edge→vertex (`E2V`)
  output for sparse `marching_cubes`.
- **Ambient occlusion:** core `ambient_occlusion` binding.
- **Solvers & energies:** `active_set`, `boundary_conditions`,
  `harmonic_integrated_from_laplacian_and_mass`, Hessian and Hessian-energy
  operators, and cross-field bindings.
- **Bounding boxes:** oriented-bounding-box functions, `bounding_box_diagonal`.
- **Curves & predicates:** cubic Bézier evaluation and roots, additional
  `igl::predicates` bindings, `igl::spectra` bindings, and
  `lexicographic_triangulation`.
- **Misc:** `centroid`, a `face_areas` overload taking intrinsic edge lengths,
  and an optional `seed` parameter for `random_points_on_mesh`.

### Changed

- Bumped the bundled libigl to
  [`f68f01c2`](https://github.com/libigl/libigl/commit/f68f01c23ac82351e2543ce8c529b6d4c89fdf16).
- `cycodebase` distance queries can now reuse a prebuilt AABB tree / precomputed
  bases for fast repeated queries.
- Releases are now cut by pushing a version bump to `main`, which tags the
  commit and creates the GitHub release and PyPI upload in one step (#313).

### Packaging / CI

- Added CPython 3.13 wheels.
- Switched the Linux CI builds to Clang to fix a 2.6.1 performance regression.
- Bumped `pypa/gh-action-pypi-publish` to 1.13.0.

## 2.6.2 — PyPI only

Interim release published to PyPI on 2025 without a git tag or GitHub release.
Its changes are folded into the 2.6.3 entry above.

## 2.6.1 — 2025-05-15

Last release before this changelog was introduced. See the
[git history](https://github.com/libigl/libigl-python-bindings/commits/2.6.1)
and the [PyPI release history](https://pypi.org/project/libigl/#history) for
earlier changes.
