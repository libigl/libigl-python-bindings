## Functions
### active_set
**`active_set(A: sparse_matrix, B: array, known: array, Y: array, Aeq: sparse_matrix, Beq: array, Aieq: sparse_matrix, Bieq: array, lx: array, ux: array, Auu_pd: bool = False, max_iter: int = 100, inactive_threshold: float = 1e-14, constraint_threshold: float = 1e-14, solution_diff_threshold: float = 1e-14)`**

ACTIVE_SET Minimize quadratic energy
0.5*Z'*A*Z + Z'*B + C with constraints
that Z(known) = Y, optionally also subject to the constraints Aeq*Z = Beq,
and further optionally subject to the linear inequality constraints that
Aieq*Z <= Bieq and constant inequality constraints lx <= x <= ux

| | |
|-|-|
|Parameters| A  n by n matrix of quadratic coefficients</br>B  n by 1 column of linear coefficients</br>known  list of indices to known rows in Z</br>Y  list of fixed values corresponding to known rows in Z</br>Aeq  meq by n list of linear equality constraint coefficients</br>Beq  meq by 1 list of linear equality constraint constant values</br>Aieq  mieq by n list of linear inequality constraint coefficients</br>Bieq  mieq by 1 list of linear inequality constraint constant values</br>lx  n by 1 list of lower bounds [] implies -Inf</br>ux  n by 1 list of upper bounds [] implies Inf</br>params  struct of additional parameters (see below)</br>Z  if not empty, is taken to be an n by 1 list of initial guess values (see output) |
|Returns| Z n by 1 list of solution values</br>Returns SOLVER_STATUS_CONVERGED = 0, SOLVER_STATUS_MAX_ITER = 1, SOLVER_STATUS_ERROR = 2, |
|Notes| For a harmonic solve on a mesh with 325K facets, matlab 2.2 secs, igl / min_quad_with_fixed.h 7.1 secs</br>Known Bugs : rows of[Aeq; Aieq] **must **be linearly independent.Should be using QR decomposition otherwise : http : //www.okstate.edu/sas/v8/sashtml/ormp/chap5/sect32.htm |


### adjacency_list
**`adjacency_list(f: array)`**

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
```


### adjacency_matrix
**`adjacency_matrix(f: array)`**

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
```


### all_pairs_distances
**`all_pairs_distances(u: array, v: array, squared: bool)`**

compute distances between each point i in V and point j in U

| | |
|-|-|
|Parameters| V  \#V by dim list of points</br>U  \#U by dim list of points</br>squared  whether to return squared distances |
|Returns| D  \#V by \#U matrix of distances, where D(i,j) gives the distance or squareed distance between V(i,:) and U(j,:) |

**Examples**
```python
D = all_pairs_distances(u,v)
```


### ambient_occlusion
**`ambient_occlusion(v: array, f: array, p: array, n: array, num_samples: int)`**


| | |
|-|-|
|Parameters| V  \#V by 3 list of mesh vertex positions</br>F  \#F by 3 list of mesh face indices into V</br>P  \#P by 3 list of origin points</br>N  \#P by 3 list of origin normals |
|Returns| S  \#P list of ambient occusion values between 1 (fully occluded) and 0 (not occluded) |


### arap_linear_block
**`arap_linear_block(v: array, f: array, d: int, energy: int)`**

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


### arap_linear_block_elements
**`arap_linear_block_elements(v: array, f: array, d: int)`**

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


### arap_linear_block_spokes
**`arap_linear_block_spokes(v: array, f: array, d: int)`**

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


### arap_linear_block_spokes_and_rims
**`arap_linear_block_spokes_and_rims(v: array, f: array, d: int)`**

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


### arap_rhs
**`arap_rhs(v: array, f: array, d: int, energy: int)`**

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


### average_onto_faces
**`average_onto_faces(f: array, s: array)`**

Move a scalar field defined on vertices to faces by averaging

| | |
|-|-|
|Parameters| f : \#f by ss list of simplexes/faces</br>s : \#v by dim list of per-vertex values |
|Returns| \#f by dim list of per-face values |
|See also| average_onto_vertices |


### average_onto_vertices
**`average_onto_vertices(v: array, f: array, s: array)`**

Move a scalar field defined on faces to vertices by averaging

| | |
|-|-|
|Parameters| v : \#v by vdim array of mesh vertices</br>f : \#f by simplex_count array of simplex indices</br>s : \#f by dim scalar field defined on simplices |
|Returns| sv: \#v by dim scalar field defined on vertices |
|See also| average_onto_faces |


### avg_edge_length
**`avg_edge_length(v: array, f: array) -> float`**

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
```


### barycenter
**`barycenter(v: array, f: array)`**

Compute the barycenter of every simplex

| | |
|-|-|
|Parameters| v : \#v x dim matrix of vertex coordinates</br>f : \#f x simplex_size  matrix of indices of simplex corners into V |
|Returns| A \#f x dim matrix where each row is the barycenter of each simplex |


### barycentric_coordinates_tet
**`barycentric_coordinates_tet(p: array, a: array, b: array, c: array, d: array)`**

Compute barycentric coordinates in a tet corresponding to the Euclidean coordinates in `p`.
The input arrays `a`, `b`, `c` and `d` are the vertices of each tet. I.e. one tet is
`a[i, :], b[i, :], c[i, :], d[:, i]`.

| | |
|-|-|
|Parameters| p : \#P by 3 Query points in 3d</br>a : \#P by 3 Tet corners in 3d</br>b : \#P by 3 Tet corners in 3d</br>c : \#P by 3 Tet corners in 3d</br>d : \#P by 3 Tet corners in 3d |
|Returns| \#P by 4 list of barycentric coordinates |


### barycentric_coordinates_tri
**`barycentric_coordinates_tri(p: array, a: array, b: array, c: array)`**

Compute barycentric coordinates in a triangle corresponding to the Euclidean coordinates in `p`.
The input arrays `a`, `b`, and `c` are the vertices of each triangle. I.e. one triangle is
`a[i, :], b[i, :], c[i, :]`.

| | |
|-|-|
|Parameters| p : \#P by 3 Query points in 3d</br>a : \#P by 3 Tri corners in 3d</br>b : \#P by 3 Tri corners in 3d</br>c : \#P by 3 Tri corners in 3d |
|Returns| \#P by 3 list of barycentric coordinates |


### bfs
**`bfs(A: sparse_matrix, s: int)`**

Construct an array indexing into a **directed** graph represented by an adjacency list using
breadth first search. I.e. the output is an array of vertices in breadth-first order.

| | |
|-|-|
|Parameters| A : \#V list of adjacency lists  or \#V by \#V adjacency matrix</br>s : starting node (index into A) |
|Returns| A tuple, (d, p) where:</br>* d is a \#V list of indices into rows of A in the order in which graph nodes are discovered</br>* p is a \#V list of indices of A of predecsors where -1 indicates root/not discovered. I.e.</br>p[i] is the index of the vertex v which preceded d[i] in the breadth first traversal.</br>Note that together, (d, p) form a spanning tree of the input graph |

**Examples**
```python
V, F, _ = igl.read_off("test.off")
A = igl.adjacency_matrix(V, F)
d, p = igl.bfs(A, V[0])
```


### bfs_orient
**`bfs_orient(f: array)`**

Consistently orient faces in orientable patches using BFS.

| | |
|-|-|
|Parameters| f : \#F by 3 list of faces |
|Returns| A tuple, (ff, c) where:</br>* ff is a \#F by 3 list of faces which are consistently oriented with</br>* c is a \#F array of connected component ids |

**Examples**
```python
v, f, _ = igl.read_off("test.off")
ff, c = igl.bfs_orient(f)
```


### biharmonic_coordinates
**`biharmonic_coordinates(v: array, t: array, s: List[List[int]], k: int = 2)`**

Compute "discrete biharmonic generalized barycentric coordinates" as
described in "Linear Subspace Design for Real-Time Shape Deformation"
[Wang et al. 2015]. Not to be confused with "Bounded Biharmonic Weights
for Real-Time Deformation" [Jacobson et al. 2011] or "Biharmonic
Coordinates" (2D complex barycentric coordinates) [Weber et al. 2012].
These weights minimize a discrete version of the squared Laplacian energy
subject to positional interpolation constraints at selected vertices
(point handles) and transformation interpolation constraints at regions
(region handles).

| | |
|-|-|
|Parameters| Templates: HType  should be a simple index type e.g. `int`,`size_t`</br>V  \#V by dim list of mesh vertex positions</br>T  \#T by dim+1 list of / triangle indices into V      if dim=2</br>\ tetrahedron indices into V   if dim=3</br>S  \#point-handles+\#region-handles list of lists of selected vertices for</br>each handle. Point handles should have singleton lists and region</br>handles should have lists of size at least dim+1 (and these points</br>should be in general position).</br>k  2-->biharmonic, 3-->triharmonic |
|Returns| W  \#V by \#points-handles+(\#region-handles * dim+1) matrix of weights so</br>that columns correspond to each handles generalized barycentric</br>coordinates (for point-handles) or animation space weights (for region</br>handles).</br>returns true only on success |

**Examples**
```python
MatrixXd W;
igl::biharmonic_coordinates(V,F,S,W);
const size_t dim = T.cols()-1;
MatrixXd H(W.cols(),dim);
{
int c = 0;
for(int h = 0;h<S.size();h++)
{
if(S[h].size()==1)
{
H.row(c++) = V.block(S[h][0],0,1,dim);
}else
{
H.block(c,0,dim+1,dim).setIdentity();
c+=dim+1;
}
}
}
assert( (V-(W*H)).array().maxCoeff() < 1e-7 );
```


### bijective_composite_harmonic_mapping
**`bijective_composite_harmonic_mapping(v: array, f: array, b: array, bc: array)`**

Compute a planar mapping of a triangulated polygon (V,F) subjected to
boundary conditions (b,bc). The mapping should be bijective in the sense
that no triangles' areas become negative (this assumes they started
positive). This mapping is computed by "composing" harmonic mappings
between incremental morphs of the boundary conditions. This is a bit like
a discrete version of "Bijective Composite Mean Value Mappings" [Schneider
et al. 2013] but with a discrete harmonic map (cf. harmonic coordinates)
instead of mean value coordinates. This is inspired by "Embedding a
triangular graph within a given boundary" [Xu et al. 2011].

| | |
|-|-|
|Parameters| V  \#V by 2 list of triangle mesh vertex positions</br>F  \#F by 3 list of triangle indices into V</br>b  \#b list of boundary indices into V</br>bc  \#b by 2 list of boundary conditions corresponding to b |
|Returns| U  \#V by 2 list of output mesh vertex locations</br>Returns true if and only if U contains a successful bijectie mapping |


### bijective_composite_harmonic_mapping_with_steps
**`bijective_composite_harmonic_mapping_with_steps(v: array, f: array, b: array, bc: array, min_steps: int, max_steps: int, num_inner_iters: int, test_for_flips: bool)`**


| | |
|-|-|
|Parameters| min_steps  minimum number of steps to take from V(b,:) to bc</br>max_steps  minimum number of steps to take from V(b,:) to bc (if max_steps == min_steps then no further number of steps will be tried)</br>num_inner_iters  number of iterations of harmonic solves to run after for each morph step (to try to push flips back in)</br>test_for_flips  whether to check if flips occurred (and trigger more steps). if test_for_flips = false then this function always returns</br>true |


### bone_parents
**`bone_parents(be: array)`**

BONE_PARENTS Recover "parent" bones from directed graph representation.

| | |
|-|-|
|Parameters| BE  \#BE by 2 list of directed bone edges |
|Returns| P  \#BE by 1 list of parent indices into BE, -1 means root. |


### boundary_conditions
**`boundary_conditions(v: array, ele: array, c: array, p: array, be: array, ce: array)`**

Compute boundary conditions for automatic weights computation. This
function expects that the given mesh (V,Ele) has sufficient samples
(vertices) exactly at point handle locations and exactly along bone and
cage edges.

| | |
|-|-|
|Parameters| V  \#V by dim list of domain vertices</br>Ele  \#Ele by simplex-size list of simplex indices</br>C  \#C by dim list of handle positions</br>P  \#P by 1 list of point handle indices into C</br>BE  \#BE by 2 list of bone edge indices into C</br>CE  \#CE by 2 list of cage edge indices into *P* |
|Returns| b  \#b list of boundary indices (indices into V of vertices which have</br>known, fixed values)</br>bc \#b by \#weights list of known/fixed values for boundary vertices</br>(notice the \#b != \#weights in general because \#b will include all the</br>intermediary samples along each bone, etc.. The ordering of the</br>weights corresponds to [P;BE]</br>Returns false if boundary conditions are suspicious:</br>P and BE are empty</br>bc is empty</br>some column of bc doesn't have a 0 (assuming bc has >1 columns)</br>some column of bc doesn't have a 1 (assuming bc has >1 columns) |


### boundary_facets
**`boundary_facets(t: array)`**

Determine boundary faces (edges) of tetrahedra (triangles).

| | |
|-|-|
|Parameters| t : tetrahedron or triangle index list, m by 4/3, where m is the number of tetrahedra/triangles |
|Returns| f : list of boundary faces, n by 3/2, where n is the number of boundary faces/edges |

**Examples**
```python
# Mesh in (v, f)
b = boundary_facets(f)
```


### boundary_loop
**`boundary_loop(f: array)`**

Compute ordered boundary loops for a manifold mesh and return the longest loop in terms of vertices.

| | |
|-|-|
|Parameters| f : \#v by dim array of mesh faces |
|Returns| l : ordered list of boundary vertices of longest boundary loop |

**Examples**
```python
# Mesh in (v, f)
l = boundary_loop(f)
```


### bounding_box
**`bounding_box(*args, **kwargs)`**

### bounding_box
**`bounding_box(v: array)`**

Build a triangle mesh of the bounding box of a given list of vertices

| | |
|-|-|
|Parameters| V  \#V by dim list of rest domain positions |
|Returns| BV  2^dim by dim list of bounding box corners positions</br>BF  \#BF by dim list of simplex facets |


### bounding_box
**`bounding_box(v: array, pad: float)`**

Build a triangle mesh of the bounding box of a given list of vertices

| | |
|-|-|
|Parameters| V  \#V by dim list of rest domain positions |
|Returns| BV  2^dim by dim list of bounding box corners positions</br>BF  \#BF by dim list of simplex facets |


### bounding_box_diagonal
**`bounding_box_diagonal(v: array) -> float`**

Compute the length of the diagonal of a given meshes axis-aligned bounding

| | |
|-|-|
|Parameters| V  \#V by 3 list of vertex positions |
|Returns| Returns length of bounding box diagonal |


### circulation
**`circulation(e: int, ccw: bool, emap: array, ef: array, ei: array) -> List[int]`**

Return list of faces around the end point of an edge. Assumes
data-structures are built from an edge-manifold **closed** mesh.

| | |
|-|-|
|Parameters| e  index into E of edge to circulate</br>ccw  whether to _continue_ in ccw direction of edge (circulate around</br>E(e,1))</br>EMAP \#F*3 list of indices into E, mapping each directed edge to unique</br>unique edge in E</br>EF  \#E by 2 list of edge flaps, EF(e,0)=f means e=(i-->j) is the edge of</br>F(f,:) opposite the vth corner, where EI(e,0)=v. Similarly EF(e,1) "</br>e=(j->i)</br>EI  \#E by 2 list of edge flap corners (see above). |
|Returns| Returns list of faces touched by circulation (in cyclically order). |


### circumradius
**`circumradius(v: array, f: array)`**

Compute the circumradius of each triangle in a mesh (V,F)

| | |
|-|-|
|Parameters| V  \#V by dim list of mesh vertex positions</br>F  \#F by 3 list of triangle indices into V |
|Returns| R  \#F list of circumradii |

**Examples**
```python
R = circumradius(V, F)
```


### collapse_small_triangles
**`collapse_small_triangles(v: array, f: array, eps: float)`**

Given a triangle mesh (V,F) compute a new mesh (VV,FF) which contains the
original faces and vertices of (V,F) except any small triangles have been
removed via collapse.
We are *not* following the rules in "Mesh Optimization" [Hoppe et al]
Section 4.2. But for our purposes we don't care about this criteria.

| | |
|-|-|
|Parameters| V  \#V by 3 list of vertex positions</br>F  \#F by 3 list of triangle indices into V</br>eps  epsilon for smallest allowed area treated as fraction of squared bounding box</br>diagonal |
|Returns| FF  \#FF by 3 list of triangle indices into V |


### comb_cross_field
**`comb_cross_field(v: array, f: array, pd1in: array, pd2in: array)`**


| | |
|-|-|
|Parameters| V          \#V by 3 eigen Matrix of mesh vertex 3D positions</br>F          \#F by 3 eigen Matrix of face indices</br>PD1in      \#F by 3 eigen Matrix of the first per face cross field vector</br>PD2in      \#F by 3 eigen Matrix of the second per face cross field vector |
|Returns| PD1out      \#F by 3 eigen Matrix of the first combed cross field vector</br>PD2out      \#F by 3 eigen Matrix of the second combed cross field vector |


### comb_frame_field
**`comb_frame_field(v: array, f: array, pd1: array, pd2: array, bis1_combed: array, bis2_combed: array)`**


| | |
|-|-|
|Parameters| V            \#V by 3 eigen Matrix of mesh vertex 3D positions</br>F            \#F by 3 eigen Matrix of face indices</br>PD1          \#F by 3 eigen Matrix of the first per face cross field vector</br>PD2          \#F by 3 eigen Matrix of the second per face cross field vector</br>BIS1_combed  \#F by 3 eigen Matrix of the first combed bisector field vector</br>BIS2_combed  \#F by 3 eigen Matrix of the second combed bisector field vector |
|Returns| PD1_combed  \#F by 3 eigen Matrix of the first combed cross field vector</br>PD2_combed  \#F by 3 eigen Matrix of the second combed cross field vector |


### comb_line_field
**`comb_line_field(v: array, f: array, pd1in: array)`**


| | |
|-|-|
|Parameters| V          \#V by 3 eigen Matrix of mesh vertex 3D positions</br>F          \#F by 3 eigen Matrix of face indices</br>PD1in      \#F by 3 eigen Matrix of the first per face cross field vector |
|Returns| PD1out      \#F by 3 eigen Matrix of the first combed cross field vector |


### compute_frame_field_bisectors
**`compute_frame_field_bisectors(v: array, f: array, b1: array, b2: array, pd1: array, pd2: array)`**

Compute bisectors of a frame field defined on mesh faces

| | |
|-|-|
|Parameters| V     \#V by 3 eigen Matrix of mesh vertex 3D positions</br>F     \#F by 3 eigen Matrix of face (triangle) indices</br>B1    \#F by 3 eigen Matrix of face (triangle) base vector 1</br>B2    \#F by 3 eigen Matrix of face (triangle) base vector 2</br>PD1   \#F by 3 eigen Matrix of the first per face frame field vector</br>PD2   \#F by 3 eigen Matrix of the second per face frame field vector |
|Returns| BIS1  \#F by 3 eigen Matrix of the first per face frame field bisector</br>BIS2  \#F by 3 eigen Matrix of the second per face frame field bisector |


### compute_frame_field_bisectors_no_basis
**`compute_frame_field_bisectors_no_basis(v: array, f: array, pd1: array, pd2: array)`**

Wrapper without given basis vectors.

| | |
|-|-|
|Parameters|  |


### connect_boundary_to_infinity
**`connect_boundary_to_infinity(f: array)`**

Connect all boundary edges to a fictitious point at infinity.

| | |
|-|-|
|Parameters| F  \#F by 3 list of face indices into some V |
|Returns| FO  \#F+\#O by 3 list of face indices into [V;inf inf inf], original F are</br>guaranteed to come first. If (V,F) was a manifold mesh, now it is</br>closed with a possibly non-manifold vertex at infinity (but it will be</br>edge-manifold). |


### connect_boundary_to_infinity_face
**`connect_boundary_to_infinity_face(v: array, f: array)`**


| | |
|-|-|
|Parameters| F  \#F by 3 list of face indices into some V |
|Returns| FO  \#F+\#O by 3 list of face indices into VO |


### connect_boundary_to_infinity_index
**`connect_boundary_to_infinity_index(f: array, inf_index: int)`**


| | |
|-|-|
|Parameters| inf_index  index of point at infinity (usually V.rows() or F.maxCoeff()) |


### connected_components
**`connected_components(a: sparse_matrix)`**

Determine the connected components of a graph described by the input
adjacency matrix (similar to MATLAB's graphconncomp).

| | |
|-|-|
|Parameters| A  \#A by \#A adjacency matrix (treated as describing an undirected graph) |
|Returns| Returns number of connected components</br>C  \#A list of component indices into [0,\#K-1]</br>K  \#K list of sizes of each component |


### cotmatrix
**`cotmatrix(v: array, f: array)`**

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
```


### cotmatrix_entries
**`cotmatrix_entries(v: array, f: array)`**

COTMATRIX_ENTRIES compute the cotangents of each angle in mesh (V,F)

| | |
|-|-|
|Parameters| V  \#V by dim list of rest domain positions</br>F  \#F by {34} list of {triangletetrahedra} indices into V |
|Returns| C  \#F by 3 list of 1/2*cotangents corresponding angles</br>for triangles, columns correspond to edges [1,2],[2,0],[0,1]</br>OR</br>C  \#F by 6 list of 1/6*cotangents of dihedral angles*edge lengths</br>for tets, columns along edges [1,2],[2,0],[0,1],[3,0],[3,1],[3,2] |


### cotmatrix_intrinsic
**`cotmatrix_intrinsic(l: array, f: array)`**

Constructs the cotangent stiffness matrix (discrete laplacian) for a given
mesh with faces F and edge lengths l.

| | |
|-|-|
|Parameters| l  \#F by 3 list of (half-)edge lengths</br>F  \#F by 3 list of face indices into some (not necessarily</br>determined/embedable) list of vertex positions V. It is assumed \#V ==</br>F.maxCoeff()+1 |
|Returns| L  \#V by \#V sparse Laplacian matrix |
|See also| cotmatrix, intrinsic_delaunay_cotmatrix |


### cross_field_mismatch
**`cross_field_mismatch(v: array, f: array, pd1: array, pd2: array, is_combed: bool)`**


| | |
|-|-|
|Parameters| V         \#V by 3 eigen Matrix of mesh vertex 3D positions</br>F         \#F by 3 eigen Matrix of face indices</br>PD1       \#F by 3 eigen Matrix of the first per face cross field vector</br>PD2       \#F by 3 eigen Matrix of the second per face cross field vector</br>isCombed  boolean, specifying whether the field is combed (i.e. matching has been precomputed.</br>If not, the field is combed first. |
|Returns| Handle_MMatch    \#F by 3 eigen Matrix containing the integer mismatch of the cross field</br>across all face edges |


### crouzeix_raviart_cotmatrix
**`crouzeix_raviart_cotmatrix(v: array, f: array)`**

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
```


### crouzeix_raviart_cotmatrix_known_e
**`crouzeix_raviart_cotmatrix_known_e(v: array, f: array, e: array, emap: array)`**

wrapper if E and EMAP are already computed (better match!)

| | |
|-|-|
|Parameters|  |


### crouzeix_raviart_massmatrix
**`crouzeix_raviart_massmatrix(v: array, f: array)`**

CROUZEIX_RAVIART_MASSMATRIX Compute the Crouzeix-Raviart mass matrix where
M(e,e) is just the sum of the areas of the triangles on either side of an
edge e.

| | |
|-|-|
|Parameters| V  \#V by dim list of vertex positions</br>F  \#F by 3 / 4 list of triangle/tetrahedron indices |
|Returns| M  \#E by \#E edge/face-based diagonal mass matrix</br>E  \#E by 2 / 3 list of edges/faces</br>EMAP  \#F*3 / 4 list of indices mapping allE to E |
|See also| crouzeix_raviart_cotmatrix |
|Notes| See for example "Discrete Quadratic Curvature Energies" [Wardetzky, Bergou,</br>Harmon, Zorin, Grinspun 2007] |


### crouzeix_raviart_massmatrix_known_e
**`crouzeix_raviart_massmatrix_known_e(v: array, f: array, e: array, emap: array)`**

wrapper if E and EMAP are already computed (better match!)

| | |
|-|-|
|Parameters|  |


### cut_mesh
**`cut_mesh(v: array, f: array, cuts: array)`**

Compute the barycenter of every simplex

| | |
|-|-|
|Parameters| v : \#v x dim matrix of vertex coordinates</br>f : \#f x simplex_size  matrix of indices of simplex corners into V</br>cuts : \#F by 3 list of boolean flags, indicating the edges that need to</br>be cut (has 1 at the face edges that are to be cut, 0 otherwise) |
|Returns| A pair (vcut, fcut) where:</br>* vcut is a \#v by 3 list of the vertex positions</br>of the cut mesh. This matrix will be similar to the original vertices except</br>some rows will be duplicated.</br>* fcut is a \#f by 3 list of the faces of the cut mesh (must be triangles). This</br>matrix will be similar to the original face matrix except some indices</br>will be redirected to point to the newly duplicated vertices. |


### cut_mesh_from_singularities
**`cut_mesh_from_singularities(v: array, f: array, mismatch: array)`**

Given a mesh (v,f) and the integer mismatch of a cross field per edge
(mismatch), finds and returns the cut_graph connecting the singularities
(seams)

| | |
|-|-|
|Parameters| v : \#v by 3 array of triangle vertices (each row is a vertex)</br>f : \#f by 3 array of triangle indices into v</br>mismatch : \#f by 3 array of per-corner integer mismatches |
|Returns| seams : \#f by 3 array of per corner booleans that denotes if an edge is a</br>seam or not |
|See also| cut_mesh |


### cut_to_disk
**`cut_to_disk(f: array) -> List[List[int]]`**

Given a triangle mesh, computes a set of edge cuts sufficient to carve the
mesh into a topological disk, without disconnecting any connected components.
Nothing else about the cuts (including number, total length, or smoothness)
is guaranteed to be optimal.
Simply-connected components without boundary (topological spheres) are left
untouched (delete any edge if you really want a disk).
All other connected components are cut into disks. Meshes with boundary are
supported; boundary edges will be included as cuts.
The cut mesh it can be materialized using cut_mesh().
Implements the triangle-deletion approach described by Gu et al's
"Geometry Images."

| | |
|-|-|
|Parameters| F  \#F by 3 list of the faces (must be triangles) |
|Returns| cuts  List of cuts. Each cut is a sequence of vertex indices (where</br>pairs of consecutive vertices share a face), is simple, and is either</br>a closed loop (in which the first and last indices are identical) or</br>an open curve. Cuts are edge-disjoint. |


### cylinder
**`cylinder(axis_devisions: int, height_devisions: int)`**

Construct a triangle mesh of a cylinder (without caps)

| | |
|-|-|
|Parameters| axis_devisions  number of vertices _around the cylinder_</br>height_devisions  number of vertices _up the cylinder_ |
|Returns| V  \#V by 3 list of mesh vertex positions</br>F  \#F by 3 list of triangle indices into V |


### decimate
**`decimate(v: array, f: array, max_m: int)`**

Assumes (V,F) is a manifold mesh (possibly with boundary) Collapses edges
until desired number of faces is achieved. This uses default edge cost and
merged vertex placement functions {edge length, edge midpoint}.

| | |
|-|-|
|Parameters| V  \#V by dim list of vertex positions</br>F  \#F by 3 list of face indices into V.</br>max_m  desired number of output faces |
|Returns| U  \#U by dim list of output vertex posistions (can be same ref as V)</br>G  \#G by 3 list of output face indices into U (can be same ref as G)</br>J  \#G list of indices into F of birth face</br>I  \#U list of indices into V of birth vertices</br>Returns true if m was reached (otherwise \#G > m) |


### deform_skeleton
**`deform_skeleton(c: array, be: array, t: array)`**

Deform a skeleton.

| | |
|-|-|
|Parameters| C  \#C by 3 list of joint positions</br>BE \#BE by 2 list of bone edge indices</br>T  \#BE*4 by 3 list of stacked transformation matrix |
|Returns| CT  \#BE*2 by 3 list of deformed joint positions</br>BET  \#BE by 2 list of bone edge indices (maintains order) |


### delaunay_triangulation
**`delaunay_triangulation(v: array)`**

Given a set of points in 2D, return a Delaunay triangulation of these
points.

| | |
|-|-|
|Parameters| V  \#V by 2 list of vertex positions |
|Returns| F  \#F by 3 of faces in Delaunay triangulation. |


### dihedral_angles
**`dihedral_angles(v: array, t: array)`**

Compute dihedral angles for all tets of a given tet mesh (v, t).

| | |
|-|-|
|Parameters| v : \#v by 3 list of vertex positions</br>t : \#v by 4 list of tet indices |
|Returns| theta : \#t by 6 list of dihedral angles (in radians)</br>cos_theta : \#t by 6 list of cosine of dihedral angles (in radians) |

**Examples**
```python
# TetMesh in (v, t)
theta, cos_theta = dihedral_angles(v, t)
```


### dihedral_angles_intrinsic
**`dihedral_angles_intrinsic(l: array, a: array)`**

See dihedral_angles for the documentation.
### directed_edge_orientations
**`directed_edge_orientations(c: array, e: array)`**

Determine rotations that take each edge from the x-axis to its given rest
orientation.

| | |
|-|-|
|Parameters| C  \#C by 3 list of edge vertex positions</br>E  \#E by 2 list of directed edges |
|Returns| Q  \#E list of quaternions |


### directed_edge_parents
**`directed_edge_parents(e: array)`**

Recover "parents" (preceding edges) in a tree given just directed edges.

| | |
|-|-|
|Parameters| e : \#e by 2 list of directed edges |
|Returns| p : \#e list of parent indices into e. (-1) means root |

**Examples**
```python
e.np.random.randint(0, 10, size=(10, 2))
p = directed_edge_parents(e)
```


### doublearea
**`doublearea(v: array, f: array)`**

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
```


### dqs
**`dqs(v: array, w: array, v_q: array, v_t: array)`**

Dual quaternion skinning

| | |
|-|-|
|Parameters| V  \#V by 3 list of rest positions</br>W  \#W by \#C list of weights</br>vQ  \#C list of rotation quaternions</br>vT  \#C list of translation vectors |
|Returns| U  \#V by 3 list of new positions |


### ears
**`ears(f: array)`**

FIND_EARS  Find all ears (faces with two boundary edges) in a given mesh

| | |
|-|-|
|Parameters| F  \#F by 3 list of triangle mesh indices |
|Returns| ears  \#ears list of indices into F of ears</br>ear_opp  \#ears list of indices indicating which edge is non-boundary</br>(connecting to flops) |

**Examples**
```python
ears,ear_opp = find_ears(F)
```


### edge_collapse_is_valid
**`edge_collapse_is_valid(edge: int, F: array, E: array, EMAP: array, EF: array, EI: array) -> bool`**

Assumes (V,F) is a closed manifold mesh (except for previouslly collapsed faces which should be set to:
[IGL_COLLAPSE_EDGE_NULL IGL_COLLAPSE_EDGE_NULL IGL_COLLAPSE_EDGE_NULL].
Tests whether collapsing exactly two faces and exactly 3 edges from E (e
and one side of each face gets collapsed to the other) will result in a
mesh with the same topology.

| | |
|-|-|
|Parameters| e  index into E of edge to try to collapse. E(e,:) = [s d] or [d s] so that s<d, then d is collapsed to s.</br>F  \#F by 3 list of face indices into V.</br>E  \#E by 2 list of edge indices into V.</br>EMAP \#F*3 list of indices into E, mapping each directed edge to unique unique edge in E</br>EF  \#E by 2 list of edge flaps, EF(e,0)=f means e=(i-->j) is the edge of F(f,:) opposite the vth corner, where EI(e,0)=v. Similarly EF(e,1) "e=(j->i)</br>EI  \#E by 2 list of edge flap corners (see above). |
|Returns| Returns true if edge collapse is valid |


### edge_flaps
**`edge_flaps(f: array)`**

Determine "edge flaps": two faces on either side of a unique edge (assumes edge-manifold mesh)

| | |
|-|-|
|Parameters| F  \#F by 3 list of face indices |
|Returns| E  \#E by 2 list of edge indices into V.</br>EMAP \#F*3 list of indices into E, mapping each directed edge to unique</br>unique edge in E</br>EF  \#E by 2 list of edge flaps, EF(e,0)=f means e=(i-->j) is the edge of</br>F(f,:) opposite the vth corner, where EI(e,0)=v. Similarly EF(e,1) "</br>e=(j->i)</br>EI  \#E by 2 list of edge flap corners (see above). |


### edge_lengths
**`edge_lengths(v: array, f: array)`**

Constructs a list of lengths of edges opposite each index in a face
(triangle/tet) list

| | |
|-|-|
|Parameters| V  eigen matrix \#V by 3</br>F  \#F by 2 list of mesh edges or</br>F  \#F by 3 list of mesh faces (must be triangles) or</br>T  \#T by 4 list of mesh elements (must be tets) |
|Returns| L  \#F by {136} list of edge lengths</br>for edges, column of lengths</br>for triangles, columns correspond to edges [1,2],[2,0],[0,1]</br>for tets, columns correspond to edges</br>[3 0],[3 1],[3 2],[1 2],[2 0],[0 1] |


### edge_topology
**`edge_topology(v: array, f: array)`**

Initialize Edges and their topological relations (assumes an edge-manifold mesh)

| | |
|-|-|
|Parameters| v : \#v by dim, list of mesh vertex positions (unused)</br>f : \#f by 3, list of triangle indices into V |
|Returns| ev : \#e by 2, list of edges described as pair of vertices.</br>fe : \#f by 3, list storing triangle-edge relation.</br>ef : \#e by w, list storing edge-triangle relation, uses -1 to indicate boundaries. |

**Examples**
```python
# Mesh in (v, f)
ev, fe, ef = edge_topology(v, f)
```


### edges
**`edges(f: array)`**

Constructs a list of unique edges represented in a given mesh (v, f)

| | |
|-|-|
|Parameters| f : \#F by dim list of mesh faces (must be triangles or tets) |
|Returns| \#e by 2 list of edges in no particular order |
|See also| adjacency_matrix |

**Examples**
```python
V, F, _ = igl.read_off("test.off")
E = igl.edges(F)
```


### edges_to_path
**`edges_to_path(e: array)`**

EDGES_TO_PATH Given a set of undirected, unique edges such that all form a
single connected compoent with exactly 0 or 2 nodes with valence =1,
determine the/a path visiting all nodes.

| | |
|-|-|
|Parameters| E  \#E by 2 list of undirected edges |
|Returns| I  \#E+1 list of nodes in order tracing the chain (loop), if the output</br>is a loop then I(1) == I(end)</br>J  \#I-1 list of indices into E of edges tracing I</br>K  \#I-1 list of indices into columns of E {1,2} so that K(i) means that</br>E(i,K(i)) comes before the other (i.e., E(i,3-K(i)) ). This means that</br>I(i) == E(J(i),K(i)) for i<\#I, or</br>I == E(sub2ind(size(E),J([1:end end]),[K;3-K(end)])))) |


### euler_characteristic
**`euler_characteristic(f: array) -> int`**

Computes the Euler characteristic of a given mesh (V,F)

| | |
|-|-|
|Parameters| F \#F by dim list of mesh faces (must be triangles) |
|Returns| Returns An int containing the Euler characteristic |


### euler_characteristic_complete
**`euler_characteristic_complete(v: array, f: array) -> int`**


| | |
|-|-|
|Parameters| V       \#V by dim list of mesh vertex positions |


### exact_geodesic
**`exact_geodesic(v: array, f: array, vs: array, vt: array, fs: numpy.array  None = None, ft: numpy.array  None = None)`**

Exact geodesic algorithm for the calculation of geodesics on a triangular mesh.

| | |
|-|-|
|Parameters| v : \#v by 3 array of 3D vertex positions</br>f : \#f by 3 array of mesh faces</br>vs : \#vs by 1 array specifying indices of source vertices</br>fs : \#fs by 1 array specifying indices of source faces</br>vt : \#vt by 1 array specifying indices of target vertices</br>ft : \#ft by 1 array specifying indices of target faces |
|Returns| d : \#vt+\#ft by 1 array of geodesic distances of each target w.r.t. the nearest one in the source set |
|Notes| Specifying a face as target/source means its center.</br>Implementation from https:code.google.com/archive/p/geodesic/ with the algorithm first described by Mitchell, Mount and Papadimitriou in 1987. |


### exterior_edges
**`exterior_edges(f: array)`**

EXTERIOR_EDGES Determines boundary "edges" and also edges with an
odd number of occurrences where seeing edge (i,j) counts as +1 and seeing
the opposite edge (j,i) counts as -1

| | |
|-|-|
|Parameters| F  \#F by simplex_size list of "faces" |
|Returns| E  \#E by simplex_size-1  list of exterior edges |


### extract_manifold_patches
**`extract_manifold_patches(f: array)`**

Extract a set of maximal patches from a given mesh.
A maximal patch is a subset of the input faces that are connected via
manifold edges; a patch is as large as possible.

| | |
|-|-|
|Parameters| F  \#F by 3 list representing triangles. |
|Returns| number of manifold patches.</br>P  \#F list of patch indices. |


### extract_non_manifold_edge_curves
**`extract_non_manifold_edge_curves(f: array, u_e2_e: List[List[int]]) -> List[List[int]]`**

Extract non-manifold curves from a given mesh.
A non-manifold curves are a set of connected non-manifold edges that
does not touch other non-manifold edges except at the end points.
They are also maximal in the sense that they cannot be expanded by
including more edges.
Assumes the input mesh have all -intersection resolved.  See ``igl::cgal::remesh__intersection`` for more details.

| | |
|-|-|
|Parameters| F  \#F by 3 list representing triangles.</br>uE2E  \#uE list of lists of indices into E of coexisting edges. |
|Returns| curves  An array of arries of unique edge indices. |


### facet_components
**`facet_components(f: array)`**

Compute connected components of facets based on edge-edge adjacency,

| | |
|-|-|
|Parameters| f : \#f x 3 array of triangle indices |
|Returns| An array, c, with shape (\#f,), of component ids |
|See also| vertex_components</br>vertex_components_from_adjacency_matrix |


### face_occurrences
**`face_occurrences(f: array)`**

Count the occruances of each face (row) in a list of face indices (irrespecitive of order)

| | |
|-|-|
|Parameters| F  \#F by simplex-size |
|Returns| C  \#F list of counts |
|Notes| Known bug: triangles/tets only (where ignoring order still gives simplex) |


### faces_first
**`faces_first(v: array, f: array)`**

FACES_FIRST Reorder vertices so that vertices in face list come before
vertices that don't appear in the face list. This is especially useful if
the face list contains only surface faces and you want surface vertices
listed before internal vertices
[RV,RF,IM] = faces_first(V,T);

| | |
|-|-|
|Parameters| V  \# vertices by 3 vertex positions</br>F  \# faces by 3 list of face indices |
|Returns| RV  \# vertices by 3 vertex positions, order such that if the jth vertex is</br>some face in F, and the kth vertex is not then j comes before k</br>RF  \# faces by 3 list of face indices, reindexed to use RV</br>IM  \#V by 1 list of indices such that: RF = IM(F) and RT = IM(T)</br>and RV(IM,:) = V |

**Examples**
```python
Tet mesh in (V,T,F)
```


### faces_first
**`faces_first(V,F,IM);`**

T = T.unaryExpr(bind1st(mem_fun( static_cast<VectorXi::Scalar&
(VectorXi::*)(VectorXi::Index)>(&VectorXi::operator())),
&IM)).eval();
### false_barycentric_subdivision
**`false_barycentric_subdivision(v: array, f: array)`**

Refine the mesh by adding the barycenter of each face

| | |
|-|-|
|Parameters| V       \#V by 3 coordinates of the vertices</br>F       \#F by 3 list of mesh faces (must be triangles) |
|Returns| VD      \#V + \#F by 3 coordinate of the vertices of the dual mesh</br>The added vertices are added at the end of VD (should not be</br>same references as (V,F)</br>FD      \#F*3 by 3 faces of the dual mesh |


### fast_winding_number_for_meshes
**`fast_winding_number_for_meshes(v: array, f: array, q: array)`**

Compute approximate winding number of a triangle soup mesh according to
"Fast Winding Numbers for Soups and Clouds" [Barill et al. 2018].

| | |
|-|-|
|Parameters| V  \#V by 3 list of mesh vertex positions</br>F  \#F by 3 list of triangle mesh indices into rows of V</br>Q  \#Q by 3 list of query points for the winding number |
|Returns| WN  \#Q by 1 list of windinng number values at each query point |


### fast_winding_number_for_points
**`fast_winding_number_for_points(p: array, n: array, a: array, q: array)`**

Evaluate the fast winding number for point data, with default expansion
order and beta (both are set to 2).
This function performes the precomputation and evaluation all in one.
If you need to acess the precomuptation for repeated evaluations, use the
two functions designed for exposed precomputation (described above).

| | |
|-|-|
|Parameters| P  \#P by 3 list of point locations</br>N  \#P by 3 list of point normals</br>A  \#P by 1 list of point areas</br>Q  \#Q by 3 list of query points for the winding number |
|Returns| WN  \#Q by 1 list of windinng number values at each query point |


### find_cross_field_singularities
**`find_cross_field_singularities(v: array, f: array, handle_m_match: array)`**

Computes singularities of a cross field, assumed combed

| | |
|-|-|
|Parameters| V                \#V by 3 eigen Matrix of mesh vertex 3D positions</br>F                \#F by 3 eigen Matrix of face indices</br>Handle_MMatch    \#F by 3 eigen Matrix containing the integer missmatch of the cross field</br>across all face edges |
|Returns| isSingularity    \#V by 1 boolean eigen Vector indicating the presence of a singularity on a vertex</br>singularityIndex \#V by 1 integer eigen Vector containing the singularity indices |


### find_cross_field_singularities_from_field
**`find_cross_field_singularities_from_field(v: array, f: array, pd1: array, pd2: array, is_combed: bool = False)`**

Wrapper that calculates the missmatch if it is not provided.
Note that the field in PD1 and PD2 MUST BE combed (see igl::comb_cross_field).

| | |
|-|-|
|Parameters| V                \#V by 3 eigen Matrix of mesh vertex 3D positions</br>F                \#F by 3 eigen Matrix of face (quad) indices</br>PD1              \#F by 3 eigen Matrix of the first per face cross field vector</br>PD2              \#F by 3 eigen Matrix of the second per face  cross field vector |
|Returns| isSingularity    \#V by 1 boolean eigen Vector indicating the presence of a singularity on a vertex</br>singularityIndex \#V by 1 integer eigen Vector containing the singularity indices |


### fit_plane
**`fit_plane(v: array)`**

This function fits a plane to a point cloud.

| | |
|-|-|
|Parameters| V \#Vx3 matrix. The 3D point cloud, one row for each vertex. |
|Returns| N 1x3 Vector. The normal of the fitted plane.</br>C 1x3 Vector. A point that lies in the fitted plane. |
|Notes| From http:missingbytes.blogspot.com/2012/06/fitting-plane-to-point-cloud.html |


### flip_avoiding_line_search
**`flip_avoiding_line_search(f: array, cur_v: array, dst_v: array, energy: Callable[[numpy.ndarray], float], cur_energy: float)`**

A bisection line search for a mesh based energy that avoids triangle flips as suggested in
"Bijective Parameterization with Free Boundaries" (Smith J. and Schaefer S., 2015).
The user specifies an initial vertices position (that has no flips) and target one (that my have flipped triangles).
This method first computes the largest step in direction of the destination vertices that does not incur flips, and then minimizes a given energy using this maximal step and a bisection linesearch (see igl::line_search).
Supports both triangle and tet meshes.

| | |
|-|-|
|Parameters| F         \#F by 3 / 4 list of mesh faces or tets</br>cur_v     \#V by dim list of variables</br>dst_v     \#V by dim list of target vertices. This mesh may have flipped triangles</br>energy    A function to compute the mesh-based energy (return an energy that is bigger than 0)</br>cur_energy(OPTIONAL)         The energy at the given point. Helps save redundant c  omputations. This is optional. If not specified, the function will compute it. |
|Returns| cur_v     \#V by dim list of variables at the new location</br>Returns the energy at the new point |


### flipped_triangles
**`flipped_triangles(v: array, f: array)`**

Finds the ids of the flipped triangles of the mesh V,F in the UV mapping uv

| | |
|-|-|
|Parameters| V  \#V by 2 list of mesh vertex positions</br>F  \#F by 3 list of mesh faces (must be triangles) |
|Returns| X  \#flipped list of containing the indices into F of the flipped triangles |


### forward_kinematics
**`forward_kinematics(c: array, be: array, p: array, d_q: array, d_t: array)`**

Given a skeleton and a set of relative bone rotations compute absolute rigid transformations for each bone.

| | |
|-|-|
|Parameters| C  \#C by dim list of joint positions</br>BE  \#BE by 2 list of bone edge indices</br>P  \#BE list of parent indices into BE</br>dQ  \#BE list of relative rotations</br>dT  \#BE list of relative translations |
|Returns| vQ  \#BE list of absolute rotations</br>vT  \#BE list of absolute translations |


### gaussian_curvature
**`gaussian_curvature(v: array, f: array)`**

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
```


### grad
**`grad(v: array, f: array, uniform: bool = False)`**

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
```


### grad_intrinsic
**`grad_intrinsic(l: array, f: array)`**

GRAD_INTRINSIC Construct an intrinsic gradient operator.

| | |
|-|-|
|Parameters| l  \#F by 3 list of edge lengths</br>F  \#F by 3 list of triangle indices into some vertex list V |
|Returns| G  \#F*2 by \#V gradient matrix: G=[Gx;Gy] where x runs along the 23 edge and</br>y runs in the counter-clockwise 90° rotation. |


### harmonic
**`harmonic(v: array, f: array, b: array, bc: array, k: int)`**

Compute k-harmonic weight functions "coordinates".

| | |
|-|-|
|Parameters| V  \#V by dim vertex positions</br>F  \#F by simplex-size list of element indices</br>b  \#b boundary indices into V</br>bc \#b by \#W list of boundary values</br>k  power of harmonic operation (1: harmonic, 2: biharmonic, etc) |
|Returns| W  \#V by \#W list of weights |


### harmonic_from_laplacian_and_mass
**`harmonic_from_laplacian_and_mass(l: sparse_matrix, m: sparse_matrix, b: array, bc: array, k: int)`**

Compute a harmonic map using a given Laplacian and mass matrix

| | |
|-|-|
|Parameters| L  \#V by \#V discrete (integrated) Laplacian</br>M  \#V by \#V mass matrix</br>b  \#b boundary indices into V</br>bc  \#b by \#W list of boundary values</br>k  power of harmonic operation (1: harmonic, 2: biharmonic, etc) |
|Returns| W  \#V by \#V list of weights |


### harmonic_integrated
**`harmonic_integrated(v: array, f: array, k: int)`**


| | |
|-|-|
|Parameters| V  \#V by dim vertex positions</br>F  \#F by simplex-size list of element indices</br>k  power of harmonic operation (1: harmonic, 2: biharmonic, etc) |
|Returns| Q  \#V by \#V discrete (integrated) k-Laplacian |


### harmonic_integrated_from_laplacian_and_mass
**`harmonic_integrated_from_laplacian_and_mass(l: sparse_matrix, m: sparse_matrix, k: int)`**

Build the discrete k-harmonic operator (computing integrated quantities).
That is, if the k-harmonic PDE is Q x = 0, then this minimizes x' Q x

| | |
|-|-|
|Parameters| L  \#V by \#V discrete (integrated) Laplacian</br>M  \#V by \#V mass matrix</br>k  power of harmonic operation (1: harmonic, 2: biharmonic, etc) |
|Returns| Q  \#V by \#V discrete (integrated) k-Laplacian |


### harmonic_uniform_laplacian
**`harmonic_uniform_laplacian(f: array, b: array, bc: array, k: int)`**

Compute harmonic map using uniform laplacian operator

| | |
|-|-|
|Parameters| F  \#F by simplex-size list of element indices</br>b  \#b boundary indices into V</br>bc \#b by \#W list of boundary values</br>k  power of harmonic operation (1: harmonic, 2: biharmonic, etc) |
|Returns| W  \#V by \#W list of weights |


### hausdorff
**`hausdorff(va: array, fa: array, vb: array, fb: array) -> float`**

HAUSDORFF compute the Hausdorff distance between mesh (VA,FA) and mesh
(VB,FB). This is the
d(A,B) = max ( max min d(a,b) , max min d(b,a) )
a∈A b∈B          b∈B a∈A

| | |
|-|-|
|Parameters| VA  \#VA by 3 list of vertex positions</br>FA  \#FA by 3 list of face indices into VA</br>VB  \#VB by 3 list of vertex positions</br>FB  \#FB by 3 list of face indices into VB |
|Returns| d  hausdorff distance</br>pair  2 by 3 list of "determiner points" so that pair(1,:) is from A</br>and pair(2,:) is from B |
|Notes| Known issue: This is only computing max(min(va,B),min(vb,A)). This is</br>better than max(min(va,Vb),min(vb,Va)). This (at least) is missing</br>"edge-edge" cases like the distance between the two different</br>triangulations of a non-planar quad in 3D. Even simpler, consider the</br>Hausdorff distance between the non-convex, block letter V polygon (with 7</br>vertices) in 2D and its convex hull. The Hausdorff distance is defined by</br>the midpoint in the middle of the segment across the concavity and some</br>non-vertex point _on the edge_ of the V. |


### heat_geodesic
**`heat_geodesic(v: array, f: array, t: float, gamma: array)`**

Compute fast approximate geodesic distances using precomputed data from a set of selected source vertices (gamma)

| | |
|-|-|
|Parameters| V  \#V by dim list of mesh vertex positions</br>F  \#F by 3 list of mesh face indices into V</br>t  "heat" parameter (smaller --> more accurate, less stable)</br>gamma  \#gamma list of indices into V of source vertices |
|Returns| D  \#V list of distances to gamma |


### hessian
**`hessian(v: array, f: array)`**

Constructs the finite element Hessian matrix
as described in https:arxiv.org/abs/1707.04348,
Natural Boundary Conditions for Smoothing in Geometry Processing
(Oded Stein, Eitan Grinspun, Max Wardetzky, Alec Jacobson)
The interior vertices are NOT set to zero yet.

| | |
|-|-|
|Parameters| V  \#V by dim list of mesh vertex positions</br>F  \#F by 3 list of mesh faces (must be triangles) |
|Returns| H  \#V by \#V Hessian energy matrix, each column i corresponding to V(i,:) |


### hessian_energy
**`hessian_energy(v: array, f: array)`**

Constructs the Hessian energy matrix using mixed FEM
as described in https:arxiv.org/abs/1707.04348
Natural Boundary Conditions for Smoothing in Geometry Processing
(Oded Stein, Eitan Grinspun, Max Wardetzky, Alec Jacobson)

| | |
|-|-|
|Parameters| V  \#V by dim list of mesh vertex positions</br>F  \#F by 3 list of mesh faces (must be triangles) |
|Returns| Q  \#V by \#V Hessian energy matrix, each row/column i</br>corresponding to V(i,:) |


### incircle
**`incircle(pa: array, pb: array, pc: array, pd: array) -> int`**

Decide whether a point is inside/outside/on a circle.

| | |
|-|-|
|Parameters| pa, pb, pc  2D points that defines an oriented circle.</br>pd          2D query point. |
|Returns| INSIDE=1 if pd is inside of the circle defined by pa, pb and pc.</br>OUSIDE=-1 if pd is outside of the circle.</br>COCIRCULAR=0 pd is exactly on the circle. |


### inradius
**`inradius(v: array, f: array)`**

Compute the inradius of each triangle in a mesh (V,F)

| | |
|-|-|
|Parameters| V  \#V by dim list of mesh vertex positions</br>F  \#F by 3 list of triangle indices into V |
|Returns| R  \#F list of inradii |


### insphere
**`insphere(pa: array, pb: array, pc: array, pd: array, pe: array) -> int`**

Decide whether a point is inside/outside/on a sphere.

| | |
|-|-|
|Parameters| pa, pb, pc, pd  3D points that defines an oriented sphere.</br>pe              3D query point. |
|Returns| INSIDE=1 if pe is inside of the sphere defined by pa, pb, pc and pd.</br>OUSIDE=-1 if pe is outside of the sphere.</br>COSPHERICAL=0 pe is exactly on the sphere. |


### internal_angles
**`internal_angles(v: array, f: array)`**

Computes internal angles for a triangle mesh.

| | |
|-|-|
|Parameters| v : \#v by dim array of mesh vertex nD positions</br>f : \#f by poly-size array of face (triangle) indices |
|Returns| k : \#f by poly-size array of internal angles. For triangles, columns correspond to edges [1,2],[2,0],[0,1]. |
|Notes| If poly-size ≠ 3 then dim must equal 3. |


### intrinsic_delaunay_cotmatrix
**`intrinsic_delaunay_cotmatrix(v: array, f: array)`**

INTRINSIC_DELAUNAY_COTMATRIX Computes the discrete cotangent Laplacian of a
mesh after converting it into its intrinsic Delaunay triangulation (see,
e.g., [Fisher et al. 2007].

| | |
|-|-|
|Parameters| V  \#V by dim list of mesh vertex positions</br>F  \#F by 3 list of mesh elements (triangles or tetrahedra) |
|Returns| L  \#V by \#V cotangent matrix, each row i corresponding to V(i,:)</br>l_intrinsic  \#F by 3 list of intrinsic edge-lengths used to compute L</br>F_intrinsic  \#F by 3 list of intrinsic face indices used to compute L |
|See also| intrinsic_delaunay_triangulation, cotmatrix, cotmatrix_intrinsic |


### intrinsic_delaunay_triangulation
**`intrinsic_delaunay_triangulation(l_in: array, f_in: array)`**

INTRINSIC_DELAUNAY_TRIANGULATION Flip edges _intrinsically_ until all are
"intrinsic Delaunay". See "An algorithm for the construction of intrinsic
delaunay triangulations with applications to digital geometry processing"
[Fisher et al. 2007].

| | |
|-|-|
|Parameters| l_in  \#F_in by 3 list of edge lengths (see edge_lengths)</br>F_in  \#F_in by 3 list of face indices into some unspecified vertex list V |
|Returns| l  \#F by 3 list of edge lengths</br>F  \#F by 3 list of new face indices. Note: Combinatorially F may contain</br>non-manifold edges, duplicate faces and -loops (e.g., an edge [1,1]</br>or a face [1,1,1]). However, the *intrinsic geometry* is still</br>well-defined and correct. See [Fisher et al. 2007] Figure 3 and 2nd to</br>last paragraph of 1st page. Since F may be "non-eddge-manifold" in the</br>usual combinatorial sense, it may be useful to call the more verbose</br>overload below if disentangling edges will be necessary later on.</br>Calling unique_edge_map on this F will give a _different_ result than</br>those outputs. |
|See also| is_intrinsic_delaunay |


### intrinsic_delaunay_triangulation_edges
**`intrinsic_delaunay_triangulation_edges(l_in: array, f_in: array)`**

INTRINSIC_DELAUNAY_TRIANGULATION Flip edges _intrinsically_ until all are
"intrinsic Delaunay". See "An algorithm for the construction of intrinsic
delaunay triangulations with applications to digital geometry processing"
[Fisher et al. 2007].

| | |
|-|-|
|Parameters| l_in  \#F_in by 3 list of edge lengths (see edge_lengths)</br>F_in  \#F_in by 3 list of face indices into some unspecified vertex list V |
|Returns| E  \#F*3 by 2 list of all directed edges, such that E.row(f+\#F*c) is the</br>edge opposite F(f,c)</br>uE  \#uE by 2 list of unique undirected edges</br>EMAP \#F*3 list of indices into uE, mapping each directed edge to unique</br>undirected edge</br>uE2E  \#uE list of lists of indices into E of coexisting edges |
|See also| unique_edge_map |


### is_border_vertex
**`is_border_vertex(v: array, f: array) -> List[bool]`**

Determine vertices on open boundary of a (manifold) mesh with triangle faces F

| | |
|-|-|
|Parameters| V  \#V by dim list of vertex positions</br>F  \#F by 3 list of triangle indices |
|Returns| \#V vector of bools revealing whether vertices are on boundary |
|Notes| Known Bugs:</br>- assumes mesh is edge manifold |


### is_delaunay
**`is_delaunay(v: array, f: array)`**

IS_DELAUNAY Determine if each edge in the mesh (V,F) is Delaunay.

| | |
|-|-|
|Parameters| V  \#V by dim list of vertex positions</br>F  \#F by 3 list of triangles indices |
|Returns| D  \#F by 3 list of bools revealing whether edges corresponding 23 31 12</br>are locally Delaunay. Boundary edges are by definition Delaunay.</br>Non-Manifold edges are by definition not Delaunay. |


### is_edge_manifold
**`is_edge_manifold(f: array) -> bool`**

Check if the mesh is edge-manifold (every edge is incident one one face (boundary) or two oppositely oriented faces).

| | |
|-|-|
|Parameters| F: \#F by 3 list of triangle indices |
|Returns| True iff all edges are manifold |

### is_vertex_manifold
**`is_vertex_manifold(f: array) -> bool`**

Check if a mesh is vertex-manifold. This only checks whether the faces incident on each vertex form exactly one connected component. Vertices incident on non-manifold edges are not consider non-manifold by this function (see is_edge_manifold). Unreferenced verties are considered non-manifold (zero components).

| | |
|-|-|
|Parameters| F  \#F by 3 list of triangle indices |
|Returns| B \#V list indicate whether each vertex is locally manifold.<br>The mesh is vertex manifold if `all(B) == True`. |

### is_intrinsic_delaunay
**`is_intrinsic_delaunay(l: array, f: array)`**

IS_INTRINSIC_DELAUNAY Determine if each edge in the mesh (V,F) is Delaunay.

| | |
|-|-|
|Parameters| l  \#l by dim list of edge lengths</br>F  \#F by 3 list of triangles indices |
|Returns| D  \#F by 3 list of bools revealing whether edges corresponding 23 31 12</br>are locally Delaunay. Boundary edges are by definition Delaunay.</br>Non-Manifold edges are by definition not Delaunay. |


### is_irregular_vertex
**`is_irregular_vertex(v: array, f: array) -> List[bool]`**

Determine if a vertex is irregular, i.e. it has more than 6 (triangles) or 4 (quads) incident edges. Vertices on the boundary are ignored.

| | |
|-|-|
|Parameters| v : \#v by dim array of vertex positions</br>f : \#f by 3[4] array of triangle[quads] indices |
|Returns| s : \#v list of bools revealing whether vertices are singular |


### isolines
**`isolines(v: array, f: array, z: array, n: int)`**

Constructs isolines for a function z given on a mesh (V,F)

| | |
|-|-|
|Parameters| V  \#V by dim list of mesh vertex positions</br>F  \#F by 3 list of mesh faces (must be triangles)</br>z  \#V by 1 list of function values evaluated at vertices</br>n  the number of desired isolines |
|Returns| isoV  \#isoV by dim list of isoline vertex positions</br>isoE  \#isoE by 2 list of isoline edge positions |


### iterative_closest_point
**`iterative_closest_point(vx: array, fx: array, vy: array, fy: array, num_samples: int, max_iters: int)`**

Solve for the rigid transformation that places mesh X onto mesh Y using the
iterative closest point method. In particular, optimize:
min      ∫_X inf ‖x*R+t - y‖² dx
R∈SO(3)      y∈Y
t∈R³
Typically optimization strategies include using Gauss Newton
("point-to-plane" linearization) and stochastic descent (sparse random
sampling each iteration).

| | |
|-|-|
|Parameters| VX  \#VX by 3 list of mesh X vertices</br>FX  \#FX by 3 list of mesh X triangle indices into rows of VX</br>VY  \#VY by 3 list of mesh Y vertices</br>FY  \#FY by 3 list of mesh Y triangle indices into rows of VY</br>num_samples  number of random samples to use (larger --> more accurate,</br>but also more suceptible to sticking to local minimum) |
|Returns| R  3x3 rotation matrix so that (VX*R+t,FX) ~~ (VY,FY)</br>t  1x3 translation row vector |


### lbs_matrix
**`lbs_matrix(v: array, w: array)`**

LBS_MATRIX Linear blend skinning can be expressed by V' = M * T where V' is
a #V by dim matrix of deformed vertex positions (one vertex per row), M is a #V by (dim+1)*#T (composed of weights and rest positions) and T is a #T*(dim+1) by dim matrix of #T stacked transposed transformation matrices.
See equations (1) and (2) in "Fast Automatic Skinning Transformations" [Jacobson et al 2012]

| | |
|-|-|
|Parameters| V  \#V by dim list of rest positions</br>W  \#V+ by \#T  list of weights |
|Returns| M  \#V by \#T*(dim+1) |

**Examples**
```python
In MATLAB:
kron(ones(1,size(W,2)),[V ones(size(V,1),1)]).*kron(W,ones(1,size(V,2)+1))
```


### lexicographic_triangulation
**`lexicographic_triangulation(p: array)`**

Given a set of points in 2D, return a lexicographic triangulation of these points.

| | |
|-|-|
|Parameters| P  \#P by 2 list of vertex positions |
|Returns| F  \#F by 3 of faces in lexicographic triangulation. |


### line_segment_in_rectangle
**`line_segment_in_rectangle(s: array, d: array, a: array, b: array) -> bool`**

Determine whether a line segment overlaps with a rectangle.

| | |
|-|-|
|Parameters| s  source point of line segment</br>d  dest point of line segment</br>A  first corner of rectangle</br>B  opposite corner of rectangle |
|Returns| Returns true if line segment is at all inside rectangle |


### local_basis
**`local_basis(v: array, f: array)`**

Compute a local orthogonal reference system for each triangle in the given mesh.

| | |
|-|-|
|Parameters| v : \#v by 3 vertex array</br>f : \#f by 3 array of mesh faces (must be triangles) |
|Returns| b1 : \#f by 3 array, each vector is tangent to the triangle</br>b2 : \#f by 3 array, each vector is tangent to the triangle and perpendicular to B1</br>b3 : \#f by 3 array, normal of the triangle |
|See also| adjacency_matrix |


### look_at
**`look_at(eye: array, center: array, up: array)`**

Implementation of the deprecated gluLookAt function.

| | |
|-|-|
|Parameters| eye  3-vector of eye position</br>center  3-vector of center reference point</br>up  3-vector of up vector |
|Returns| R  4x4 rotation matrix |


### loop
**`loop(v: array, f: array, number_of_subdivs: int = 1)`**

LOOP Given the triangle mesh [V, F], where n_verts = V.rows(), computes
newV and a sparse matrix S s.t. [newV, newF] is the subdivided mesh where
newV = S*V.

| | |
|-|-|
|Parameters| V an n by 3 matrix of vertices</br>F an m by 3 matrix of integers of triangle faces</br>number_of_subdivs an integer that specifies how many subdivision steps to do |
|Returns| NV a matrix containing the new vertices</br>NF a matrix containing the new faces |


### loop_subdivision_matrix
**`loop_subdivision_matrix(n_verts: int, f: array)`**

LOOP Given the triangle mesh [V, F], where n_verts = V.rows(), computes
newV and a sparse matrix S s.t. [newV, newF] is the subdivided mesh where
newV = S*V.

| | |
|-|-|
|Parameters| n_verts  an integer (number of mesh vertices)</br>F  an m by 3 matrix of integers of triangle faces |
|Returns| S  a sparse matrix (will become the subdivision matrix)</br>newF  a matrix containing the new faces |


### lscm
**`lscm(v: array, f: array, b: array, bc: array)`**

Compute a Least-squares conformal map parametrization.

| | |
|-|-|
|Parameters| v : \#v by 3 array of mesh vertex positions</br>f : \#f by 3 array of mesh faces (must be triangles)</br>b : \#b boundary indices into v</br>bc : \#b by 2 list of boundary values |
|Returns| uv \#v by 2 list of 2D mesh vertex positions in UV space |
|Notes| Derived in "Intrinsic Parameterizations of Surface Meshes" [Desbrun et al.</br>2002] and "Least Squares Conformal Maps for Automatic Texture Atlas</br>Generation" [Lévy et al. 2002]), though this implementation follows the</br>derivation in: "Spectral Conformal Parameterization" [Mullen et al. 2008]</br>(note, this does **not** implement the Eigen-decomposition based method in</br>[Mullen et al. 2008], which is not equivalent. Input should be a manifold</br>mesh (also no unreferenced vertices) and "boundary" (fixed vertices) `b`</br>should contain at least two vertices per connected component.</br>Returns true only on solver success. |


### map_vertices_to_circle
**`map_vertices_to_circle(v: array, bnd: array)`**

Map the vertices whose indices are in a given boundary loop (bnd) on the unit circle with spacing proportional to the original boundary edge lengths.

| | |
|-|-|
|Parameters| v : \#v by dim array of mesh vertex positions</br>b : \#w list of vertex ids |
|Returns| uv : \#w by 2 list of 2D positions on the unit circle for the vertices in b |


### marching_tets
**`marching_tets(TV: array, TT: array, S: array, isovalue: float)`**

Performs the marching tetrahedra algorithm on a tet mesh defined by TV and
TT with scalar values defined at each vertex in TV. The output is a
triangle mesh approximating the isosurface coresponding to the value
isovalue.

| | |
|-|-|
|Parameters| TV  \#tet_vertices x 3 array -- The vertices of the tetrahedral mesh</br>TT  \#tets x 4 array --  The indexes of each tet in the tetrahedral mesh</br>S  \#tet_vertices x 1 array -- The values defined on each tet vertex</br>isovalue  scalar -- The isovalue of the level set we want to compute |
|Returns| SV : \#SV x 3 array -- The vertices of the output level surface mesh</br>SF : \#SF x 3 array -- The face indexes of the output level surface mesh</br>J : \#SF list of indices into TT revealing which tet each face comes from</br>BC : \#SV x \#TV list of barycentric coordinates so that SV = BC*TV |

**Examples**
```python
sv, sf, j, bc = igl.marching_tets(tv, tt, s, isovalue)
```


### massmatrix
**`massmatrix(v: array, f: array, type: int = 1)`**

Constructs the mass (area) matrix for a given mesh (V,F).

| | |
|-|-|
|Parameters| v : \#v by dim list of mesh vertex positions</br>f : \#f by simplex_size list of mesh faces (must be triangles)</br>type : one of the following types:</br>-igl.MASSMATRIX_TYPE_BARYCENTRIC  barycentric</br>-igl.MASSMATRIX_TYPE_VORONOI voronoi-hybrid (default)</br>-igl.MASSMATRIX_TYPE_FULL full (not implemented) |
|Returns| m : \#v by \#v mass matrix |
|See also| adjacency_matrix, cotmatrix, grad |


### massmatrix_intrinsic
**`massmatrix_intrinsic(l: array, f: array, type: int = 1)`**

Constructs the mass (area) matrix for a given mesh (V,F).

| | |
|-|-|
|Parameters| l  \#l by simplex_size list of mesh edge lengths</br>F  \#F by simplex_size list of mesh elements (triangles or tetrahedra)</br>type  one of the following ints:</br>-igl.MASSMATRIX_TYPE_BARYCENTRIC  barycentric</br>-igl.MASSMATRIX_TYPE_VORONOI voronoi-hybrid (default)</br>-igl.MASSMATRIX_TYPE_FULL full (not implemented) |
|Returns| M  \#V by \#V mass matrix |
|See also| adjacency_matrix |


### min_quad_with_fixed
**`min_quad_with_fixed(A: sparse_matrix, B: array, known: array, Y: array, Aeq: sparse_matrix, Beq: array, is_A_pd: bool)`**

MIN_QUAD_WITH_FIXED Minimize a quadratic energy of the form
trace( 0.5*Z'*A*Z + Z'*B + constant )
subject to
Z(known,:) = Y, and
Aeq*Z = Beq

| | |
|-|-|
|Parameters| A  n by n matrix of quadratic coefficients</br>B  n by 1 column of linear coefficients</br>known list of indices to known rows in Z</br>Y  list of fixed values corresponding to known rows in Z</br>Aeq  m by n list of linear equality constraint coefficients</br>Beq  m by 1 list of linear equality constraint constant values</br>is_A_pd  flag specifying whether A(unknown,unknown) is positive definite |
|Returns| Z  n by k solution |


### mvc
**`mvc(v: array, c: array)`**

MEAN VALUE COORDINATES

| | |
|-|-|
|Parameters| V  \#V x dim list of vertex positions (dim = 2 or dim = 3)</br>C  \#C x dim list of polygon vertex positions in counter-clockwise order (dim = 2 or dim = 3) |
|Returns| W  weights, \#V by \#C matrix of weights |
|Notes| Known Bugs: implementation is listed as "Broken" |

**Examples**
```python
W = mvc(V,C)
```


### normal_derivative
**`normal_derivative(v: array, f: array)`**

NORMAL_DERIVATIVE Computes the directional derivative **normal** to
**all** (half-)edges of a triangle mesh (not just boundary edges). These
are integrated along the edge: they're the per-face constant gradient dot
the rotated edge vector (unit rotated edge vector for direction then
magnitude for integration).

| | |
|-|-|
|Parameters| V  \#V by dim list of mesh vertex positions</br>F  \#F by 34 list of triangletetrahedron indices into V |
|Returns| DD  \#F*34 by \#V sparse matrix representing operator to compute</br>directional derivative with respect to each facet of each element. |


### offset_surface
**`offset_surface(v: array, f: array, isolevel: int, s: int, signed_distance_type: int)`**

Compute a triangulated offset surface using matching cubes on a grid of
signed distance values from the input triangle mesh.

| | |
|-|-|
|Parameters| V  \#V by 3 list of mesh vertex positions</br>F  \#F by 3 list of mesh triangle indices into V</br>isolevel  iso level to extract (signed distance: negative inside)</br>s  number of grid cells along longest side (controls resolution)</br>signed_distance_type  type of signing to use one of SIGNED_DISTANCE_TYPE_PSEUDONORMAL, SIGNED_DISTANCE_TYPE_WINDING_NUMBER, SIGNED_DISTANCE_TYPE_DEFAULT, SIGNED_DISTANCE_TYPE_UNSIGNED |
|Returns| SV  \#SV by 3 list of output surface mesh vertex positions</br>SF  \#SF by 3 list of output mesh triangle indices into SV</br>GV  \#GV=side(0)*side(1)*side(2) by 3 list of grid cell centers</br>side  list of number of grid cells in x, y, and z directions</br>So  \#GV by 3 list of signed distance values _near_ `isolevel` ("far" from `isolevel` these values are incorrect) |


### orient2d
**`orient2d(pa: array, pb: array, pc: array) -> int`**

Compute the orientation of the triangle formed by pa, pb, pc.

| | |
|-|-|
|Parameters| pa, pb, pc  2D points. |
|Returns| POSITIVE=1 if pa, pb, pc are counterclockwise oriented.</br>NEGATIVE=-1 if they are clockwise oriented.</br>COLLINEAR=0 if they are collinear. |


### orient3d
**`orient3d(pa: array, pb: array, pc: array, pd: array) -> int`**

Compute the orientation of the tetrahedron formed by pa, pb, pc, pd.

| | |
|-|-|
|Parameters| pa, pb, pc, pd  3D points. |
|Returns| POSITIVE=1 if pd is "below" the oriented plane formed by pa, pb and pc.</br>NEGATIVE=-1 if pd is "above" the plane.</br>COPLANAR=0 if pd is on the plane. |


### orient_outward
**`orient_outward(v: array, f: array, c: array)`**

Orient each component (identified by C) of a mesh (V,F) so the normals on
average point away from the patch's centroid.

| | |
|-|-|
|Parameters| V  \#V by 3 list of vertex positions</br>F  \#F by 3 list of triangle indices</br>C  \#F list of components (output of orientable_patches) |
|Returns| FF  \#F by 3 list of new triangle indices such that FF(~I,:) = F(~I,:) and</br>FF(I,:) = fliplr(F(I,:)) (OK if &FF = &F)</br>I  max(C)+1 list of whether face has been flipped |


### orientable_patches
**`orientable_patches(f: array)`**

Compute connected components of facets connected by manifold edges.

| | |
|-|-|
|Parameters| f : n by dim array of face ids |
|Returns| A tuple (c, A) where c is an array of component ids (starting with 0)</br>and A is a \#f x \#f adjacency matri |
|See also| components |
|Notes| Known bugs: This will detect a moebius strip as a single patch (manifold, non-orientable) and also non-manfiold, yet orientable patches. |


### oriented_facets
**`oriented_facets(f: array)`**

Determines all 'directed [facets](https:en.wikipedia.org/wiki/Simplex#Elements)' of a given set
of simplicial elements. For a manifold triangle mesh, this computes all half-edges.
For a manifold tetrahedral mesh, this computes all half-faces.

| | |
|-|-|
|Parameters| f : \#F by simplex_size list of simplices |
|Returns| \#E : by simplex_size-1 list of half-edges/facets |
|See also| edges |
|Notes| This is not the same as igl::edges because this includes every</br>directed edge including repeats (meaning interior edges on a surface will</br>show up once for each direction and non-manifold edges may appear more than</br>once for each direction). |


### outer_edge
**`outer_edge(v: array, f: array, i: array)`**

Find an edge that is reachable from infinity without crossing any faces.
Such edge is called "outer edge."
Precondition: The input mesh must have all -intersection resolved and
no duplicated vertices.  The correctness of the output depends on the fact
that there is no edge overlap.  See cgal::remesh__intersections.h for
how to obtain such input.

| | |
|-|-|
|Parameters| V  \#V by 3 list of vertex positions</br>F  \#F by 3 list of triangle indices into V</br>I  \#I list of facets to consider |
|Returns| v1 index of the first end point of outer edge</br>v2 index of the second end point of outer edge</br>A  \#A list of facets incident to the outer edge |


### outer_facet
**`outer_facet(v: array, f: array, n: array, i: array)`**

Find a facet that is reachable from infinity without crossing any faces.
Such facet is called "outer facet."
Precondition: The input mesh must have all -intersection resolved.  I.e
there is no duplicated vertices, no overlapping edge and no intersecting
faces (the only exception is there could be topologically duplicated faces).
See cgal::remesh__intersections.h for how to obtain such input.

| | |
|-|-|
|Parameters| V  \#V by 3 list of vertex positions</br>F  \#F by 3 list of triangle indices into V</br>N  \#N by 3 list of face normals</br>I  \#I list of facets to consider |
|Returns| f  Index of the outer facet.</br>flipped  true iff the normal of f points inwards. |


### outer_vertex
**`outer_vertex(v: array, f: array, i: array)`**

Find a vertex that is reachable from infinite without crossing any faces.
Such vertex is called "outer vertex."
Precondition: The input mesh must have all -intersection resolved and
no duplicated vertices.  See cgal::remesh__intersections.h for how to
obtain such input.

| | |
|-|-|
|Parameters| V  \#V by 3 list of vertex positions</br>F  \#F by 3 list of triangle indices into V</br>I  \#I list of facets to consider |
|Returns| v_index  index of outer vertex</br>A  \#A list of facets incident to the outer vertex |


### partition
**`partition(w: array, k: int)`**

PARTITION partition vertices into groups based on each
vertex's vector: vertices with similar coordinates (close in
space) will be put in the same group.

| | |
|-|-|
|Parameters| W  \#W by dim coordinate matrix</br>k  desired number of groups default is dim |
|Returns| G  \#W list of group indices (1 to k) for each vertex, such that vertex i is assigned to group G(i)</br>S  k  list of seed vertices</br>D  \#W list of squared distances for each vertex to it's corresponding closest seed |


### path_to_edges
**`path_to_edges(i: array, make_loop: bool = False)`**

Given a path as an ordered list of N>=2 vertex indices I[0], I[1], ..., I[N-1]
construct a list of edges [[I[0],I[1]], [I[1],I[2]], ..., [I[N-2], I[N-1]]]
connecting each sequential pair of vertices.

| | |
|-|-|
|Parameters| I  \#I list of vertex indices</br>make_loop bool If true, include an edge connecting I[N-1] to I[0] |
|Returns| E  \#I-1 by 2 list of edges |


### per_edge_normals
**`per_edge_normals(v: array, f: array, weight: int = 0, fn: array)`**

Compute face normals via vertex position list, face list

| | |
|-|-|
|Parameters| V  \#V by 3 eigen Matrix of mesh vertex 3D positions</br>F  \#F by 3 eigen Matrix of face (triangle) indices</br>weight  weighting type</br>FN  \#F by 3 matrix of 3D face normals per face |
|Returns| N  \#2 by 3 matrix of mesh edge 3D normals per row</br>E  \#E by 2 matrix of edge indices per row</br>EMAP  \#E by 1 matrix of indices from all edges to E |


### per_face_normals
**`per_face_normals(v: array, f: array, z: array)`**

Compute face normals via vertex position list, face list

| | |
|-|-|
|Parameters| V  \#V by 3 eigen Matrix of mesh vertex 3D positions</br>F  \#F by 3 eigen Matrix of face (triangle) indices</br>Z  3 vector normal given to faces with degenerate normal. |
|Returns| N  \#F by 3 eigen Matrix of mesh face (triangle) 3D normals |

**Examples**
```python
Give degenerate faces (1/3,1/3,1/3)^0.5
per_face_normals(V,F,Vector3d(1,1,1).normalized(),N);
```


### per_vertex_attribute_smoothing
**`per_vertex_attribute_smoothing(ain: array, f: array)`**

Smooth vertex attributes using uniform Laplacian

| | |
|-|-|
|Parameters| Ain  \#V by \#A eigen Matrix of mesh vertex attributes (each vertex has \#A attributes)</br>F    \#F by 3 eigne Matrix of face (triangle) indices |
|Returns| Aout \#V by \#A eigen Matrix of mesh vertex attributes |


### per_vertex_normals
**`per_vertex_normals(v: array, f: array, weighting: int = 0)`**

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
```


### piecewise_constant_winding_number
**`piecewise_constant_winding_number(f: array) -> bool`**

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


### planarize_quad_mesh
**`planarize_quad_mesh(v: array, f: array, max_iter: int, threshold: float)`**

Planarize a quad mesh.

| | |
|-|-|
|Parameters| v : \#v by 3 array of mesh vertex 3D positions</br>f : \#f by 4 array of face (quad) indices</br>max_iter : maximum numbers of iterations</br>threshold : minimum allowed threshold for non-planarity |
|Returns| out : \#v by 3 array of planar mesh vertex 3D positions |


### point_in_circle
**`point_in_circle(qx: float, qy: float, cx: float, cy: float, r: float) -> bool`**

Determine if 2d point is in a circle

| | |
|-|-|
|Parameters| qx  x-coordinate of query point</br>qy  y-coordinate of query point</br>cx  x-coordinate of circle center</br>cy  y-coordinate of circle center</br>r  radius of circle |
|Returns| Returns true if query point is in circle, false otherwise |


### point_in_poly
**`point_in_poly(poly: List[List[int]], xt: int, yt: int) -> bool`**

Determine if 2d point is inside a 2D polygon

| | |
|-|-|
|Parameters| poly  vector of polygon points, [0]=x, [1]=y. Polyline need not be closed (i.e. first point != last point), the line segment between last and first selected points is constructed within this function.</br>x     x-coordinate of query point</br>y     y-coordinate of query point |
|Returns| Returns true if query point is in polygon, false otherwise |
|Notes| From http:www.visibone.com/inpoly/ |


### point_mesh_squared_distance
**`point_mesh_squared_distance(p: array, v: array, ele: array)`**

Compute distances from a set of points P to a triangle mesh (V,F)

| | |
|-|-|
|Parameters| P  \#P by 3 list of query point positions</br>V  \#V by 3 list of vertex positions</br>Ele  \#Ele by (321) list of (triangleedgepoint) indices |
|Returns| sqrD  \#P list of smallest squared distances</br>I  \#P list of primitive indices corresponding to smallest distances</br>C  \#P by 3 list of closest points |
|Notes| Known bugs: This only computes distances to given primitivess. So</br>unreferenced vertices are ignored. However, degenerate primitives are</br>handled correctly: triangle [1 2 2] is treated as a segment [1 2], and</br>triangle [1 1 1] is treated as a point. So one _could_ add extra</br>combinatorially degenerate rows to Ele for all unreferenced vertices to</br>also get distances to points. |


### point_simplex_squared_distance
**`point_simplex_squared_distance(p: array, v: array, ele: array, i: int)`**

Determine squared distance from a point to linear simplex.
Also return barycentric coordinate of closest point.

| | |
|-|-|
|Parameters| p  d-long query point</br>V  \#V by d list of vertices</br>Ele  \#Ele by ss<=d+1 list of simplex indices into V</br>i  index into Ele of simplex |
|Returns| sqr_d  squared distance of Ele(i) to p</br>c  closest point on Ele(i)</br>b  barycentric coordinates of closest point on Ele(i) |


### polar_dec
**`polar_dec(a: array)`**

Computes the polar decomposition (R,T) of a matrix A

| | |
|-|-|
|Parameters| A  3 by 3 matrix to be decomposed |
|Returns| R  3 by 3 orthonormal matrix part of decomposition</br>T  3 by 3 stretch matrix part of decomposition |


### principal_curvature
**`principal_curvature(v: array, f: array, radius: int = 5, use_k_ring: bool = True)`**

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
```


### procrustes
**`procrustes(x: array, y: array, include_scaling: bool, include_reflections: bool)`**

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
```


### project
**`project(v: array, model: array, proj: array, viewport: array)`**

Project

| | |
|-|-|
|Parameters| V  \#V by 3 list of object points</br>model  model matrix</br>proj  projection matrix</br>viewport  viewport vector |
|Returns| P  \#V by 3 list of screen space points |


### project_isometrically_to_plane
**`project_isometrically_to_plane(v: array, f: array)`**

Project each triangle to the plane

| | |
|-|-|
|Parameters| V  \#V by 3 list of vertex positions</br>F  \#F by 3 list of mesh indices |
|Returns| U  \#F*3 by 2 list of triangle positions</br>UF  \#F by 3 list of mesh indices into U</br>I  \#V by \#F*3 such that I(i,j) = 1 implies U(j,:) corresponds to V(i,:) |

**Examples**
```python
[U,UF,I] = project_isometrically_to_plane(V,F)
```


### project_to_line
**`project_to_line(p: array, s: array, d: array)`**

PROJECT_TO_LINE  project points onto vectors, that is find the parameter
t for a point p such that proj_p = (y-x).*t, additionally compute the
squared distance from p to the line of the vector, such that
p - proj_p² = sqr_d

| | |
|-|-|
|Parameters| P  \#P by dim list of points to be projected</br>S  size dim start position of line vector</br>D  size dim destination position of line vector |
|Returns| T  \#P by 1 list of parameters</br>sqrD  \#P by 1 list of squared distances |

**Examples**
```python
[T,sqrD] = project_to_line(P,S,D)
```


### project_to_line_segment
**`project_to_line_segment(p: array, s: array, d: array)`**

PROJECT_TO_LINE_SEGMENT project points onto vectors, that is find the parameter
t for a point p such that proj_p = (y-x).*t, additionally compute the
squared distance from p to the line of the vector, such that
p - proj_p² = sqr_d

| | |
|-|-|
|Parameters| P  \#P by dim list of points to be projected</br>S  size dim start position of line vector</br>D  size dim destination position of line vector |
|Returns| T  \#P by 1 list of parameters</br>sqrD  \#P by 1 list of squared distances |

**Examples**
```python
[T,sqrD] = project_to_line_segment(P,S,D)
```


### pso
**`pso(f: Callable[[numpy.ndarray[float64[m, 1]]], float], lb: numpy.ndarray, ub: numpy.ndarray, max_iters: int, population: int)`**

Solve the problem:
minimize f(x)
subject to lb ≤ x ≤ ub
by particle swarm optimization (PSO).

| | |
|-|-|
|Parameters| f  function that evaluates the objective for a given "particle" location</br>LB  \#X vector of lower bounds</br>UB  \#X vector of upper bounds</br>max_iters  maximum number of iterations</br>population  number of particles in swarm |
|Returns| f(X) objective corresponding to best particle seen so far</br>X  best particle seen so far |


### qslim
**`qslim(v: array, f: array, max_m: int)`**

Decimate (simplify) a triangle mesh in nD according to the paper
"Simplifying Surfaces with Color and Texture using Quadric Error Metrics"
by [Garland and Heckbert, 1987] (technically a followup to qslim). The
mesh can have open boundaries but should be edge-manifold.

| | |
|-|-|
|Parameters| V  \#V by dim list of vertex positions. Assumes that vertices w</br>F  \#F by 3 list of triangle indices into V</br>max_m  desired number of output faces |
|Returns| U  \#U by dim list of output vertex posistions (can be same ref as V)</br>G  \#G by 3 list of output face indices into U (can be same ref as G)</br>J  \#G list of indices into F of birth face</br>I  \#U list of indices into V of birth vertices |


### quad_grid
**`quad_grid(nx: int, ny: int)`**

Generate a quad mesh over a regular grid.

| | |
|-|-|
|Parameters| nx  number of vertices in the x direction</br>ny  number of vertices in the y direction |
|Returns| V  nx*ny by 2 list of vertex positions</br>Q  (nx-1)*(ny-1) by 4 list of quad indices into V</br>E  (nx-1)*ny+(ny-1)*nx by 2 list of undirected quad edge indices into V |
|See also| grid, triangulated_grid |


### quad_planarity
**`quad_planarity(v: array, f: array)`**

Compute planarity of the faces of a quad mesh.

| | |
|-|-|
|Parameters| v : \#v by 3 array of mesh vertex 3D positions</br>f : \#f by 4 array of face (quad) indices |
|Returns| p : \#f by 1 array of mesh face (quad) planarities |


### ramer_douglas_peucker
**`ramer_douglas_peucker(p: array, tol: float)`**

Run (Ramer-)Duglass-Peucker curve simplification but keep track of where
every point on the original curve maps to on the simplified curve.

| | |
|-|-|
|Parameters| P  \#P by dim list of points, (use P([1:end 1],:) for loops)</br>tol  DP tolerance |
|Returns| S  \#S by dim list of points along simplified curve</br>J  \#S indices into P of simplified points</br>Q  \#P by dim list of points mapping along simplified curve |


### random_points_on_mesh
**`random_points_on_mesh(n: int, v: array, f: array)`**

RANDOM_POINTS_ON_MESH Randomly sample a mesh (V,F) n times.

| | |
|-|-|
|Parameters| n  number of samples</br>V  \#V by dim list of mesh vertex positions</br>F  \#F by 3 list of mesh triangle indices |
|Returns| B  n by 3 list of barycentric coordinates, ith row are coordinates of</br>ith sampled point in face FI(i)</br>FI  n list of indices into F |


### random_search
**`random_search(f: Callable[[numpy.ndarray[float64[m, 1]]], float], lb: numpy.ndarray, ub: numpy.ndarray, iters: int)`**

Solve the problem:
minimize f(x)
subject to lb ≤ x ≤ ub
by uniform random search.

| | |
|-|-|
|Parameters| f  function to minimize</br>LB  \#X vector of finite lower bounds</br>UB  \#X vector of finite upper bounds</br>iters  number of iterations |
|Returns| f(X)</br>X  \#X optimal parameter vector |


### ray_box_intersect
**`ray_box_intersect(source: array, dir: array, box_min: array, box_max: array, t0: float, t1: float)`**

Determine whether a ray origin+t*dir and box intersect within the ray's parameterized
range (t0,t1)

| | |
|-|-|
|Parameters| source  3-vector origin of ray</br>dir  3-vector direction of ray</br>box_min  min axis aligned box</br>box_max  max axis aligned box</br>t0  hit only if hit.t less than t0</br>t1  hit only if hit.t greater than t1 |
|Returns| true if hit</br>tmin  minimum of interval of overlap within [t0,t1]</br>tmax  maximum of interval of overlap within [t0,t1] |


### ray_mesh_intersect
**`ray_mesh_intersect(source: array, dir: array, v: array, f: array) -> List[Tuple[int, int, float, float, float]]`**

Shoot a ray against a mesh (V,F) and collect the first hit.

| | |
|-|-|
|Parameters| source  3-vector origin of ray</br>dir  3-vector direction of ray</br>V  \#V by 3 list of mesh vertex positions</br>F  \#F by 3 list of mesh face indices into V |
|Returns| hits  **sorted** list of hits: id, gid, u, v, t |


### ray_sphere_intersect
**`ray_sphere_intersect(source: array, dir: array, center: array, r: float)`**

Compute the intersection between a ray from O in direction D and a sphere centered at C with radius r

| | |
|-|-|
|Parameters| source  origin of ray</br>dir  direction of ray</br>center  center of sphere</br>r  radius of sphere |
|Returns| Returns the number of hits</br>t0  parameterization of first hit (set only if exists) so that hit position = o + t0*d</br>t1  parameterization of second hit (set only if exists) |


### read_dmat
**`read_dmat(filename: str, dtype: dtype = 'float64')`**

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
```


### read_mesh
**`read_mesh(filename: str, dtypef: dtype = 'float')`**

Load a tetrahedral volume mesh from a .mesh file.

| | |
|-|-|
|Parameters| filename : path of .mesh file</br>dtype : data-type of the returned vertices, optional. Default is `float64`.</br>(returned faces always have type int32.) |
|Returns| v : array of vertex positions \#v by 3</br>t : \#t by 4 array of tet indices into vertex positions</br>f : \#f by 3 array of face indices into vertex positions |
|Notes| Known bugs: Holes and regions are not supported |

**Examples**
```python
v, t, f = read_mesh("my_mesh.mesh")
```


### read_msh
**`read_msh(filename: str, dtypef: dtype = 'float')`**

Read a mesh (e.g., tet mesh) from a gmsh .msh file

| | |
|-|-|
|Parameters| filename  path to .msh file</br>dtype : data-type of the returned vertices, optional. Default is `float64`.</br>(returned faces always have type int32.) |
|Returns| V  \#V by 3 list of 3D mesh vertex positions</br>T  \#T by ss list of 3D ss-element indices into V (e.g., ss=4 for tets) |


### read_obj
**`read_obj(filename: str, dtype: dtype = 'float64')`**

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
```


### read_off
**`read_off(filename: str, read_normals: bool = True, dtype: dtype = 'float64')`**

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
```


### read_tgf
**`read_tgf(tgf_filename: str)`**

Read a graph from a .tgf file

| | |
|-|-|
|Parameters| filename  .tgf file name |
|Returns| V  \# vertices by 3 list of vertex positions</br>E  \# edges by 2 list of edge indices</br>P  \# point-handles list of point handle indices</br>BE \# bone-edges by 2 list of bone-edge indices</br>CE \# cage-edges by 2 list of cage-edge indices</br>PE \# pseudo-edges by 2 list of pseudo-edge indices |
|Notes| Assumes that graph vertices are 3 dimensional |

**Examples**
```python
V,E,P,BE,CE,PE = igl.read_tgf(filename)
```


### read_triangle_mesh
**`read_triangle_mesh(filename: str, dtypef: dtype = 'float')`**

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
```


### remove_duplicate_vertices
**`remove_duplicate_vertices(v: array, f: array, epsilon: float)`**

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
```


### remove_duplicates
**`remove_duplicates(v: array, f: array, epsilon: float)`**

Merge the duplicate vertices from V, fixing the topology accordingly

| | |
|-|-|
|Parameters| V,F       mesh description</br>epsilon   minimal distance to consider two vertices identical |
|Returns| NV, NF    new mesh without duplicate vertices |


### remove_unreferenced
**`remove_unreferenced(v: array, f: array)`**

Remove unreferenced vertices from V, updating F accordingly

| | |
|-|-|
|Parameters| V  \#V by dim list of mesh vertex positions</br>F  \#F by ss list of simplices (Values of -1 are quitely skipped) |
|Returns| NV  \#NV by dim list of mesh vertex positions</br>NF  \#NF by ss list of simplices</br>IM  \#V by 1 list of indices such that: NF = IM(F) and NT = IM(T)</br>and V(find(IM<=size(NV,1)),:) = NV</br>J  \#RV by 1 list, such that RV = V(J,:) |


### resolve_duplicated_faces
**`resolve_duplicated_faces(f1: array)`**

Resolve duplicated faces according to the following rules per unique face:
- If the number of positively oriented faces equals the number of
negatively oriented faces, remove all duplicated faces at this triangle.
- If the number of positively oriented faces equals the number of
negatively oriented faces plus 1, keeps one of the positively oriented
face.
- If the number of positively oriented faces equals the number of
negatively oriented faces minus 1, keeps one of the negatively oriented
face.
- If the number of postively oriented faces differ with the number of
negativley oriented faces by more than 1, the mesh is not orientable.
An exception will be thrown.

| | |
|-|-|
|Parameters| F1  \#F1 by 3 array of input faces. |
|Returns| F2  \#F2 by 3 array of output faces without duplicated faces.</br>J   \#F2 list of indices into F1. |


### rigid_alignment
**`rigid_alignment(x: array, p: array, n: array)`**

Find the rigid transformation that best aligns the 3D points X to their
corresponding points P with associated normals N.
min       ‖(X*R+t-P)'N‖²
R∈SO(3)
t∈R³

| | |
|-|-|
|Parameters| X  \#X by 3 list of query points</br>P  \#X by 3 list of corresponding (e.g., closest) points</br>N  \#X by 3 list of unit normals for each row in P |
|Returns| R  3 by 3 rotation matrix</br>t  1 by 3 translation vector |
|See also| icp |


### rotate_vectors
**`rotate_vectors(v: array, a: array, b1: array, b2: array)`**

Rotate the vectors V by A radiants on the tangent plane spanned by B1 and B2

| | |
|-|-|
|Parameters| V     \#V by 3 eigen Matrix of vectors</br>A     \#V eigen vector of rotation angles or a single angle to be applied to all vectors</br>B1    \#V by 3 eigen Matrix of base vector 1</br>B2    \#V by 3 eigen Matrix of base vector 2 |
|Returns| Returns the rotated vectors |


### sample_edges
**`sample_edges(v: array, e: array, k: int)`**

Compute samples_per_edge extra points along each edge in E defined over
vertices of V.

| | |
|-|-|
|Parameters| V  vertices over which edges are defined, \# vertices by dim</br>E  edge list, \# edges by 2</br>k  number of extra samples to be computed along edge not including start and end points |
|Returns| S  sampled vertices, size less than \# edges * (2+k) by dim always begins</br>with V so that E is also defined over S |


### segments_intersect
**`segments_intersect(p: array, r: array, q: array, s: array)`**

Determine whether two line segments A,B intersect
A: p + t*r :  t \in [0,1]
B: q + u*s :  u \in [0,1]

| | |
|-|-|
|Parameters| p  3-vector origin of segment A</br>r  3-vector direction of segment A</br>q  3-vector origin of segment B</br>s  3-vector direction of segment B</br>eps precision |
|Returns| t  scalar point of intersection along segment A, t \in [0,1]</br>u  scalar point of intersection along segment B, u \in [0,1]</br>Returns true if intersection |


### shape_diameter_function
**`shape_diameter_function(v: array, f: array, p: array, n: array, num_samples: int)`**

Compute shape diamater function per given point. In the parlence of the
paper "Consistent Mesh Partitioning and Skeletonisation using the Shape
Diameter Function" [Shapiro et al. 2008], this implementation uses a 180°
cone and a _uniform_ average (_not_ a average weighted by inverse angles).

| | |
|-|-|
|Parameters| V  \#V by 3 list of mesh vertex positions</br>F  \#F by 3 list of mesh face indices into V</br>P  \#P by 3 list of origin points</br>N  \#P by 3 list of origin normals |
|Returns| S  \#P list of shape diamater function values between bounding box</br>diagonal (perfect sphere) and 0 (perfect needle hook) |


### sharp_edges
**`sharp_edges(v: array, f: array, angle: float)`**

SHARP_EDGES Given a mesh, compute sharp edges.

| | |
|-|-|
|Parameters| V  \#V by 3 list of vertex positions</br>F  \#F by 3 list of triangle mesh indices into V</br>angle  dihedral angle considered to sharp (e.g., igl::PI * 0.11) |
|Returns| SE  \#SE by 2 list of edge indices into V</br>E   \#e by 2 list of edges in no particular order</br>uE  \#uE by 2 list of unique undirected edges</br>EMAP \#F*3 list of indices into uE, mapping each directed edge to unique</br>undirected edge so that uE(EMAP(f+\#F*c)) is the unique edge</br>corresponding to E.row(f+\#F*c)</br>uE2E  \#uE list of lists of indices into E of coexisting edges, so that</br>E.row(uE2E[i][j]) corresponds to uE.row(i) for all j in</br>0..uE2E[i].size()-1.</br>sharp  \#SE list of indices into uE revealing sharp undirected edges |


### signed_angle
**`signed_angle(a: array, b: array, p: array) -> float`**

Compute the signed angle subtended by the oriented 3d triangle (A,B,C) at some point P

| | |
|-|-|
|Parameters| A  2D position of corner</br>B  2D position of corner</br>P  2D position of query point |
|Returns| returns signed angle |


### signed_distance
**`signed_distance(p: array, v: array, f: array, return_normals: bool = False) -> tuple`**

SIGNED_DISTANCE computes signed distance to a mesh

| | |
|-|-|
|Parameters| P  \#P by 3 list of query point positions</br>V  \#V by 3 list of vertex positions</br>F  \#F by ss list of triangle indices, ss should be 3 unless sign_type</br>return_normals  (Optional, defaults to False) If set to True, will return pseudonormals of</br>closest points to each query point in P |
|Returns| S  \#P list of smallest signed distances</br>I  \#P list of facet indices corresponding to smallest distances</br>C  \#P by 3 list of closest points |
|Notes| Known issue: This only computes distances to triangles. So unreferenced</br>vertices and degenerate triangles are ignored. |

**Examples**
```python
S, I, C = signed_distance(P, V, F, return_normals=False)
```


### simplify_polyhedron
**`simplify_polyhedron(ov: array, of: array)`**

Simplify a polyhedron represented as a triangle mesh (OV,OF) by collapsing
any edge that doesn't contribute to defining surface's pointset. This
_would_ also make sense for open and non-manifold meshes, but the current
implementation only works with closed manifold surfaces with well defined
triangle normals.

| | |
|-|-|
|Parameters| OV  \#OV by 3 list of input mesh vertex positions</br>OF  \#OF by 3 list of input mesh triangle indices into OV |
|Returns| V  \#V by 3 list of output mesh vertex positions</br>F  \#F by 3 list of input mesh triangle indices into V</br>J  \#F list of indices into OF of birth parents |


### snap_points
**`snap_points(c: array, v: array)`**

SNAP_POINTS snap list of points C to closest of another list of points V
[I,minD,VI] = snap_points(C,V)

| | |
|-|-|
|Parameters| C  \#C by dim list of query point positions</br>V  \#V by dim list of data point positions |
|Returns| I  \#C list of indices into V of closest points to C</br>minD  \#C list of squared (^p) distances to closest points</br>VI  \#C by dim list of new point positions, VI = V(I,:) |


### solid_angle
**`solid_angle(a: array, b: array, c: array, p: array) -> float`**

Compute the signed solid angle subtended by the oriented 3d triangle (A,B,C) at some point P

| | |
|-|-|
|Parameters| A  3D position of corner</br>B  3D position of corner</br>C  3D position of corner</br>P  3D position of query point |
|Returns| Returns signed solid angle |


### sort_angles
**`sort_angles(m: array)`**

Sort angles in ascending order in a numerically robust way.
Instead of computing angles using atan2(y, x), sort directly on (y, x).

| | |
|-|-|
|Parameters| M: m by n matrix of scalars. (n >= 2).  Assuming the first column of M</br>contains values for y, and the second column is x.  Using the rest</br>of the columns as tie-breaker. |
|Returns| R: an array of m indices.  M.row(R[i]) contains the i-th smallest</br>angle. |
|Notes| None. |


### sparse_voxel_grid
**`sparse_voxel_grid(p0: numpy.ndarray, scalar_func: Callable[[numpy.ndarray[float64[1, 3]]], float], eps: float, expected_number_of_cubes: int)`**

Given a point, p0, on an isosurface, construct a shell of epsilon sized cubes surrounding the surface.
These cubes can be used as the input to marching cubes.

| | |
|-|-|
|Parameters| p0  A 3D point on the isosurface surface defined by scalarFunc(x) = 0</br>scalarFunc  A scalar function from R^3 to R -- points which map to 0 lie</br>on the surface, points which are negative lie inside the surface,</br>and points which are positive lie outside the surface</br>eps  The edge length of the cubes surrounding the surface</br>expected_number_of_cubes  This pre-allocates internal data structures to speed things up |
|Returns| CS  \#cube-vertices by 1 list of scalar values at the cube vertices</br>CV  \#cube-vertices by 3 list of cube vertex positions</br>CI  \#number of cubes by 8 list of indexes into CS and CV. Each row represents a cube |


### swept_volume_bounding_box
**`swept_volume_bounding_box(n: int, v: Callable[[int, float], numpy.ndarray[float64[1, 3]]], steps: int)`**

Construct an axis-aligned bounding box containing a shape undergoing a
motion sampled at `steps` discrete momements.

| | |
|-|-|
|Parameters| n  number of mesh vertices</br>V  function handle so that V(i,t) returns the 3d position of vertex i at time t, for t∈[0,1]</br>steps  number of time steps: steps=3 --> t∈{0,0.5,1} |
|Returns| min,max  corners of box containing mesh under motion |


### tet_tet_adjacency
**`tet_tet_adjacency(t: array)`**

Constructs the tet_tet adjacency matrix for a given tet mesh with tets T

| | |
|-|-|
|Parameters| T  \#T by 4 list of tets |
|Returns| TT   \#T by \#4 adjacency matrix, the element i,j is the id of the tet adjacent to the j face of tet i</br>TTi  \#T by \#4 adjacency matrix, the element i,j is the id of face of the tet TT(i,j) that is adjacent to tet i |
|Notes| the first face of a tet is [0,1,2], the second [0,1,3], the third [1,2,3], and the fourth [2,0,3]. |


### topological_hole_fill
**`topological_hole_fill(f: array, b: array, holes: List[List[int]])`**

Topological fill hole on a mesh, with one additional vertex each hole
Index of new abstract vertices will be F.maxCoeff() + (index of hole)

| | |
|-|-|
|Parameters| F  \#F by simplex-size list of element indices</br>b  \#b boundary indices to preserve</br>holes vector of hole loops to fill |
|Returns| F_filled  input F stacked with filled triangles. |


### triangle_fan
**`triangle_fan(e: array)`**

Given a list of faces tessellate all of the "exterior" edges forming another
list of

| | |
|-|-|
|Parameters| E  \#E by 2  list of exterior edges (see exterior_edges.h) |
|Returns| cap  \#cap by simplex_size  list of "faces" tessellating the boundary edges |


### triangle_triangle_adjacency
**`triangle_triangle_adjacency(f: array)`**

Constructs the triangle-triangle adjacency matrix for a given
mesh (V,F).

| | |
|-|-|
|Parameters| F  \#F by simplex_size list of mesh faces (must be triangles) |
|Returns| TT   \#F by \#3 adjacent matrix, the element i,j is the id of the triangle</br>adjacent to the j edge of triangle i</br>TTi  \#F by \#3 adjacent matrix, the element i,j is the id of edge of the</br>triangle TT(i,j) that is adjacent with triangle i |
|Notes| NOTE: the first edge of a triangle is [0,1] the second [1,2] and the third</br>[2,3].  this convention is DIFFERENT from cotmatrix_entries.h |


### triangles_from_strip
**`triangles_from_strip(s: array)`**

TRIANGLES_FROM_STRIP Create a list of triangles from a stream of indices
along a strip.

| | |
|-|-|
|Parameters| S  \#S list of indices |
|Returns| F  \#S-2 by 3 list of triangle indices |


### triangulated_grid
**`triangulated_grid(nx: int, ny: int)`**

Create a regular grid of elements (only 2D supported, currently)
Vertex position order is compatible with `igl::grid`

| | |
|-|-|
|Parameters| nx  number of vertices in the x direction</br>ny  number of vertices in the y direction |
|Returns| GV  nx*ny by 2 list of mesh vertex positions.</br>GF  2*(nx-1)*(ny-1) by 3  list of triangle indices |
|See also| grid, quad_grid |


### two_axis_valuator_fixed_up
**`two_axis_valuator_fixed_up(w: int, h: int, speed: float, down_quat: array, down_x: int, down_y: int, mouse_x: int, mouse_y: int)`**

Applies a two-axis valuator drag rotation (as seen in Maya/Studio max) to a given rotation.

| | |
|-|-|
|Parameters| w  width of the trackball context</br>h  height of the trackball context</br>speed  controls how fast the trackball feels, 1 is normal</br>down_quat  rotation at mouse down, i.e. the rotation we're applying the</br>trackball motion to (as quaternion). **Note:** Up-vector that is fixed</br>is with respect to this rotation.</br>down_x position of mouse down</br>down_y position of mouse down</br>mouse_x  current x position of mouse</br>mouse_y  current y position of mouse |
|Returns| quat  the resulting rotation (as quaternion) |
|See also| snap_to_fixed_up |


### uniformly_sample_two_manifold_at_vertices
**`uniformly_sample_two_manifold_at_vertices(ow: array, k: int, push: float)`**

Find uniform sampling up to placing samples on mesh vertices

| | |
|-|-|
|Parameters|  |


### uniformly_sample_two_manifold_internal
**`uniformly_sample_two_manifold_internal(w: array, f: array, k: int, push: float)`**

UNIFORMLY_SAMPLE_TWO_MANIFOLD Attempt to sample a mesh uniformly by
furthest point relaxation as described in "Fast Automatic Skinning
Transformations"
[Jacobson et al. 12] Section 3.3.

| | |
|-|-|
|Parameters| W  \#W by dim positions of mesh in weight space</br>F  \#F by 3 indices of triangles</br>k  number of samplse</br>push  factor by which corners should be pushed away |
|Returns| WS  k by dim locations in weights space |


### unique_edge_map
**`unique_edge_map(f: array)`**

Construct relationships between facet "half"-(or rather "viewed")-edges E
to unique edges of the mesh seen as a graph.

| | |
|-|-|
|Parameters| F  \#F by 3  list of simplices |
|Returns| E  \#F*3 by 2 list of all directed edges, such that E.row(f+\#F*c) is the</br>edge opposite F(f,c)</br>uE  \#uE by 2 list of unique undirected edges</br>EMAP \#F*3 list of indices into uE, mapping each directed edge to unique</br>undirected edge so that uE(EMAP(f+\#F*c)) is the unique edge</br>corresponding to E.row(f+\#F*c)</br>uE2E  \#uE list of lists of indices into E of coexisting edges, so that</br>E.row(uE2E[i][j]) corresponds to uE.row(i) for all j in</br>0..uE2E[i].size()-1. |


### unique_simplices
**`unique_simplices(f: array)`**

Find *combinatorially* unique simplices in F.  **Order independent**

| | |
|-|-|
|Parameters| F  \#F by simplex-size list of simplices |
|Returns| FF  \#FF by simplex-size list of unique simplices in F</br>IA  \#FF index vector so that FF == sort(F(IA,:),2);</br>IC  \#F index vector so that sort(F,2) == FF(IC,:); |


### unproject
**`unproject(win: array, model: array, proj: array, viewport: array)`**

Reimplementation of gluUnproject

| | |
|-|-|
|Parameters| win  \#P by 3 or 3-vector (\#P=1) of screen space x, y, and z coordinates</br>model  4x4 model-view matrix</br>proj  4x4 projection matrix</br>viewport  4-long viewport vector |
|Returns| scene  \#P by 3 or 3-vector (\#P=1) the unprojected x, y, and z coordinates |


### unproject_in_mesh
**`unproject_in_mesh(pos: array, model: array, proj: array, viewport: array, v: array, f: array)`**

Unproject a screen location (using current opengl viewport, projection, and
model view) to a 3D position _inside_ a given mesh. If the ray through the
given screen location (x,y) _hits_ the mesh more than twice then the 3D
midpoint between the first two hits is return. If it hits once, then that
point is return. If it does not hit the mesh then obj is not set.

| | |
|-|-|
|Parameters| pos        screen space coordinates</br>model      model matrix</br>proj       projection matrix</br>viewport   vieweport vector</br>V   \#V by 3 list of mesh vertex positions</br>F   \#F by 3 list of mesh triangle indices into V |
|Returns| obj        3d unprojected mouse point in mesh</br>hits       vector of hits</br>Returns number of hits |


### unproject_on_line
**`unproject_on_line(uv: array, m: array, vp: array, origin: array, dir: array)`**

Given a screen space point (u,v) and the current projection matrix (e.g.
gl_proj * gl_modelview) and viewport, _unproject_ the point into the scene
so that it lies on given line (origin and dir) and projects as closely as
possible to the given screen space point.

| | |
|-|-|
|Parameters| UV  2-long uv-coordinates of screen space point</br>M  4 by 4 projection matrix</br>VP  4-long viewport: (corner_u, corner_v, width, height)</br>origin  point on line</br>dir  vector parallel to line |
|Returns| t  line parameter so that closest poin on line to viewer ray through UV</br>lies at origin+t*dir</br>Z  3d position of closest point on line to viewing ray through UV |


### unproject_on_plane
**`unproject_on_plane(uv: array, m: array, vp: array, p: array)`**

Given a screen space point (u,v) and the current projection matrix (e.g.
gl_proj * gl_modelview) and viewport, _unproject_ the point into the scene
so that it lies on given plane.

| | |
|-|-|
|Parameters| UV  2-long uv-coordinates of screen space point</br>M  4 by 4 projection matrix</br>VP  4-long viewport: (corner_u, corner_v, width, height)</br>P  4-long plane equation coefficients: P*(X 1) = 0 |
|Returns| Z  3-long world coordinate |


### unproject_onto_mesh
**`unproject_onto_mesh(pos: array, model: array, proj: array, viewport: array, v: array, f: array)`**

Unproject a screen location (using current opengl viewport, projection, and
model view) to a 3D position _onto_ a given mesh, if the ray through the
given screen location (x,y) _hits_ the mesh.

| | |
|-|-|
|Parameters| pos        screen space coordinates</br>model      model matrix</br>proj       projection matrix</br>viewport   vieweport vector</br>V   \#V by 3 list of mesh vertex positions</br>F   \#F by 3 list of mesh triangle indices into V |
|Returns| fid  id of the first face hit</br>bc  barycentric coordinates of hit</br>Returns true if there's a hit |


### unproject_ray
**`unproject_ray(pos: array, model: array, proj: array, viewport: array)`**

Construct a ray (source point + direction vector) given a screen space
positions (e.g. mouse) and a model-view projection constellation.

| | |
|-|-|
|Parameters| pos  2d screen-space position (x,y)</br>model  4x4 model-view matrix</br>proj  4x4 projection matrix</br>viewport  4-long viewport vector |
|Returns| s  source of ray (pos unprojected with z=0)</br>dir  direction of ray (d - s) where d is pos unprojected with z=1 |


### upsample
**`upsample(v: array, f: array, number_of_subdivs: int = 1)`**

Subdivide a mesh without moving vertices: loop subdivision but odd
vertices stay put and even vertices are just edge midpoints

| | |
|-|-|
|Parameters| V  \#V by dim  mesh vertices</br>F  \#F by 3  mesh triangles |
|Returns| NV new vertex positions, V is guaranteed to be at top</br>NF new list of face indices |
|Notes| - assumes (V,F) is edge-manifold. |


### vector_area_matrix
**`vector_area_matrix(f: array)`**

Constructs the symmetric area matrix A, s.t. [V.col(0)' V.col(1)'] * A *
[V.col(0); V.col(1)] is the **vector area** of the mesh (V,F).

| | |
|-|-|
|Parameters| f : \#f by 3 array of mesh faces (must be triangles) |
|Returns| a : \#vx2 by \#vx2 area matrix |


### vertex_components
**`vertex_components(f: array)`**

Compute connected components of the vertices of a mesh given the mesh' face indices.

| | |
|-|-|
|Parameters| f : \#f x dim array of face indices |
|Returns| An array of component ids (starting with 0) |
|See also| vertex_components_from_adjacency_matrix</br>facet_components |


### vertex_components_from_adjacency_matrix
**`vertex_components_from_adjacency_matrix(a: sparse_matrix)`**

Compute connected components of a graph represented by a sparse adjacency
matrix.

| | |
|-|-|
|Parameters| a : n by n sparse adjacency matrix |
|Returns| A tuple (c, counts) where c is an array of component ids (starting with 0)</br>and counts is a \#components array of counts for each component |
|See also| vertex_components</br>facet_components |


### vertex_triangle_adjacency
**`vertex_triangle_adjacency(f: array, n: int)`**

vertex_face_adjacency constructs the vertex-face topology of a given mesh (V,F)

| | |
|-|-|
|Parameters| F  \#F by 3 list of triangle indices into some vertex list V</br>n  number of vertices, \#V (e.g., F.maxCoeff()+1) |
|Returns| VF  3*\#F list  List of faces indice on each vertex, so that VF(NI(i)+j) =</br>f, means that face f is the jth face (in no particular order) incident</br>on vertex i.</br>NI  \#V+1 list  cumulative sum of vertex-triangle degrees with a</br>preceeding zero. "How many faces" have been seen before visiting this</br>vertex and its incident faces. |


### volume
**`volume(v: array, t: array)`**

Computes volume for all tets of a given tet mesh (V,T)

| | |
|-|-|
|Parameters| V  \#V by dim list of vertex positions</br>T  \#V by 4 list of tet indices |
|Returns| vol  \#T list of dihedral angles (in radians) |

**Examples**
```python
vol = volume(V,T)
```


### volume_from_edges
**`volume_from_edges(l: array)`**

Computes volume for all tets from edge lengths

| | |
|-|-|
|Parameters| L  \#V by 6 list of edge lengths (see edge_lengths) |
|Returns| vol  volume of the tets |


### volume_from_vertices
**`volume_from_vertices(a: array, b: array, c: array, d: array)`**

Compute volumes of a list of tets defined by a, b, c, d

| | |
|-|-|
|Parameters| a,b,c,d list of vertices vertices of the tets |
|Returns| vol  volume of the tets |


### volume_single
**`volume_single(a: array, b: array, c: array, d: array) -> float`**

Volume of a single tet

| | |
|-|-|
|Parameters| a,b,c,d vertices |
|Returns| volume |

**Examples**
```python
Single tet
```


### winding_number
**`winding_number(v: array, f: array, o: array)`**

WINDING_NUMBER Compute the sum of solid angles of a triangle/tetrahedron
described by points (vectors) V

| | |
|-|-|
|Parameters| V  n by 3 list of vertex positions</br>F  \#F by 3 list of triangle indices, minimum index is 0</br>O  no by 3 list of origin positions |
|Returns| S  no by 1 list of winding numbers |


### winding_number_for_point
**`winding_number_for_point(v: array, f: array, p: array) -> float`**

Compute winding number of a single point

| | |
|-|-|
|Parameters| V  n by dim list of vertex positions</br>F  \#F by dim list of triangle indices, minimum index is 0</br>p  single origin position |
|Returns| w  winding number of this point |


### write_obj
**`write_obj(filename: str, v: array, f: array) -> bool`**

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
```


### write_off
**`write_off(str: str, v: array, f: array, c: array) -> bool`**

Export geometry and colors-by-vertex
Export a mesh from an ascii OFF file, filling in vertex positions.
Only triangle meshes are supported

| | |
|-|-|
|Parameters| str  path to .off output file</br>V  \#V by 3 mesh vertex positions</br>F  \#F by 3 mesh indices into V</br>C  double matrix of rgb values per vertex \#V by 3 |
|Returns| Returns true on success, false on errors |


### write_triangle_mesh
**`write_triangle_mesh(str: str, v: array, f: array, force_ascii: bool = True) -> bool`**

write mesh to a file with automatic detection of file format.  supported: obj, off, stl, wrl, ply, mesh).

| | |
|-|-|
|Parameters| str  path to file</br>V  double matrix \#V by 3</br>F  int matrix \#F by 3</br>force_ascii=True  force ascii format even if binary is available |
|Returns| Returns true iff success |



## class ARAP

**`solve(: igl.pyigl_classes.ARAP, bc: numpy.ndarray, initial_guess: numpy.ndarray)`**

## class BBW

**`solve(: igl.pyigl_classes.BBW, V: numpy.ndarray, F: numpy.ndarray, b: numpy.ndarray[int32[m, 1]], bc: numpy.ndarray)`**

## class SLIM

**`energy(: igl.pyigl_classes.SLIM) -> float`**

**`solve(: igl.pyigl_classes.SLIM, num_iters: int)`**

**`vertices(: igl.pyigl_classes.SLIM)`**

## class shapeup

**`solve(: igl.pyigl_classes.shapeup, bc: numpy.ndarray, P0: numpy.ndarray, local_projection: str = 'regular_face_projection', quietIterations: bool = True)`**
