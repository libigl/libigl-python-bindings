"""Generate the Python API reference from the nanobind ``.pyi`` type stubs.

The stubs (emitted by ``nanobind_add_stub`` during the build) are the reliable
source of truth for compiled-module signatures: statically parsing them avoids
importing the extension and sidesteps the introspection quirks of compiled
modules. For every module we emit one Material-for-MkDocs page, and every
function that has a matching ``igl/<name>.h`` header is cross-linked to its C++
Doxygen page on libigl.github.io/dox so the Python and C++ references stay
coherent.

Usage:
    python website/generate_api.py \
        --package igl \
        --igl-include <path-to>/libigl/include \
        --out website/docs/api
"""
from __future__ import annotations

import argparse
import ast
import os
import re
from collections import Counter
from pathlib import Path

DOX_BASE = "https://libigl.github.io/dox"

# Human-facing titles for each module (path -> title). Anything not listed
# falls back to the dotted module name.
MODULE_TITLES = {
    "igl": "igl (core)",
    "igl.copyleft": "igl.copyleft",
    "igl.copyleft.cgal": "igl.copyleft.cgal",
    "igl.copyleft.tetgen": "igl.copyleft.tetgen",
    "igl.cycodebase": "igl.cycodebase",
    "igl.embree": "igl.embree",
    "igl.predicates": "igl.predicates",
    "igl.spectra": "igl.spectra",
    "igl.triangle": "igl.triangle",
}


def clean_annotation(node: ast.AST) -> str:
    """Turn a stub type annotation AST into a compact, readable string.

    nanobind array parameters are annotated as
    ``Annotated[ArrayLike, dict(dtype='float64', shape=(None, None), ...)]``;
    we render those as e.g. ``float64[m, n]``.
    """
    if node is None:
        return ""
    if isinstance(node, ast.Name):
        return node.id
    if isinstance(node, ast.Attribute):
        return f"{clean_annotation(node.value)}.{node.attr}"
    if isinstance(node, ast.Constant):
        return "None" if node.value is None else repr(node.value)
    if isinstance(node, ast.Tuple):
        return ", ".join(clean_annotation(e) for e in node.elts)
    if isinstance(node, ast.Subscript):
        base = clean_annotation(node.value)
        if base == "Annotated":
            return _clean_annotated(node.slice)
        return f"{base}[{clean_annotation(node.slice)}]"
    # Fallback: best-effort unparse.
    try:
        return ast.unparse(node)
    except Exception:
        return "Any"


def _clean_annotated(slice_node: ast.AST) -> str:
    """Render the payload of an ``Annotated[Base, dict(...)]`` array type."""
    elts = slice_node.elts if isinstance(slice_node, ast.Tuple) else [slice_node]
    dtype = None
    dims = None
    for elt in elts:
        if isinstance(elt, ast.Call):  # the dict(...) metadata
            for kw in elt.keywords:
                if kw.arg == "dtype" and isinstance(kw.value, ast.Constant):
                    dtype = kw.value.value
                elif kw.arg == "shape":
                    letters = ["m", "n", "p", "q"]
                    # A 1-D shape is emitted as `shape=(None)` (a bare value),
                    # a 2-D+ shape as a real tuple `shape=(None, None)`.
                    shape_elts = (kw.value.elts if isinstance(kw.value, ast.Tuple)
                                  else [kw.value])
                    dims = ", ".join(
                        letters[i] if isinstance(d, ast.Constant) and d.value is None
                        else clean_annotation(d)
                        for i, d in enumerate(shape_elts))
    if dtype and dims is not None:
        return f"{dtype}[{dims}]"
    if dtype:
        return f"{dtype}[...]"
    return "ArrayLike"


def render_signature(fn: ast.FunctionDef) -> str:
    """Render a def's argument list, dropping ``self`` and cleaning types."""
    a = fn.args
    parts = []
    defaults = [None] * (len(a.args) - len(a.defaults)) + list(a.defaults)
    for arg, default in zip(a.args, defaults):
        if arg.arg == "self":
            continue
        s = arg.arg
        if arg.annotation is not None:
            s += f": {clean_annotation(arg.annotation)}"
        if default is not None:
            s += f" = {clean_annotation(default)}"
        parts.append(s)
    ret = f" -> {clean_annotation(fn.returns)}" if fn.returns else ""
    return f"{fn.name}({', '.join(parts)}){ret}"


def _esc(text: str) -> str:
    """Escape a leading '#' so libigl's '#V'/'#E'/'#F' ("number of") notation
    isn't parsed as a Markdown heading (python-markdown accepts space-less
    '#heading'), which would otherwise pollute the table of contents."""
    return re.sub(r"^(\s*)(#+)", r"\1\\\2", text)


def format_docstring(doc: str) -> str:
    """Turn a doxygen-style docstring into Material markdown.

    The leading prose becomes the description; ``@param[in|out] name  text``
    lines become a Parameters list and ``@return`` becomes Returns.
    """
    if not doc:
        return "_No description available._\n"
    lines = [l.rstrip() for l in doc.strip("\n").splitlines()]
    desc, params, returns = [], [], []
    bucket = desc
    for line in lines:
        stripped = line.strip()
        if stripped.startswith("@param"):
            rest = stripped.split(None, 1)[1] if " " in stripped else ""
            params.append(rest)
            bucket = params
        elif stripped.startswith(("@return", "@returns")):
            rest = stripped.split(None, 1)[1] if " " in stripped else ""
            returns.append(rest)
            bucket = returns
        elif stripped.startswith("\\see") or stripped.startswith("@see"):
            bucket = None  # drop see-also cross-refs for now
        elif bucket is not None:
            if bucket is desc:
                bucket.append(line)
            elif stripped:  # continuation of a param/return entry
                bucket[-1] += " " + stripped

    out = []
    text = "\n".join(_esc(l) for l in desc).strip()
    if text:
        out.append(text + "\n")
    if params:
        out.append("**Parameters**\n")
        for p in params:
            name, _, rest = p.partition(" ")
            out.append(f"- `{name}` — {_esc(rest.strip())}")
        out.append("")
    if returns:
        out.append("**Returns**\n")
        for r in returns:
            out.append(f"- {_esc(r.strip())}")
        out.append("")
    return "\n".join(out) + "\n"


def module_for(stub: Path, package_parent: Path) -> str:
    """Dotted module name from a stub path (its parent dir under the package)."""
    rel = stub.parent.relative_to(package_parent)
    return ".".join(rel.parts)


def _split_top_level(argstr: str):
    """Split a signature argument list on top-level commas (bracket-aware)."""
    parts, depth, cur = [], 0, ""
    for ch in argstr:
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        if ch == "," and depth == 0:
            parts.append(cur)
            cur = ""
        else:
            cur += ch
    if cur.strip():
        parts.append(cur)
    return parts


def _repair_arg_order(src: str) -> str:
    """Give every argument a default once any earlier one has one.

    nanobind occasionally emits a required argument after an optional one
    (e.g. mesh_boolean's ``type_str``), which is not valid Python. Adding a
    synthetic ``= ...`` makes the stub parseable; such args render with ``...``.
    """
    open_i = src.find("(")
    if open_i < 0:
        return src
    depth, close_i = 0, -1
    for i in range(open_i, len(src)):
        if src[i] in "([{":
            depth += 1
        elif src[i] in ")]}":
            depth -= 1
            if depth == 0:
                close_i = i
                break
    if close_i < 0:
        return src
    args = _split_top_level(src[open_i + 1:close_i])
    seen_default = False
    fixed = []
    for i, a in enumerate(args):
        # Name any unnamed parameter (nanobind sometimes drops the name, e.g.
        # "(: Annotated[...]" when a binding omits the argument label).
        if a.lstrip().startswith(":"):
            lead = a[:len(a) - len(a.lstrip())]
            a = f"{lead}arg{i}{a.lstrip()}"
        has_default = "=" in _strip_brackets(a)
        if seen_default and not has_default and a.strip():
            a = a + " = ..."
            has_default = True
        seen_default = seen_default or has_default
        fixed.append(a)
    return src[:open_i + 1] + ",".join(fixed) + src[close_i:]


def _strip_brackets(s: str) -> str:
    """Remove bracketed spans so a top-level '=' can be detected."""
    out, depth = "", 0
    for ch in s:
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        elif depth == 0:
            out += ch
    return out


def _parse_tolerant(text: str):
    """Parse a stub, repairing the invalid signatures nanobind sometimes emits.

    Each stub signature is a single line, so we repair argument ordering on
    every ``def`` line (see _repair_arg_order) before parsing the whole file,
    which keeps ``@overload`` decorators attached to their functions.
    """
    try:
        return ast.parse(text).body
    except SyntaxError:
        pass
    repaired = []
    for line in text.splitlines(keepends=True):
        if line.lstrip().startswith("def ") and line.rstrip().endswith(":"):
            repaired.append(_repair_arg_order(line))
        else:
            repaired.append(line)
    try:
        return ast.parse("".join(repaired)).body
    except SyntaxError as e:
        print(f"  warning: stub still unparseable after repair: {e}")
        return []


def collect(stub: Path):
    """Return (functions, classes) from a stub, merging @overload groups."""
    functions, classes = {}, []
    for node in _parse_tolerant(stub.read_text()):
        if isinstance(node, ast.FunctionDef):
            functions.setdefault(node.name, []).append(node)
        elif isinstance(node, ast.ClassDef):
            methods = [n for n in node.body if isinstance(n, ast.FunctionDef)
                       and not n.name.startswith("__")]
            classes.append((node, methods, ast.get_docstring(node)))
    return functions, classes


def dox_filename(name: str) -> str:
    """Doxygen file-reference page filename for igl/<name>.h.

    Doxygen mangles the output name by turning '.h' into '_8h' and doubling
    every underscore; case is preserved (e.g. marching_cubes.h ->
    marching__cubes_8h.html, AABB.h -> AABB_8h.html)."""
    return f"{name.replace('_', '__')}_8h.html"


def cpp_chip(name: str, linkable: dict) -> str:
    """A standalone C++ cross-link line placed under a heading.

    Kept out of the heading itself so it does not leak into the table of
    contents. `linkable` maps a Python function/class name to its verified
    Doxygen page filename; only names present there are linked, so we never
    emit a 404 (see build of `linkable` in main)."""
    page = linkable.get(name)
    if page:
        return f"[C++ reference]({DOX_BASE}/{page}){{ .cpp-xref }}\n"
    return ""


def emit_function(name, defs, linkable) -> str:
    out = [f"### {name}\n"]
    chip = cpp_chip(name, linkable)
    if chip:
        out.append(chip)
    seen = set()
    for fn in defs:
        sig = render_signature(fn)
        out.append(f"```python\n{sig}\n```\n")
        doc = ast.get_docstring(fn)
        if doc and doc not in seen:
            seen.add(doc)
            out.append(format_docstring(doc))
    return "\n".join(out)


def emit_class(node, methods, doc, linkable) -> str:
    out = [f"### {node.name}\n"]
    chip = cpp_chip(node.name, linkable)
    if chip:
        out.append(chip)
    if doc:
        out.append(format_docstring(doc))
    for m in methods:
        out.append(f"#### {node.name}.{m.name}\n")
        out.append(f"```python\n{render_signature(m)}\n```\n")
        mdoc = ast.get_docstring(m)
        if mdoc:
            out.append(format_docstring(mdoc))
    return "\n".join(out)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--package", default="igl", help="path to the igl package dir")
    ap.add_argument("--igl-include", default="", help="path to libigl include/ dir")
    ap.add_argument("--dox-index", default="",
                    help="Doxygen files.html (or any page listing) for the "
                         "target /dox/ site; links are validated against it so "
                         "none 404. Omit to link by header-name heuristic only.")
    ap.add_argument("--out", default="website/docs/api")
    args = ap.parse_args()

    package = Path(args.package).resolve()
    package_parent = package.parent
    out = Path(args.out)
    out.mkdir(parents=True, exist_ok=True)

    # Cross-link a function to its C++ Doxygen page only when its header basename
    # is unique across the whole libigl tree — duplicated names (e.g.
    # marching_cubes exists in both igl/ and igl/copyleft/) get disambiguated by
    # Doxygen into non-derivable page names, so we skip them.
    unique = set()
    if args.igl_include:
        counts = Counter(h.stem for h in Path(args.igl_include).glob("igl/**/*.h"))
        unique = {stem for stem, c in counts.items() if c == 1}

    # When a Doxygen index is supplied, additionally require that the derived
    # page actually exists there. This keeps the preview free of 404s even when
    # the deployed /dox/ lags the bindings' libigl version (new/renamed headers).
    dox_pages = None
    if args.dox_index:
        dox_pages = set(re.findall(r"[A-Za-z0-9_]+_8h\.html",
                                   Path(args.dox_index).read_text()))

    linkable = {}
    for name in unique:
        page = dox_filename(name)
        if dox_pages is None or page in dox_pages:
            linkable[name] = page
    print(f"  cross-linkable functions: {len(linkable)}"
          + (f" (validated against {len(dox_pages)} dox pages)" if dox_pages else ""))

    stubs = sorted(package.rglob("pyigl_*.pyi"))
    index_rows = []
    for stub in stubs:
        module = module_for(stub, package_parent)
        title = MODULE_TITLES.get(module, module)
        functions, classes = collect(stub)
        page = [f"# {title}\n"]
        page.append(f"Python API reference for `{module}`.\n")
        for name in sorted(functions):
            page.append(emit_function(name, functions[name], linkable))
        for node, methods, doc in sorted(classes, key=lambda c: c[0].name):
            page.append(emit_class(node, methods, doc, linkable))
        fname = module.replace(".", "_") + ".md"
        (out / fname).write_text("\n".join(page))
        n = len(functions) + len(classes)
        index_rows.append((title, fname, n))
        print(f"  {module}: {len(functions)} functions, {len(classes)} classes -> {fname}")

    # An index page listing every module.
    idx = ["# API Reference\n",
           "Auto-generated from the compiled bindings' type stubs. Functions with "
           "a C++ counterpart link to the [C++ Doxygen reference]"
           f"({DOX_BASE}/).\n",
           "| Module | Symbols |", "| --- | --- |"]
    for title, fname, n in index_rows:
        idx.append(f"| [{title}]({fname}) | {n} |")
    (out / "index.md").write_text("\n".join(idx) + "\n")
    print(f"Wrote {len(stubs)} module pages + index to {out}")


if __name__ == "__main__":
    main()
