# Documentation site

The Python-bindings documentation is a [Material for MkDocs](https://squidfunk.github.io/mkdocs-material/)
site. The API reference is generated from the compiled package's `.pyi` type
stubs, so it always matches what is actually bound.

## Build locally

```bash
python -m pip install .                       # build/install the bindings (produces the .pyi stubs)
python -m pip install -r website/requirements.txt
python website/generate_api.py \
    --package "$(python -c 'import igl, os; print(os.path.dirname(igl.__file__))')" \
    --igl-include <path-to>/libigl/include \
    --out website/docs/api
cd website && python -m mkdocs serve
```

`--igl-include` points at a libigl `include/` tree and is optional: it is used
only to decide which functions get a C++ Doxygen cross-link. When building the
bindings from source, CMake fetches libigl under `build*/_deps/libigl-src`.

The generated `website/docs/api/*.md` pages and the built `website/site/` are
not committed; CI regenerates them.
