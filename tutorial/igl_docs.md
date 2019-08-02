## Functions

### **`adjacency_list(f: array)`**
Constructs the graph adjacency list of a given mesh (v, f)

| | |
|-|-|
|Parameters| f : \#f by dim array of fixed dimensional (e.g. triangle (\#f by 3),</br>tet (\#f by 4), quad (\#f by 4), etc...) mesh faces |
|Returns| list of lists containing at index i the adjacent vertices of vertex i |
|See also| adjacency_matrix |

**Examples**
```python
# Mesh in (v, f)
 a = mesh_adjacency_list(f)
igl.adjacency_matrix = adjacency_matrix(...) method of builtins.PyCapsule instance
```

### **`adjacency_matrix(f: array)`**
Constructs the graph adjacency matrix of a given mesh (v, f).

| | |
|-|-|
|Parameters| f : \#f by dim list of mesh simplices |
|Returns| a : max(f) by max(f) cotangent matrix, each row i corresponding to v(i, :) |
|See also| adjacency_list, edges, cotmatrix, diag |

**Examples**
```python
# Mesh in (v, f)
 a = adjacency_matrix(f)
# Sum each row
 a_sum = np.sum(a, axis=1)
# Convert row sums into diagonal of sparse matrix
 a_diag = diag(a_sum)
# Build uniform laplacian
 u = a - a_diag
igl.ambient_occlusion = ambient_occlusion(...) method of builtins.PyCapsule instance
```

### **`ambient_occlusion(v: array, f: array, p: array, n: array, num_samples: int)`**

| | |
|-|-|
|Parameters| V  \#V by 3 list of mesh vertex positions</br>F  \#F by 3 list of mesh face indices into V</br>P  \#P by 3 list of origin points</br>N  \#P by 3 list of origin normals |
|Returns| S  \#P list of ambient occusion values between 1 (fully occluded) and 0 (not occluded) |

**Examples**
```python
igl.arap_linear_block = arap_linear_block(...) method of builtins.PyCapsule instance
```

### **`arap_linear_block(v: array, f: array, d: int, energy: int)`**
Constructs a block of the matrix which constructs the
linear terms of a given arap energy. When treating rotations as knowns
(arranged in a column), then this constructs Kd of K such that the linear
portion of the energy is as a column:
K * R = [Kx Z  ... Ky Z  ...
Z  Kx ... Z  Ky ...
... ]
These blocks are also used to build the "covariance scatter matrices".
Here we want to build a scatter matrix that multiplies against positions
(treated as known) producing covariance matrices to fit each rotation.
Notice that in the case of the RHS of the poisson solve the rotations are
known and the positions unknown, and vice versa for rotation fitting.
These linear block just relate the rotations to the positions, linearly in
each.

| | |
|-|-|
|Parameters| v : \#v by dim list of initial domain positions</br>f : \#f by \#simplex size list of triangle indices into V</br>d : coordinate of linear constructor to build |
|Returns| \#v by \#v/\#f block of the linear constructor matrix corresponding to coordinate d |
|See also| arap, arap_dof |

**Examples**
```python
igl.arap_linear_block_elements = arap_linear_block_elements(...) method of builtins.PyCapsule instance
```

### **`arap_linear_block_elements(v: array, f: array, d: int)`**
Constructs a block of the matrix which constructs the
linear terms of a given arap energy. When treating rotations as knowns
(arranged in a column), then this constructs Kd of K such that the linear
portion of the energy is as a column:
K * R = [Kx Z  ... Ky Z  ...
Z  Kx ... Z  Ky ...
... ]
These blocks are also used to build the "covariance scatter matrices".
Here we want to build a scatter matrix that multiplies against positions
(treated as known) producing covariance matrices to fit each rotation.
Notice that in the case of the RHS of the poisson solve the rotations are
known and the positions unknown, and vice versa for rotation fitting.
These linear block just relate the rotations to the positions, linearly in
each.

| | |
|-|-|
|Parameters| v : \#v by dim list of initial domain positions</br>f : \#f by \#simplex size list of triangle indices into V</br>d : coordinate of linear constructor to build |
|Returns| \#v by \#v/\#f block of the linear constructor matrix corresponding to coordinate d |
|See also| arap, arap_dof |

**Examples**
```python
igl.arap_linear_block_spokes = arap_linear_block_spokes(...) method of builtins.PyCapsule instance
```

### **`arap_linear_block_spokes(v: array, f: array, d: int)`**
Constructs a block of the matrix which constructs the
linear terms of a given arap energy. When treating rotations as knowns
(arranged in a column), then this constructs Kd of K such that the linear
portion of the energy is as a column:
K * R = [Kx Z  ... Ky Z  ...
Z  Kx ... Z  Ky ...
... ]
These blocks are also used to build the "covariance scatter matrices".
Here we want to build a scatter matrix that multiplies against positions
(treated as known) producing covariance matrices to fit each rotation.
Notice that in the case of the RHS of the poisson solve the rotations are
known and the positions unknown, and vice versa for rotation fitting.
These linear block just relate the rotations to the positions, linearly in
each.

| | |
|-|-|
|Parameters| v : \#v by dim list of initial domain positions</br>f : \#f by \#simplex size list of triangle indices into V</br>d : coordinate of linear constructor to build |
|Returns| \#v by \#v/\#f block of the linear constructor matrix corresponding to coordinate d |
|See also| arap, arap_dof |

**Examples**
```python
igl.arap_linear_block_spokes_and_rims = arap_linear_block_spokes_and_rims(...) method of builtins.PyCapsule instance
```

### **`arap_linear_block_spokes_and_rims(v: array, f: array, d: int)`**
Constructs a block of the matrix which constructs the
linear terms of a given arap energy. When treating rotations as knowns
(arranged in a column), then this constructs Kd of K such that the linear
portion of the energy is as a column:
K * R = [Kx Z  ... Ky Z  ...
Z  Kx ... Z  Ky ...
... ]
These blocks are also used to build the "covariance scatter matrices".
Here we want to build a scatter matrix that multiplies against positions
(treated as known) producing covariance matrices to fit each rotation.
Notice that in the case of the RHS of the poisson solve the rotations are
known and the positions unknown, and vice versa for rotation fitting.
These linear block just relate the rotations to the positions, linearly in
each.

| | |
|-|-|
|Parameters| v : \#v by dim list of initial domain positions</br>f : \#f by \#simplex size list of triangle indices into V</br>d : coordinate of linear constructor to build |
|Returns| \#v by \#v/\#f block of the linear constructor matrix corresponding to coordinate d |
|See also| arap, arap_dof |

**Examples**
```python
igl.arap_rhs = arap_rhs(...) method of builtins.PyCapsule instance
```

### **`arap_rhs(v: array, f: array, d: int, energy: int)`**
Guild right-hand side constructor of global poisson solve for various ARAP energies
Inputs:
Outputs:
K  #V*dim by #(FV)*dim*dim matrix such that:
b = K * reshape(permute(R,[3 1 2]),size(VF,1)*size(V,2)*size(V,2),1);

| | |
|-|-|
|Parameters| v : \#v by Vdim list of initial domain positions</br>f : \#f by 3 list of triangle indices into v</br>d : dimension being used at solve time. For deformation usually dim = V.cols(), for surface parameterization V.cols() = 3 and dim = 2</br>energy : ARAPEnergyType enum value defining which energy is being used. See igl.ARAPEnergyType for valid options and explanations. |
|Returns| \#v*d by \#(fv)*dim*dim matrix such that: b = K * reshape(permute(R,[3 1 2]),size(VF,1)*size(V,2)*size(V,2),1); |
|See also| arap_linear_block, arap |

**Examples**
```python
igl.average_onto_vertices = average_onto_vertices(...) method of builtins.PyCapsule instance
```

### **`average_onto_vertices(v: array, f: array, s: array)`**
Move a scalar field defined on faces to vertices by averaging

| | |
|-|-|
|Parameters| v : \#v by vdim array of mesh vertices</br>f : \#f by simplex_count array of simplex indices</br>s : \#f by dim scalar field defined on simplices |
|Returns| \#v by dim scalar field defined on vertices |
|See also| average_onto_faces |

**Examples**
```python
igl.avg_edge_length = avg_edge_length(...) method of builtins.PyCapsule instance
```

### **`avg_edge_length(v: array, f: array) -> float`**
Compute the average edge length for the given triangle mesh.

| | |
|-|-|
|Parameters| v : array_like \#v by 3 vertex array</br>f : f \#f by simplex-size list of mesh faces (must be simplex) |
|Returns| l : average edge length |
|See also| adjacency_matrix |

**Examples**
```python
# Mesh in (v, f)
 length = avg_edge_length(v, f)
igl.barycenter = barycenter(...) method of builtins.PyCapsule instance
```

### **`barycenter(v: array, f: array)`**
Compute the barycenter of every simplex

| | |
|-|-|
|Parameters| v : \#v x dim matrix of vertex coordinates</br>f : \#f x simplex_size  matrix of indices of simplex corners into V |
|Returns| A \#f x dim matrix where each row is the barycenter of each simplex |

**Examples**
```python
igl.barycentric_coordinates_tet = barycentric_coordinates_tet(...) method of builtins.PyCapsule instance
```

### **`barycentric_coordinates_tet(p: array, a: array, b: array, c: array, d: array)`**
Compute barycentric coordinates in a tet corresponding to the Euclidean coordinates in `p`.
The input arrays `a`, `b`, `c` and `d` are the vertices of each tet. I.e. one tet is
`a[i, :], b[i, :], c[i, :], d[:, i]`.

| | |
|-|-|
|Parameters| p : \#P by 3 Query points in 3d</br>a : \#P by 3 Tet corners in 3d</br>b : \#P by 3 Tet corners in 3d</br>c : \#P by 3 Tet corners in 3d</br>d : \#P by 3 Tet corners in 3d |
|Returns| \#P by 4 list of barycentric coordinates |

**Examples**
```python
igl.barycentric_coordinates_tri = barycentric_coordinates_tri(...) method of builtins.PyCapsule instance
```

### **`barycentric_coordinates_tri(p: array, a: array, b: array, c: array)`**
Compute barycentric coordinates in a triangle corresponding to the Euclidean coordinates in `p`.
The input arrays `a`, `b`, and `c` are the vertices of each triangle. I.e. one triangle is
`a[i, :], b[i, :], c[i, :]`.

| | |
|-|-|
|Parameters| p : \#P by 3 Query points in 3d</br>a : \#P by 3 Tri corners in 3d</br>b : \#P by 3 Tri corners in 3d</br>c : \#P by 3 Tri corners in 3d |
|Returns| \#P by 3 list of barycentric coordinates |

**Examples**
```python
igl.bfs = bfs(...) method of builtins.PyCapsule instance
```

### **`bfs(A: sparse_matrix, s: int)`**
Construct an array indexing into a **directed** graph represented by an adjacency list using
breadth first search. I.e. the output is an array of vertices in breadth-first order.

| | |
|-|-|
|Parameters| A : \#V list of adjacency lists  or \#V by \#V adjacency matrix</br>s : starting node (index into A) |
|Returns| A tuple, (d, p) where:</br>* d is a \#V list of indices into rows of A in the order in which graph nodes are discovered</br>* p is a \#V list of indices of A of predecsors where -1 indicates root/not discovered. I.e.</br>p[i] is the index of the vertex v which preceded d[i] in the breadth first traversal.</br>Note that together, (d, p) form a spanning tree of the input graph |

**Examples**
```python
 V, F, _ = igl.readOFF("test.off)
 A = igl.adjacency_matrix(V, F)
 d, p = igl.bfs(A, V[0])
igl.bfs_orient = bfs_orient(...) method of builtins.PyCapsule instance
```

### **`bfs_orient(f: array)`**
Consistently orient faces in orientable patches using BFS.

| | |
|-|-|
|Parameters| f : \#F by 3 list of faces |
|Returns| A tuple, (ff, c) where:</br>* ff is a \#F by 3 list of faces which are consistently oriented with</br>* c is a \#F array of connected component ids |

**Examples**
```python
 v, f, _ = igl.readOFF("test.off)
 ff, c = igl.bfs_orient(f)
igl.bone_parents = bone_parents(...) method of builtins.PyCapsule instance
```

### **`bone_parents(be: array)`**
BONE_PARENTS Recover "parent" bones from directed graph representation.

| | |
|-|-|
|Parameters| BE  \#BE by 2 list of directed bone edges |
|Returns| P  \#BE by 1 list of parent indices into BE, -1 means root. |

**Examples**
```python
igl.boundary_facets = boundary_facets(...) method of builtins.PyCapsule instance
```

### **`boundary_facets(t: array)`**
Determine boundary faces (edges) of tetrahedra (triangles).

| | |
|-|-|
|Parameters| t : tetrahedron or triangle index list, m by 4/3, where m is the number of tetrahedra/triangles |
|Returns| f : list of boundary faces, n by 3/2, where n is the number of boundary faces/edges |

**Examples**
```python
# Mesh in (v, f)
 b = boundary_facets(f)
igl.boundary_loop = boundary_loop(...) method of builtins.PyCapsule instance
```

### **`boundary_loop(f: array)`**
Compute ordered boundary loops for a manifold mesh and return the longest loop in terms of vertices.

| | |
|-|-|
|Parameters| f : \#v by dim array of mesh faces |
|Returns| l : ordered list of boundary vertices of longest boundary loop |

**Examples**
```python
# Mesh in (v, f)
l = boundary_loop(f)
igl.bounding_box = bounding_box(...) method of builtins.PyCapsule instance
```

### **`bounding_box(*args, **kwargs)`**

### **`bounding_box(v: array)`**
Build a triangle mesh of the bounding box of a given list of vertices

| | |
|-|-|
|Parameters| V  \#V by dim list of rest domain positions |
|Returns| BV  2^dim by dim list of bounding box corners positions</br>BF  \#BF by dim list of simplex facets |

### **`bounding_box(v: array, pad: float)`**
Build a triangle mesh of the bounding box of a given list of vertices

| | |
|-|-|
|Parameters| V  \#V by dim list of rest domain positions |
|Returns| BV  2^dim by dim list of bounding box corners positions</br>BF  \#BF by dim list of simplex facets |

**Examples**
```python
igl.bounding_box_diagonal = bounding_box_diagonal(...) method of builtins.PyCapsule instance
```

### **`bounding_box_diagonal(v: array) -> float`**
Compute the length of the diagonal of a given meshes axis-aligned bounding

| | |
|-|-|
|Parameters| V  \#V by 3 list of vertex positions |
|Returns| Returns length of bounding box diagonal |

**Examples**
```python
igl.circumradius = circumradius(...) method of builtins.PyCapsule instance
```

### **`circumradius(v: array, f: array)`**
Compute the circumradius of each triangle in a mesh (V,F)

| | |
|-|-|
|Parameters| V  \#V by dim list of mesh vertex positions</br>F  \#F by 3 list of triangle indices into V |
|Returns| R  \#F list of circumradii |

**Examples**
```python
R = circumradius(V, F)
igl.collapse_small_triangles = collapse_small_triangles(...) method of builtins.PyCapsule instance
```

### **`collapse_small_triangles(v: array, f: array, eps: float)`**
Given a triangle mesh (V,F) compute a new mesh (VV,FF) which contains the
original faces and vertices of (V,F) except any small triangles have been
removed via collapse.
We are *not* following the rules in "Mesh Optimization" [Hoppe et al]
Section 4.2. But for our purposes we don't care about this criteria.

| | |
|-|-|
|Parameters| V  \#V by 3 list of vertex positions</br>F  \#F by 3 list of triangle indices into V</br>eps  epsilon for smallest allowed area treated as fraction of squared bounding box</br>diagonal |
|Returns| FF  \#FF by 3 list of triangle indices into V |

**Examples**
```python
igl.connect_boundary_to_infinity = connect_boundary_to_infinity(...) method of builtins.PyCapsule instance
```

### **`connect_boundary_to_infinity(f: array)`**
Connect all boundary edges to a fictitious point at infinity.

| | |
|-|-|
|Parameters| F  \#F by 3 list of face indices into some V |
|Returns| FO  \#F+\#O by 3 list of face indices into [V;inf inf inf], original F are</br>guaranteed to come first. If (V,F) was a manifold mesh, now it is</br>closed with a possibly non-manifold vertex at infinity (but it will be</br>edge-manifold). |

**Examples**
```python
igl.connect_boundary_to_infinity_face = connect_boundary_to_infinity_face(...) method of builtins.PyCapsule instance
```

### **`connect_boundary_to_infinity_face(v: array, f: array)`**

| | |
|-|-|
|Parameters| F  \#F by 3 list of face indices into some V |
|Returns| FO  \#F+\#O by 3 list of face indices into VO |

**Examples**
```python
igl.connect_boundary_to_infinity_index = connect_boundary_to_infinity_index(...) method of builtins.PyCapsule instance
```

### **`connect_boundary_to_infinity_index(f: array, inf_index: int)`**

| | |
|-|-|
|Parameters| inf_index  index of point at infinity (usually V.rows() or F.maxCoeff()) |
|Returns|  |

**Examples**
```python
igl.cotmatrix = cotmatrix(...) method of builtins.PyCapsule instance
```

### **`cotmatrix(v: array, f: array)`**
Constructs the cotangent stiffness matrix (discrete laplacian) for a given mesh
(v, f).

| | |
|-|-|
|Parameters| v : \#v by dim list of mesh vertex positions</br>f : \#f by simplex_size list of mesh faces (must be triangles) |
|Returns| l : \#v by \#v cotangent matrix, each row i corresponding to v(i, :) |
|See also| adjacency_matrix |
|Notes| This Laplacian uses the convention that diagonal entries are</br>**minus** the sum of off-diagonal entries. The diagonal entries are</br>therefore in general negative and the matrix is **negative** semi-definite</br>(immediately, -L is **positive** semi-definite) |

**Examples**
```python
# Mesh in (v, f)
 l = cotmatrix(v, f)
igl.cotmatrix_entries = cotmatrix_entries(...) method of builtins.PyCapsule instance
```

### **`cotmatrix_entries(v: array, f: array)`**
COTMATRIX_ENTRIES compute the cotangents of each angle in mesh (V,F)

| | |
|-|-|
|Parameters| V  \#V by dim list of rest domain positions</br>F  \#F by {34} list of {triangletetrahedra} indices into V |
|Returns| C  \#F by 3 list of 1/2*cotangents corresponding angles</br>for triangles, columns correspond to edges [1,2],[2,0],[0,1]</br>OR</br>C  \#F by 6 list of 1/6*cotangents of dihedral angles*edge lengths</br>for tets, columns along edges [1,2],[2,0],[0,1],[3,0],[3,1],[3,2] |

**Examples**
```python
igl.crouzeix_raviart_cotmatrix = crouzeix_raviart_cotmatrix(...) method of builtins.PyCapsule instance
```

### **`crouzeix_raviart_cotmatrix(v: array, f: array)`**
CROUZEIX_RAVIART_COTMATRIX Compute the Crouzeix-Raviart cotangent
stiffness matrix.

| | |
|-|-|
|Parameters| V  \#V by dim list of vertex positions</br>F  \#F by 3 / 4 list of triangle/tetrahedron indices |
|Returns| L  \#E by \#E edge/face-based diagonal cotangent matrix</br>E  \#E by 2 / 3 list of edges/faces</br>EMAP  \#F*3 / 4 list of indices mapping allE to E |
|See also| See also: crouzeix_raviart_massmatrix |

**Examples**
```python
See for example "Discrete Quadratic Curvature Energies" [Wardetzky, Bergou,
Harmon, Zorin, Grinspun 2007]
igl.crouzeix_raviart_cotmatrix_known_e = crouzeix_raviart_cotmatrix_known_e(...) method of builtins.PyCapsule instance
```

### **`crouzeix_raviart_cotmatrix_known_e(v: array, f: array, e: array, emap: array)`**
wrapper if E and EMAP are already computed (better match!)

| | |
|-|-|
|Parameters|  |
|Returns|  |

**Examples**
```python
igl.crouzeix_raviart_massmatrix = crouzeix_raviart_massmatrix(...) method of builtins.PyCapsule instance
```

### **`crouzeix_raviart_massmatrix(v: array, f: array)`**
CROUZEIX_RAVIART_MASSMATRIX Compute the Crouzeix-Raviart mass matrix where
M(e,e) is just the sum of the areas of the triangles on either side of an
edge e.

| | |
|-|-|
|Parameters| V  \#V by dim list of vertex positions</br>F  \#F by 3 / 4 list of triangle/tetrahedron indices |
|Returns| M  \#E by \#E edge/face-based diagonal mass matrix</br>E  \#E by 2 / 3 list of edges/faces</br>EMAP  \#F*3 / 4 list of indices mapping allE to E |
|See also| crouzeix_raviart_cotmatrix |
|Notes| See for example "Discrete Quadratic Curvature Energies" [Wardetzky, Bergou,</br>Harmon, Zorin, Grinspun 2007] |

**Examples**
```python
igl.crouzeix_raviart_massmatrix_known_e = crouzeix_raviart_massmatrix_known_e(...) method of builtins.PyCapsule instance
```

### **`crouzeix_raviart_massmatrix_known_e(v: array, f: array, e: array, emap: array)`**
wrapper if E and EMAP are already computed (better match!)

| | |
|-|-|
|Parameters|  |
|Returns|  |

**Examples**
```python
igl.cylinder = cylinder(...) method of builtins.PyCapsule instance
```

### **`cylinder(axis_devisions: int, height_devisions: int)`**
Construct a triangle mesh of a cylinder (without caps)

| | |
|-|-|
|Parameters| axis_devisions  number of vertices _around the cylinder_</br>height_devisions  number of vertices _up the cylinder_ |
|Returns| V  \#V by 3 list of mesh vertex positions</br>F  \#F by 3 list of triangle indices into V |

**Examples**
```python
igl.decimate = decimate(...) method of builtins.PyCapsule instance
```

### **`decimate(v: array, f: array, max_m: int)`**
Assumes (V,F) is a manifold mesh (possibly with boundary) Collapses edges
until desired number of faces is achieved. This uses default edge cost and
merged vertex placement functions {edge length, edge midpoint}.

| | |
|-|-|
|Parameters| V  \#V by dim list of vertex positions</br>F  \#F by 3 list of face indices into V.</br>max_m  desired number of output faces |
|Returns| U  \#U by dim list of output vertex posistions (can be same ref as V)</br>G  \#G by 3 list of output face indices into U (can be same ref as G)</br>J  \#G list of indices into F of birth face</br>I  \#U list of indices into V of birth vertices</br>Returns true if m was reached (otherwise \#G > m) |

**Examples**
```python
igl.dihedral_angles = dihedral_angles(...) method of builtins.PyCapsule instance
```

### **`dihedral_angles(v: array, t: array)`**
Compute dihedral angles for all tets of a given tet mesh (v, t).

| | |
|-|-|
|Parameters| v : \#v by dim list of vertex positions</br>t : \#v by 4 list of tet indices |
|Returns| theta : \#t by 6 list of dihedral angles (in radians)</br>cos_theta : \#t by 6 list of cosine of dihedral angles (in radians) |

**Examples**
```python
# TetMesh in (v, t)
 theta, cos_theta = dihedral_angles(v, t)
igl.dihedral_angles_intrinsic = dihedral_angles_intrinsic(...) method of builtins.PyCapsule instance
```

### **`dihedral_angles_intrinsic(l: array, a: array)`**
See dihedral_angles for the documentation.
igl.directed_edge_parents = directed_edge_parents(...) method of builtins.PyCapsule instance

### **`directed_edge_parents(e: array)`**
Recover "parents" (preceding edges) in a tree given just directed edges.

| | |
|-|-|
|Parameters| e : \#e by 2 list of directed edges |
|Returns| p : \#e list of parent indices into e. (-1) means root |

**Examples**
```python
e.np.random.randint(0, 10, size=(10, 2))
p = directed_edge_parents(e)
igl.doublearea = doublearea(...) method of builtins.PyCapsule instance
```

### **`doublearea(v: array, f: array)`**
Computes twice the area for each input triangle[quad]

| | |
|-|-|
|Parameters| v : \#v by dim array of mesh vertex positions</br>f : \#f by simplex_size array of mesh faces (must be triangles or quads) |
|Returns| d_area : \#f list of triangle[quad] double areas (SIGNED only for 2D input) |
|Notes| Known bug: For dim==3 complexity is O(\#V + \#F)!! Not just O(\#F). This is a big deal if you have 1million unreferenced vertices and 1 face |

**Examples**
```python
# Mesh in (v, f)
 dbl_area = doublearea(v, f)
igl.ears = ears(...) method of builtins.PyCapsule instance
```

### **`ears(f: array)`**
FIND_EARS  Find all ears (faces with two boundary edges) in a given mesh

| | |
|-|-|
|Parameters| F  \#F by 3 list of triangle mesh indices |
|Returns| ears  \#ears list of indices into F of ears</br>ear_opp  \#ears list of indices indicating which edge is non-boundary</br>(connecting to flops) |

**Examples**
```python
ears,ear_opp = find_ears(F)
igl.edge_topology = edge_topology(...) method of builtins.PyCapsule instance
```

### **`edge_topology(v: array, f: array)`**
Initialize Edges and their topological relations (assumes an edge-manifold mesh)

| | |
|-|-|
|Parameters| v : \#v by dim, list of mesh vertex positions (unused)</br>f : \#f by 3, list of triangle indices into V |
|Returns| ev : \#e by 2, list of edges described as pair of vertices.</br>fe : \#f by 3, list storing triangle-edge relation.</br>ef : \#e by w, list storing edge-triangle relation, uses -1 to indicate boundaries. |

**Examples**
```python
# Mesh in (v, f)
 ev, fe, ef = edge_topology(v, f)
igl.edges = edges(...) method of builtins.PyCapsule instance
```

### **`edges(f: array)`**
Constructs a list of unique edges represented in a given mesh (v, f)

| | |
|-|-|
|Parameters| f : \#F by dim list of mesh faces (must be triangles or tets) |
|Returns| \#e by 2 list of edges in no particular order |
|See also| adjacency_matrix |

**Examples**
```python
 V, F, _ = igl.readOFF("test.off)
 E = igl.edges(F)
igl.euler_characteristic = euler_characteristic(...) method of builtins.PyCapsule instance
```

### **`euler_characteristic(f: array) -> int`**
Computes the Euler characteristic of a given mesh (V,F)

| | |
|-|-|
|Parameters| F \#F by dim list of mesh faces (must be triangles) |
|Returns| Returns An int containing the Euler characteristic |

**Examples**
```python
igl.euler_characteristic_complete = euler_characteristic_complete(...) method of builtins.PyCapsule instance
```

### **`euler_characteristic_complete(v: array, f: array) -> int`**

| | |
|-|-|
|Parameters| V       \#V by dim list of mesh vertex positions |
|Returns|  |

**Examples**
```python
igl.exact_geodesic = exact_geodesic(...) method of builtins.PyCapsule instance
```

### **`exact_geodesic(v: array, f: array, vs: array, vt: array, fs: numpy.array  None = None, ft: numpy.array  None = None)`**
Exact geodesic algorithm for the calculation of geodesics on a triangular mesh.

| | |
|-|-|
|Parameters| v : \#v by 3 array of 3D vertex positions</br>f : \#f by 3 array of mesh faces</br>vs : \#vs by 1 array specifying indices of source vertices</br>fs : \#fs by 1 array specifying indices of source faces</br>vt : \#vt by 1 array specifying indices of target vertices</br>ft : \#ft by 1 array specifying indices of target faces |
|Returns| d : \#vt+\#ft by 1 array of geodesic distances of each target w.r.t. the nearest one in the source set |
|Notes| Specifying a face as target/source means its center.</br>Implementation from https:code.google.com/archive/p/geodesic/ with the algorithm first described by Mitchell, Mount and Papadimitriou in 1987. |

**Examples**
```python
igl.face_components = face_components(...) method of builtins.PyCapsule instance
```

### **`face_components(f: array)`**
Compute connected components of facets based on edge-edge adjacency,

| | |
|-|-|
|Parameters| f : \#f x 3 array of triangle indices |
|Returns| An array, c, with shape (\#f,), of component ids |
|See also| vertex_components</br>vertex_components_from_adjacency_matrix |

**Examples**
```python
igl.fit_plane = fit_plane(...) method of builtins.PyCapsule instance
```

### **`fit_plane(v: array)`**
This function fits a plane to a point cloud.

| | |
|-|-|
|Parameters| V \#Vx3 matrix. The 3D point cloud, one row for each vertex. |
|Returns| N 1x3 Vector. The normal of the fitted plane.</br>C 1x3 Vector. A point that lies in the fitted plane. |
|Notes| From http:missingbytes.blogspot.com/2012/06/fitting-plane-to-point-cloud.html |

**Examples**
```python
igl.gaussian_curvature = gaussian_curvature(...) method of builtins.PyCapsule instance
```

### **`gaussian_curvature(v: array, f: array)`**
Compute discrete local integral gaussian curvature (angle deficit, without
averaging by local area).

| | |
|-|-|
|Parameters| v : \#v by 3 array of mesh vertex 3D positions</br>f : \#f by 3 array of face (triangle) indices |
|Returns| k : \#v by 1 array of discrete gaussian curvature values |
|See also| principal_curvature |

**Examples**
```python
# Mesh in (v, f)
 k = gaussian_curvature(v, f)
igl.grad = grad(...) method of builtins.PyCapsule instance
```

### **`grad(v: array, f: array, uniform: bool = False)`**
Compute the numerical gradient operator.

| | |
|-|-|
|Parameters| v : \#v by 3 list of mesh vertex positions</br>f : \#f by 3 list of mesh face indices [or a \#faces by 4 list of tetrahedral indices]</br>uniform : boolean (default false). Use a uniform mesh instead of the vertices v |
|Returns| g : \#faces * dim by \#v gradient operator |
|See also| cotmatrix, massmatrix |
|Notes| Gradient of a scalar function defined on piecewise linear elements (mesh)</br>is constant on each triangle [tetrahedron] i,j,k:</br>grad(Xijk) = (Xj-Xi) * (Vi - Vk)^R90 / 2A + (Xk-Xi) * (Vj - Vi)^R90 / 2A</br>where Xi is the scalar value at vertex i, Vi is the 3D position of vertex</br>i, and A is the area of triangle (i,j,k). ^R90 represent a rotation of</br>90 degrees. |

**Examples**
```python
# Mesh in (v, f)
 g = grad(v, f)
igl.harmonic_integrated_with_laplacian = harmonic_integrated_with_laplacian(...) method of builtins.PyCapsule instance
```

### **`harmonic_integrated_with_laplacian(l: sparse_matrix, m: sparse_matrix, k: int)`**
Build the discrete k-harmonic operator (computing integrated quantities).
That is, if the k-harmonic PDE is Q x = 0, then this minimizes x' Q x

| | |
|-|-|
|Parameters| L  \#V by \#V discrete (integrated) Laplacian</br>M  \#V by \#V mass matrix</br>k  power of harmonic operation (1: harmonic, 2: biharmonic, etc) |
|Returns| Q  \#V by \#V discrete (integrated) k-Laplacian |

**Examples**
```python
igl.harmonic_uniform_laplacian = harmonic_uniform_laplacian(...) method of builtins.PyCapsule instance
```

### **`harmonic_uniform_laplacian(f: array, b: array, bc: array, k: int)`**
Compute harmonic map using uniform laplacian operator

| | |
|-|-|
|Parameters| F  \#F by simplex-size list of element indices</br>b  \#b boundary indices into V</br>bc \#b by \#W list of boundary values</br>k  power of harmonic operation (1: harmonic, 2: biharmonic, etc) |
|Returns| W  \#V by \#W list of weights |

**Examples**
```python
igl.harmonic_weights = harmonic_weights(...) method of builtins.PyCapsule instance
```

### **`harmonic_weights(v: array, f: array, b: array, bc: array, k: int)`**
Compute k-harmonic weight functions "coordinates".

| | |
|-|-|
|Parameters| V  \#V by dim vertex positions</br>F  \#F by simplex-size list of element indices</br>b  \#b boundary indices into V</br>bc \#b by \#W list of boundary values</br>k  power of harmonic operation (1: harmonic, 2: biharmonic, etc) |
|Returns| W  \#V by \#W list of weights |

**Examples**
```python
igl.internal_angles = internal_angles(...) method of builtins.PyCapsule instance
```

### **`internal_angles(v: array, f: array)`**
Computes internal angles for a triangle mesh.

| | |
|-|-|
|Parameters| v : \#v by dim array of mesh vertex nD positions</br>f : \#f by poly-size array of face (triangle) indices |
|Returns| k : \#f by poly-size array of internal angles. For triangles, columns correspond to edges [1,2],[2,0],[0,1]. |
|Notes| If poly-size ≠ 3 then dim must equal 3. |

**Examples**
```python
igl.is_edge_manifold = is_edge_manifold(...) method of builtins.PyCapsule instance
```

### **`is_edge_manifold(f: array) -> bool`**
See is_edge_manifold for the documentation.
igl.is_irregular_vertex = is_irregular_vertex(...) method of builtins.PyCapsule instance

### **`is_irregular_vertex(v: array, f: array) -> List[bool]`**
Determine if a vertex is irregular, i.e. it has more than 6 (triangles) or 4 (quads) incident edges. Vertices on the boundary are ignored.

| | |
|-|-|
|Parameters| v : \#v by dim array of vertex positions</br>f : \#f by 3[4] array of triangle[quads] indices |
|Returns| s : \#v list of bools revealing whether vertices are singular |

**Examples**
```python
igl.isolines = isolines(...) method of builtins.PyCapsule instance
```

### **`isolines(v: array, f: array, z: array, n: int)`**
Constructs isolines for a function z given on a mesh (V,F)

| | |
|-|-|
|Parameters| V  \#V by dim list of mesh vertex positions</br>F  \#F by 3 list of mesh faces (must be triangles)</br>z  \#V by 1 list of function values evaluated at vertices</br>n  the number of desired isolines |
|Returns| isoV  \#isoV by dim list of isoline vertex positions</br>isoE  \#isoE by 2 list of isoline edge positions |

**Examples**
```python
igl.massmatrix = massmatrix(...) method of builtins.PyCapsule instance
```

### **`massmatrix(v: array, f: array, type: int = 1)`**
Constructs the mass (area) matrix for a given mesh (V,F).

| | |
|-|-|
|Parameters| v : \#v by dim list of mesh vertex positions</br>f : \#f by simplex_size list of mesh faces (must be triangles)</br>type : one of the following types:</br>-igl.MASSMATRIX_TYPE_BARYCENTRIC  barycentric</br>-igl.MASSMATRIX_TYPE_VORONOI voronoi-hybrid (default)</br>-igl.MASSMATRIX_TYPE_FULL full (not implemented) |
|Returns| m : \#v by \#v mass matrix |
|See also| adjacency_matrix, cotmatrix, grad |

**Examples**
```python
igl.min_quad_dense_precompute = min_quad_dense_precompute(...) method of builtins.PyCapsule instance
```

### **`min_quad_dense_precompute(a: array, aeq: array, use_lu_decomposition: bool)`**
MIN_QUAD_WITH_FIXED Minimize quadratic energy Z'*A*Z + Z'*B + C
subject to linear constraints Aeq*Z = Beq

| | |
|-|-|
|Parameters| A  n by n matrix of quadratic coefficients</br>B  n by 1 column of linear coefficients</br>Aeq  m by n list of linear equality constraint coefficients</br>Beq  m by 1 list of linear equality constraint constant values</br>use_lu_decomposition  use lu rather than SVD |
|Returns| S  n by (n + m) "solve" matrix, such that S*[B', Beq'] is a solution |

**Examples**
```python
igl.orientable_patches = orientable_patches(...) method of builtins.PyCapsule instance
```

### **`orientable_patches(f: array)`**
Compute connected components of facets connected by manifold edges.

| | |
|-|-|
|Parameters| f : n by dim array of face ids |
|Returns| A tuple (c, A) where c is an array of component ids (starting with 0)</br>and A is a \#f x \#f adjacency matri |
|See also| components |
|Notes| Known bugs: This will detect a moebius strip as a single patch (manifold, non-orientable) and also non-manfiold, yet orientable patches. |

**Examples**
```python
igl.oriented_facets = oriented_facets(...) method of builtins.PyCapsule instance
```

### **`oriented_facets(f: array)`**
Determines all 'directed [facets](https:en.wikipedia.org/wiki/Simplex#Elements)' of a given set
of simplicial elements. For a manifold triangle mesh, this computes all half-edges.
For a manifold tetrahedral mesh, this computes all half-faces.

| | |
|-|-|
|Parameters| f : \#F by simplex_size list of simplices |
|Returns| \#E : by simplex_size-1 list of half-edges/facets |
|See also| edges |
|Notes| This is not the same as igl::edges because this includes every</br>directed edge including repeats (meaning interior edges on a surface will</br>show up once for each direction and non-manifold edges may appear more than</br>once for each direction). |

**Examples**
```python
igl.per_edge_normals = per_edge_normals(...) method of builtins.PyCapsule instance
```

### **`per_edge_normals(v: array, f: array, weight: int = 0, fn: array)`**
Compute face normals via vertex position list, face list

| | |
|-|-|
|Parameters| V  \#V by 3 eigen Matrix of mesh vertex 3D positions</br>F  \#F by 3 eigen Matrix of face (triangle) indices</br>weight  weighting type</br>FN  \#F by 3 matrix of 3D face normals per face |
|Returns| N  \#2 by 3 matrix of mesh edge 3D normals per row</br>E  \#E by 2 matrix of edge indices per row</br>EMAP  \#E by 1 matrix of indices from all edges to E |

**Examples**
```python
igl.per_face_normals = per_face_normals(...) method of builtins.PyCapsule instance
```

### **`per_face_normals(v: array, f: array, z: array)`**
Compute face normals via vertex position list, face list

| | |
|-|-|
|Parameters| V  \#V by 3 eigen Matrix of mesh vertex 3D positions</br>F  \#F by 3 eigen Matrix of face (triangle) indices</br>Z  3 vector normal given to faces with degenerate normal. |
|Returns| N  \#F by 3 eigen Matrix of mesh face (triangle) 3D normals |

**Examples**
```python
Give degenerate faces (1/3,1/3,1/3)^0.5
```

### **`per_face_normals(V,F,Vector3d(1,1,1).normalized(),N);`**
igl.per_vertex_attribute_smoothing = per_vertex_attribute_smoothing(...) method of builtins.PyCapsule instance

### **`per_vertex_attribute_smoothing(ain: array, f: array)`**
Smooth vertex attributes using uniform Laplacian

| | |
|-|-|
|Parameters| Ain  \#V by \#A eigen Matrix of mesh vertex attributes (each vertex has \#A attributes)</br>F    \#F by 3 eigne Matrix of face (triangle) indices |
|Returns| Aout \#V by \#A eigen Matrix of mesh vertex attributes |

**Examples**
```python
igl.per_vertex_normals = per_vertex_normals(...) method of builtins.PyCapsule instance
```

### **`per_vertex_normals(v: array, f: array, weighting: int = 0)`**
Compute vertex normals via vertex position list, face list.

| | |
|-|-|
|Parameters| v : \#v by 3 array of mesh vertex 3D positions</br>f : \#f by 3 array of face (triangle) indices</br>weighting : Weighting type, one of the following</br>-igl.PER_VERTEX_NORMALS_WEIGHTING_TYPE_UNIFORM uniform influence</br>-igl.PER_VERTEX_NORMALS_WEIGHTING_TYPE_AREA area weighted</br>-igl.PER_VERTEX_NORMALS_WEIGHTING_TYPE_ANGLE angle weighted |
|Returns| n  \#v by 3 array of mesh vertex 3D normals |
|See also| per_face_normals, per_edge_normals |

**Examples**
```python
# Mesh in (v, f)
 n = per_vertex_normals(v, f)
igl.piecewise_constant_winding_number = piecewise_constant_winding_number(...) method of builtins.PyCapsule instance
```

### **`piecewise_constant_winding_number(f: array) -> bool`**
PIECEWISE_CONSTANT_WINDING_NUMBER Determine if a given mesh induces a
piecewise constant winding number field: Is this mesh valid input to solid
set operations.  **Assumes** that `(V,F)` contains no -intersections
(including degeneracies and co-incidences).  If there are co-planar and
co-incident vertex placements, a mesh could _fail_ this combinatorial test
but still induce a piecewise-constant winding number _geometrically_. For
example, consider a hemisphere with boundary and then pinch the boundary
"shut" along a line segment. The **_bullet-proof_** check is to first
resolve all -intersections in `(V,F) -> (SV,SF)` (i.e. what the
`igl::copyleft::cgal::piecewise_constant_winding_number` overload does).

| | |
|-|-|
|Parameters| F  \#F by 3 list of triangle indices into some (abstract) list of</br>vertices V |
|Returns| Returns true if the mesh _combinatorially_ induces a piecewise constant</br>winding number field. |

**Examples**
```python
igl.principal_curvature = principal_curvature(...) method of builtins.PyCapsule instance
```

### **`principal_curvature(v: array, f: array, radius: int = 5, use_k_ring: bool = True)`**
Compute the principal curvature directions and magnitude of the given triangle mesh.

| | |
|-|-|
|Parameters| v : vertex array of size \#V by 3</br>f : face index array \#F by 3 list of mesh faces (must be triangles)</br>radius : controls the size of the neighbourhood used, 1 = average edge length (default: 5)</br>use_k_ring : (default: True) |
|Returns| pd1 : \#v by 3 maximal curvature direction for each vertex</br>pd2 : \#v by 3 minimal curvature direction for each vertex</br>pv1 : \#v by 1 maximal curvature value for each vertex</br>pv2 : \#v by 1 minimal curvature value for each vertex |
|See also| average_onto_faces, average_onto_vertices |
|Notes| This function has been developed by: Nikolas De Giorgis, Luigi Rocca and Enrico Puppo.</br>The algorithm is based on: Efficient Multi-scale Curvature and Crease Estimation</br>Daniele Panozzo, Enrico Puppo, Luigi Rocca GraVisMa, 2010 |

**Examples**
```python
# Mesh in (v, f)
 pd1, pd2, pv1, pv2 = principal_curvature(v, f)
igl.procrustes = procrustes(...) method of builtins.PyCapsule instance
```

### **`procrustes(x: array, y: array, include_scaling: bool, include_reflections: bool)`**
Solve Procrustes problem in d dimensions.  Given two point sets X,Y in R^d
find best scale s, orthogonal R  and translation t s.t. s*X*R + t - Y^2
is minimized.

| | |
|-|-|
|Parameters| X  \#V by DIM first list of points</br>Y  \#V by DIM second list of points</br>includeScaling  if scaling should be allowed</br>includeReflections  if R is allowed to be a reflection |
|Returns| scale  scaling</br>R      orthogonal matrix</br>t      translation |

**Examples**
```python
MatrixXd X, Y; (containing 3d points as rows)
double scale;
MatrixXd R;
VectorXd t;
igl::procrustes(X,Y,true,false,scale,R,t);
R *= scale;
MatrixXd Xprime = (X * R).rowwise() + t.transpose();
igl.qslim = qslim(...) method of builtins.PyCapsule instance
```

### **`qslim(v: array, f: array, max_m: int)`**
Decimate (simplify) a triangle mesh in nD according to the paper
"Simplifying Surfaces with Color and Texture using Quadric Error Metrics"
by [Garland and Heckbert, 1987] (technically a followup to qslim). The
mesh can have open boundaries but should be edge-manifold.

| | |
|-|-|
|Parameters| V  \#V by dim list of vertex positions. Assumes that vertices w</br>F  \#F by 3 list of triangle indices into V</br>max_m  desired number of output faces |
|Returns| U  \#U by dim list of output vertex posistions (can be same ref as V)</br>G  \#G by 3 list of output face indices into U (can be same ref as G)</br>J  \#G list of indices into F of birth face</br>I  \#U list of indices into V of birth vertices |

**Examples**
```python
igl.quad_planarity = quad_planarity(...) method of builtins.PyCapsule instance
```

### **`quad_planarity(v: array, f: array)`**
Compute planarity of the faces of a quad mesh.

| | |
|-|-|
|Parameters| v : \#v by 3 array of mesh vertex 3D positions</br>f : \#f by 4 array of face (quad) indices |
|Returns| p : \#f by 1 array of mesh face (quad) planarities |

**Examples**
```python
igl.random_points_on_mesh = random_points_on_mesh(...) method of builtins.PyCapsule instance
```

### **`random_points_on_mesh(n: int, v: array, f: array)`**
RANDOM_POINTS_ON_MESH Randomly sample a mesh (V,F) n times.

| | |
|-|-|
|Parameters| n  number of samples</br>V  \#V by dim list of mesh vertex positions</br>F  \#F by 3 list of mesh triangle indices |
|Returns| B  n by 3 list of barycentric coordinates, ith row are coordinates of</br>ith sampled point in face FI(i)</br>FI  n list of indices into F |

**Examples**
```python
igl.read_dmat = read_dmat(...) method of builtins.PyCapsule instance
```

### **`read_dmat(filename: str, dtype: dtype = 'float64')`**
Read a matrix from an ascii dmat file, a simple ascii matrix file type, defined as follows. The first line is always:
<#columns> <#rows>
Then the coefficients of the matrix are given separated by whitespace with columns running fastest.

| | |
|-|-|
|Parameters| filename : string, path to .dmat file</br>dtype : data-type of the returned matrix. Default is `float64`.</br>(returned faces always have type int32.) |
|Returns| w : array containing read-in coefficients |
|See also| read_triangle_mesh, read_off |

**Examples**
```python
 w = read_dmat("my_model.dmat")
igl.read_obj = read_obj(...) method of builtins.PyCapsule instance
```

### **`read_obj(filename: str, dtype: dtype = 'float64')`**
Read a mesh from an ascii obj file, filling in vertex positions, normals
and texture coordinates. Mesh may have faces of any number of degree.

| | |
|-|-|
|Parameters| filename : string, path to .obj file</br>dtype : data-type of the returned faces, texture coordinates and normals, optional. Default is `float64`.</br>(returned faces always have type int32.) |
|Returns| v : array of vertex positions \#v by 3</br>tc : array of texture coordinats \#tc by 2</br>n : array of corner normals \#n by 3</br>f : \#f array of face indices into vertex positions</br>ftc : \#f array of face indices into vertex texture coordinates</br>fn : \#f array of face indices into vertex normals |
|See also| read_triangle_mesh, read_off |

**Examples**
```python
 v, _, n, f, _, _ = read_obj("my_model.obj")
igl.read_off = read_off(...) method of builtins.PyCapsule instance
```

### **`read_off(filename: str, read_normals: bool = True, dtype: dtype = 'float64')`**
Read a mesh from an ascii off file, filling in vertex positions, normals
and texture coordinates. Mesh may have faces of any number of degree.

| | |
|-|-|
|Parameters| filename : string, path to .off file</br>read_normals : bool, determines whether normals are read. If false, returns []</br>dtype : data-type of the returned vertices, faces, and normals, optional. Default is `float64`.</br>(returned faces always have type int32.) |
|Returns| v : array of vertex positions \#v by 3</br>f : \#f list of face indices into vertex positions</br>n : list of vertex normals \#v by 3 |
|See also| read_triangle_mesh, read_obj |

**Examples**
```python
 v, f, n, c = read_off("my_model.off")
igl.read_triangle_mesh = read_triangle_mesh(...) method of builtins.PyCapsule instance
```

### **`read_triangle_mesh(filename: str, dtype: dtype = 'float64')`**
Read mesh from an ascii file with automatic detection of file format.
Supported: obj, off, stl, wrl, ply, mesh.

| | |
|-|-|
|Parameters| filename : string, path to mesh file</br>dtype : data-type of the returned vertices, optional. Default is `float64`.</br>(returned faces always have type int32.) |
|Returns| v : array of vertex positions \#v by 3</br>f : \#f list of face indices into vertex positions |
|See also| read_obj, read_off, read_stl |

**Examples**
```python
 v, f = read_triangle_mesh("my_model.obj")
igl.remove_duplicate_vertices = remove_duplicate_vertices(...) method of builtins.PyCapsule instance
```

### **`remove_duplicate_vertices(v: array, f: array, epsilon: float)`**
REMOVE_DUPLICATE_VERTICES Remove duplicate vertices upto a uniqueness
tolerance (epsilon)

| | |
|-|-|
|Parameters| V  \#V by dim list of vertex positions</br>epsilon  uniqueness tolerance (significant digit), can probably think of</br>this as a tolerance on L1 distance |
|Returns| SV  \#SV by dim new list of vertex positions</br>SVI \#V by 1 list of indices so SV = V(SVI,:)</br>SVJ \#SV by 1 list of indices so V = SV(SVJ,:)</br>Wrapper that also remaps given faces (F) --> (SF) so that SF index SV |

**Examples**
```python
% Mesh in (V,F)
[SV,SVI,SVJ] = remove_duplicate_vertices(V,1e-7);
% remap faces
SF = SVJ(F);
igl.remove_duplicates = remove_duplicates(...) method of builtins.PyCapsule instance
```

### **`remove_duplicates(v: array, f: array, epsilon: float)`**
Merge the duplicate vertices from V, fixing the topology accordingly

| | |
|-|-|
|Parameters| V,F       mesh description</br>epsilon   minimal distance to consider two vertices identical |
|Returns| NV, NF    new mesh without duplicate vertices |

**Examples**
```python
igl.remove_unreferenced = remove_unreferenced(...) method of builtins.PyCapsule instance
```

### **`remove_unreferenced(v: array, f: array)`**
Remove unreferenced vertices from V, updating F accordingly

| | |
|-|-|
|Parameters| V  \#V by dim list of mesh vertex positions</br>F  \#F by ss list of simplices (Values of -1 are quitely skipped) |
|Returns| NV  \#NV by dim list of mesh vertex positions</br>NF  \#NF by ss list of simplices</br>IM  \#V by 1 list of indices such that: NF = IM(F) and NT = IM(T)</br>and V(find(IM<=size(NV,1)),:) = NV</br>J  \#RV by 1 list, such that RV = V(J,:) |

**Examples**
```python
igl.resolve_duplicated_faces = resolve_duplicated_faces(...) method of builtins.PyCapsule instance
```

### **`resolve_duplicated_faces(f1: array)`**
Resolve duplicated faces according to the following rules per unique face:

### **`If the number of positively oriented faces equals the number of`**
negatively oriented faces, remove all duplicated faces at this triangle.

### **`If the number of positively oriented faces equals the number of`**
negatively oriented faces plus 1, keeps one of the positively oriented
face.

### **`If the number of positively oriented faces equals the number of`**
negatively oriented faces minus 1, keeps one of the negatively oriented
face.

### **`If the number of postively oriented faces differ with the number of`**
negativley oriented faces by more than 1, the mesh is not orientable.
An exception will be thrown.

| | |
|-|-|
|Parameters| F1  \#F1 by 3 array of input faces. |
|Returns| F2  \#F2 by 3 array of output faces without duplicated faces.</br>J   \#F2 list of indices into F1. |

**Examples**
```python
igl.shape_diameter_function = shape_diameter_function(...) method of builtins.PyCapsule instance
```

### **`shape_diameter_function(v: array, f: array, p: array, n: array, num_samples: int)`**
Compute shape diamater function per given point. In the parlence of the
paper "Consistent Mesh Partitioning and Skeletonisation using the Shape
Diameter Function" [Shapiro et al. 2008], this implementation uses a 180°
cone and a _uniform_ average (_not_ a average weighted by inverse angles).

| | |
|-|-|
|Parameters| V  \#V by 3 list of mesh vertex positions</br>F  \#F by 3 list of mesh face indices into V</br>P  \#P by 3 list of origin points</br>N  \#P by 3 list of origin normals |
|Returns| S  \#P list of shape diamater function values between bounding box</br>diagonal (perfect sphere) and 0 (perfect needle hook) |

**Examples**
```python
igl.sort_angles = sort_angles(...) method of builtins.PyCapsule instance
```

### **`sort_angles(m: array)`**
Sort angles in ascending order in a numerically robust way.
Instead of computing angles using atan2(y, x), sort directly on (y, x).

| | |
|-|-|
|Parameters| M: m by n matrix of scalars. (n >= 2).  Assuming the first column of M</br>contains values for y, and the second column is x.  Using the rest</br>of the columns as tie-breaker. |
|Returns| R: an array of m indices.  M.row(R[i]) contains the i-th smallest</br>angle. |
|Notes| None. |

**Examples**
```python
igl.tet_tet_adjacency = tet_tet_adjacency(...) method of builtins.PyCapsule instance
```

### **`tet_tet_adjacency(t: array)`**
Constructs the tet_tet adjacency matrix for a given tet mesh with tets T

| | |
|-|-|
|Parameters| T  \#T by 4 list of tets |
|Returns| TT   \#T by \#4 adjacency matrix, the element i,j is the id of the tet adjacent to the j face of tet i</br>TTi  \#T by \#4 adjacency matrix, the element i,j is the id of face of the tet TT(i,j) that is adjacent to tet i |
|Notes| the first face of a tet is [0,1,2], the second [0,1,3], the third [1,2,3], and the fourth [2,0,3]. |

**Examples**
```python
igl.tetrahedralize = tetrahedralize(...) method of builtins.PyCapsule instance
```

### **`tetrahedralize(v: array, f: array, switches: str = 'pYQ')`**
Mesh the interior of a surface mesh (V,F) using tetgen.

| | |
|-|-|
|Parameters| v : \#v by 3 vertex position array</br>f : \#v array of polygon face indices into V (0-indexed)</br>switches : string of tetgen options (See tetgen documentation) e.g.</br>"pq1.414a0.01" tries to mesh the interior of a given surface with quality and area constraints. Will mesh the convex hull constrained to pass through V (ignores F) |
|Returns| tv  \#v by 3 vertex position array</br>tt  \#t by 4 array of tet face indices</br>tf  \#f by 3 array of triangle face indices |
|Notes| Returns status:</br>0 success</br>1 tetgen threw exception</br>2 tetgen did not crash but could not create any tets (probably there are</br>holes, duplicate faces etc.)</br>-1 other error |

**Examples**
```python
igl.triangle_triangle_adjacency = triangle_triangle_adjacency(...) method of builtins.PyCapsule instance
```

### **`triangle_triangle_adjacency(f: array)`**
Constructs the triangle-triangle adjacency matrix for a given
mesh (V,F).

| | |
|-|-|
|Parameters| F  \#F by simplex_size list of mesh faces (must be triangles) |
|Returns| TT   \#F by \#3 adjacent matrix, the element i,j is the id of the triangle</br>adjacent to the j edge of triangle i</br>TTi  \#F by \#3 adjacent matrix, the element i,j is the id of edge of the</br>triangle TT(i,j) that is adjacent with triangle i |
|Notes| NOTE: the first edge of a triangle is [0,1] the second [1,2] and the third</br>[2,3].  this convention is DIFFERENT from cotmatrix_entries.h |

**Examples**
```python
igl.triangulate = triangulate(...) method of builtins.PyCapsule instance
```

### **`triangulate(v: array, e: array, h: array, flags: str = 'a0.005qQ')`**
Triangulate the interior of a polygon using the triangle library.

| | |
|-|-|
|Parameters| v : \#v by 2 array of 2D vertex positions</br>e : \#e by 2 array of vertex ids forming unoriented edges of the boundary of the polygon</br>h : \#h by 2 coordinates of points contained inside holes of the polygon</br>m : optional \#v list of markers for input vertices</br>flags : string of options pass to triangle (see triangle documentation) (default 'a0.005q') |
|Returns| v2 : \#v2 by 2 coordinates of the vertives of the generated triangulation</br>f2 : \#f2 by 3 array of indices forming the faces of the generated triangulation</br>m2 : (only if you passed in m) \#v2 list of markers for output vertices |

**Examples**
```python
 v2, f2 = triangulate(v, e, h)
igl.uniformly_sample_two_manifold_at_vertices = uniformly_sample_two_manifold_at_vertices(...) method of builtins.PyCapsule instance
```

### **`uniformly_sample_two_manifold_at_vertices(ow: array, k: int, push: float)`**
Find uniform sampling up to placing samples on mesh vertices

| | |
|-|-|
|Parameters|  |
|Returns|  |

**Examples**
```python
igl.uniformly_sample_two_manifold_internal = uniformly_sample_two_manifold_internal(...) method of builtins.PyCapsule instance
```

### **`uniformly_sample_two_manifold_internal(w: array, f: array, k: int, push: float)`**
UNIFORMLY_SAMPLE_TWO_MANIFOLD Attempt to sample a mesh uniformly by
furthest point relaxation as described in "Fast Automatic Skinning
Transformations"
[Jacobson et al. 12] Section 3.3.

| | |
|-|-|
|Parameters| W  \#W by dim positions of mesh in weight space</br>F  \#F by 3 indices of triangles</br>k  number of samplse</br>push  factor by which corners should be pushed away |
|Returns| WS  k by dim locations in weights space |

**Examples**
```python
igl.unproject = unproject(...) method of builtins.PyCapsule instance
```

### **`unproject(win: array, model: array, proj: array, viewport: array)`**
Reimplementation of gluUnproject

| | |
|-|-|
|Parameters| win  \#P by 3 or 3-vector (\#P=1) of screen space x, y, and z coordinates</br>model  4x4 model-view matrix</br>proj  4x4 projection matrix</br>viewport  4-long viewport vector |
|Returns| scene  \#P by 3 or 3-vector (\#P=1) the unprojected x, y, and z coordinates |

**Examples**
```python
igl.unproject_in_mesh = unproject_in_mesh(...) method of builtins.PyCapsule instance
```

### **`unproject_in_mesh(pos: numpy.ndarray[float32[2, 1]], model: numpy.ndarray[float32[4, 4]], proj: numpy.ndarray[float32[4, 4]], viewport: numpy.ndarray[float32[4, 1]], v: array, f: array)`**
Unproject a screen location (using current opengl viewport, projection, and
model view) to a 3D position _inside_ a given mesh. If the ray through the
given screen location (x,y) _hits_ the mesh more than twice then the 3D
midpoint between the first two hits is return. If it hits once, then that
point is return. If it does not hit the mesh then obj is not set.

| | |
|-|-|
|Parameters| pos        screen space coordinates</br>model      model matrix</br>proj       projection matrix</br>viewport   vieweport vector</br>V   \#V by 3 list of mesh vertex positions</br>F   \#F by 3 list of mesh triangle indices into V |
|Returns| obj        3d unprojected mouse point in mesh</br>hits       vector of hits</br>Returns number of hits |

**Examples**
```python
igl.unproject_onto_mesh = unproject_onto_mesh(...) method of builtins.PyCapsule instance
```

### **`unproject_onto_mesh(pos: array, model: array, proj: array, viewport: array, v: array, f: array)`**
Unproject a screen location (using current opengl viewport, projection, and
model view) to a 3D position _onto_ a given mesh, if the ray through the
given screen location (x,y) _hits_ the mesh.

| | |
|-|-|
|Parameters| pos        screen space coordinates</br>model      model matrix</br>proj       projection matrix</br>viewport   vieweport vector</br>V   \#V by 3 list of mesh vertex positions</br>F   \#F by 3 list of mesh triangle indices into V |
|Returns| fid  id of the first face hit</br>bc  barycentric coordinates of hit</br>Returns true if there's a hit |

**Examples**
```python
igl.unproject_ray = unproject_ray(...) method of builtins.PyCapsule instance
```

### **`unproject_ray(pos: array, model: array, proj: array, viewport: array)`**
Construct a ray (source point + direction vector) given a screen space
positions (e.g. mouse) and a model-view projection constellation.

| | |
|-|-|
|Parameters| pos  2d screen-space position (x,y)</br>model  4x4 model-view matrix</br>proj  4x4 projection matrix</br>viewport  4-long viewport vector |
|Returns| s  source of ray (pos unprojected with z=0)</br>dir  direction of ray (d - s) where d is pos unprojected with z=1 |

**Examples**
```python
igl.upsample = upsample(...) method of builtins.PyCapsule instance
```

### **`upsample(v: array, f: array, number_of_subdivs: int = 1)`**
Subdivide a mesh without moving vertices: loop subdivision but odd
vertices stay put and even vertices are just edge midpoints

| | |
|-|-|
|Parameters| V  \#V by dim  mesh vertices</br>F  \#F by 3  mesh triangles |
|Returns| NV new vertex positions, V is guaranteed to be at top</br>NF new list of face indices |
|Notes| - assumes (V,F) is edge-manifold. |

**Examples**
```python
igl.vector_area_matrix = vector_area_matrix(...) method of builtins.PyCapsule instance
```

### **`vector_area_matrix(f: array)`**
Constructs the symmetric area matrix A, s.t. [V.col(0)' V.col(1)'] * A *
[V.col(0); V.col(1)] is the **vector area** of the mesh (V,F).

| | |
|-|-|
|Parameters| f : \#f by 3 array of mesh faces (must be triangles) |
|Returns| a : \#vx2 by \#vx2 area matrix |

**Examples**
```python
igl.vertex_components = vertex_components(...) method of builtins.PyCapsule instance
```

### **`vertex_components(f: array)`**
Compute connected components of the vertices of a mesh given the mesh' face indices.

| | |
|-|-|
|Parameters| f : \#f x dim array of face indices |
|Returns| An array of component ids (starting with 0) |
|See also| vertex_components_from_adjacency_matrix</br>face_components_from_faces |

**Examples**
```python
igl.vertex_components_from_adjacency_matrix = vertex_components_from_adjacency_matrix(...) method of builtins.PyCapsule instance
```

### **`vertex_components_from_adjacency_matrix(a: sparse_matrix)`**
Compute connected components of a graph represented by a sparse adjacency
matrix.

| | |
|-|-|
|Parameters| a : n by n sparse adjacency matrix |
|Returns| A tuple (c, counts) where c is an array of component ids (starting with 0)</br>and counts is a \#components array of counts for each component |
|See also| vertex_components</br>face_components |

**Examples**
```python
igl.vertex_triangle_adjacency = vertex_triangle_adjacency(...) method of builtins.PyCapsule instance
```

### **`vertex_triangle_adjacency(f: array, n: int)`**
vertex_face_adjacency constructs the vertex-face topology of a given mesh (V,F)

| | |
|-|-|
|Parameters| F  \#F by 3 list of triangle indices into some vertex list V</br>n  number of vertices, \#V (e.g., F.maxCoeff()+1) |
|Returns| VF  3*\#F list  List of faces indice on each vertex, so that VF(NI(i)+j) =</br>f, means that face f is the jth face (in no particular order) incident</br>on vertex i.</br>NI  \#V+1 list  cumulative sum of vertex-triangle degrees with a</br>preceeding zero. "How many faces" have been seen before visiting this</br>vertex and its incident faces. |

**Examples**
```python
igl.winding_number = winding_number(...) method of builtins.PyCapsule instance
```

### **`winding_number(v: array, f: array, o: array)`**
WINDING_NUMBER Compute the sum of solid angles of a triangle/tetrahedron
described by points (vectors) V

| | |
|-|-|
|Parameters| V  n by 3 list of vertex positions</br>F  \#F by 3 list of triangle indices, minimum index is 0</br>O  no by 3 list of origin positions |
|Returns| S  no by 1 list of winding numbers |

**Examples**
```python
igl.winding_number_for_point = winding_number_for_point(...) method of builtins.PyCapsule instance
```

### **`winding_number_for_point(v: array, f: array, p: array) -> float`**
Compute winding number of a single point

| | |
|-|-|
|Parameters| V  n by dim list of vertex positions</br>F  \#F by dim list of triangle indices, minimum index is 0</br>p  single origin position |
|Returns| w  winding number of this point |

**Examples**
```python
igl.write_obj = write_obj(...) method of builtins.PyCapsule instance
```

### **`write_obj(filename: str, v: array, f: array) -> bool`**
Write a mesh in an ascii obj file.

| | |
|-|-|
|Parameters| filename : path to outputfile</br>v : array of vertex positions \#v by 3</br>f : \#f list of face indices into vertex positions |
|Returns| ret : bool if output was successful |
|See also| read_obj |

**Examples**
```python
# Mesh in (v, f)
 success = write_obj(v, f)
igl.write_off = write_off(...) method of builtins.PyCapsule instance
```

### **`write_off(str: str, v: array, f: array, c: array) -> bool`**
Export geometry and colors-by-vertex
Export a mesh from an ascii OFF file, filling in vertex positions.
Only triangle meshes are supported

| | |
|-|-|
|Parameters| str  path to .off output file</br>V  \#V by 3 mesh vertex positions</br>F  \#F by 3 mesh indices into V</br>C  double matrix of rgb values per vertex \#V by 3 |
|Returns| Returns true on success, false on errors |

**Examples**
```python
igl.write_triangle_mesh = write_triangle_mesh(...) method of builtins.PyCapsule instance
```

### **`write_triangle_mesh(str: str, v: array, f: array, force_ascii: bool = True) -> bool`**
write mesh to a file with automatic detection of file format.  supported: obj, off, stl, wrl, ply, mesh).

| | |
|-|-|
|Parameters| str  path to file</br>V  eigen double matrix \#V by 3</br>F  eigen int matrix \#F by 3</br>force_ascii=True  force ascii format even if binary is available |
|Returns| Returns true iff success |

## class ARAP

**`solve(: igl.pyigl_classes.ARAP, arg0: numpy.ndarray, arg1: numpy.ndarray)`**
Static methods inherited from :

## class BBW

**`solve(: igl.pyigl_classes.BBW, arg0: numpy.ndarray, arg1: numpy.ndarray, arg2: numpy.ndarray[int32[m, 1]], arg3: numpy.ndarray)`**
Static methods inherited from :

## class SLIM

**`energy(: igl.pyigl_classes.SLIM) -> float`**

**`solve(: igl.pyigl_classes.SLIM, arg0: int)`**

**`vertices(: igl.pyigl_classes.SLIM)`**
Static methods inherited from :
