# Verify skill for libigl-python-bindings

## Handle
- Python is `.venv/bin/python` (system python3 is externally-managed)
- Build: `CMAKE_BUILD_PARALLEL_LEVEL=10 .venv/bin/python -m pip install --no-build-isolation --config-settings=editable.rebuild=true -Cbuild-dir=build -ve .`
- Build output is noisy (cmake install lines); real output comes at the end

## Surface
Library. Drive via `import igl` — **not** via test file. Example:
```python
.venv/bin/python -c "import igl, numpy as np; ..."
```

## Gotchas
- `ambient_occlusion` is in core `igl` (not `igl.embree`), backed by Embree but exposed in the main module
- Build triggers a cmake rebuild on every `pip install` invocation even when up to date — this is expected
- `resolve_duplicated_faces`: two same-orientation duplicates → libigl returns empty (not 2); this is C++ library behavior
