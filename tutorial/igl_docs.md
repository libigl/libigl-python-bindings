

### **`adjacency_list(f: array) -> handle`**

Constructs the graph adjacency list of a given mesh (v, f)

**Parameters**



f : #f by dim array of fixed dimensional (e.g. triangle (#f by 3),

tet (#f by 4), quad (#f by 4), etc...) mesh faces

----------------
**Returns**



list of lists containing at index i the adjacent vertices of vertex i

----------------

**See also**



adjacency_matrix

--------------

**Notes**



**Examples**



Mesh in (v, f)

a = mesh_adjacency_list(f)

------------------

### **`adjacency_matrix(f: array) -> object`**

Constructs the graph adjacency matrix of a given mesh (v, f).

**Parameters**



f : #f by dim list of mesh simplices

----------------
**Returns**



a : max(f) by max(f) cotangent matrix, each row i corresponding to v(i, :)

----------------

**See also**



adjacency_list, edges, cotmatrix, diag

--------------

**Notes**



None

**Examples**



Mesh in (v, f)

a = adjacency_matrix(f)

Sum each row

a_sum = np.sum(a, axis=1)

Convert row sums into diagonal of sparse matrix

a_diag = diag(a_sum)

Build uniform laplacian

u = a - a_diag

------------------

### **`ambient_occlusion(v: array, f: array, p: array, n: array, num_samples: int) -> object`**

**Parameters**



V  #V by 3 list of mesh vertex positions

F  #F by 3 list of mesh face indices into V

P  #P by 3 list of origin points

N  #P by 3 list of origin normals

----------------
**Returns**



S  #P list of ambient occusion values between 1 (fully occluded) and 0 (not occluded)

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`arap_linear_block(v: array, f: array, d: int, energy: int) -> object`**

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

**Parameters**



v : #v by dim list of initial domain positions

f : #f by #simplex size list of triangle indices into V

d : coordinate of linear constructor to build

----------------
**Returns**



\#v by #v/#f block of the linear constructor matrix corresponding to coordinate d

----------------

**See also**



arap, arap_dof

--------------

**Notes**



**Examples**



------------------

### **`arap_linear_block_elements(v: array, f: array, d: int) -> object`**

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

**Parameters**



v : #v by dim list of initial domain positions

f : #f by #simplex size list of triangle indices into V

d : coordinate of linear constructor to build

----------------
**Returns**



\#v by #v/#f block of the linear constructor matrix corresponding to coordinate d

----------------

**See also**



arap, arap_dof

--------------

**Notes**



**Examples**



------------------

### **`arap_linear_block_spokes(v: array, f: array, d: int) -> object`**

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

**Parameters**



v : #v by dim list of initial domain positions

f : #f by #simplex size list of triangle indices into V

d : coordinate of linear constructor to build

----------------
**Returns**



\#v by #v/#f block of the linear constructor matrix corresponding to coordinate d

----------------

**See also**



arap, arap_dof

--------------

**Notes**



**Examples**



------------------

### **`arap_linear_block_spokes_and_rims(v: array, f: array, d: int) -> object`**

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

**Parameters**



v : #v by dim list of initial domain positions

f : #f by #simplex size list of triangle indices into V

d : coordinate of linear constructor to build

----------------
**Returns**



\#v by #v/#f block of the linear constructor matrix corresponding to coordinate d

----------------

**See also**



arap, arap_dof

--------------

**Notes**



**Examples**



------------------

### **`arap_rhs(v: array, f: array, d: int, energy: int) -> object`**

Guild right-hand side constructor of global poisson solve for various ARAP energies

Inputs:

Outputs:

K  #V*dim by #(FV)*dim*dim matrix such that:

b = K * reshape(permute(R,[3 1 2]),size(VF,1)*size(V,2)*size(V,2),1);

**Parameters**



v : #v by Vdim list of initial domain positions

f : #f by 3 list of triangle indices into v

d : dimension being used at solve time. For deformation usually dim = V.cols(), for surface parameterization V.cols() = 3 and dim = 2

energy : ARAPEnergyType enum value defining which energy is being used. See igl.ARAPEnergyType for valid options and explanations.

----------------
**Returns**



\#v*d by #(fv)*dim*dim matrix such that: b = K * reshape(permute(R,[3 1 2]),size(VF,1)*size(V,2)*size(V,2),1);

----------------

**See also**



arap_linear_block, arap

--------------

**Notes**



**Examples**



------------------

### **`average_onto_vertices(v: array, f: array, s: array) -> object`**

Move a scalar field defined on faces to vertices by averaging

**Parameters**



v : #v by vdim array of mesh vertices

f : #f by simplex_count array of simplex indices

s : #f by dim scalar field defined on simplices

----------------
**Returns**



\#v by dim scalar field defined on vertices

----------------

**See also**



average_onto_faces

--------------

**Notes**



**Examples**



------------------

### **`avg_edge_length(v: array, f: array) -> float`**

Compute the average edge length for the given triangle mesh.

**Parameters**



v : array_like #v by 3 vertex array

f : f #f by simplex-size list of mesh faces (must be simplex)

----------------
**Returns**



l : average edge length

----------------

**See also**



adjacency_matrix

--------------

**Notes**



None

**Examples**



Mesh in (v, f)

length = avg_edge_length(v, f)

------------------

### **`barycenter(v: array, f: array) -> object`**

Compute the barycenter of every simplex

**Parameters**



v : #v x dim matrix of vertex coordinates

f : #f x simplex_size  matrix of indices of simplex corners into V

----------------
**Returns**



A #f x dim matrix where each row is the barycenter of each simplex

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`barycentric_coordinates_tet(p: array, a: array, b: array, c: array, d: array) -> object`**

Compute barycentric coordinates in a tet corresponding to the Euclidean coordinates in `p`.

The input arrays `a`, `b`, `c` and `d` are the vertices of each tet. I.e. one tet is

`a[i, :], b[i, :], c[i, :], d[:, i]`.

**Parameters**



p : #P by 3 Query points in 3d

a : #P by 3 Tet corners in 3d

b : #P by 3 Tet corners in 3d

c : #P by 3 Tet corners in 3d

d : #P by 3 Tet corners in 3d

----------------
**Returns**



\#P by 4 list of barycentric coordinates

----------------

**See also**



--------------

**Notes**



**Examples**



------------------

### **`barycentric_coordinates_tri(p: array, a: array, b: array, c: array) -> object`**

Compute barycentric coordinates in a triangle corresponding to the Euclidean coordinates in `p`.

The input arrays `a`, `b`, and `c` are the vertices of each triangle. I.e. one triangle is

`a[i, :], b[i, :], c[i, :]`.

**Parameters**



p : #P by 3 Query points in 3d

a : #P by 3 Tri corners in 3d

b : #P by 3 Tri corners in 3d

c : #P by 3 Tri corners in 3d

----------------
**Returns**



\#P by 3 list of barycentric coordinates

----------------

**See also**



--------------

**Notes**



**Examples**



------------------

### **`bfs(A: scipy.sparse.csr_matrix  scipy.sparse.csc_matrix, s: int) -> Tuple[object, object]`**

Construct an array indexing into a **directed** graph represented by an adjacency list using

breadth first search. I.e. the output is an array of vertices in breadth-first order.

**Parameters**



A : #V list of adjacency lists  or #V by #V adjacency matrix

s : starting node (index into A)

----------------
**Returns**



A tuple, (d, p) where:

* d is a #V list of indices into rows of A in the order in which graph nodes are discovered

* p is a #V list of indices of A of predecsors where -1 indicates root/not discovered. I.e.

p[i] is the index of the vertex v which preceded d[i] in the breadth first traversal.

Note that together, (d, p) form a spanning tree of the input graph

----------------

**See also**



--------------

**Notes**



**Examples**



V, F, _ = igl.readOFF("test.off)

A = igl.adjacency_matrix(V, F)

d, p = igl.bfs(A, V[0])

------------------

### **`bfs_orient(f: array) -> Tuple[object, object]`**

Consistently orient faces in orientable patches using BFS.

**Parameters**



f : #F by 3 list of faces

----------------
**Returns**



A tuple, (ff, c) where:

* ff is a #F by 3 list of faces which are consistently oriented with

* c is a #F array of connected component ids

----------------

**See also**



--------------

**Notes**



**Examples**



v, f, _ = igl.readOFF("test.off)

ff, c = igl.bfs_orient(f)

------------------

### **`bone_parents(be: array) -> object`**

BONE_PARENTS Recover "parent" bones from directed graph representation.

**Parameters**



BE  #BE by 2 list of directed bone edges

----------------
**Returns**



P  #BE by 1 list of parent indices into BE, -1 means root.

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`boundary_conditions(v: array, ele: array, c: array, p: array, be: array, ce: array) -> Tuple[bool, object, object]`**

Compute boundary conditions for automatic weights computation. This

function expects that the given mesh (V,Ele) has sufficient samples

(vertices) exactly at point handle locations and exactly along bone and

cage edges.

**Parameters**



V  #V by dim list of domain vertices

Ele  #Ele by simplex-size list of simplex indices

C  #C by dim list of handle positions

P  #P by 1 list of point handle indices into C

BE  #BE by 2 list of bone edge indices into C

CE  #CE by 2 list of cage edge indices into *P*

----------------
**Returns**



b  #b list of boundary indices (indices into V of vertices which have

known, fixed values)

bc #b by #weights list of known/fixed values for boundary vertices

(notice the #b != #weights in general because #b will include all the

intermediary samples along each bone, etc.. The ordering of the

weights corresponds to [P;BE]

**Returns false if boundary conditions are suspicious:**

P and BE are empty

bc is empty

some column of bc doesn't have a 0 (assuming bc has >1 columns)

some column of bc doesn't have a 1 (assuming bc has >1 columns)

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`boundary_facets(t: array) -> object`**

Determine boundary faces (edges) of tetrahedra (triangles).

**Parameters**



t : tetrahedron or triangle index list, m by 4/3, where m is the number of tetrahedra/triangles

----------------
**Returns**



f : list of boundary faces, n by 3/2, where n is the number of boundary faces/edges

----------------

**See also**



None

--------------

**Notes**



None

**Examples**



Mesh in (v, f)

b = boundary_facets(f)

------------------

### **`boundary_loop(f: array) -> object`**

Compute ordered boundary loops for a manifold mesh and return the longest loop in terms of vertices.

**Parameters**



f : #v by dim array of mesh faces

----------------
**Returns**



l : ordered list of boundary vertices of longest boundary loop

----------------

**See also**



--------------

**Notes**



None

**Examples**



Mesh in (v, f)

l = boundary_loop(f)

------------------

### **`bounding_box(*args, **kwargs)`**

------------------

### **`bounding_box(v: array) -> Tuple[object, object]`**

Build a triangle mesh of the bounding box of a given list of vertices

**Parameters**



V  #V by dim list of rest domain positions

----------------
**Returns**



BV  2^dim by dim list of bounding box corners positions

BF  #BF by dim list of simplex facets

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`bounding_box(v: array, pad: float) -> Tuple[object, object]`**

Build a triangle mesh of the bounding box of a given list of vertices

**Parameters**



V  #V by dim list of rest domain positions

----------------
**Returns**



BV  2^dim by dim list of bounding box corners positions

BF  #BF by dim list of simplex facets

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`bounding_box_diagonal(v: array) -> float`**

Compute the length of the diagonal of a given meshes axis-aligned bounding

**Parameters**



V  #V by 3 list of vertex positions

F  #F by 3 list of triangle indices into V

----------------
**Returns**



**Returns length of bounding box diagonal**

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`centroid(v: array, f: array) -> Tuple[object]`**

Computes the centroid of a closed mesh using a surface integral.

**Parameters**



v : #v by dim array of rest domain positions

f : #f by 3 array of triangle indices into v

----------------
**Returns**



c : dim array of centroid coordinates

vol : total volume of solid

----------------

**See also**



None

--------------

**Notes**



None

**Examples**



Mesh in (v, f)

c, vol = centroid(v, f)

------------------

### **`circulation(e: int, ccw: bool, emap: array, ef: array, ei: array) -> List[int]`**

Return list of faces around the end point of an edge. Assumes

data-structures are built from an edge-manifold **closed** mesh.

**Parameters**



e  index into E of edge to circulate

ccw  whether to _continue_ in ccw direction of edge (circulate around

------------------

### **`EMAP #F*3 list of indices into E, mapping each directed edge to unique`**

unique edge in E

EF  #E by 2 list of edge flaps, EF(e,0)=f means e=(i-->j) is the edge of

------------------

### **`e=(j->i)`**

EI  #E by 2 list of edge flap corners (see above).

----------------
**Returns**



**Returns list of faces touched by circulation (in cyclically order).**

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`circumradius(v: array, f: array) -> object`**

Compute the circumradius of each triangle in a mesh (V,F)

**Parameters**



V  #V by dim list of mesh vertex positions

F  #F by 3 list of triangle indices into V

----------------
**Returns**



R  #F list of circumradii

----------------

**See also**



--------------

**Notes**



None

**Examples**



R = circumradius(V, F)

------------------

### **`collapse_small_triangles(v: array, f: array, eps: float) -> object`**

Given a triangle mesh (V,F) compute a new mesh (VV,FF) which contains the

original faces and vertices of (V,F) except any small triangles have been

removed via collapse.

We are *not* following the rules in "Mesh Optimization" [Hoppe et al]

Section 4.2. But for our purposes we don't care about this criteria.

**Parameters**



V  #V by 3 list of vertex positions

F  #F by 3 list of triangle indices into V

eps  epsilon for smallest allowed area treated as fraction of squared bounding box

diagonal

----------------
**Returns**



FF  #FF by 3 list of triangle indices into V

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`connect_boundary_to_infinity(f: array) -> object`**

Connect all boundary edges to a fictitious point at infinity.

**Parameters**



F  #F by 3 list of face indices into some V

----------------
**Returns**



FO  #F+#O by 3 list of face indices into [V;inf inf inf], original F are

guaranteed to come first. If (V,F) was a manifold mesh, now it is

closed with a possibly non-manifold vertex at infinity (but it will be

edge-manifold).

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`connect_boundary_to_infinity_face(v: array, f: array) -> Tuple[object, object]`**

**Parameters**



F  #F by 3 list of face indices into some V

----------------
**Returns**



FO  #F+#O by 3 list of face indices into VO

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`connect_boundary_to_infinity_index(f: array, inf_index: int) -> object`**

**Parameters**



inf_index  index of point at infinity (usually V.rows() or F.maxCoeff())

----------------
**Returns**



----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`cotmatrix(v: array, f: array) -> object`**

Constructs the cotangent stiffness matrix (discrete laplacian) for a given mesh

(v, f).

**Parameters**



v : #v by dim list of mesh vertex positions

f : #f by simplex_size list of mesh faces (must be triangles)

----------------
**Returns**



l : #v by #v cotangent matrix, each row i corresponding to v(i, :)

----------------

**See also**



adjacency_matrix

--------------

**Notes**



This Laplacian uses the convention that diagonal entries are

**minus** the sum of off-diagonal entries. The diagonal entries are

therefore in general negative and the matrix is **negative** semi-definite

(immediately, -L is **positive** semi-definite)

**Examples**



Mesh in (v, f)

l = cotmatrix(v, f)

------------------

### **`cotmatrix_entries(v: array, f: array) -> object`**

COTMATRIX_ENTRIES compute the cotangents of each angle in mesh (V,F)

**Parameters**



V  #V by dim list of rest domain positions

F  #F by {34} list of {triangletetrahedra} indices into V

----------------
**Returns**



C  #F by 3 list of 1/2*cotangents corresponding angles

for triangles, columns correspond to edges [1,2],[2,0],[0,1]

OR

C  #F by 6 list of 1/6*cotangents of dihedral angles*edge lengths

for tets, columns along edges [1,2],[2,0],[0,1],[3,0],[3,1],[3,2]

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`crouzeix_raviart_cotmatrix(v: array, f: array) -> Tuple[object, object, object]`**

CROUZEIX_RAVIART_COTMATRIX Compute the Crouzeix-Raviart cotangent

stiffness matrix.

**Parameters**



V  #V by dim list of vertex positions

F  #F by 3/4 list of triangle/tetrahedron indices

----------------
**Returns**



L  #E by #E edge/face-based diagonal cotangent matrix

E  #E by 2/3 list of edges/faces

EMAP  #F*3/4 list of indices mapping allE to E

----------------

**See also**



**See also: crouzeix_raviart_massmatrix**

--------------

**Notes**



None

**Examples**



See for example "Discrete Quadratic Curvature Energies" [Wardetzky, Bergou,

Harmon, Zorin, Grinspun 2007]

------------------

### **`crouzeix_raviart_cotmatrix_known_e(v: array, f: array, e: array, emap: array) -> object`**

wrapper if E and EMAP are already computed (better match!)

**Parameters**



----------------
**Returns**



----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`crouzeix_raviart_massmatrix(v: array, f: array) -> Tuple[object, object, object]`**

CROUZEIX_RAVIART_MASSMATRIX Compute the Crouzeix-Raviart mass matrix where

------------------

### **`edge e.`**

**Parameters**



V  #V by dim list of vertex positions

F  #F by 3/4 list of triangle/tetrahedron indices

----------------
**Returns**



M  #E by #E edge/face-based diagonal mass matrix

E  #E by 2/3 list of edges/faces

EMAP  #F*3/4 list of indices mapping allE to E

----------------

**See also**



crouzeix_raviart_cotmatrix

--------------

**Notes**



See for example "Discrete Quadratic Curvature Energies" [Wardetzky, Bergou,

Harmon, Zorin, Grinspun 2007]

**Examples**



------------------

### **`crouzeix_raviart_massmatrix_known_e(v: array, f: array, e: array, emap: array) -> object`**

wrapper if E and EMAP are already computed (better match!)

**Parameters**



----------------
**Returns**



----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`cut_mesh(v: array, f: array, cuts: array) -> Tuple[object, object]`**

Compute the barycenter of every simplex

**Parameters**



v : #v x dim matrix of vertex coordinates

f : #f x simplex_size  matrix of indices of simplex corners into V

cuts : #F by 3 list of boolean flags, indicating the edges that need to

be cut (has 1 at the face edges that are to be cut, 0 otherwise)

----------------
**Returns**



A pair (vcut, fcut) where:

* vcut is a #v by 3 list of the vertex positions

of the cut mesh. This matrix will be similar to the original vertices except

some rows will be duplicated.

* fcut is a #f by 3 list of the faces of the cut mesh (must be triangles). This

matrix will be similar to the original face matrix except some indices

will be redirected to point to the newly duplicated vertices.

----------------

**See also**



--------------

**Notes**



**Examples**



------------------

### **`cut_mesh_from_singularities(v: array, f: array, mismatch: array) -> object`**

Given a mesh (v,f) and the integer mismatch of a cross field per edge

(mismatch), finds and **returns the cut_graph connecting the singularities**

(seams)

**Parameters**



v : #v by 3 array of triangle vertices (each row is a vertex)

f : #f by 3 array of triangle indices into v

mismatch : #f by 3 array of per-corner integer mismatches

----------------
**Returns**



seams : #f by 3 array of per corner booleans that de**notes if an edge is a**

seam or not

----------------

**See also**



cut_mesh

--------------

**Notes**



**Examples**



------------------

### **`cylinder(axis_devisions: int, height_devisions: int) -> Tuple[object, object]`**

Construct a triangle mesh of a cylinder (without caps)

**Parameters**



axis_devisions  number of vertices _around the cylinder_

height_devisions  number of vertices _up the cylinder_

----------------
**Returns**



V  #V by 3 list of mesh vertex positions

F  #F by 3 list of triangle indices into V

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`decimate(v: array, f: array, max_m: int) -> Tuple[bool, object, object, object, object]`**

Assumes (V,F) is a manifold mesh (possibly with boundary) Collapses edges

until desired number of faces is achieved. This uses default edge cost and

merged vertex placement functions {edge length, edge midpoint}.

**Parameters**



V  #V by dim list of vertex positions

F  #F by 3 list of face indices into V.

max_m  desired number of output faces

----------------
**Returns**



U  #U by dim list of output vertex posistions (can be same ref as V)

G  #G by 3 list of output face indices into U (can be same ref as G)

J  #G list of indices into F of birth face

I  #U list of indices into V of birth vertices

**Returns true if m was reached (otherwise #G > m)**

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`dihedral_angles(v: array, t: array) -> Tuple[object, object]`**

Compute dihedral angles for all tets of a given tet mesh (v, t).

**Parameters**



v : #v by dim list of vertex positions

t : #v by 4 list of tet indices

----------------
**Returns**



theta : #t by 6 list of dihedral angles (in radians)

cos_theta : #t by 6 list of cosine of dihedral angles (in radians)

----------------

**See also**



--------------

**Notes**



None

**Examples**



TetMesh in (v, t)

theta, cos_theta = dihedral_angles(v, t)

------------------

### **`dihedral_angles_intrinsic(l: array, a: array) -> Tuple[object, object]`**

See dihedral_angles for the documentation.

------------------

### **`directed_edge_parents(e: array) -> object`**

Recover "parents" (preceding edges) in a tree given just directed edges.

**Parameters**



e : #e by 2 list of directed edges

----------------
**Returns**



p : #e list of parent indices into e. (-1) means root

----------------

**See also**



--------------

**Notes**



None

**Examples**



p = edges(e)

------------------

### **`doublearea(v: array, f: array) -> object`**

Computes twice the area for each input triangle[quad]

**Parameters**



v : #v by dim array of mesh vertex positions

f : #f by simplex_size array of mesh faces (must be triangles or quads)

----------------
**Returns**



d_area : #f list of triangle[quad] double areas (SIGNED only for 2D input)

----------------

**See also**



None

--------------

**Notes**



Known bug: For dim==3 complexity is O(#V + #F)!! Not just O(#F). This is a big deal if you have 1million unreferenced vertices and 1 face

**Examples**



Mesh in (v, f)

dbl_area = doublearea(v, f)

------------------

### **`ears(f: array) -> Tuple[object, object]`**

FIND_EARS  Find all ears (faces with two boundary edges) in a given mesh

**Parameters**



F  #F by 3 list of triangle mesh indices

----------------
**Returns**



ears  #ears list of indices into F of ears

ear_opp  #ears list of indices indicating which edge is non-boundary

(connecting to flops)

----------------

**See also**



--------------

**Notes**



None

**Examples**



ears,ear_opp = find_ears(F)

------------------

### **`edge_topology(v: array, f: array) -> Tuple[object, object, object]`**

Initialize Edges and their topological relations (assumes an edge-manifold mesh)

**Parameters**



v : #v by dim, list of mesh vertex positions (unused)

f : #f by 3, list of triangle indices into V

----------------
**Returns**



ev : #e by 2, list of edges described as pair of vertices.

fe : #f by 3, list storing triangle-edge relation.

ef : #e by w, list storing edge-triangle relation, uses -1 to indicate boundaries.

----------------

**See also**



--------------

**Notes**



None

**Examples**


Mesh in (v, f)

ev, fe, ef = edge_topology(v, f)

------------------

### **`edges(f: array) -> object`**

Constructs a list of unique edges represented in a given mesh (v, f)

**Parameters**



f : #F by dim list of mesh faces (must be triangles or tets)

----------------
**Returns**



\#e by 2 list of edges in no particular order

----------------

**See also**



adjacency_matrix

--------------

**Notes**



**Examples**



V, F, _ = igl.readOFF("test.off)

E = igl.edges(F)

------------------

### **`euler_characteristic(f: array) -> int`**

Computes the Euler characteristic of a given mesh (V,F)

**Parameters**



F #F by dim list of mesh faces (must be triangles)

----------------
**Returns**



**Returns An int containing the Euler characteristic**

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`euler_characteristic_complete(v: array, f: array) -> int`**

**Parameters**



V       #V by dim list of mesh vertex positions

----------------
**Returns**



----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`exact_geodesic(v: array, f: array, vs: array, vt: array, fs: numpy.array  None = None, ft: numpy.array  None = None) -> object`**

Exact geodesic algorithm for the calculation of geodesics on a triangular mesh.

**Parameters**



v : #v by 3 array of 3D vertex positions

f : #f by 3 array of mesh faces

vs : #vs by 1 array specifying indices of source vertices

fs : #fs by 1 array specifying indices of source faces

vt : #vt by 1 array specifying indices of target vertices

ft : #ft by 1 array specifying indices of target faces

----------------
**Returns**



d : #vt+#ft by 1 array of geodesic distances of each target w.r.t. the nearest one in the source set

----------------

**See also**



--------------

**Notes**



Specifying a face as target/source means its center.

Implementation from https:code.google.com/archive/p/geodesic/ with the algorithm first described by Mitchell, Mount and Papadimitriou in 1987.

**Examples**



------------------

### **`face_components(f: array) -> object`**

Compute connected components of facets based on edge-edge adjacency,

**Parameters**



f : #f x 3 array of triangle indices

----------------
**Returns**



An array, c, with shape (#f,), of component ids

----------------

**See also**



vertex_components

vertex_components_from_adjacency_matrix

--------------

**Notes**



**Examples**



------------------

### **`fit_plane(v: array) -> Tuple[object, object]`**

This function fits a plane to a point cloud.

**Parameters**



V #Vx3 matrix. The 3D point cloud, one row for each vertex.

----------------
**Returns**



N 1x3 Vector. The normal of the fitted plane.

C 1x3 Vector. A point that lies in the fitted plane.

----------------

**See also**



--------------

**Notes**



From http:missingbytes.blogspot.com/2012/06/fitting-plane-to-point-cloud.html

**Examples**



------------------

### **`flip_avoiding_line_search(f: array, cur_v: array, dst_v: array, energy: std::__1::function<double (Eigen::Matrix<double, -1, -1, 0, -1, -1>)>, cur_energy: float) -> Tuple[float, object]`**

A bisection line search for a mesh based energy that avoids triangle flips as suggested in

"Bijective Parameterization with Free Boundaries" (Smith J. and Schaefer S., 2015).

The user specifies an initial vertices position (that has no flips) and target one (that my have flipped triangles).

This method first computes the largest step in direction of the destination vertices that does not incur flips, and then minimizes a given energy using this maximal step and a bisection linesearch (see igl::line_search).

Supports both triangle and tet meshes.

**Parameters**



F         #F by 3/4 list of mesh faces or tets

cur_v     #V by dim list of variables

dst_v     #V by dim list of target vertices. This mesh may have flipped triangles

energy    A function to compute the mesh-based energy (return an energy that is bigger than 0)

------------------

### **`cur_energy(OPTIONAL)         The energy at the given point. Helps save redundant c  omputations. This is optional. If not specified, the function will compute it.`**

----------------
**Returns**



cur_v     #V by dim list of variables at the new location

**Returns the energy at the new point**

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`gaussian_curvature(v: array, f: array) -> object`**

Compute discrete local integral gaussian curvature (angle deficit, without

averaging by local area).

**Parameters**



v : #v by 3 array of mesh vertex 3D positions

f : #f by 3 array of face (triangle) indices

----------------
**Returns**



k : #v by 1 array of discrete gaussian curvature values

----------------

**See also**



principal_curvature

--------------

**Notes**



None

**Examples**



Mesh in (v, f)

k = gaussian_curvature(v, f)

------------------

### **`grad(v: array, f: array, uniform: bool = False) -> object`**

Compute the numerical gradient operator.

**Parameters**



v : #v by 3 list of mesh vertex positions

f : #f by 3 list of mesh face indices [or a #faces by 4 list of tetrahedral indices]

uniform : boolean (default false). Use a uniform mesh instead of the vertices v

----------------
**Returns**



g : #faces * dim by #v gradient operator

----------------

**See also**



cotmatrix, massmatrix

--------------

**Notes**



Gradient of a scalar function defined on piecewise linear elements (mesh)

is constant on each triangle [tetrahedron] i,j,k:

------------------

### **`grad(Xijk) = (Xj-Xi) * (Vi - Vk)^R90 / 2A + (Xk-Xi) * (Vj - Vi)^R90 / 2A`**

where Xi is the scalar value at vertex i, Vi is the 3D position of vertex

i, and A is the area of triangle (i,j,k). ^R90 represent a rotation of

90 degrees.

**Examples**



Mesh in (v, f)

g = grad(v, f)

------------------

### **`harmonic(l: scipy.sparse.csr_matrix  scipy.sparse.csc_matrix, m: scipy.sparse.csr_matrix  scipy.sparse.csc_matrix, b: array, bc: array, k: int) -> object`**

Compute a harmonic map using a given Laplacian and mass matrix

**Parameters**



L  #V by #V discrete (integrated) Laplacian

M  #V by #V mass matrix

b  #b boundary indices into V

bc  #b by #W list of boundary values

k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)

----------------
**Returns**



W  #V by #V list of weights

----------------

**See also**



--------------

**Notes**



**Examples**



------------------

### **`harmonic_integrated_with_laplacian(l: scipy.sparse.csr_matrix  scipy.sparse.csc_matrix, m: scipy.sparse.csr_matrix  scipy.sparse.csc_matrix, k: int) -> object`**

Build the discrete k-harmonic operator (computing integrated quantities).

That is, if the k-harmonic PDE is Q x = 0, then this minimizes x' Q x

**Parameters**



L  #V by #V discrete (integrated) Laplacian

M  #V by #V mass matrix

k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)

----------------
**Returns**



Q  #V by #V discrete (integrated) k-Laplacian

----------------

**See also**



--------------

**Notes**



**Examples**



------------------

### **`harmonic_uniform_laplacian(f: array, b: array, bc: array, k: int) -> object`**

Compute harmonic map using uniform laplacian operator

**Parameters**



F  #F by simplex-size list of element indices

b  #b boundary indices into V

bc #b by #W list of boundary values

k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)

----------------
**Returns**



W  #V by #W list of weights

----------------

**See also**



--------------

**Notes**



**Examples**



------------------

### **`harmonic_weights(v: array, f: array, b: array, bc: array, k: int) -> object`**

Compute k-harmonic weight functions "coordinates".

**Parameters**



V  #V by dim vertex positions

F  #F by simplex-size list of element indices

b  #b boundary indices into V

bc #b by #W list of boundary values

k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)

----------------
**Returns**



W  #V by #W list of weights

----------------

**See also**



--------------

**Notes**



**Examples**



------------------

### **`hausdorff(va: array, fa: array, vb: array, fb: array) -> float`**

HAUSDORFF compute the Hausdorff distance between mesh (VA,FA) and mesh

(VB,FB). This is the

------------------

### **`a∈A b∈B          b∈B a∈A`**

**Parameters**



VA  #VA by 3 list of vertex positions

FA  #FA by 3 list of face indices into VA

VB  #VB by 3 list of vertex positions

FB  #FB by 3 list of face indices into VB

----------------
**Returns**



d  hausdorff distance

pair  2 by 3 list of "determiner points" so that pair(1,:) is from A

and pair(2,:) is from B

----------------

**See also**



--------------

**Notes**



Known issue: This is only computing max(min(va,B),min(vb,A)). This is

better than max(min(va,Vb),min(vb,Va)). This (at least) is missing

"edge-edge" cases like the distance between the two different

triangulations of a non-planar quad in 3D. Even simpler, consider the

Hausdorff distance between the non-convex, block letter V polygon (with 7

vertices) in 2D and its convex hull. The Hausdorff distance is defined by

the midpoint in the middle of the segment across the concavity and some

non-vertex point _on the edge_ of the V.

**Examples**



------------------

### **`internal_angles(v: array, f: array) -> object`**

Computes internal angles for a triangle mesh.

**Parameters**



v : #v by dim array of mesh vertex nD positions

f : #f by poly-size array of face (triangle) indices

----------------
**Returns**



k : #f by poly-size array of internal angles. For triangles, columns correspond to edges [1,2],[2,0],[0,1].

----------------

**See also**



None

--------------

**Notes**



If poly-size ≠ 3 then dim must equal 3.

**Examples**



------------------

### **`is_edge_manifold(f: array) -> bool`**

See is_edge_manifold for the documentation.

------------------

### **`is_irregular_vertex(v: array, f: array) -> std::__1::vector<bool, std::__1::allocator<bool> >`**

Determine if a vertex is irregular, i.e. it has more than 6 (triangles) or 4 (quads) incident edges. Vertices on the boundary are ignored.

**Parameters**



v : #v by dim array of vertex positions

f : #f by 3[4] array of triangle[quads] indices

----------------
**Returns**



s : #v list of bools revealing whether vertices are singular

----------------

**See also**



None

--------------

**Notes**



None

**Examples**



------------------

### **`isolines(v: array, f: array, z: array, n: int) -> Tuple[object, object]`**

Constructs isolines for a function z given on a mesh (V,F)

**Parameters**



V  #V by dim list of mesh vertex positions

F  #F by 3 list of mesh faces (must be triangles)

z  #V by 1 list of function values evaluated at vertices

n  the number of desired isolines

----------------
**Returns**



isoV  #isoV by dim list of isoline vertex positions

isoE  #isoE by 2 list of isoline edge positions

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`lscm(v: array, f: array, b: array, bc: array) -> Tuple[bool, object]`**

Compute a Least-squares conformal map parametrization.

**Parameters**



v : #v by 3 array of mesh vertex positions

f : #f by 3 array of mesh faces (must be triangles)

b : #b boundary indices into v

bc : #b by 3 list of boundary values

----------------
**Returns**



uv #v by 2 list of 2D mesh vertex positions in UV space

----------------

**See also**



None

--------------

**Notes**



Derived in "Intrinsic Parameterizations of Surface Meshes" [Desbrun et al.

2002] and "Least Squares Conformal Maps for Automatic Texture Atlas

Generation" [Lévy et al. 2002]), though this implementation follows the

derivation in: "Spectral Conformal Parameterization" [Mullen et al. 2008]

(note, this does **not** implement the Eigen-decomposition based method in

[Mullen et al. 2008], which is not equivalent. Input should be a manifold

mesh (also no unreferenced vertices) and "boundary" (fixed vertices) `b`

should contain at least two vertices per connected component.

**Returns true only on solver success.**

**Examples**



------------------

### **`map_vertices_to_circle(v: array, bnd: array) -> object`**

Map the vertices whose indices are in a given boundary loop (bnd) on the unit circle with spacing proportional to the original boundary edge lengths.

**Parameters**



v : #v by dim array of mesh vertex positions

b : #w list of vertex ids

----------------
**Returns**



uv : #w by 2 list of 2D positions on the unit circle for the vertices in b

----------------

**See also**



None

--------------

**Notes**



None

**Examples**



------------------

### **`massmatrix(v: array, f: array, type: int = 1) -> object`**

Constructs the mass (area) matrix for a given mesh (V,F).

**Parameters**



v : #v by dim list of mesh vertex positions

f : #f by simplex_size list of mesh faces (must be triangles)

type : one of the following types:

-igl.MASSMATRIX_TYPE_BARYCENTRIC  barycentric

-igl.MASSMATRIX_TYPE_VORONOI voronoi-hybrid (default)

-igl.MASSMATRIX_TYPE_FULL full (not implemented)

----------------
**Returns**



m : #v by #v mass matrix

----------------

**See also**



adjacency_matrix, cotmatrix, grad

--------------

**Notes**



**Examples**



------------------

### **`min_quad_dense_precompute(a: array, aeq: array, use_lu_decomposition: bool) -> object`**

MIN_QUAD_WITH_FIXED Minimize quadratic energy Z'*A*Z + Z'*B + C

subject to linear constraints Aeq*Z = Beq

**Parameters**



A  n by n matrix of quadratic coefficients

B  n by 1 column of linear coefficients

Aeq  m by n list of linear equality constraint coefficients

Beq  m by 1 list of linear equality constraint constant values

use_lu_decomposition  use lu rather than SVD

----------------
**Returns**



S  n by (n + m) "solve" matrix, such that S*[B', Beq'] is a solution

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`orientable_patches(f: array) -> Tuple[object, object]`**

Compute connected components of facets connected by manifold edges.

**Parameters**



f : n by dim array of face ids

----------------
**Returns**



A tuple (c, A) where c is an array of component ids (starting with 0)

and A is a #f x #f adjacency matri

----------------

**See also**



components

--------------

**Notes**



Known bugs: This will detect a moebius strip as a single patch (manifold, non-orientable) and also non-manfiold, yet orientable patches.

**Examples**



------------------

### **`oriented_facets(f: array) -> object`**

Determines all 'directed [facets](https:en.wikipedia.org/wiki/Simplex#Elements)' of a given set

of simplicial elements. For a manifold triangle mesh, this computes all half-edges.

For a manifold tetrahedral mesh, this computes all half-faces.

**Parameters**



f : #F by simplex_size list of simplices

----------------
**Returns**



\#E : by simplex_size-1 list of half-edges/facets

----------------

**See also**



edges

--------------

**Notes**



This is not the same as igl::edges because this includes every

directed edge including repeats (meaning interior edges on a surface will

show up once for each direction and non-manifold edges may appear more than

once for each direction).

**Examples**



------------------

### **`per_edge_normals(v: array, f: array, weight: igl::PerEdgeNormalsWeightingType, fn: array) -> Tuple[object, object, object]`**

Compute face normals via vertex position list, face list

**Parameters**



V  #V by 3 eigen Matrix of mesh vertex 3D positions

F  #F by 3 eigen Matrix of face (triangle) indices

weight  weighting type

FN  #F by 3 matrix of 3D face normals per face

----------------
**Returns**



N  #2 by 3 matrix of mesh edge 3D normals per row

E  #E by 2 matrix of edge indices per row

EMAP  #E by 1 matrix of indices from all edges to E

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`per_face_normals(v: array, f: array, z: array) -> object`**

Compute face normals via vertex position list, face list

**Parameters**



V  #V by 3 eigen Matrix of mesh vertex 3D positions

F  #F by 3 eigen Matrix of face (triangle) indices

Z  3 vector normal given to faces with degenerate normal.

----------------
**Returns**



N  #F by 3 eigen Matrix of mesh face (triangle) 3D normals

----------------

**See also**



--------------

**Notes**



None

**Examples**



Give degenerate faces (1/3,1/3,1/3)^0.5

------------------

### **`per_face_normals(V,F,Vector3d(1,1,1).normalized(),N);`**

------------------

### **`per_vertex_attribute_smoothing(ain: array, f: array) -> object`**

Smooth vertex attributes using uniform Laplacian

**Parameters**



Ain  #V by #A eigen Matrix of mesh vertex attributes (each vertex has #A attributes)

F    #F by 3 eigne Matrix of face (triangle) indices

----------------
**Returns**



Aout #V by #A eigen Matrix of mesh vertex attributes

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`per_vertex_normals(v: array, f: array, weighting: int = 0) -> object`**

Compute vertex normals via vertex position list, face list.

**Parameters**



v : #v by 3 array of mesh vertex 3D positions

f : #f by 3 array of face (triangle) indices

weighting : Weighting type, one of the following

-igl.PER_VERTEX_NORMALS_WEIGHTING_TYPE_UNIFORM uniform influence

-igl.PER_VERTEX_NORMALS_WEIGHTING_TYPE_AREA area weighted

-igl.PER_VERTEX_NORMALS_WEIGHTING_TYPE_ANGLE angle weighted

----------------
**Returns**



n  #v by 3 array of mesh vertex 3D normals

----------------

**See also**



per_face_normals, per_edge_normals

--------------

**Notes**



None

**Examples**



Mesh in (v, f)

n = per_vertex_normals(v, f)

------------------

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

**Parameters**



F  #F by 3 list of triangle indices into some (abstract) list of

vertices V

----------------
**Returns**



**Returns true if the mesh _combinatorially_ induces a piecewise constant**

winding number field.

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`principal_curvature(v: array, f: array, radius: int = 5, use_k_ring: bool = True) -> Tuple[object, object, object, object]`**

Compute the principal curvature directions and magnitude of the given triangle mesh.

**Parameters**



v : vertex array of size #V by 3

f : face index array #F by 3 list of mesh faces (must be triangles)

radius : controls the size of the neighbourhood used, 1 = average edge length (default: 5)

use_k_ring : (default: True)

----------------
**Returns**



pd1 : #v by 3 maximal curvature direction for each vertex

pd2 : #v by 3 minimal curvature direction for each vertex

pv1 : #v by 1 maximal curvature value for each vertex

pv2 : #v by 1 minimal curvature value for each vertex

----------------

**See also**



average_onto_faces, average_onto_vertices

--------------

**Notes**



This function has been developed by: Nikolas De Giorgis, Luigi Rocca and Enrico Puppo.

The algorithm is based on: Efficient Multi-scale Curvature and Crease Estimation

Daniele Panozzo, Enrico Puppo, Luigi Rocca GraVisMa, 2010

**Examples**



Mesh in (v, f)

pd1, pd2, pv1, pv2 = principal_curvature(v, f)

------------------

### **`procrustes(x: array, y: array) -> Tuple[bool, bool, float, object, object]`**

Solve Procrustes problem in d dimensions.  Given two point sets X,Y in R^d

find best scale s, orthogonal R  and translation t s.t. s*X*R + t - Y^2

is minimized.

**Parameters**



X  #V by DIM first list of points

Y  #V by DIM second list of points

includeScaling  if scaling should be allowed

includeReflections  if R is allowed to be a reflection

----------------
**Returns**



scale  scaling

R      orthogonal matrix

t      translation

----------------

**See also**



--------------

**Notes**



None

**Examples**



MatrixXd X, Y; (containing 3d points as rows)

double scale;

MatrixXd R;

VectorXd t;

igl::procrustes(X,Y,true,false,scale,R,t);

R *= scale;

MatrixXd Xprime = (X * R).rowwise() + t.transpose();

------------------

### **`qslim(v: array, f: array, max_m: int) -> Tuple[bool, object, object, object, object]`**

Decimate (simplify) a triangle mesh in nD according to the paper

"Simplifying Surfaces with Color and Texture using Quadric Error Metrics"

by [Garland and Heckbert, 1987] (technically a followup to qslim). The

mesh can have open boundaries but should be edge-manifold.

**Parameters**



V  #V by dim list of vertex positions. Assumes that vertices w

F  #F by 3 list of triangle indices into V

max_m  desired number of output faces

----------------
**Returns**



U  #U by dim list of output vertex posistions (can be same ref as V)

G  #G by 3 list of output face indices into U (can be same ref as G)

J  #G list of indices into F of birth face

I  #U list of indices into V of birth vertices

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`quad_planarity(v: array, f: array) -> object`**

Compute planarity of the faces of a quad mesh.

**Parameters**



v : #v by 3 array of mesh vertex 3D positions

f : #f by 4 array of face (quad) indices

----------------
**Returns**



p : #f by 1 array of mesh face (quad) planarities

----------------

**See also**



None

--------------

**Notes**



None

**Examples**



------------------

### **`random_points_on_mesh(n: int, v: array, f: array) -> Tuple[object, object]`**

RANDOM_POINTS_ON_MESH Randomly sample a mesh (V,F) n times.

**Parameters**



n  number of samples

V  #V by dim list of mesh vertex positions

F  #F by 3 list of mesh triangle indices

----------------
**Returns**



B  n by 3 list of barycentric coordinates, ith row are coordinates of

ith sampled point in face FI(i)

FI  n list of indices into F

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`read_dmat(filename: str, dtype: numpy.dtype  str  type = 'float64') -> object`**

Read a matrix from an ascii dmat file, a simple ascii matrix file type, defined as follows. The first line is always:

<#columns> <#rows>

Then the coefficients of the matrix are given separated by whitespace with columns running fastest.

**Parameters**



filename : string, path to .dmat file

dtype : data-type of the returned matrix. Default is `float64`.

(returned faces always have type int32.)

----------------
**Returns**



w : array containing read-in coefficients

----------------

**See also**



read_triangle_mesh, read_off

--------------

**Notes**



None

**Examples**



w = read_dmat("my_model.dmat")

------------------

### **`read_obj(filename: str, dtype: numpy.dtype  str  type = 'float64') -> Tuple[object, object, object, object, object, object]`**

Read a mesh from an ascii obj file, filling in vertex positions, normals

and texture coordinates. Mesh may have faces of any number of degree.

**Parameters**



filename : string, path to .obj file

dtype : data-type of the returned faces, texture coordinates and normals, optional. Default is `float64`.

(returned faces always have type int32.)

----------------
**Returns**



v : array of vertex positions #v by 3

tc : array of texture coordinats #tc by 2

n : array of corner normals #n by 3

f : #f array of face indices into vertex positions

ftc : #f array of face indices into vertex texture coordinates

fn : #f array of face indices into vertex normals

----------------

**See also**



read_triangle_mesh, read_off

--------------

**Notes**



None

**Examples**



v, _, n, f, _, _ = read_obj("my_model.obj")

------------------

### **`read_off(filename: str, read_normals: bool = True, dtype: numpy.dtype  str  type = 'float64') -> Tuple[object, object, object]`**

Read a mesh from an ascii off file, filling in vertex positions, normals

and texture coordinates. Mesh may have faces of any number of degree.

**Parameters**



filename : string, path to .off file

read_normals : bool, determines whether normals are read. If false, **returns []**

dtype : data-type of the returned vertices, faces, and normals, optional. Default is `float64`.

(returned faces always have type int32.)

----------------
**Returns**



v : array of vertex positions #v by 3

f : #f list of face indices into vertex positions

n : list of vertex normals #v by 3

----------------

**See also**



read_triangle_mesh, read_obj

--------------

**Notes**



None

**Examples**



v, f, n, c = read_off("my_model.off")

------------------

### **`read_triangle_mesh(filename: str, dtype: numpy.dtype  str  type = 'float64') -> Tuple[object, object]`**

Read mesh from an ascii file with automatic detection of file format.

Supported: obj, off, stl, wrl, ply, mesh.

**Parameters**



filename : string, path to mesh file

dtype : data-type of the returned vertices, optional. Default is `float64`.

(returned faces always have type int32.)

----------------
**Returns**



v : array of vertex positions #v by 3

f : #f list of face indices into vertex positions

----------------

**See also**



read_obj, read_off, read_stl

--------------

**Notes**



None

**Examples**



v, f = read_triangle_mesh("my_model.obj")

------------------

### **`remove_duplicate_vertices(v: array, f: array, epsilon: float) -> Tuple[object, object, object, object]`**

REMOVE_DUPLICATE_VERTICES Remove duplicate vertices upto a uniqueness

tolerance (epsilon)

**Parameters**



V  #V by dim list of vertex positions

epsilon  uniqueness tolerance (significant digit), can probably think of

this as a tolerance on L1 distance

----------------
**Returns**



SV  #SV by dim new list of vertex positions

SVI #V by 1 list of indices so SV = V(SVI,:)

SVJ #SV by 1 list of indices so V = SV(SVJ,:)

Wrapper that also remaps given faces (F) --> (SF) so that SF index SV

----------------

**See also**



--------------

**Notes**



None

**Examples**



% Mesh in (V,F)

[SV,SVI,SVJ] = remove_duplicate_vertices(V,1e-7);

% remap faces

SF = SVJ(F);

------------------

### **`remove_duplicates(v: array, f: array, epsilon: float) -> Tuple[object, object, object]`**

Merge the duplicate vertices from V, fixing the topology accordingly

**Parameters**



V,F       mesh description

epsilon   minimal distance to consider two vertices identical

----------------
**Returns**



NV, NF    new mesh without duplicate vertices

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`remove_unreferenced(v: array, f: array) -> Tuple[object, object, object, object]`**

Remove unreferenced vertices from V, updating F accordingly

**Parameters**



V  #V by dim list of mesh vertex positions

F  #F by ss list of simplices (Values of -1 are quitely skipped)

----------------
**Returns**



NV  #NV by dim list of mesh vertex positions

NF  #NF by ss list of simplices

IM  #V by 1 list of indices such that: NF = IM(F) and NT = IM(T)

and V(find(IM<=size(NV,1)),:) = NV

J  #RV by 1 list, such that RV = V(J,:)

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`resolve_duplicated_faces(f1: array) -> Tuple[object, object]`**

Resolve duplicated faces according to the following rules per unique face:

------------------

### **`If the number of positively oriented faces equals the number of`**

negatively oriented faces, remove all duplicated faces at this triangle.

------------------

### **`If the number of positively oriented faces equals the number of`**

negatively oriented faces plus 1, keeps one of the positively oriented

face.

------------------

### **`If the number of positively oriented faces equals the number of`**

negatively oriented faces minus 1, keeps one of the negatively oriented

face.

------------------

### **`If the number of postively oriented faces differ with the number of`**

negativley oriented faces by more than 1, the mesh is not orientable.

An exception will be thrown.

**Parameters**



F1  #F1 by 3 array of input faces.

----------------
**Returns**



F2  #F2 by 3 array of output faces without duplicated faces.

J   #F2 list of indices into F1.

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`shape_diameter_function(v: array, f: array, p: array, n: array, num_samples: int) -> object`**

Compute shape diamater function per given point. In the parlence of the

paper "Consistent Mesh Partitioning and Skeletonisation using the Shape

Diameter Function" [Shapiro et al. 2008], this implementation uses a 180°

cone and a _uniform_ average (_not_ a average weighted by inverse angles).

**Parameters**



V  #V by 3 list of mesh vertex positions

F  #F by 3 list of mesh face indices into V

P  #P by 3 list of origin points

N  #P by 3 list of origin normals

----------------
**Returns**



S  #P list of shape diamater function values between bounding box

diagonal (perfect sphere) and 0 (perfect needle hook)

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`sort_angles(m: array) -> object`**

Sort angles in ascending order in a numerically robust way.

Instead of computing angles using atan2(y, x), sort directly on (y, x).

**Parameters**

-

M: m by n matrix of scalars. (n >= 2).  Assuming the first column of M

contains values for y, and the second column is x.  Using the rest

of the columns as tie-breaker.

----------------
**Returns**



R: an array of m indices.  M.row(R[i]) contains the i-th smallest

angle.

----------------

**See also**



--------------

**Notes**



None.

**Examples**



------------------

### **`tetrahedralize(v: array, f: array, switches: str = 'pYQ') -> Tuple[int, object, object, object]`**

Mesh the interior of a surface mesh (V,F) using tetgen.

**Parameters**



v : #v by 3 vertex position array

f : #v array of polygon face indices into V (0-indexed)

switches : string of tetgen options (See tetgen documentation) e.g.

"pq1.414a0.01" tries to mesh the interior of a given surface with quality and area constraints. Will mesh the convex hull constrained to pass through V (ignores F)

----------------
**Returns**



tv  #v by 3 vertex position array

tt  #t by 4 array of tet face indices

tf  #f by 3 array of triangle face indices

----------------

**See also**



None

--------------

**Notes**



**Returns status:**

0 success

1 tetgen threw exception

2 tetgen did not crash but could not create any tets (probably there are

holes, duplicate faces etc.)

-1 other error

**Examples**



------------------

### **`triangle_triangle_adjacency(f: array) -> Tuple[object, object]`**

Constructs the triangle-triangle adjacency matrix for a given

mesh (V,F).

**Parameters**



F  #F by simplex_size list of mesh faces (must be triangles)

----------------
**Returns**



TT   #F by #3 adjacent matrix, the element i,j is the id of the triangle

adjacent to the j edge of triangle i

TTi  #F by #3 adjacent matrix, the element i,j is the id of edge of the

triangle TT(i,j) that is adjacent with triangle i

----------------

**See also**



--------------

**Notes**



NOTE: the first edge of a triangle is [0,1] the second [1,2] and the third

[2,3].  this convention is DIFFERENT from cotmatrix_entries.h

**Examples**



------------------

### **`triangulate(v: array, e: array, h: array, flags: str = 'a0.005qQ') -> Tuple[object, object]`**

Triangulate the interior of a polygon using the triangle library.

**Parameters**



v : #v by 2 array of 2D vertex positions

e : #e by 2 array of vertex ids forming unoriented edges of the boundary of the polygon

h : #h by 2 coordinates of points contained inside holes of the polygon

m : optional #v list of markers for input vertices

flags : string of options pass to triangle (see triangle documentation) (default 'a0.005q')

----------------
**Returns**



v2 : #v2 by 2 coordinates of the vertives of the generated triangulation

f2 : #f2 by 3 array of indices forming the faces of the generated triangulation

m2 : (only if you passed in m) #v2 list of markers for output vertices

----------------

**See also**



--------------

**Notes**



**Examples**



v2, f2 = triangulate(v, e, h)

------------------

### **`uniformly_sample_two_manifold_at_vertices(ow: array, k: int, push: float) -> object`**

Find uniform sampling up to placing samples on mesh vertices

**Parameters**



----------------
**Returns**



----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`uniformly_sample_two_manifold_internal(w: array, f: array, k: int, push: float) -> object`**

UNIFORMLY_SAMPLE_TWO_MANIFOLD Attempt to sample a mesh uniformly by

furthest point relaxation as described in "Fast Automatic Skinning

Transformations"

[Jacobson et al. 12] Section 3.3.

**Parameters**



W  #W by dim positions of mesh in weight space

F  #F by 3 indices of triangles

k  number of samplse

push  factor by which corners should be pushed away

----------------
**Returns**



WS  k by dim locations in weights space

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`unproject(win: array, model: array, proj: array, viewport: array) -> object`**

Reimplementation of gluUnproject

**Parameters**



win  #P by 3 or 3-vector (#P=1) of screen space x, y, and z coordinates

model  4x4 model-view matrix

proj  4x4 projection matrix

viewport  4-long viewport vector

----------------
**Returns**



scene  #P by 3 or 3-vector (#P=1) the unprojected x, y, and z coordinates

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`unproject_in_mesh(pos: numpy.ndarray[float32[2, 1]], model: numpy.ndarray[float32[4, 4]], proj: numpy.ndarray[float32[4, 4]], viewport: numpy.ndarray[float32[4, 1]], v: array, f: array) -> Tuple[object, std::__1::vector<igl::Hit, std::__1::allocator<igl::Hit> >]`**

Unproject a screen location (using current opengl viewport, projection, and

model view) to a 3D position _inside_ a given mesh. If the ray through the

given screen location (x,y) _hits_ the mesh more than twice then the 3D

midpoint between the first two hits is return. If it hits once, then that

point is return. If it does not hit the mesh then obj is not set.

**Parameters**



pos        screen space coordinates

model      model matrix

proj       projection matrix

viewport   vieweport vector

V   #V by 3 list of mesh vertex positions

F   #F by 3 list of mesh triangle indices into V

----------------
**Returns**



obj        3d unprojected mouse point in mesh

hits       vector of hits

**Returns number of hits**

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`unproject_onto_mesh(pos: array, model: array, proj: array, viewport: array, v: array, f: array) -> Tuple[bool, int, object]`**

Unproject a screen location (using current opengl viewport, projection, and

model view) to a 3D position _onto_ a given mesh, if the ray through the

given screen location (x,y) _hits_ the mesh.

**Parameters**



pos        screen space coordinates

model      model matrix

proj       projection matrix

viewport   vieweport vector

V   #V by 3 list of mesh vertex positions

F   #F by 3 list of mesh triangle indices into V

----------------
**Returns**



fid  id of the first face hit

bc  barycentric coordinates of hit

**Returns true if there's a hit**

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`unproject_ray(pos: array, model: array, proj: array, viewport: array) -> Tuple[object, object]`**

Construct a ray (source point + direction vector) given a screen space

positions (e.g. mouse) and a model-view projection constellation.

**Parameters**



pos  2d screen-space position (x,y)

model  4x4 model-view matrix

proj  4x4 projection matrix

viewport  4-long viewport vector

----------------
**Returns**



s  source of ray (pos unprojected with z=0)

dir  direction of ray (d - s) where d is pos unprojected with z=1

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`upsample(v: array, f: array, number_of_subdivs: int = 1) -> Tuple[object, object]`**

Subdivide a mesh without moving vertices: loop subdivision but odd

vertices stay put and even vertices are just edge midpoints

**Parameters**



V  #V by dim  mesh vertices

F  #F by 3  mesh triangles

----------------
**Returns**



NV new vertex positions, V is guaranteed to be at top

NF new list of face indices

----------------

**See also**



--------------

**Notes**



- assumes (V,F) is edge-manifold.

**Examples**



------------------

### **`vector_area_matrix(f: array) -> object`**

Constructs the symmetric area matrix A, s.t. [V.col(0)' V.col(1)'] * A *

[V.col(0); V.col(1)] is the **vector area** of the mesh (V,F).

**Parameters**



f : #f by 3 array of mesh faces (must be triangles)

----------------
**Returns**



a : #vx2 by #vx2 area matrix

----------------

**See also**



None

--------------

**Notes**



None

**Examples**



------------------

### **`vertex_components(f: array) -> object`**

Compute connected components of the vertices of a mesh given the mesh' face indices.

**Parameters**



f : #f x dim array of face indices

----------------
**Returns**



An array of component ids (starting with 0)

----------------

**See also**



vertex_components_from_adjacency_matrix

face_components_from_faces

--------------

**Notes**



**Examples**



------------------

### **`vertex_components_from_adjacency_matrix(a: scipy.sparse.csr_matrix  scipy.sparse.csc_matrix) -> Tuple[object, object]`**

Compute connected components of a graph represented by a sparse adjacency

matrix.

**Parameters**



a : n by n sparse adjacency matrix

----------------
**Returns**



A tuple (c, counts) where c is an array of component ids (starting with 0)

and counts is a #components array of counts for each component

----------------

**See also**



vertex_components

face_components

--------------

**Notes**



**Examples**



------------------

### **`vertex_triangle_adjacency(f: array, n: int) -> Tuple[object, object]`**

vertex_face_adjacency constructs the vertex-face topology of a given mesh (V,F)

**Parameters**



F  #F by 3 list of triangle indices into some vertex list V

n  number of vertices, #V (e.g., F.maxCoeff()+1)

----------------
**Returns**



VF  3*#F list  List of faces indice on each vertex, so that VF(NI(i)+j) =

f, means that face f is the jth face (in no particular order) incident

on vertex i.

NI  #V+1 list  cumulative sum of vertex-triangle degrees with a

preceeding zero. "How many faces" have been seen before visiting this

vertex and its incident faces.

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`winding_number(v: array, f: array, o: array) -> object`**

WINDING_NUMBER Compute the sum of solid angles of a triangle/tetrahedron

described by points (vectors) V

**Parameters**



V  n by 3 list of vertex positions

F  #F by 3 list of triangle indices, minimum index is 0

O  no by 3 list of origin positions

----------------
**Returns**



S  no by 1 list of winding numbers

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`winding_number_for_point(v: array, f: array, p: array) -> float`**

Compute winding number of a single point

**Parameters**



V  n by dim list of vertex positions

F  #F by dim list of triangle indices, minimum index is 0

p  single origin position

----------------
**Returns**



w  winding number of this point

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`write_obj(filename: str, v: array, f: array) -> bool`**

Write a mesh in an ascii obj file.

**Parameters**



filename : path to outputfile

v : array of vertex positions #v by 3

f : #f list of face indices into vertex positions

----------------
**Returns**



ret : bool if output was successful

----------------

**See also**



read_obj

--------------

**Notes**



None

**Examples**



Mesh in (v, f)

success = write_obj(v, f)

------------------

### **`write_off(str: str, v: array, f: array, c: array) -> bool`**

Export geometry and colors-by-vertex

Export a mesh from an ascii OFF file, filling in vertex positions.

Only triangle meshes are supported

**Parameters**



str  path to .off output file

V  #V by 3 mesh vertex positions

F  #F by 3 mesh indices into V

C  double matrix of rgb values per vertex #V by 3

----------------
**Returns**



**Returns true on success, false on errors**

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`write_triangle_mesh(str: str, v: array, f: array, force_ascii: bool = True) -> bool`**

write mesh to a file with automatic detection of file format.  supported: obj, off, stl, wrl, ply, mesh).

**Parameters**



str  path to file

V  eigen double matrix #V by 3

F  eigen int matrix #F by 3

force_ascii=True  force ascii format even if binary is available

----------------
**Returns**



**Returns true iff success**

----------------

**See also**



--------------

**Notes**



**Examples**



VERSION

dev

FILE

/Users/teseo/data/igl/python/igl/pyigl.cpython-36m-darwin.so




igl.adjacency_list = adjacency_list(...) method of builtins.PyCapsule instance

------------------

### **`adjacency_list(f: array) -> handle`**

Constructs the graph adjacency list of a given mesh (v, f)

**Parameters**



f : #f by dim array of fixed dimensional (e.g. triangle (#f by 3),

tet (#f by 4), quad (#f by 4), etc...) mesh faces

----------------
**Returns**



list of lists containing at index i the adjacent vertices of vertex i

----------------

**See also**



adjacency_matrix

--------------

**Notes**



**Examples**



Mesh in (v, f)

a = mesh_adjacency_list(f)




igl.adjacency_list = adjacency_list(...) method of builtins.PyCapsule instance

------------------

### **`adjacency_list(f: array) -> handle`**

Constructs the graph adjacency list of a given mesh (v, f)

**Parameters**



f : #f by dim array of fixed dimensional (e.g. triangle (#f by 3),

tet (#f by 4), quad (#f by 4), etc...) mesh faces

----------------
**Returns**



list of lists containing at index i the adjacent vertices of vertex i

----------------

**See also**



adjacency_matrix

--------------

**Notes**



**Examples**



Mesh in (v, f)

a = mesh_adjacency_list(f)




igl.adjacency_matrix = adjacency_matrix(...) method of builtins.PyCapsule instance

------------------

### **`adjacency_matrix(f: array) -> object`**

Constructs the graph adjacency matrix of a given mesh (v, f).

**Parameters**



f : #f by dim list of mesh simplices

----------------
**Returns**



a : max(f) by max(f) cotangent matrix, each row i corresponding to v(i, :)

----------------

**See also**



adjacency_list, edges, cotmatrix, diag

--------------

**Notes**



None

**Examples**



Mesh in (v, f)

a = adjacency_matrix(f)

Sum each row

a_sum = np.sum(a, axis=1)

Convert row sums into diagonal of sparse matrix

a_diag = diag(a_sum)

Build uniform laplacian

u = a - a_diag




igl.adjacency_matrix = adjacency_matrix(...) method of builtins.PyCapsule instance

------------------

### **`adjacency_matrix(f: array) -> object`**

Constructs the graph adjacency matrix of a given mesh (v, f).

**Parameters**



f : #f by dim list of mesh simplices

----------------
**Returns**



a : max(f) by max(f) cotangent matrix, each row i corresponding to v(i, :)

----------------

**See also**



adjacency_list, edges, cotmatrix, diag

--------------

**Notes**



None

**Examples**



Mesh in (v, f)

a = adjacency_matrix(f)

Sum each row

a_sum = np.sum(a, axis=1)

Convert row sums into diagonal of sparse matrix

a_diag = diag(a_sum)

Build uniform laplacian

u = a - a_diag




igl.ambient_occlusion = ambient_occlusion(...) method of builtins.PyCapsule instance

------------------

### **`ambient_occlusion(v: array, f: array, p: array, n: array, num_samples: int) -> object`**

**Parameters**



V  #V by 3 list of mesh vertex positions

F  #F by 3 list of mesh face indices into V

P  #P by 3 list of origin points

N  #P by 3 list of origin normals

----------------
**Returns**



S  #P list of ambient occusion values between 1 (fully occluded) and 0 (not occluded)

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.ambient_occlusion = ambient_occlusion(...) method of builtins.PyCapsule instance

------------------

### **`ambient_occlusion(v: array, f: array, p: array, n: array, num_samples: int) -> object`**

**Parameters**



V  #V by 3 list of mesh vertex positions

F  #F by 3 list of mesh face indices into V

P  #P by 3 list of origin points

N  #P by 3 list of origin normals

----------------
**Returns**



S  #P list of ambient occusion values between 1 (fully occluded) and 0 (not occluded)

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.arap_linear_block = arap_linear_block(...) method of builtins.PyCapsule instance

------------------

### **`arap_linear_block(v: array, f: array, d: int, energy: int) -> object`**

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

**Parameters**



v : #v by dim list of initial domain positions

f : #f by #simplex size list of triangle indices into V

d : coordinate of linear constructor to build

----------------
**Returns**



by #v/#f block of the linear constructor matrix corresponding to coordinate d

----------------

**See also**



arap, arap_dof

--------------

**Notes**



**Examples**






igl.arap_linear_block = arap_linear_block(...) method of builtins.PyCapsule instance

------------------

### **`arap_linear_block(v: array, f: array, d: int, energy: int) -> object`**

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

**Parameters**



v : #v by dim list of initial domain positions

f : #f by #simplex size list of triangle indices into V

d : coordinate of linear constructor to build

----------------
**Returns**



by #v/#f block of the linear constructor matrix corresponding to coordinate d

----------------

**See also**



arap, arap_dof

--------------

**Notes**



**Examples**






igl.arap_linear_block_elements = arap_linear_block_elements(...) method of builtins.PyCapsule instance

------------------

### **`arap_linear_block_elements(v: array, f: array, d: int) -> object`**

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

**Parameters**



v : #v by dim list of initial domain positions

f : #f by #simplex size list of triangle indices into V

d : coordinate of linear constructor to build

----------------
**Returns**



by #v/#f block of the linear constructor matrix corresponding to coordinate d

----------------

**See also**



arap, arap_dof

--------------

**Notes**



**Examples**






igl.arap_linear_block_elements = arap_linear_block_elements(...) method of builtins.PyCapsule instance

------------------

### **`arap_linear_block_elements(v: array, f: array, d: int) -> object`**

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

**Parameters**



v : #v by dim list of initial domain positions

f : #f by #simplex size list of triangle indices into V

d : coordinate of linear constructor to build

----------------
**Returns**



by #v/#f block of the linear constructor matrix corresponding to coordinate d

----------------

**See also**



arap, arap_dof

--------------

**Notes**



**Examples**






igl.arap_linear_block_spokes = arap_linear_block_spokes(...) method of builtins.PyCapsule instance

------------------

### **`arap_linear_block_spokes(v: array, f: array, d: int) -> object`**

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

**Parameters**



v : #v by dim list of initial domain positions

f : #f by #simplex size list of triangle indices into V

d : coordinate of linear constructor to build

----------------
**Returns**



by #v/#f block of the linear constructor matrix corresponding to coordinate d

----------------

**See also**



arap, arap_dof

--------------

**Notes**



**Examples**






igl.arap_linear_block_spokes = arap_linear_block_spokes(...) method of builtins.PyCapsule instance

------------------

### **`arap_linear_block_spokes(v: array, f: array, d: int) -> object`**

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

**Parameters**



v : #v by dim list of initial domain positions

f : #f by #simplex size list of triangle indices into V

d : coordinate of linear constructor to build

----------------
**Returns**



by #v/#f block of the linear constructor matrix corresponding to coordinate d

----------------

**See also**



arap, arap_dof

--------------

**Notes**



**Examples**






igl.arap_linear_block_spokes_and_rims = arap_linear_block_spokes_and_rims(...) method of builtins.PyCapsule instance

------------------

### **`arap_linear_block_spokes_and_rims(v: array, f: array, d: int) -> object`**

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

**Parameters**



v : #v by dim list of initial domain positions

f : #f by #simplex size list of triangle indices into V

d : coordinate of linear constructor to build

----------------
**Returns**



by #v/#f block of the linear constructor matrix corresponding to coordinate d

----------------

**See also**



arap, arap_dof

--------------

**Notes**



**Examples**






igl.arap_linear_block_spokes_and_rims = arap_linear_block_spokes_and_rims(...) method of builtins.PyCapsule instance

------------------

### **`arap_linear_block_spokes_and_rims(v: array, f: array, d: int) -> object`**

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

**Parameters**



v : #v by dim list of initial domain positions

f : #f by #simplex size list of triangle indices into V

d : coordinate of linear constructor to build

----------------
**Returns**



by #v/#f block of the linear constructor matrix corresponding to coordinate d

----------------

**See also**



arap, arap_dof

--------------

**Notes**



**Examples**






igl.arap_rhs = arap_rhs(...) method of builtins.PyCapsule instance

------------------

### **`arap_rhs(v: array, f: array, d: int, energy: int) -> object`**

Guild right-hand side constructor of global poisson solve for various ARAP energies

Inputs:

Outputs:

K  #V*dim by #(FV)*dim*dim matrix such that:

b = K * reshape(permute(R,[3 1 2]),size(VF,1)*size(V,2)*size(V,2),1);

**Parameters**



v : #v by Vdim list of initial domain positions

f : #f by 3 list of triangle indices into v

d : dimension being used at solve time. For deformation usually dim = V.cols(), for surface parameterization V.cols() = 3 and dim = 2

energy : ARAPEnergyType enum value defining which energy is being used. See igl.ARAPEnergyType for valid options and explanations.

----------------
**Returns**



*d by #(fv)*dim*dim matrix such that: b = K * reshape(permute(R,[3 1 2]),size(VF,1)*size(V,2)*size(V,2),1);

----------------

**See also**



arap_linear_block, arap

--------------

**Notes**



**Examples**






igl.arap_rhs = arap_rhs(...) method of builtins.PyCapsule instance

------------------

### **`arap_rhs(v: array, f: array, d: int, energy: int) -> object`**

Guild right-hand side constructor of global poisson solve for various ARAP energies

Inputs:

Outputs:

K  #V*dim by #(FV)*dim*dim matrix such that:

b = K * reshape(permute(R,[3 1 2]),size(VF,1)*size(V,2)*size(V,2),1);

**Parameters**



v : #v by Vdim list of initial domain positions

f : #f by 3 list of triangle indices into v

d : dimension being used at solve time. For deformation usually dim = V.cols(), for surface parameterization V.cols() = 3 and dim = 2

energy : ARAPEnergyType enum value defining which energy is being used. See igl.ARAPEnergyType for valid options and explanations.

----------------
**Returns**



*d by #(fv)*dim*dim matrix such that: b = K * reshape(permute(R,[3 1 2]),size(VF,1)*size(V,2)*size(V,2),1);

----------------

**See also**



arap_linear_block, arap

--------------

**Notes**



**Examples**






igl.average_onto_vertices = average_onto_vertices(...) method of builtins.PyCapsule instance

------------------

### **`average_onto_vertices(v: array, f: array, s: array) -> object`**

Move a scalar field defined on faces to vertices by averaging

**Parameters**



v : #v by vdim array of mesh vertices

f : #f by simplex_count array of simplex indices

s : #f by dim scalar field defined on simplices

----------------
**Returns**



by dim scalar field defined on vertices

----------------

**See also**



average_onto_faces

--------------

**Notes**



**Examples**






igl.average_onto_vertices = average_onto_vertices(...) method of builtins.PyCapsule instance

------------------

### **`average_onto_vertices(v: array, f: array, s: array) -> object`**

Move a scalar field defined on faces to vertices by averaging

**Parameters**



v : #v by vdim array of mesh vertices

f : #f by simplex_count array of simplex indices

s : #f by dim scalar field defined on simplices

----------------
**Returns**



by dim scalar field defined on vertices

----------------

**See also**



average_onto_faces

--------------

**Notes**



**Examples**






igl.avg_edge_length = avg_edge_length(...) method of builtins.PyCapsule instance

------------------

### **`avg_edge_length(v: array, f: array) -> float`**

Compute the average edge length for the given triangle mesh.

**Parameters**



v : array_like #v by 3 vertex array

f : f #f by simplex-size list of mesh faces (must be simplex)

----------------
**Returns**



l : average edge length

----------------

**See also**



adjacency_matrix

--------------

**Notes**



None

**Examples**



Mesh in (v, f)

length = avg_edge_length(v, f)




igl.avg_edge_length = avg_edge_length(...) method of builtins.PyCapsule instance

------------------

### **`avg_edge_length(v: array, f: array) -> float`**

Compute the average edge length for the given triangle mesh.

**Parameters**



v : array_like #v by 3 vertex array

f : f #f by simplex-size list of mesh faces (must be simplex)

----------------
**Returns**



l : average edge length

----------------

**See also**



adjacency_matrix

--------------

**Notes**



None

**Examples**



Mesh in (v, f)

length = avg_edge_length(v, f)




igl.barycenter = barycenter(...) method of builtins.PyCapsule instance

------------------

### **`barycenter(v: array, f: array) -> object`**

Compute the barycenter of every simplex

**Parameters**



v : #v x dim matrix of vertex coordinates

f : #f x simplex_size  matrix of indices of simplex corners into V

----------------
**Returns**



A #f x dim matrix where each row is the barycenter of each simplex

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.barycenter = barycenter(...) method of builtins.PyCapsule instance

------------------

### **`barycenter(v: array, f: array) -> object`**

Compute the barycenter of every simplex

**Parameters**



v : #v x dim matrix of vertex coordinates

f : #f x simplex_size  matrix of indices of simplex corners into V

----------------
**Returns**



A #f x dim matrix where each row is the barycenter of each simplex

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.barycentric_coordinates_tet = barycentric_coordinates_tet(...) method of builtins.PyCapsule instance

------------------

### **`barycentric_coordinates_tet(p: array, a: array, b: array, c: array, d: array) -> object`**

Compute barycentric coordinates in a tet corresponding to the Euclidean coordinates in `p`.

The input arrays `a`, `b`, `c` and `d` are the vertices of each tet. I.e. one tet is

`a[i, :], b[i, :], c[i, :], d[:, i]`.

**Parameters**



p : #P by 3 Query points in 3d

a : #P by 3 Tet corners in 3d

b : #P by 3 Tet corners in 3d

c : #P by 3 Tet corners in 3d

d : #P by 3 Tet corners in 3d

----------------
**Returns**



by 4 list of barycentric coordinates

----------------

**See also**



--------------

**Notes**



**Examples**






igl.barycentric_coordinates_tet = barycentric_coordinates_tet(...) method of builtins.PyCapsule instance

------------------

### **`barycentric_coordinates_tet(p: array, a: array, b: array, c: array, d: array) -> object`**

Compute barycentric coordinates in a tet corresponding to the Euclidean coordinates in `p`.

The input arrays `a`, `b`, `c` and `d` are the vertices of each tet. I.e. one tet is

`a[i, :], b[i, :], c[i, :], d[:, i]`.

**Parameters**



p : #P by 3 Query points in 3d

a : #P by 3 Tet corners in 3d

b : #P by 3 Tet corners in 3d

c : #P by 3 Tet corners in 3d

d : #P by 3 Tet corners in 3d

----------------
**Returns**



by 4 list of barycentric coordinates

----------------

**See also**



--------------

**Notes**



**Examples**






igl.barycentric_coordinates_tri = barycentric_coordinates_tri(...) method of builtins.PyCapsule instance

------------------

### **`barycentric_coordinates_tri(p: array, a: array, b: array, c: array) -> object`**

Compute barycentric coordinates in a triangle corresponding to the Euclidean coordinates in `p`.

The input arrays `a`, `b`, and `c` are the vertices of each triangle. I.e. one triangle is

`a[i, :], b[i, :], c[i, :]`.

**Parameters**



p : #P by 3 Query points in 3d

a : #P by 3 Tri corners in 3d

b : #P by 3 Tri corners in 3d

c : #P by 3 Tri corners in 3d

----------------
**Returns**



by 3 list of barycentric coordinates

----------------

**See also**



--------------

**Notes**



**Examples**






igl.barycentric_coordinates_tri = barycentric_coordinates_tri(...) method of builtins.PyCapsule instance

------------------

### **`barycentric_coordinates_tri(p: array, a: array, b: array, c: array) -> object`**

Compute barycentric coordinates in a triangle corresponding to the Euclidean coordinates in `p`.

The input arrays `a`, `b`, and `c` are the vertices of each triangle. I.e. one triangle is

`a[i, :], b[i, :], c[i, :]`.

**Parameters**



p : #P by 3 Query points in 3d

a : #P by 3 Tri corners in 3d

b : #P by 3 Tri corners in 3d

c : #P by 3 Tri corners in 3d

----------------
**Returns**



by 3 list of barycentric coordinates

----------------

**See also**



--------------

**Notes**



**Examples**






igl.bfs = bfs(...) method of builtins.PyCapsule instance

------------------

### **`bfs(A: scipy.sparse.csr_matrix  scipy.sparse.csc_matrix, s: int) -> Tuple[object, object]`**

Construct an array indexing into a **directed** graph represented by an adjacency list using

breadth first search. I.e. the output is an array of vertices in breadth-first order.

**Parameters**



A : #V list of adjacency lists  or #V by #V adjacency matrix

s : starting node (index into A)

----------------
**Returns**



A tuple, (d, p) where:

* d is a #V list of indices into rows of A in the order in which graph nodes are discovered

* p is a #V list of indices of A of predecsors where -1 indicates root/not discovered. I.e.

p[i] is the index of the vertex v which preceded d[i] in the breadth first traversal.

Note that together, (d, p) form a spanning tree of the input graph

----------------

**See also**



--------------

**Notes**



**Examples**



V, F, _ = igl.readOFF("test.off)

A = igl.adjacency_matrix(V, F)

d, p = igl.bfs(A, V[0])




igl.bfs = bfs(...) method of builtins.PyCapsule instance

------------------

### **`bfs(A: scipy.sparse.csr_matrix  scipy.sparse.csc_matrix, s: int) -> Tuple[object, object]`**

Construct an array indexing into a **directed** graph represented by an adjacency list using

breadth first search. I.e. the output is an array of vertices in breadth-first order.

**Parameters**



A : #V list of adjacency lists  or #V by #V adjacency matrix

s : starting node (index into A)

----------------
**Returns**



A tuple, (d, p) where:

* d is a #V list of indices into rows of A in the order in which graph nodes are discovered

* p is a #V list of indices of A of predecsors where -1 indicates root/not discovered. I.e.

p[i] is the index of the vertex v which preceded d[i] in the breadth first traversal.

Note that together, (d, p) form a spanning tree of the input graph

----------------

**See also**



--------------

**Notes**



**Examples**



V, F, _ = igl.readOFF("test.off)

A = igl.adjacency_matrix(V, F)

d, p = igl.bfs(A, V[0])




igl.bfs_orient = bfs_orient(...) method of builtins.PyCapsule instance

------------------

### **`bfs_orient(f: array) -> Tuple[object, object]`**

Consistently orient faces in orientable patches using BFS.

**Parameters**



f : #F by 3 list of faces

----------------
**Returns**



A tuple, (ff, c) where:

* ff is a #F by 3 list of faces which are consistently oriented with

* c is a #F array of connected component ids

----------------

**See also**



--------------

**Notes**



**Examples**



v, f, _ = igl.readOFF("test.off)

ff, c = igl.bfs_orient(f)




igl.bfs_orient = bfs_orient(...) method of builtins.PyCapsule instance

------------------

### **`bfs_orient(f: array) -> Tuple[object, object]`**

Consistently orient faces in orientable patches using BFS.

**Parameters**



f : #F by 3 list of faces

----------------
**Returns**



A tuple, (ff, c) where:

* ff is a #F by 3 list of faces which are consistently oriented with

* c is a #F array of connected component ids

----------------

**See also**



--------------

**Notes**



**Examples**



v, f, _ = igl.readOFF("test.off)

ff, c = igl.bfs_orient(f)




igl.bone_parents = bone_parents(...) method of builtins.PyCapsule instance

------------------

### **`bone_parents(be: array) -> object`**

BONE_PARENTS Recover "parent" bones from directed graph representation.

**Parameters**



BE  #BE by 2 list of directed bone edges

----------------
**Returns**



P  #BE by 1 list of parent indices into BE, -1 means root.

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.bone_parents = bone_parents(...) method of builtins.PyCapsule instance

------------------

### **`bone_parents(be: array) -> object`**

BONE_PARENTS Recover "parent" bones from directed graph representation.

**Parameters**



BE  #BE by 2 list of directed bone edges

----------------
**Returns**



P  #BE by 1 list of parent indices into BE, -1 means root.

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.boundary_conditions = boundary_conditions(...) method of builtins.PyCapsule instance

------------------

### **`boundary_conditions(v: array, ele: array, c: array, p: array, be: array, ce: array) -> Tuple[bool, object, object]`**

Compute boundary conditions for automatic weights computation. This

function expects that the given mesh (V,Ele) has sufficient samples

(vertices) exactly at point handle locations and exactly along bone and

cage edges.

**Parameters**



V  #V by dim list of domain vertices

Ele  #Ele by simplex-size list of simplex indices

C  #C by dim list of handle positions

P  #P by 1 list of point handle indices into C

BE  #BE by 2 list of bone edge indices into C

CE  #CE by 2 list of cage edge indices into *P*

----------------
**Returns**



b  #b list of boundary indices (indices into V of vertices which have

known, fixed values)

bc #b by #weights list of known/fixed values for boundary vertices

(notice the #b != #weights in general because #b will include all the

intermediary samples along each bone, etc.. The ordering of the

weights corresponds to [P;BE]

**Returns false if boundary conditions are suspicious:**

P and BE are empty

bc is empty

some column of bc doesn't have a 0 (assuming bc has >1 columns)

some column of bc doesn't have a 1 (assuming bc has >1 columns)

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.boundary_conditions = boundary_conditions(...) method of builtins.PyCapsule instance

------------------

### **`boundary_conditions(v: array, ele: array, c: array, p: array, be: array, ce: array) -> Tuple[bool, object, object]`**

Compute boundary conditions for automatic weights computation. This

function expects that the given mesh (V,Ele) has sufficient samples

(vertices) exactly at point handle locations and exactly along bone and

cage edges.

**Parameters**



V  #V by dim list of domain vertices

Ele  #Ele by simplex-size list of simplex indices

C  #C by dim list of handle positions

P  #P by 1 list of point handle indices into C

BE  #BE by 2 list of bone edge indices into C

CE  #CE by 2 list of cage edge indices into *P*

----------------
**Returns**



b  #b list of boundary indices (indices into V of vertices which have

known, fixed values)

bc #b by #weights list of known/fixed values for boundary vertices

(notice the #b != #weights in general because #b will include all the

intermediary samples along each bone, etc.. The ordering of the

weights corresponds to [P;BE]

**Returns false if boundary conditions are suspicious:**

P and BE are empty

bc is empty

some column of bc doesn't have a 0 (assuming bc has >1 columns)

some column of bc doesn't have a 1 (assuming bc has >1 columns)

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.boundary_facets = boundary_facets(...) method of builtins.PyCapsule instance

------------------

### **`boundary_facets(t: array) -> object`**

Determine boundary faces (edges) of tetrahedra (triangles).

**Parameters**



t : tetrahedron or triangle index list, m by 4/3, where m is the number of tetrahedra/triangles

----------------
**Returns**



f : list of boundary faces, n by 3/2, where n is the number of boundary faces/edges

----------------

**See also**



None

--------------

**Notes**



None

**Examples**



Mesh in (v, f)

b = boundary_facets(f)




igl.boundary_facets = boundary_facets(...) method of builtins.PyCapsule instance

------------------

### **`boundary_facets(t: array) -> object`**

Determine boundary faces (edges) of tetrahedra (triangles).

**Parameters**



t : tetrahedron or triangle index list, m by 4/3, where m is the number of tetrahedra/triangles

----------------
**Returns**



f : list of boundary faces, n by 3/2, where n is the number of boundary faces/edges

----------------

**See also**



None

--------------

**Notes**



None

**Examples**



Mesh in (v, f)

b = boundary_facets(f)




igl.boundary_loop = boundary_loop(...) method of builtins.PyCapsule instance

------------------

### **`boundary_loop(f: array) -> object`**

Compute ordered boundary loops for a manifold mesh and return the longest loop in terms of vertices.

**Parameters**



f : #v by dim array of mesh faces

----------------
**Returns**



l : ordered list of boundary vertices of longest boundary loop

----------------

**See also**



--------------

**Notes**



None

**Examples**



Mesh in (v, f)

l = boundary_loop(f)




igl.boundary_loop = boundary_loop(...) method of builtins.PyCapsule instance

------------------

### **`boundary_loop(f: array) -> object`**

Compute ordered boundary loops for a manifold mesh and return the longest loop in terms of vertices.

**Parameters**



f : #v by dim array of mesh faces

----------------
**Returns**



l : ordered list of boundary vertices of longest boundary loop

----------------

**See also**



--------------

**Notes**



None

**Examples**



Mesh in (v, f)

l = boundary_loop(f)




igl.bounding_box = bounding_box(...) method of builtins.PyCapsule instance

------------------

### **`bounding_box(*args, **kwargs)`**

------------------

### **`bounding_box(v: array) -> Tuple[object, object]`**

Build a triangle mesh of the bounding box of a given list of vertices

**Parameters**



V  #V by dim list of rest domain positions

----------------
**Returns**



BV  2^dim by dim list of bounding box corners positions

BF  #BF by dim list of simplex facets

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`bounding_box(v: array, pad: float) -> Tuple[object, object]`**

Build a triangle mesh of the bounding box of a given list of vertices

**Parameters**



V  #V by dim list of rest domain positions

----------------
**Returns**



BV  2^dim by dim list of bounding box corners positions

BF  #BF by dim list of simplex facets

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.bounding_box = bounding_box(...) method of builtins.PyCapsule instance

------------------

### **`bounding_box(*args, **kwargs)`**

------------------

### **`bounding_box(v: array) -> Tuple[object, object]`**

Build a triangle mesh of the bounding box of a given list of vertices

**Parameters**



V  #V by dim list of rest domain positions

----------------
**Returns**



BV  2^dim by dim list of bounding box corners positions

BF  #BF by dim list of simplex facets

----------------

**See also**



--------------

**Notes**



None

**Examples**



------------------

### **`bounding_box(v: array, pad: float) -> Tuple[object, object]`**

Build a triangle mesh of the bounding box of a given list of vertices

**Parameters**



V  #V by dim list of rest domain positions

----------------
**Returns**



BV  2^dim by dim list of bounding box corners positions

BF  #BF by dim list of simplex facets

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.bounding_box_diagonal = bounding_box_diagonal(...) method of builtins.PyCapsule instance

------------------

### **`bounding_box_diagonal(v: array) -> float`**

Compute the length of the diagonal of a given meshes axis-aligned bounding

**Parameters**



V  #V by 3 list of vertex positions

F  #F by 3 list of triangle indices into V

----------------
**Returns**



**Returns length of bounding box diagonal**

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.bounding_box_diagonal = bounding_box_diagonal(...) method of builtins.PyCapsule instance

------------------

### **`bounding_box_diagonal(v: array) -> float`**

Compute the length of the diagonal of a given meshes axis-aligned bounding

**Parameters**



V  #V by 3 list of vertex positions

F  #F by 3 list of triangle indices into V

----------------
**Returns**



**Returns length of bounding box diagonal**

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.centroid = centroid(...) method of builtins.PyCapsule instance

------------------

### **`centroid(v: array, f: array) -> Tuple[object]`**

Computes the centroid of a closed mesh using a surface integral.

**Parameters**



v : #v by dim array of rest domain positions

f : #f by 3 array of triangle indices into v

----------------
**Returns**



c : dim array of centroid coordinates

vol : total volume of solid

----------------

**See also**



None

--------------

**Notes**



None

**Examples**



Mesh in (v, f)

c, vol = centroid(v, f)




igl.centroid = centroid(...) method of builtins.PyCapsule instance

------------------

### **`centroid(v: array, f: array) -> Tuple[object]`**

Computes the centroid of a closed mesh using a surface integral.

**Parameters**



v : #v by dim array of rest domain positions

f : #f by 3 array of triangle indices into v

----------------
**Returns**



c : dim array of centroid coordinates

vol : total volume of solid

----------------

**See also**



None

--------------

**Notes**



None

**Examples**



Mesh in (v, f)

c, vol = centroid(v, f)




igl.circulation = circulation(...) method of builtins.PyCapsule instance

------------------

### **`circulation(e: int, ccw: bool, emap: array, ef: array, ei: array) -> List[int]`**

Return list of faces around the end point of an edge. Assumes

data-structures are built from an edge-manifold **closed** mesh.

**Parameters**



e  index into E of edge to circulate

ccw  whether to _continue_ in ccw direction of edge (circulate around

------------------

### **`EMAP #F*3 list of indices into E, mapping each directed edge to unique`**

unique edge in E

EF  #E by 2 list of edge flaps, EF(e,0)=f means e=(i-->j) is the edge of

------------------

### **`e=(j->i)`**

EI  #E by 2 list of edge flap corners (see above).

----------------
**Returns**



**Returns list of faces touched by circulation (in cyclically order).**

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.circulation = circulation(...) method of builtins.PyCapsule instance

------------------

### **`circulation(e: int, ccw: bool, emap: array, ef: array, ei: array) -> List[int]`**

Return list of faces around the end point of an edge. Assumes

data-structures are built from an edge-manifold **closed** mesh.

**Parameters**



e  index into E of edge to circulate

ccw  whether to _continue_ in ccw direction of edge (circulate around

------------------

### **`EMAP #F*3 list of indices into E, mapping each directed edge to unique`**

unique edge in E

EF  #E by 2 list of edge flaps, EF(e,0)=f means e=(i-->j) is the edge of

------------------

### **`e=(j->i)`**

EI  #E by 2 list of edge flap corners (see above).

----------------
**Returns**



**Returns list of faces touched by circulation (in cyclically order).**

----------------

**See also**



--------------

**Notes**



None

**Examples**












igl.circumradius = circumradius(...) method of builtins.PyCapsule instance

------------------

### **`circumradius(v: array, f: array) -> object`**

Compute the circumradius of each triangle in a mesh (V,F)

**Parameters**



V  #V by dim list of mesh vertex positions

F  #F by 3 list of triangle indices into V

----------------
**Returns**



R  #F list of circumradii

----------------

**See also**



--------------

**Notes**



None

**Examples**



R = circumradius(V, F)




igl.circumradius = circumradius(...) method of builtins.PyCapsule instance

------------------

### **`circumradius(v: array, f: array) -> object`**

Compute the circumradius of each triangle in a mesh (V,F)

**Parameters**



V  #V by dim list of mesh vertex positions

F  #F by 3 list of triangle indices into V

----------------
**Returns**



R  #F list of circumradii

----------------

**See also**



--------------

**Notes**



None

**Examples**



R = circumradius(V, F)




igl.collapse_small_triangles = collapse_small_triangles(...) method of builtins.PyCapsule instance

------------------

### **`collapse_small_triangles(v: array, f: array, eps: float) -> object`**

Given a triangle mesh (V,F) compute a new mesh (VV,FF) which contains the

original faces and vertices of (V,F) except any small triangles have been

removed via collapse.

We are *not* following the rules in "Mesh Optimization" [Hoppe et al]

Section 4.2. But for our purposes we don't care about this criteria.

**Parameters**



V  #V by 3 list of vertex positions

F  #F by 3 list of triangle indices into V

eps  epsilon for smallest allowed area treated as fraction of squared bounding box

diagonal

----------------
**Returns**



FF  #FF by 3 list of triangle indices into V

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.collapse_small_triangles = collapse_small_triangles(...) method of builtins.PyCapsule instance

------------------

### **`collapse_small_triangles(v: array, f: array, eps: float) -> object`**

Given a triangle mesh (V,F) compute a new mesh (VV,FF) which contains the

original faces and vertices of (V,F) except any small triangles have been

removed via collapse.

We are *not* following the rules in "Mesh Optimization" [Hoppe et al]

Section 4.2. But for our purposes we don't care about this criteria.

**Parameters**



V  #V by 3 list of vertex positions

F  #F by 3 list of triangle indices into V

eps  epsilon for smallest allowed area treated as fraction of squared bounding box

diagonal

----------------
**Returns**



FF  #FF by 3 list of triangle indices into V

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.connect_boundary_to_infinity = connect_boundary_to_infinity(...) method of builtins.PyCapsule instance

------------------

### **`connect_boundary_to_infinity(f: array) -> object`**

Connect all boundary edges to a fictitious point at infinity.

**Parameters**



F  #F by 3 list of face indices into some V

----------------
**Returns**



FO  #F+#O by 3 list of face indices into [V;inf inf inf], original F are

guaranteed to come first. If (V,F) was a manifold mesh, now it is

closed with a possibly non-manifold vertex at infinity (but it will be

edge-manifold).

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.connect_boundary_to_infinity = connect_boundary_to_infinity(...) method of builtins.PyCapsule instance

------------------

### **`connect_boundary_to_infinity(f: array) -> object`**

Connect all boundary edges to a fictitious point at infinity.

**Parameters**



F  #F by 3 list of face indices into some V

----------------
**Returns**



FO  #F+#O by 3 list of face indices into [V;inf inf inf], original F are

guaranteed to come first. If (V,F) was a manifold mesh, now it is

closed with a possibly non-manifold vertex at infinity (but it will be

edge-manifold).

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.connect_boundary_to_infinity_face = connect_boundary_to_infinity_face(...) method of builtins.PyCapsule instance

------------------

### **`connect_boundary_to_infinity_face(v: array, f: array) -> Tuple[object, object]`**

**Parameters**



F  #F by 3 list of face indices into some V

----------------
**Returns**



FO  #F+#O by 3 list of face indices into VO

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.connect_boundary_to_infinity_face = connect_boundary_to_infinity_face(...) method of builtins.PyCapsule instance

------------------

### **`connect_boundary_to_infinity_face(v: array, f: array) -> Tuple[object, object]`**

**Parameters**



F  #F by 3 list of face indices into some V

----------------
**Returns**



FO  #F+#O by 3 list of face indices into VO

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.connect_boundary_to_infinity_index = connect_boundary_to_infinity_index(...) method of builtins.PyCapsule instance

------------------

### **`connect_boundary_to_infinity_index(f: array, inf_index: int) -> object`**

**Parameters**



inf_index  index of point at infinity (usually V.rows() or F.maxCoeff())

----------------
**Returns**



----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.connect_boundary_to_infinity_index = connect_boundary_to_infinity_index(...) method of builtins.PyCapsule instance

------------------

### **`connect_boundary_to_infinity_index(f: array, inf_index: int) -> object`**

**Parameters**



inf_index  index of point at infinity (usually V.rows() or F.maxCoeff())

----------------
**Returns**



----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.cotmatrix = cotmatrix(...) method of builtins.PyCapsule instance

------------------

### **`cotmatrix(v: array, f: array) -> object`**

Constructs the cotangent stiffness matrix (discrete laplacian) for a given mesh

(v, f).

**Parameters**



v : #v by dim list of mesh vertex positions

f : #f by simplex_size list of mesh faces (must be triangles)

----------------
**Returns**



l : #v by #v cotangent matrix, each row i corresponding to v(i, :)

----------------

**See also**



adjacency_matrix

--------------

**Notes**



This Laplacian uses the convention that diagonal entries are

**minus** the sum of off-diagonal entries. The diagonal entries are

therefore in general negative and the matrix is **negative** semi-definite

(immediately, -L is **positive** semi-definite)

**Examples**



Mesh in (v, f)

l = cotmatrix(v, f)




igl.cotmatrix = cotmatrix(...) method of builtins.PyCapsule instance

------------------

### **`cotmatrix(v: array, f: array) -> object`**

Constructs the cotangent stiffness matrix (discrete laplacian) for a given mesh

(v, f).

**Parameters**



v : #v by dim list of mesh vertex positions

f : #f by simplex_size list of mesh faces (must be triangles)

----------------
**Returns**



l : #v by #v cotangent matrix, each row i corresponding to v(i, :)

----------------

**See also**



adjacency_matrix

--------------

**Notes**



This Laplacian uses the convention that diagonal entries are

**minus** the sum of off-diagonal entries. The diagonal entries are

therefore in general negative and the matrix is **negative** semi-definite

(immediately, -L is **positive** semi-definite)

**Examples**



Mesh in (v, f)

l = cotmatrix(v, f)




igl.cotmatrix_entries = cotmatrix_entries(...) method of builtins.PyCapsule instance

------------------

### **`cotmatrix_entries(v: array, f: array) -> object`**

COTMATRIX_ENTRIES compute the cotangents of each angle in mesh (V,F)

**Parameters**



V  #V by dim list of rest domain positions

F  #F by {34} list of {triangletetrahedra} indices into V

----------------
**Returns**



C  #F by 3 list of 1/2*cotangents corresponding angles

for triangles, columns correspond to edges [1,2],[2,0],[0,1]

OR

C  #F by 6 list of 1/6*cotangents of dihedral angles*edge lengths

for tets, columns along edges [1,2],[2,0],[0,1],[3,0],[3,1],[3,2]

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.cotmatrix_entries = cotmatrix_entries(...) method of builtins.PyCapsule instance

------------------

### **`cotmatrix_entries(v: array, f: array) -> object`**

COTMATRIX_ENTRIES compute the cotangents of each angle in mesh (V,F)

**Parameters**



V  #V by dim list of rest domain positions

F  #F by {34} list of {triangletetrahedra} indices into V

----------------
**Returns**



C  #F by 3 list of 1/2*cotangents corresponding angles

for triangles, columns correspond to edges [1,2],[2,0],[0,1]

OR

C  #F by 6 list of 1/6*cotangents of dihedral angles*edge lengths

for tets, columns along edges [1,2],[2,0],[0,1],[3,0],[3,1],[3,2]

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.crouzeix_raviart_cotmatrix = crouzeix_raviart_cotmatrix(...) method of builtins.PyCapsule instance

------------------

### **`crouzeix_raviart_cotmatrix(v: array, f: array) -> Tuple[object, object, object]`**

CROUZEIX_RAVIART_COTMATRIX Compute the Crouzeix-Raviart cotangent

stiffness matrix.

**Parameters**



V  #V by dim list of vertex positions

F  #F by 3/4 list of triangle/tetrahedron indices

----------------
**Returns**



L  #E by #E edge/face-based diagonal cotangent matrix

E  #E by 2/3 list of edges/faces

EMAP  #F*3/4 list of indices mapping allE to E

----------------

**See also**



**See also: crouzeix_raviart_massmatrix**

--------------

**Notes**



None

**Examples**



See for example "Discrete Quadratic Curvature Energies" [Wardetzky, Bergou,

Harmon, Zorin, Grinspun 2007]




igl.crouzeix_raviart_cotmatrix = crouzeix_raviart_cotmatrix(...) method of builtins.PyCapsule instance

------------------

### **`crouzeix_raviart_cotmatrix(v: array, f: array) -> Tuple[object, object, object]`**

CROUZEIX_RAVIART_COTMATRIX Compute the Crouzeix-Raviart cotangent

stiffness matrix.

**Parameters**



V  #V by dim list of vertex positions

F  #F by 3/4 list of triangle/tetrahedron indices

----------------
**Returns**



L  #E by #E edge/face-based diagonal cotangent matrix

E  #E by 2/3 list of edges/faces

EMAP  #F*3/4 list of indices mapping allE to E

----------------

**See also**



**See also: crouzeix_raviart_massmatrix**

--------------

**Notes**



None

**Examples**



See for example "Discrete Quadratic Curvature Energies" [Wardetzky, Bergou,

Harmon, Zorin, Grinspun 2007]




igl.crouzeix_raviart_cotmatrix_known_e = crouzeix_raviart_cotmatrix_known_e(...) method of builtins.PyCapsule instance

------------------

### **`crouzeix_raviart_cotmatrix_known_e(v: array, f: array, e: array, emap: array) -> object`**

wrapper if E and EMAP are already computed (better match!)

**Parameters**



----------------
**Returns**



----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.crouzeix_raviart_cotmatrix_known_e = crouzeix_raviart_cotmatrix_known_e(...) method of builtins.PyCapsule instance

------------------

### **`crouzeix_raviart_cotmatrix_known_e(v: array, f: array, e: array, emap: array) -> object`**

wrapper if E and EMAP are already computed (better match!)

**Parameters**



----------------
**Returns**



----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.crouzeix_raviart_massmatrix = crouzeix_raviart_massmatrix(...) method of builtins.PyCapsule instance

------------------

### **`crouzeix_raviart_massmatrix(v: array, f: array) -> Tuple[object, object, object]`**

CROUZEIX_RAVIART_MASSMATRIX Compute the Crouzeix-Raviart mass matrix where

------------------

### **`edge e.`**

**Parameters**



V  #V by dim list of vertex positions

F  #F by 3/4 list of triangle/tetrahedron indices

----------------
**Returns**



M  #E by #E edge/face-based diagonal mass matrix

E  #E by 2/3 list of edges/faces

EMAP  #F*3/4 list of indices mapping allE to E

----------------

**See also**



crouzeix_raviart_cotmatrix

--------------

**Notes**



See for example "Discrete Quadratic Curvature Energies" [Wardetzky, Bergou,

Harmon, Zorin, Grinspun 2007]

**Examples**






igl.crouzeix_raviart_massmatrix = crouzeix_raviart_massmatrix(...) method of builtins.PyCapsule instance

------------------

### **`crouzeix_raviart_massmatrix(v: array, f: array) -> Tuple[object, object, object]`**

CROUZEIX_RAVIART_MASSMATRIX Compute the Crouzeix-Raviart mass matrix where

------------------

### **`edge e.`**

**Parameters**



V  #V by dim list of vertex positions

F  #F by 3/4 list of triangle/tetrahedron indices

----------------
**Returns**



M  #E by #E edge/face-based diagonal mass matrix

E  #E by 2/3 list of edges/faces

EMAP  #F*3/4 list of indices mapping allE to E

----------------

**See also**



crouzeix_raviart_cotmatrix

--------------

**Notes**



See for example "Discrete Quadratic Curvature Energies" [Wardetzky, Bergou,

Harmon, Zorin, Grinspun 2007]

**Examples**









igl.crouzeix_raviart_massmatrix_known_e = crouzeix_raviart_massmatrix_known_e(...) method of builtins.PyCapsule instance

------------------

### **`crouzeix_raviart_massmatrix_known_e(v: array, f: array, e: array, emap: array) -> object`**

wrapper if E and EMAP are already computed (better match!)

**Parameters**



----------------
**Returns**



----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.crouzeix_raviart_massmatrix_known_e = crouzeix_raviart_massmatrix_known_e(...) method of builtins.PyCapsule instance

------------------

### **`crouzeix_raviart_massmatrix_known_e(v: array, f: array, e: array, emap: array) -> object`**

wrapper if E and EMAP are already computed (better match!)

**Parameters**



----------------
**Returns**



----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.cut_mesh = cut_mesh(...) method of builtins.PyCapsule instance

------------------

### **`cut_mesh(v: array, f: array, cuts: array) -> Tuple[object, object]`**

Compute the barycenter of every simplex

**Parameters**



v : #v x dim matrix of vertex coordinates

f : #f x simplex_size  matrix of indices of simplex corners into V

cuts : #F by 3 list of boolean flags, indicating the edges that need to

be cut (has 1 at the face edges that are to be cut, 0 otherwise)

----------------
**Returns**



A pair (vcut, fcut) where:

* vcut is a #v by 3 list of the vertex positions

of the cut mesh. This matrix will be similar to the original vertices except

some rows will be duplicated.

* fcut is a #f by 3 list of the faces of the cut mesh (must be triangles). This

matrix will be similar to the original face matrix except some indices

will be redirected to point to the newly duplicated vertices.

----------------

**See also**



--------------

**Notes**



**Examples**






igl.cut_mesh = cut_mesh(...) method of builtins.PyCapsule instance

------------------

### **`cut_mesh(v: array, f: array, cuts: array) -> Tuple[object, object]`**

Compute the barycenter of every simplex

**Parameters**



v : #v x dim matrix of vertex coordinates

f : #f x simplex_size  matrix of indices of simplex corners into V

cuts : #F by 3 list of boolean flags, indicating the edges that need to

be cut (has 1 at the face edges that are to be cut, 0 otherwise)

----------------
**Returns**



A pair (vcut, fcut) where:

* vcut is a #v by 3 list of the vertex positions

of the cut mesh. This matrix will be similar to the original vertices except

some rows will be duplicated.

* fcut is a #f by 3 list of the faces of the cut mesh (must be triangles). This

matrix will be similar to the original face matrix except some indices

will be redirected to point to the newly duplicated vertices.

----------------

**See also**



--------------

**Notes**



**Examples**






igl.cut_mesh_from_singularities = cut_mesh_from_singularities(...) method of builtins.PyCapsule instance

------------------

### **`cut_mesh_from_singularities(v: array, f: array, mismatch: array) -> object`**

Given a mesh (v,f) and the integer mismatch of a cross field per edge

(mismatch), finds and **returns the cut_graph connecting the singularities**

(seams)

**Parameters**



v : #v by 3 array of triangle vertices (each row is a vertex)

f : #f by 3 array of triangle indices into v

mismatch : #f by 3 array of per-corner integer mismatches

----------------
**Returns**



seams : #f by 3 array of per corner booleans that de**notes if an edge is a**

seam or not

----------------

**See also**



cut_mesh

--------------

**Notes**



**Examples**






igl.cut_mesh_from_singularities = cut_mesh_from_singularities(...) method of builtins.PyCapsule instance

------------------

### **`cut_mesh_from_singularities(v: array, f: array, mismatch: array) -> object`**

Given a mesh (v,f) and the integer mismatch of a cross field per edge

(mismatch), finds and **returns the cut_graph connecting the singularities**

(seams)

**Parameters**



v : #v by 3 array of triangle vertices (each row is a vertex)

f : #f by 3 array of triangle indices into v

mismatch : #f by 3 array of per-corner integer mismatches

----------------
**Returns**



seams : #f by 3 array of per corner booleans that de**notes if an edge is a**

seam or not

----------------

**See also**



cut_mesh

--------------

**Notes**



**Examples**






igl.cylinder = cylinder(...) method of builtins.PyCapsule instance

------------------

### **`cylinder(axis_devisions: int, height_devisions: int) -> Tuple[object, object]`**

Construct a triangle mesh of a cylinder (without caps)

**Parameters**



axis_devisions  number of vertices _around the cylinder_

height_devisions  number of vertices _up the cylinder_

----------------
**Returns**



V  #V by 3 list of mesh vertex positions

F  #F by 3 list of triangle indices into V

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.cylinder = cylinder(...) method of builtins.PyCapsule instance

------------------

### **`cylinder(axis_devisions: int, height_devisions: int) -> Tuple[object, object]`**

Construct a triangle mesh of a cylinder (without caps)

**Parameters**



axis_devisions  number of vertices _around the cylinder_

height_devisions  number of vertices _up the cylinder_

----------------
**Returns**



V  #V by 3 list of mesh vertex positions

F  #F by 3 list of triangle indices into V

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.decimate = decimate(...) method of builtins.PyCapsule instance

------------------

### **`decimate(v: array, f: array, max_m: int) -> Tuple[bool, object, object, object, object]`**

Assumes (V,F) is a manifold mesh (possibly with boundary) Collapses edges

until desired number of faces is achieved. This uses default edge cost and

merged vertex placement functions {edge length, edge midpoint}.

**Parameters**



V  #V by dim list of vertex positions

F  #F by 3 list of face indices into V.

max_m  desired number of output faces

----------------
**Returns**



U  #U by dim list of output vertex posistions (can be same ref as V)

G  #G by 3 list of output face indices into U (can be same ref as G)

J  #G list of indices into F of birth face

I  #U list of indices into V of birth vertices

**Returns true if m was reached (otherwise #G > m)**

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.decimate = decimate(...) method of builtins.PyCapsule instance

------------------

### **`decimate(v: array, f: array, max_m: int) -> Tuple[bool, object, object, object, object]`**

Assumes (V,F) is a manifold mesh (possibly with boundary) Collapses edges

until desired number of faces is achieved. This uses default edge cost and

merged vertex placement functions {edge length, edge midpoint}.

**Parameters**



V  #V by dim list of vertex positions

F  #F by 3 list of face indices into V.

max_m  desired number of output faces

----------------
**Returns**



U  #U by dim list of output vertex posistions (can be same ref as V)

G  #G by 3 list of output face indices into U (can be same ref as G)

J  #G list of indices into F of birth face

I  #U list of indices into V of birth vertices

**Returns true if m was reached (otherwise #G > m)**

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.dihedral_angles = dihedral_angles(...) method of builtins.PyCapsule instance

------------------

### **`dihedral_angles(v: array, t: array) -> Tuple[object, object]`**

Compute dihedral angles for all tets of a given tet mesh (v, t).

**Parameters**



v : #v by dim list of vertex positions

t : #v by 4 list of tet indices

----------------
**Returns**



theta : #t by 6 list of dihedral angles (in radians)

cos_theta : #t by 6 list of cosine of dihedral angles (in radians)

----------------

**See also**



--------------

**Notes**



None

**Examples**



TetMesh in (v, t)

theta, cos_theta = dihedral_angles(v, t)




igl.dihedral_angles = dihedral_angles(...) method of builtins.PyCapsule instance

------------------

### **`dihedral_angles(v: array, t: array) -> Tuple[object, object]`**

Compute dihedral angles for all tets of a given tet mesh (v, t).

**Parameters**



v : #v by dim list of vertex positions

t : #v by 4 list of tet indices

----------------
**Returns**



theta : #t by 6 list of dihedral angles (in radians)

cos_theta : #t by 6 list of cosine of dihedral angles (in radians)

----------------

**See also**



--------------

**Notes**



None

**Examples**



TetMesh in (v, t)

theta, cos_theta = dihedral_angles(v, t)




igl.dihedral_angles_intrinsic = dihedral_angles_intrinsic(...) method of builtins.PyCapsule instance

------------------

### **`dihedral_angles_intrinsic(l: array, a: array) -> Tuple[object, object]`**

See dihedral_angles for the documentation.




igl.dihedral_angles_intrinsic = dihedral_angles_intrinsic(...) method of builtins.PyCapsule instance

------------------

### **`dihedral_angles_intrinsic(l: array, a: array) -> Tuple[object, object]`**

See dihedral_angles for the documentation.




igl.directed_edge_parents = directed_edge_parents(...) method of builtins.PyCapsule instance

------------------

### **`directed_edge_parents(e: array) -> object`**

Recover "parents" (preceding edges) in a tree given just directed edges.

**Parameters**



e : #e by 2 list of directed edges

----------------
**Returns**



p : #e list of parent indices into e. (-1) means root

----------------

**See also**



--------------

**Notes**



None

**Examples**



p = edges(e)




igl.directed_edge_parents = directed_edge_parents(...) method of builtins.PyCapsule instance

------------------

### **`directed_edge_parents(e: array) -> object`**

Recover "parents" (preceding edges) in a tree given just directed edges.

**Parameters**



e : #e by 2 list of directed edges

----------------
**Returns**



p : #e list of parent indices into e. (-1) means root

----------------

**See also**



--------------

**Notes**



None

**Examples**



p = edges(e)




igl.doublearea = doublearea(...) method of builtins.PyCapsule instance

------------------

### **`doublearea(v: array, f: array) -> object`**

Computes twice the area for each input triangle[quad]

**Parameters**



v : #v by dim array of mesh vertex positions

f : #f by simplex_size array of mesh faces (must be triangles or quads)

----------------
**Returns**



d_area : #f list of triangle[quad] double areas (SIGNED only for 2D input)

----------------

**See also**



None

--------------

**Notes**



Known bug: For dim==3 complexity is O(#V + #F)!! Not just O(#F). This is a big deal if you have 1million unreferenced vertices and 1 face

**Examples**



Mesh in (v, f)

dbl_area = doublearea(v, f)




igl.doublearea = doublearea(...) method of builtins.PyCapsule instance

------------------

### **`doublearea(v: array, f: array) -> object`**

Computes twice the area for each input triangle[quad]

**Parameters**



v : #v by dim array of mesh vertex positions

f : #f by simplex_size array of mesh faces (must be triangles or quads)

----------------
**Returns**



d_area : #f list of triangle[quad] double areas (SIGNED only for 2D input)

----------------

**See also**



None

--------------

**Notes**



Known bug: For dim==3 complexity is O(#V + #F)!! Not just O(#F). This is a big deal if you have 1million unreferenced vertices and 1 face

**Examples**



Mesh in (v, f)

dbl_area = doublearea(v, f)




igl.ears = ears(...) method of builtins.PyCapsule instance

------------------

### **`ears(f: array) -> Tuple[object, object]`**

FIND_EARS  Find all ears (faces with two boundary edges) in a given mesh

**Parameters**



F  #F by 3 list of triangle mesh indices

----------------
**Returns**



ears  #ears list of indices into F of ears

ear_opp  #ears list of indices indicating which edge is non-boundary

(connecting to flops)

----------------

**See also**



--------------

**Notes**



None

**Examples**



ears,ear_opp = find_ears(F)




igl.ears = ears(...) method of builtins.PyCapsule instance

------------------

### **`ears(f: array) -> Tuple[object, object]`**

FIND_EARS  Find all ears (faces with two boundary edges) in a given mesh

**Parameters**



F  #F by 3 list of triangle mesh indices

----------------
**Returns**



ears  #ears list of indices into F of ears

ear_opp  #ears list of indices indicating which edge is non-boundary

(connecting to flops)

----------------

**See also**



--------------

**Notes**



None

**Examples**



ears,ear_opp = find_ears(F)




igl.edge_topology = edge_topology(...) method of builtins.PyCapsule instance

------------------

### **`edge_topology(v: array, f: array) -> Tuple[object, object, object]`**

Initialize Edges and their topological relations (assumes an edge-manifold mesh)

**Parameters**



v : #v by dim, list of mesh vertex positions (unused)

f : #f by 3, list of triangle indices into V

----------------
**Returns**



ev : #e by 2, list of edges described as pair of vertices.

fe : #f by 3, list storing triangle-edge relation.

ef : #e by w, list storing edge-triangle relation, uses -1 to indicate boundaries.

----------------

**See also**



--------------

**Notes**



None

**Examples**



Mesh in (v, f)

ev, fe, ef = edge_topology(v, f)




igl.edge_topology = edge_topology(...) method of builtins.PyCapsule instance

------------------

### **`edge_topology(v: array, f: array) -> Tuple[object, object, object]`**

Initialize Edges and their topological relations (assumes an edge-manifold mesh)

**Parameters**



v : #v by dim, list of mesh vertex positions (unused)

f : #f by 3, list of triangle indices into V

----------------
**Returns**



ev : #e by 2, list of edges described as pair of vertices.

fe : #f by 3, list storing triangle-edge relation.

ef : #e by w, list storing edge-triangle relation, uses -1 to indicate boundaries.

----------------

**See also**



--------------

**Notes**



None

**Examples**



Mesh in (v, f)

ev, fe, ef = edge_topology(v, f)




igl.edges = edges(...) method of builtins.PyCapsule instance

------------------

### **`edges(f: array) -> object`**

Constructs a list of unique edges represented in a given mesh (v, f)

**Parameters**



f : #F by dim list of mesh faces (must be triangles or tets)

----------------
**Returns**



by 2 list of edges in no particular order

----------------

**See also**



adjacency_matrix

--------------

**Notes**



**Examples**



V, F, _ = igl.readOFF("test.off)

E = igl.edges(F)




igl.edges = edges(...) method of builtins.PyCapsule instance

------------------

### **`edges(f: array) -> object`**

Constructs a list of unique edges represented in a given mesh (v, f)

**Parameters**



f : #F by dim list of mesh faces (must be triangles or tets)

----------------
**Returns**



by 2 list of edges in no particular order

----------------

**See also**



adjacency_matrix

--------------

**Notes**



**Examples**



V, F, _ = igl.readOFF("test.off)

E = igl.edges(F)




igl.euler_characteristic = euler_characteristic(...) method of builtins.PyCapsule instance

------------------

### **`euler_characteristic(f: array) -> int`**

Computes the Euler characteristic of a given mesh (V,F)

**Parameters**



F #F by dim list of mesh faces (must be triangles)

----------------
**Returns**



**Returns An int containing the Euler characteristic**

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.euler_characteristic = euler_characteristic(...) method of builtins.PyCapsule instance

------------------

### **`euler_characteristic(f: array) -> int`**

Computes the Euler characteristic of a given mesh (V,F)

**Parameters**



F #F by dim list of mesh faces (must be triangles)

----------------
**Returns**



**Returns An int containing the Euler characteristic**

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.euler_characteristic_complete = euler_characteristic_complete(...) method of builtins.PyCapsule instance

------------------

### **`euler_characteristic_complete(v: array, f: array) -> int`**

**Parameters**



V       #V by dim list of mesh vertex positions

----------------
**Returns**



----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.euler_characteristic_complete = euler_characteristic_complete(...) method of builtins.PyCapsule instance

------------------

### **`euler_characteristic_complete(v: array, f: array) -> int`**

**Parameters**



V       #V by dim list of mesh vertex positions

----------------
**Returns**



----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.exact_geodesic = exact_geodesic(...) method of builtins.PyCapsule instance

------------------

### **`exact_geodesic(v: array, f: array, vs: array, vt: array, fs: numpy.array  None = None, ft: numpy.array  None = None) -> object`**

Exact geodesic algorithm for the calculation of geodesics on a triangular mesh.

**Parameters**



v : #v by 3 array of 3D vertex positions

f : #f by 3 array of mesh faces

vs : #vs by 1 array specifying indices of source vertices

fs : #fs by 1 array specifying indices of source faces

vt : #vt by 1 array specifying indices of target vertices

ft : #ft by 1 array specifying indices of target faces

----------------
**Returns**



d : #vt+#ft by 1 array of geodesic distances of each target w.r.t. the nearest one in the source set

----------------

**See also**



--------------

**Notes**



Specifying a face as target/source means its center.

Implementation from https:code.google.com/archive/p/geodesic/ with the algorithm first described by Mitchell, Mount and Papadimitriou in 1987.

**Examples**






igl.exact_geodesic = exact_geodesic(...) method of builtins.PyCapsule instance

------------------

### **`exact_geodesic(v: array, f: array, vs: array, vt: array, fs: numpy.array  None = None, ft: numpy.array  None = None) -> object`**

Exact geodesic algorithm for the calculation of geodesics on a triangular mesh.

**Parameters**



v : #v by 3 array of 3D vertex positions

f : #f by 3 array of mesh faces

vs : #vs by 1 array specifying indices of source vertices

fs : #fs by 1 array specifying indices of source faces

vt : #vt by 1 array specifying indices of target vertices

ft : #ft by 1 array specifying indices of target faces

----------------
**Returns**



d : #vt+#ft by 1 array of geodesic distances of each target w.r.t. the nearest one in the source set

----------------

**See also**



--------------

**Notes**



Specifying a face as target/source means its center.

Implementation from https:code.google.com/archive/p/geodesic/ with the algorithm first described by Mitchell, Mount and Papadimitriou in 1987.

**Examples**






igl.face_components = face_components(...) method of builtins.PyCapsule instance

------------------

### **`face_components(f: array) -> object`**

Compute connected components of facets based on edge-edge adjacency,

**Parameters**



f : #f x 3 array of triangle indices

----------------
**Returns**



An array, c, with shape (#f,), of component ids

----------------

**See also**



vertex_components

vertex_components_from_adjacency_matrix

--------------

**Notes**



**Examples**






igl.face_components = face_components(...) method of builtins.PyCapsule instance

------------------

### **`face_components(f: array) -> object`**

Compute connected components of facets based on edge-edge adjacency,

**Parameters**



f : #f x 3 array of triangle indices

----------------
**Returns**



An array, c, with shape (#f,), of component ids

----------------

**See also**



vertex_components

vertex_components_from_adjacency_matrix

--------------

**Notes**



**Examples**






igl.fit_plane = fit_plane(...) method of builtins.PyCapsule instance

------------------

### **`fit_plane(v: array) -> Tuple[object, object]`**

This function fits a plane to a point cloud.

**Parameters**



V #Vx3 matrix. The 3D point cloud, one row for each vertex.

----------------
**Returns**



N 1x3 Vector. The normal of the fitted plane.

C 1x3 Vector. A point that lies in the fitted plane.

----------------

**See also**



--------------

**Notes**



From http:missingbytes.blogspot.com/2012/06/fitting-plane-to-point-cloud.html

**Examples**






igl.fit_plane = fit_plane(...) method of builtins.PyCapsule instance

------------------

### **`fit_plane(v: array) -> Tuple[object, object]`**

This function fits a plane to a point cloud.

**Parameters**



V #Vx3 matrix. The 3D point cloud, one row for each vertex.

----------------
**Returns**



N 1x3 Vector. The normal of the fitted plane.

C 1x3 Vector. A point that lies in the fitted plane.

----------------

**See also**



--------------

**Notes**



From http:missingbytes.blogspot.com/2012/06/fitting-plane-to-point-cloud.html

**Examples**






igl.flip_avoiding_line_search = flip_avoiding_line_search(...) method of builtins.PyCapsule instance

------------------

### **`flip_avoiding_line_search(f: array, cur_v: array, dst_v: array, energy: std::__1::function<double (Eigen::Matrix<double, -1, -1, 0, -1, -1>)>, cur_energy: float) -> Tuple[float, object]`**

A bisection line search for a mesh based energy that avoids triangle flips as suggested in

"Bijective Parameterization with Free Boundaries" (Smith J. and Schaefer S., 2015).

The user specifies an initial vertices position (that has no flips) and target one (that my have flipped triangles).

This method first computes the largest step in direction of the destination vertices that does not incur flips, and then minimizes a given energy using this maximal step and a bisection linesearch (see igl::line_search).

Supports both triangle and tet meshes.

**Parameters**



F         #F by 3/4 list of mesh faces or tets

cur_v     #V by dim list of variables

dst_v     #V by dim list of target vertices. This mesh may have flipped triangles

energy    A function to compute the mesh-based energy (return an energy that is bigger than 0)

------------------

### **`cur_energy(OPTIONAL)         The energy at the given point. Helps save redundant c  omputations. This is optional. If not specified, the function will compute it.`**

----------------
**Returns**



cur_v     #V by dim list of variables at the new location

**Returns the energy at the new point**

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.flip_avoiding_line_search = flip_avoiding_line_search(...) method of builtins.PyCapsule instance

------------------

### **`flip_avoiding_line_search(f: array, cur_v: array, dst_v: array, energy: std::__1::function<double (Eigen::Matrix<double, -1, -1, 0, -1, -1>)>, cur_energy: float) -> Tuple[float, object]`**

A bisection line search for a mesh based energy that avoids triangle flips as suggested in

"Bijective Parameterization with Free Boundaries" (Smith J. and Schaefer S., 2015).

The user specifies an initial vertices position (that has no flips) and target one (that my have flipped triangles).

This method first computes the largest step in direction of the destination vertices that does not incur flips, and then minimizes a given energy using this maximal step and a bisection linesearch (see igl::line_search).

Supports both triangle and tet meshes.

**Parameters**



F         #F by 3/4 list of mesh faces or tets

cur_v     #V by dim list of variables

dst_v     #V by dim list of target vertices. This mesh may have flipped triangles

energy    A function to compute the mesh-based energy (return an energy that is bigger than 0)

------------------

### **`cur_energy(OPTIONAL)         The energy at the given point. Helps save redundant c  omputations. This is optional. If not specified, the function will compute it.`**

----------------
**Returns**



cur_v     #V by dim list of variables at the new location

**Returns the energy at the new point**

----------------

**See also**



--------------

**Notes**



None

**Examples**









igl.gaussian_curvature = gaussian_curvature(...) method of builtins.PyCapsule instance

------------------

### **`gaussian_curvature(v: array, f: array) -> object`**

Compute discrete local integral gaussian curvature (angle deficit, without

averaging by local area).

**Parameters**



v : #v by 3 array of mesh vertex 3D positions

f : #f by 3 array of face (triangle) indices

----------------
**Returns**



k : #v by 1 array of discrete gaussian curvature values

----------------

**See also**



principal_curvature

--------------

**Notes**



None

**Examples**



Mesh in (v, f)

k = gaussian_curvature(v, f)




igl.gaussian_curvature = gaussian_curvature(...) method of builtins.PyCapsule instance

------------------

### **`gaussian_curvature(v: array, f: array) -> object`**

Compute discrete local integral gaussian curvature (angle deficit, without

averaging by local area).

**Parameters**



v : #v by 3 array of mesh vertex 3D positions

f : #f by 3 array of face (triangle) indices

----------------
**Returns**



k : #v by 1 array of discrete gaussian curvature values

----------------

**See also**



principal_curvature

--------------

**Notes**



None

**Examples**



Mesh in (v, f)

k = gaussian_curvature(v, f)




igl.grad = grad(...) method of builtins.PyCapsule instance

------------------

### **`grad(v: array, f: array, uniform: bool = False) -> object`**

Compute the numerical gradient operator.

**Parameters**



v : #v by 3 list of mesh vertex positions

f : #f by 3 list of mesh face indices [or a #faces by 4 list of tetrahedral indices]

uniform : boolean (default false). Use a uniform mesh instead of the vertices v

----------------
**Returns**



g : #faces * dim by #v gradient operator

----------------

**See also**



cotmatrix, massmatrix

--------------

**Notes**



Gradient of a scalar function defined on piecewise linear elements (mesh)

is constant on each triangle [tetrahedron] i,j,k:

------------------

### **`grad(Xijk) = (Xj-Xi) * (Vi - Vk)^R90 / 2A + (Xk-Xi) * (Vj - Vi)^R90 / 2A`**

where Xi is the scalar value at vertex i, Vi is the 3D position of vertex

i, and A is the area of triangle (i,j,k). ^R90 represent a rotation of

90 degrees.

**Examples**



Mesh in (v, f)

g = grad(v, f)




igl.grad = grad(...) method of builtins.PyCapsule instance

------------------

### **`grad(v: array, f: array, uniform: bool = False) -> object`**

Compute the numerical gradient operator.

**Parameters**



v : #v by 3 list of mesh vertex positions

f : #f by 3 list of mesh face indices [or a #faces by 4 list of tetrahedral indices]

uniform : boolean (default false). Use a uniform mesh instead of the vertices v

----------------
**Returns**



g : #faces * dim by #v gradient operator

----------------

**See also**



cotmatrix, massmatrix

--------------

**Notes**



Gradient of a scalar function defined on piecewise linear elements (mesh)

is constant on each triangle [tetrahedron] i,j,k:

------------------

### **`grad(Xijk) = (Xj-Xi) * (Vi - Vk)^R90 / 2A + (Xk-Xi) * (Vj - Vi)^R90 / 2A`**

where Xi is the scalar value at vertex i, Vi is the 3D position of vertex

i, and A is the area of triangle (i,j,k). ^R90 represent a rotation of

90 degrees.

**Examples**



Mesh in (v, f)

g = grad(v, f)




igl.grad = grad(...) method of builtins.PyCapsule instance

------------------

### **`grad(v: array, f: array, uniform: bool = False) -> object`**

Compute the numerical gradient operator.

**Parameters**



v : #v by 3 list of mesh vertex positions

f : #f by 3 list of mesh face indices [or a #faces by 4 list of tetrahedral indices]

uniform : boolean (default false). Use a uniform mesh instead of the vertices v

----------------
**Returns**



g : #faces * dim by #v gradient operator

----------------

**See also**



cotmatrix, massmatrix

--------------

**Notes**



Gradient of a scalar function defined on piecewise linear elements (mesh)

is constant on each triangle [tetrahedron] i,j,k:

------------------

### **`grad(Xijk) = (Xj-Xi) * (Vi - Vk)^R90 / 2A + (Xk-Xi) * (Vj - Vi)^R90 / 2A`**

where Xi is the scalar value at vertex i, Vi is the 3D position of vertex

i, and A is the area of triangle (i,j,k). ^R90 represent a rotation of

90 degrees.

**Examples**



Mesh in (v, f)

g = grad(v, f)




igl.harmonic_integrated_with_laplacian = harmonic_integrated_with_laplacian(...) method of builtins.PyCapsule instance

------------------

### **`harmonic_integrated_with_laplacian(l: scipy.sparse.csr_matrix  scipy.sparse.csc_matrix, m: scipy.sparse.csr_matrix  scipy.sparse.csc_matrix, k: int) -> object`**

Build the discrete k-harmonic operator (computing integrated quantities).

That is, if the k-harmonic PDE is Q x = 0, then this minimizes x' Q x

**Parameters**



L  #V by #V discrete (integrated) Laplacian

M  #V by #V mass matrix

k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)

----------------
**Returns**



Q  #V by #V discrete (integrated) k-Laplacian

----------------

**See also**



--------------

**Notes**



**Examples**






igl.harmonic_integrated_with_laplacian = harmonic_integrated_with_laplacian(...) method of builtins.PyCapsule instance

------------------

### **`harmonic_integrated_with_laplacian(l: scipy.sparse.csr_matrix  scipy.sparse.csc_matrix, m: scipy.sparse.csr_matrix  scipy.sparse.csc_matrix, k: int) -> object`**

Build the discrete k-harmonic operator (computing integrated quantities).

That is, if the k-harmonic PDE is Q x = 0, then this minimizes x' Q x

**Parameters**



L  #V by #V discrete (integrated) Laplacian

M  #V by #V mass matrix

k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)

----------------
**Returns**



Q  #V by #V discrete (integrated) k-Laplacian

----------------

**See also**



--------------

**Notes**



**Examples**






igl.harmonic_uniform_laplacian = harmonic_uniform_laplacian(...) method of builtins.PyCapsule instance

------------------

### **`harmonic_uniform_laplacian(f: array, b: array, bc: array, k: int) -> object`**

Compute harmonic map using uniform laplacian operator

**Parameters**



F  #F by simplex-size list of element indices

b  #b boundary indices into V

bc #b by #W list of boundary values

k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)

----------------
**Returns**



W  #V by #W list of weights

----------------

**See also**



--------------

**Notes**



**Examples**






igl.harmonic_uniform_laplacian = harmonic_uniform_laplacian(...) method of builtins.PyCapsule instance

------------------

### **`harmonic_uniform_laplacian(f: array, b: array, bc: array, k: int) -> object`**

Compute harmonic map using uniform laplacian operator

**Parameters**



F  #F by simplex-size list of element indices

b  #b boundary indices into V

bc #b by #W list of boundary values

k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)

----------------
**Returns**



W  #V by #W list of weights

----------------

**See also**



--------------

**Notes**



**Examples**






igl.harmonic_weights = harmonic_weights(...) method of builtins.PyCapsule instance

------------------

### **`harmonic_weights(v: array, f: array, b: array, bc: array, k: int) -> object`**

Compute k-harmonic weight functions "coordinates".

**Parameters**



V  #V by dim vertex positions

F  #F by simplex-size list of element indices

b  #b boundary indices into V

bc #b by #W list of boundary values

k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)

----------------
**Returns**



W  #V by #W list of weights

----------------

**See also**



--------------

**Notes**



**Examples**






igl.harmonic_weights = harmonic_weights(...) method of builtins.PyCapsule instance

------------------

### **`harmonic_weights(v: array, f: array, b: array, bc: array, k: int) -> object`**

Compute k-harmonic weight functions "coordinates".

**Parameters**



V  #V by dim vertex positions

F  #F by simplex-size list of element indices

b  #b boundary indices into V

bc #b by #W list of boundary values

k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)

----------------
**Returns**



W  #V by #W list of weights

----------------

**See also**



--------------

**Notes**



**Examples**






igl.hausdorff = hausdorff(...) method of builtins.PyCapsule instance

------------------

### **`hausdorff(va: array, fa: array, vb: array, fb: array) -> float`**

HAUSDORFF compute the Hausdorff distance between mesh (VA,FA) and mesh

(VB,FB). This is the

------------------

### **`a∈A b∈B          b∈B a∈A`**

**Parameters**



VA  #VA by 3 list of vertex positions

FA  #FA by 3 list of face indices into VA

VB  #VB by 3 list of vertex positions

FB  #FB by 3 list of face indices into VB

----------------
**Returns**



d  hausdorff distance

pair  2 by 3 list of "determiner points" so that pair(1,:) is from A

and pair(2,:) is from B

----------------

**See also**



--------------

**Notes**



Known issue: This is only computing max(min(va,B),min(vb,A)). This is

better than max(min(va,Vb),min(vb,Va)). This (at least) is missing

"edge-edge" cases like the distance between the two different

triangulations of a non-planar quad in 3D. Even simpler, consider the

Hausdorff distance between the non-convex, block letter V polygon (with 7

vertices) in 2D and its convex hull. The Hausdorff distance is defined by

the midpoint in the middle of the segment across the concavity and some

non-vertex point _on the edge_ of the V.

**Examples**






igl.hausdorff = hausdorff(...) method of builtins.PyCapsule instance

------------------

### **`hausdorff(va: array, fa: array, vb: array, fb: array) -> float`**

HAUSDORFF compute the Hausdorff distance between mesh (VA,FA) and mesh

(VB,FB). This is the

------------------

### **`a∈A b∈B          b∈B a∈A`**

**Parameters**



VA  #VA by 3 list of vertex positions

FA  #FA by 3 list of face indices into VA

VB  #VB by 3 list of vertex positions

FB  #FB by 3 list of face indices into VB

----------------
**Returns**



d  hausdorff distance

pair  2 by 3 list of "determiner points" so that pair(1,:) is from A

and pair(2,:) is from B

----------------

**See also**



--------------

**Notes**



Known issue: This is only computing max(min(va,B),min(vb,A)). This is

better than max(min(va,Vb),min(vb,Va)). This (at least) is missing

"edge-edge" cases like the distance between the two different

triangulations of a non-planar quad in 3D. Even simpler, consider the

Hausdorff distance between the non-convex, block letter V polygon (with 7

vertices) in 2D and its convex hull. The Hausdorff distance is defined by

the midpoint in the middle of the segment across the concavity and some

non-vertex point _on the edge_ of the V.

**Examples**









igl.internal_angles = internal_angles(...) method of builtins.PyCapsule instance

------------------

### **`internal_angles(v: array, f: array) -> object`**

Computes internal angles for a triangle mesh.

**Parameters**



v : #v by dim array of mesh vertex nD positions

f : #f by poly-size array of face (triangle) indices

----------------
**Returns**



k : #f by poly-size array of internal angles. For triangles, columns correspond to edges [1,2],[2,0],[0,1].

----------------

**See also**



None

--------------

**Notes**



If poly-size ≠ 3 then dim must equal 3.

**Examples**






igl.internal_angles = internal_angles(...) method of builtins.PyCapsule instance

------------------

### **`internal_angles(v: array, f: array) -> object`**

Computes internal angles for a triangle mesh.

**Parameters**



v : #v by dim array of mesh vertex nD positions

f : #f by poly-size array of face (triangle) indices

----------------
**Returns**



k : #f by poly-size array of internal angles. For triangles, columns correspond to edges [1,2],[2,0],[0,1].

----------------

**See also**



None

--------------

**Notes**



If poly-size ≠ 3 then dim must equal 3.

**Examples**






igl.is_edge_manifold = is_edge_manifold(...) method of builtins.PyCapsule instance

------------------

### **`is_edge_manifold(f: array) -> bool`**

See is_edge_manifold for the documentation.




igl.is_edge_manifold = is_edge_manifold(...) method of builtins.PyCapsule instance

------------------

### **`is_edge_manifold(f: array) -> bool`**

See is_edge_manifold for the documentation.




igl.is_irregular_vertex = is_irregular_vertex(...) method of builtins.PyCapsule instance

------------------

### **`is_irregular_vertex(v: array, f: array) -> std::__1::vector<bool, std::__1::allocator<bool> >`**

Determine if a vertex is irregular, i.e. it has more than 6 (triangles) or 4 (quads) incident edges. Vertices on the boundary are ignored.

**Parameters**



v : #v by dim array of vertex positions

f : #f by 3[4] array of triangle[quads] indices

----------------
**Returns**



s : #v list of bools revealing whether vertices are singular

----------------

**See also**



None

--------------

**Notes**



None

**Examples**






igl.is_irregular_vertex = is_irregular_vertex(...) method of builtins.PyCapsule instance

------------------

### **`is_irregular_vertex(v: array, f: array) -> std::__1::vector<bool, std::__1::allocator<bool> >`**

Determine if a vertex is irregular, i.e. it has more than 6 (triangles) or 4 (quads) incident edges. Vertices on the boundary are ignored.

**Parameters**



v : #v by dim array of vertex positions

f : #f by 3[4] array of triangle[quads] indices

----------------
**Returns**



s : #v list of bools revealing whether vertices are singular

----------------

**See also**



None

--------------

**Notes**



None

**Examples**






igl.isolines = isolines(...) method of builtins.PyCapsule instance

------------------

### **`isolines(v: array, f: array, z: array, n: int) -> Tuple[object, object]`**

Constructs isolines for a function z given on a mesh (V,F)

**Parameters**



V  #V by dim list of mesh vertex positions

F  #F by 3 list of mesh faces (must be triangles)

z  #V by 1 list of function values evaluated at vertices

n  the number of desired isolines

----------------
**Returns**



isoV  #isoV by dim list of isoline vertex positions

isoE  #isoE by 2 list of isoline edge positions

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.isolines = isolines(...) method of builtins.PyCapsule instance

------------------

### **`isolines(v: array, f: array, z: array, n: int) -> Tuple[object, object]`**

Constructs isolines for a function z given on a mesh (V,F)

**Parameters**



V  #V by dim list of mesh vertex positions

F  #F by 3 list of mesh faces (must be triangles)

z  #V by 1 list of function values evaluated at vertices

n  the number of desired isolines

----------------
**Returns**



isoV  #isoV by dim list of isoline vertex positions

isoE  #isoE by 2 list of isoline edge positions

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.lscm = lscm(...) method of builtins.PyCapsule instance

------------------

### **`lscm(v: array, f: array, b: array, bc: array) -> Tuple[bool, object]`**

Compute a Least-squares conformal map parametrization.

**Parameters**



v : #v by 3 array of mesh vertex positions

f : #f by 3 array of mesh faces (must be triangles)

b : #b boundary indices into v

bc : #b by 3 list of boundary values

----------------
**Returns**



uv #v by 2 list of 2D mesh vertex positions in UV space

----------------

**See also**



None

--------------

**Notes**



Derived in "Intrinsic Parameterizations of Surface Meshes" [Desbrun et al.

2002] and "Least Squares Conformal Maps for Automatic Texture Atlas

Generation" [Lévy et al. 2002]), though this implementation follows the

derivation in: "Spectral Conformal Parameterization" [Mullen et al. 2008]

(note, this does **not** implement the Eigen-decomposition based method in

[Mullen et al. 2008], which is not equivalent. Input should be a manifold

mesh (also no unreferenced vertices) and "boundary" (fixed vertices) `b`

should contain at least two vertices per connected component.

**Returns true only on solver success.**

**Examples**






igl.lscm = lscm(...) method of builtins.PyCapsule instance

------------------

### **`lscm(v: array, f: array, b: array, bc: array) -> Tuple[bool, object]`**

Compute a Least-squares conformal map parametrization.

**Parameters**



v : #v by 3 array of mesh vertex positions

f : #f by 3 array of mesh faces (must be triangles)

b : #b boundary indices into v

bc : #b by 3 list of boundary values

----------------
**Returns**



uv #v by 2 list of 2D mesh vertex positions in UV space

----------------

**See also**



None

--------------

**Notes**



Derived in "Intrinsic Parameterizations of Surface Meshes" [Desbrun et al.

2002] and "Least Squares Conformal Maps for Automatic Texture Atlas

Generation" [Lévy et al. 2002]), though this implementation follows the

derivation in: "Spectral Conformal Parameterization" [Mullen et al. 2008]

(note, this does **not** implement the Eigen-decomposition based method in

[Mullen et al. 2008], which is not equivalent. Input should be a manifold

mesh (also no unreferenced vertices) and "boundary" (fixed vertices) `b`

should contain at least two vertices per connected component.

**Returns true only on solver success.**

**Examples**






igl.massmatrix = massmatrix(...) method of builtins.PyCapsule instance

------------------

### **`massmatrix(v: array, f: array, type: int = 1) -> object`**

Constructs the mass (area) matrix for a given mesh (V,F).

**Parameters**



v : #v by dim list of mesh vertex positions

f : #f by simplex_size list of mesh faces (must be triangles)

type : one of the following types:

-igl.MASSMATRIX_TYPE_BARYCENTRIC  barycentric

-igl.MASSMATRIX_TYPE_VORONOI voronoi-hybrid (default)

-igl.MASSMATRIX_TYPE_FULL full (not implemented)

----------------
**Returns**



m : #v by #v mass matrix

----------------

**See also**



adjacency_matrix, cotmatrix, grad

--------------

**Notes**



**Examples**






igl.massmatrix = massmatrix(...) method of builtins.PyCapsule instance

------------------

### **`massmatrix(v: array, f: array, type: int = 1) -> object`**

Constructs the mass (area) matrix for a given mesh (V,F).

**Parameters**



v : #v by dim list of mesh vertex positions

f : #f by simplex_size list of mesh faces (must be triangles)

type : one of the following types:

-igl.MASSMATRIX_TYPE_BARYCENTRIC  barycentric

-igl.MASSMATRIX_TYPE_VORONOI voronoi-hybrid (default)

-igl.MASSMATRIX_TYPE_FULL full (not implemented)

----------------
**Returns**



m : #v by #v mass matrix

----------------

**See also**



adjacency_matrix, cotmatrix, grad

--------------

**Notes**



**Examples**






igl.min_quad_dense_precompute = min_quad_dense_precompute(...) method of builtins.PyCapsule instance

------------------

### **`min_quad_dense_precompute(a: array, aeq: array, use_lu_decomposition: bool) -> object`**

MIN_QUAD_WITH_FIXED Minimize quadratic energy Z'*A*Z + Z'*B + C

subject to linear constraints Aeq*Z = Beq

**Parameters**



A  n by n matrix of quadratic coefficients

B  n by 1 column of linear coefficients

Aeq  m by n list of linear equality constraint coefficients

Beq  m by 1 list of linear equality constraint constant values

use_lu_decomposition  use lu rather than SVD

----------------
**Returns**



S  n by (n + m) "solve" matrix, such that S*[B', Beq'] is a solution

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.min_quad_dense_precompute = min_quad_dense_precompute(...) method of builtins.PyCapsule instance

------------------

### **`min_quad_dense_precompute(a: array, aeq: array, use_lu_decomposition: bool) -> object`**

MIN_QUAD_WITH_FIXED Minimize quadratic energy Z'*A*Z + Z'*B + C

subject to linear constraints Aeq*Z = Beq

**Parameters**



A  n by n matrix of quadratic coefficients

B  n by 1 column of linear coefficients

Aeq  m by n list of linear equality constraint coefficients

Beq  m by 1 list of linear equality constraint constant values

use_lu_decomposition  use lu rather than SVD

----------------
**Returns**



S  n by (n + m) "solve" matrix, such that S*[B', Beq'] is a solution

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.orientable_patches = orientable_patches(...) method of builtins.PyCapsule instance

------------------

### **`orientable_patches(f: array) -> Tuple[object, object]`**

Compute connected components of facets connected by manifold edges.

**Parameters**



f : n by dim array of face ids

----------------
**Returns**



A tuple (c, A) where c is an array of component ids (starting with 0)

and A is a #f x #f adjacency matri

----------------

**See also**



components

--------------

**Notes**



Known bugs: This will detect a moebius strip as a single patch (manifold, non-orientable) and also non-manfiold, yet orientable patches.

**Examples**






igl.orientable_patches = orientable_patches(...) method of builtins.PyCapsule instance

------------------

### **`orientable_patches(f: array) -> Tuple[object, object]`**

Compute connected components of facets connected by manifold edges.

**Parameters**



f : n by dim array of face ids

----------------
**Returns**



A tuple (c, A) where c is an array of component ids (starting with 0)

and A is a #f x #f adjacency matri

----------------

**See also**



components

--------------

**Notes**



Known bugs: This will detect a moebius strip as a single patch (manifold, non-orientable) and also non-manfiold, yet orientable patches.

**Examples**






igl.oriented_facets = oriented_facets(...) method of builtins.PyCapsule instance

------------------

### **`oriented_facets(f: array) -> object`**

Determines all 'directed [facets](https:en.wikipedia.org/wiki/Simplex#Elements)' of a given set

of simplicial elements. For a manifold triangle mesh, this computes all half-edges.

For a manifold tetrahedral mesh, this computes all half-faces.

**Parameters**



f : #F by simplex_size list of simplices

----------------
**Returns**



: by simplex_size-1 list of half-edges/facets

----------------

**See also**



edges

--------------

**Notes**



This is not the same as igl::edges because this includes every

directed edge including repeats (meaning interior edges on a surface will

show up once for each direction and non-manifold edges may appear more than

once for each direction).

**Examples**






igl.oriented_facets = oriented_facets(...) method of builtins.PyCapsule instance

------------------

### **`oriented_facets(f: array) -> object`**

Determines all 'directed [facets](https:en.wikipedia.org/wiki/Simplex#Elements)' of a given set

of simplicial elements. For a manifold triangle mesh, this computes all half-edges.

For a manifold tetrahedral mesh, this computes all half-faces.

**Parameters**



f : #F by simplex_size list of simplices

----------------
**Returns**



: by simplex_size-1 list of half-edges/facets

----------------

**See also**



edges

--------------

**Notes**



This is not the same as igl::edges because this includes every

directed edge including repeats (meaning interior edges on a surface will

show up once for each direction and non-manifold edges may appear more than

once for each direction).

**Examples**






igl.per_edge_normals = per_edge_normals(...) method of builtins.PyCapsule instance

------------------

### **`per_edge_normals(v: array, f: array, weight: igl::PerEdgeNormalsWeightingType, fn: array) -> Tuple[object, object, object]`**

Compute face normals via vertex position list, face list

**Parameters**



V  #V by 3 eigen Matrix of mesh vertex 3D positions

F  #F by 3 eigen Matrix of face (triangle) indices

weight  weighting type

FN  #F by 3 matrix of 3D face normals per face

----------------
**Returns**



N  #2 by 3 matrix of mesh edge 3D normals per row

E  #E by 2 matrix of edge indices per row

EMAP  #E by 1 matrix of indices from all edges to E

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.per_edge_normals = per_edge_normals(...) method of builtins.PyCapsule instance

------------------

### **`per_edge_normals(v: array, f: array, weight: igl::PerEdgeNormalsWeightingType, fn: array) -> Tuple[object, object, object]`**

Compute face normals via vertex position list, face list

**Parameters**



V  #V by 3 eigen Matrix of mesh vertex 3D positions

F  #F by 3 eigen Matrix of face (triangle) indices

weight  weighting type

FN  #F by 3 matrix of 3D face normals per face

----------------
**Returns**



N  #2 by 3 matrix of mesh edge 3D normals per row

E  #E by 2 matrix of edge indices per row

EMAP  #E by 1 matrix of indices from all edges to E

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.per_face_normals = per_face_normals(...) method of builtins.PyCapsule instance

------------------

### **`per_face_normals(v: array, f: array, z: array) -> object`**

Compute face normals via vertex position list, face list

**Parameters**



V  #V by 3 eigen Matrix of mesh vertex 3D positions

F  #F by 3 eigen Matrix of face (triangle) indices

Z  3 vector normal given to faces with degenerate normal.

----------------
**Returns**



N  #F by 3 eigen Matrix of mesh face (triangle) 3D normals

----------------

**See also**



--------------

**Notes**



None

**Examples**



Give degenerate faces (1/3,1/3,1/3)^0.5

------------------

### **`per_face_normals(V,F,Vector3d(1,1,1).normalized(),N);`**




igl.per_face_normals = per_face_normals(...) method of builtins.PyCapsule instance

------------------

### **`per_face_normals(v: array, f: array, z: array) -> object`**

Compute face normals via vertex position list, face list

**Parameters**



V  #V by 3 eigen Matrix of mesh vertex 3D positions

F  #F by 3 eigen Matrix of face (triangle) indices

Z  3 vector normal given to faces with degenerate normal.

----------------
**Returns**



N  #F by 3 eigen Matrix of mesh face (triangle) 3D normals

----------------

**See also**



--------------

**Notes**



None

**Examples**



Give degenerate faces (1/3,1/3,1/3)^0.5

------------------

### **`per_face_normals(V,F,Vector3d(1,1,1).normalized(),N);`**




igl.per_face_normals = per_face_normals(...) method of builtins.PyCapsule instance

------------------

### **`per_face_normals(v: array, f: array, z: array) -> object`**

Compute face normals via vertex position list, face list

**Parameters**



V  #V by 3 eigen Matrix of mesh vertex 3D positions

F  #F by 3 eigen Matrix of face (triangle) indices

Z  3 vector normal given to faces with degenerate normal.

----------------
**Returns**



N  #F by 3 eigen Matrix of mesh face (triangle) 3D normals

----------------

**See also**



--------------

**Notes**



None

**Examples**



Give degenerate faces (1/3,1/3,1/3)^0.5

------------------

### **`per_face_normals(V,F,Vector3d(1,1,1).normalized(),N);`**




igl.per_vertex_attribute_smoothing = per_vertex_attribute_smoothing(...) method of builtins.PyCapsule instance

------------------

### **`per_vertex_attribute_smoothing(ain: array, f: array) -> object`**

Smooth vertex attributes using uniform Laplacian

**Parameters**



Ain  #V by #A eigen Matrix of mesh vertex attributes (each vertex has #A attributes)

F    #F by 3 eigne Matrix of face (triangle) indices

----------------
**Returns**



Aout #V by #A eigen Matrix of mesh vertex attributes

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.per_vertex_attribute_smoothing = per_vertex_attribute_smoothing(...) method of builtins.PyCapsule instance

------------------

### **`per_vertex_attribute_smoothing(ain: array, f: array) -> object`**

Smooth vertex attributes using uniform Laplacian

**Parameters**



Ain  #V by #A eigen Matrix of mesh vertex attributes (each vertex has #A attributes)

F    #F by 3 eigne Matrix of face (triangle) indices

----------------
**Returns**



Aout #V by #A eigen Matrix of mesh vertex attributes

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.per_vertex_normals = per_vertex_normals(...) method of builtins.PyCapsule instance

------------------

### **`per_vertex_normals(v: array, f: array, weighting: int = 0) -> object`**

Compute vertex normals via vertex position list, face list.

**Parameters**



v : #v by 3 array of mesh vertex 3D positions

f : #f by 3 array of face (triangle) indices

weighting : Weighting type, one of the following

-igl.PER_VERTEX_NORMALS_WEIGHTING_TYPE_UNIFORM uniform influence

-igl.PER_VERTEX_NORMALS_WEIGHTING_TYPE_AREA area weighted

-igl.PER_VERTEX_NORMALS_WEIGHTING_TYPE_ANGLE angle weighted

----------------
**Returns**



n  #v by 3 array of mesh vertex 3D normals

----------------

**See also**



per_face_normals, per_edge_normals

--------------

**Notes**



None

**Examples**



Mesh in (v, f)

n = per_vertex_normals(v, f)




igl.per_vertex_normals = per_vertex_normals(...) method of builtins.PyCapsule instance

------------------

### **`per_vertex_normals(v: array, f: array, weighting: int = 0) -> object`**

Compute vertex normals via vertex position list, face list.

**Parameters**



v : #v by 3 array of mesh vertex 3D positions

f : #f by 3 array of face (triangle) indices

weighting : Weighting type, one of the following

-igl.PER_VERTEX_NORMALS_WEIGHTING_TYPE_UNIFORM uniform influence

-igl.PER_VERTEX_NORMALS_WEIGHTING_TYPE_AREA area weighted

-igl.PER_VERTEX_NORMALS_WEIGHTING_TYPE_ANGLE angle weighted

----------------
**Returns**



n  #v by 3 array of mesh vertex 3D normals

----------------

**See also**



per_face_normals, per_edge_normals

--------------

**Notes**



None

**Examples**



Mesh in (v, f)

n = per_vertex_normals(v, f)




igl.piecewise_constant_winding_number = piecewise_constant_winding_number(...) method of builtins.PyCapsule instance

------------------

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

**Parameters**



F  #F by 3 list of triangle indices into some (abstract) list of

vertices V

----------------
**Returns**



**Returns true if the mesh _combinatorially_ induces a piecewise constant**

winding number field.

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.piecewise_constant_winding_number = piecewise_constant_winding_number(...) method of builtins.PyCapsule instance

------------------

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

**Parameters**



F  #F by 3 list of triangle indices into some (abstract) list of

vertices V

----------------
**Returns**



**Returns true if the mesh _combinatorially_ induces a piecewise constant**

winding number field.

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.principal_curvature = principal_curvature(...) method of builtins.PyCapsule instance

------------------

### **`principal_curvature(v: array, f: array, radius: int = 5, use_k_ring: bool = True) -> Tuple[object, object, object, object]`**

Compute the principal curvature directions and magnitude of the given triangle mesh.

**Parameters**



v : vertex array of size #V by 3

f : face index array #F by 3 list of mesh faces (must be triangles)

radius : controls the size of the neighbourhood used, 1 = average edge length (default: 5)

use_k_ring : (default: True)

----------------
**Returns**



pd1 : #v by 3 maximal curvature direction for each vertex

pd2 : #v by 3 minimal curvature direction for each vertex

pv1 : #v by 1 maximal curvature value for each vertex

pv2 : #v by 1 minimal curvature value for each vertex

----------------

**See also**



average_onto_faces, average_onto_vertices

--------------

**Notes**



This function has been developed by: Nikolas De Giorgis, Luigi Rocca and Enrico Puppo.

The algorithm is based on: Efficient Multi-scale Curvature and Crease Estimation

Daniele Panozzo, Enrico Puppo, Luigi Rocca GraVisMa, 2010

**Examples**



Mesh in (v, f)

pd1, pd2, pv1, pv2 = principal_curvature(v, f)




igl.principal_curvature = principal_curvature(...) method of builtins.PyCapsule instance

------------------

### **`principal_curvature(v: array, f: array, radius: int = 5, use_k_ring: bool = True) -> Tuple[object, object, object, object]`**

Compute the principal curvature directions and magnitude of the given triangle mesh.

**Parameters**



v : vertex array of size #V by 3

f : face index array #F by 3 list of mesh faces (must be triangles)

radius : controls the size of the neighbourhood used, 1 = average edge length (default: 5)

use_k_ring : (default: True)

----------------
**Returns**



pd1 : #v by 3 maximal curvature direction for each vertex

pd2 : #v by 3 minimal curvature direction for each vertex

pv1 : #v by 1 maximal curvature value for each vertex

pv2 : #v by 1 minimal curvature value for each vertex

----------------

**See also**



average_onto_faces, average_onto_vertices

--------------

**Notes**



This function has been developed by: Nikolas De Giorgis, Luigi Rocca and Enrico Puppo.

The algorithm is based on: Efficient Multi-scale Curvature and Crease Estimation

Daniele Panozzo, Enrico Puppo, Luigi Rocca GraVisMa, 2010

**Examples**



Mesh in (v, f)

pd1, pd2, pv1, pv2 = principal_curvature(v, f)




igl.procrustes = procrustes(...) method of builtins.PyCapsule instance

------------------

### **`procrustes(x: array, y: array) -> Tuple[bool, bool, float, object, object]`**

Solve Procrustes problem in d dimensions.  Given two point sets X,Y in R^d

find best scale s, orthogonal R  and translation t s.t. s*X*R + t - Y^2

is minimized.

**Parameters**



X  #V by DIM first list of points

Y  #V by DIM second list of points

includeScaling  if scaling should be allowed

includeReflections  if R is allowed to be a reflection

----------------
**Returns**



scale  scaling

R      orthogonal matrix

t      translation

----------------

**See also**



--------------

**Notes**



None

**Examples**



MatrixXd X, Y; (containing 3d points as rows)

double scale;

MatrixXd R;

VectorXd t;

igl::procrustes(X,Y,true,false,scale,R,t);

R *= scale;

MatrixXd Xprime = (X * R).rowwise() + t.transpose();




igl.procrustes = procrustes(...) method of builtins.PyCapsule instance

------------------

### **`procrustes(x: array, y: array) -> Tuple[bool, bool, float, object, object]`**

Solve Procrustes problem in d dimensions.  Given two point sets X,Y in R^d

find best scale s, orthogonal R  and translation t s.t. s*X*R + t - Y^2

is minimized.

**Parameters**



X  #V by DIM first list of points

Y  #V by DIM second list of points

includeScaling  if scaling should be allowed

includeReflections  if R is allowed to be a reflection

----------------
**Returns**



scale  scaling

R      orthogonal matrix

t      translation

----------------

**See also**



--------------

**Notes**



None

**Examples**



MatrixXd X, Y; (containing 3d points as rows)

double scale;

MatrixXd R;

VectorXd t;

igl::procrustes(X,Y,true,false,scale,R,t);

R *= scale;

MatrixXd Xprime = (X * R).rowwise() + t.transpose();




igl.qslim = qslim(...) method of builtins.PyCapsule instance

------------------

### **`qslim(v: array, f: array, max_m: int) -> Tuple[bool, object, object, object, object]`**

Decimate (simplify) a triangle mesh in nD according to the paper

"Simplifying Surfaces with Color and Texture using Quadric Error Metrics"

by [Garland and Heckbert, 1987] (technically a followup to qslim). The

mesh can have open boundaries but should be edge-manifold.

**Parameters**



V  #V by dim list of vertex positions. Assumes that vertices w

F  #F by 3 list of triangle indices into V

max_m  desired number of output faces

----------------
**Returns**



U  #U by dim list of output vertex posistions (can be same ref as V)

G  #G by 3 list of output face indices into U (can be same ref as G)

J  #G list of indices into F of birth face

I  #U list of indices into V of birth vertices

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.qslim = qslim(...) method of builtins.PyCapsule instance

------------------

### **`qslim(v: array, f: array, max_m: int) -> Tuple[bool, object, object, object, object]`**

Decimate (simplify) a triangle mesh in nD according to the paper

"Simplifying Surfaces with Color and Texture using Quadric Error Metrics"

by [Garland and Heckbert, 1987] (technically a followup to qslim). The

mesh can have open boundaries but should be edge-manifold.

**Parameters**



V  #V by dim list of vertex positions. Assumes that vertices w

F  #F by 3 list of triangle indices into V

max_m  desired number of output faces

----------------
**Returns**



U  #U by dim list of output vertex posistions (can be same ref as V)

G  #G by 3 list of output face indices into U (can be same ref as G)

J  #G list of indices into F of birth face

I  #U list of indices into V of birth vertices

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.quad_planarity = quad_planarity(...) method of builtins.PyCapsule instance

------------------

### **`quad_planarity(v: array, f: array) -> object`**

Compute planarity of the faces of a quad mesh.

**Parameters**



v : #v by 3 array of mesh vertex 3D positions

f : #f by 4 array of face (quad) indices

----------------
**Returns**



p : #f by 1 array of mesh face (quad) planarities

----------------

**See also**



None

--------------

**Notes**



None

**Examples**






igl.quad_planarity = quad_planarity(...) method of builtins.PyCapsule instance

------------------

### **`quad_planarity(v: array, f: array) -> object`**

Compute planarity of the faces of a quad mesh.

**Parameters**



v : #v by 3 array of mesh vertex 3D positions

f : #f by 4 array of face (quad) indices

----------------
**Returns**



p : #f by 1 array of mesh face (quad) planarities

----------------

**See also**



None

--------------

**Notes**



None

**Examples**






igl.random_points_on_mesh = random_points_on_mesh(...) method of builtins.PyCapsule instance

------------------

### **`random_points_on_mesh(n: int, v: array, f: array) -> Tuple[object, object]`**

RANDOM_POINTS_ON_MESH Randomly sample a mesh (V,F) n times.

**Parameters**



n  number of samples

V  #V by dim list of mesh vertex positions

F  #F by 3 list of mesh triangle indices

----------------
**Returns**



B  n by 3 list of barycentric coordinates, ith row are coordinates of

ith sampled point in face FI(i)

FI  n list of indices into F

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.random_points_on_mesh = random_points_on_mesh(...) method of builtins.PyCapsule instance

------------------

### **`random_points_on_mesh(n: int, v: array, f: array) -> Tuple[object, object]`**

RANDOM_POINTS_ON_MESH Randomly sample a mesh (V,F) n times.

**Parameters**



n  number of samples

V  #V by dim list of mesh vertex positions

F  #F by 3 list of mesh triangle indices

----------------
**Returns**



B  n by 3 list of barycentric coordinates, ith row are coordinates of

ith sampled point in face FI(i)

FI  n list of indices into F

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.read_dmat = read_dmat(...) method of builtins.PyCapsule instance

------------------

### **`read_dmat(filename: str, dtype: numpy.dtype  str  type = 'float64') -> object`**

Read a matrix from an ascii dmat file, a simple ascii matrix file type, defined as follows. The first line is always:

<#columns> <#rows>

Then the coefficients of the matrix are given separated by whitespace with columns running fastest.

**Parameters**



filename : string, path to .dmat file

dtype : data-type of the returned matrix. Default is `float64`.

(returned faces always have type int32.)

----------------
**Returns**



w : array containing read-in coefficients

----------------

**See also**



read_triangle_mesh, read_off

--------------

**Notes**



None

**Examples**



w = read_dmat("my_model.dmat")




igl.read_dmat = read_dmat(...) method of builtins.PyCapsule instance

------------------

### **`read_dmat(filename: str, dtype: numpy.dtype  str  type = 'float64') -> object`**

Read a matrix from an ascii dmat file, a simple ascii matrix file type, defined as follows. The first line is always:

<#columns> <#rows>

Then the coefficients of the matrix are given separated by whitespace with columns running fastest.

**Parameters**



filename : string, path to .dmat file

dtype : data-type of the returned matrix. Default is `float64`.

(returned faces always have type int32.)

----------------
**Returns**



w : array containing read-in coefficients

----------------

**See also**



read_triangle_mesh, read_off

--------------

**Notes**



None

**Examples**



w = read_dmat("my_model.dmat")




igl.read_obj = read_obj(...) method of builtins.PyCapsule instance

------------------

### **`read_obj(filename: str, dtype: numpy.dtype  str  type = 'float64') -> Tuple[object, object, object, object, object, object]`**

Read a mesh from an ascii obj file, filling in vertex positions, normals

and texture coordinates. Mesh may have faces of any number of degree.

**Parameters**



filename : string, path to .obj file

dtype : data-type of the returned faces, texture coordinates and normals, optional. Default is `float64`.

(returned faces always have type int32.)

----------------
**Returns**



v : array of vertex positions #v by 3

tc : array of texture coordinats #tc by 2

n : array of corner normals #n by 3

f : #f array of face indices into vertex positions

ftc : #f array of face indices into vertex texture coordinates

fn : #f array of face indices into vertex normals

----------------

**See also**



read_triangle_mesh, read_off

--------------

**Notes**



None

**Examples**



v, _, n, f, _, _ = read_obj("my_model.obj")




igl.read_obj = read_obj(...) method of builtins.PyCapsule instance

------------------

### **`read_obj(filename: str, dtype: numpy.dtype  str  type = 'float64') -> Tuple[object, object, object, object, object, object]`**

Read a mesh from an ascii obj file, filling in vertex positions, normals

and texture coordinates. Mesh may have faces of any number of degree.

**Parameters**



filename : string, path to .obj file

dtype : data-type of the returned faces, texture coordinates and normals, optional. Default is `float64`.

(returned faces always have type int32.)

----------------
**Returns**



v : array of vertex positions #v by 3

tc : array of texture coordinats #tc by 2

n : array of corner normals #n by 3

f : #f array of face indices into vertex positions

ftc : #f array of face indices into vertex texture coordinates

fn : #f array of face indices into vertex normals

----------------

**See also**



read_triangle_mesh, read_off

--------------

**Notes**



None

**Examples**



v, _, n, f, _, _ = read_obj("my_model.obj")




igl.read_off = read_off(...) method of builtins.PyCapsule instance

------------------

### **`read_off(filename: str, read_normals: bool = True, dtype: numpy.dtype  str  type = 'float64') -> Tuple[object, object, object]`**

Read a mesh from an ascii off file, filling in vertex positions, normals

and texture coordinates. Mesh may have faces of any number of degree.

**Parameters**



filename : string, path to .off file

read_normals : bool, determines whether normals are read. If false, **returns []**

dtype : data-type of the returned vertices, faces, and normals, optional. Default is `float64`.

(returned faces always have type int32.)

----------------
**Returns**



v : array of vertex positions #v by 3

f : #f list of face indices into vertex positions

n : list of vertex normals #v by 3

----------------

**See also**



read_triangle_mesh, read_obj

--------------

**Notes**



None

**Examples**



v, f, n, c = read_off("my_model.off")




igl.read_off = read_off(...) method of builtins.PyCapsule instance

------------------

### **`read_off(filename: str, read_normals: bool = True, dtype: numpy.dtype  str  type = 'float64') -> Tuple[object, object, object]`**

Read a mesh from an ascii off file, filling in vertex positions, normals

and texture coordinates. Mesh may have faces of any number of degree.

**Parameters**



filename : string, path to .off file

read_normals : bool, determines whether normals are read. If false, **returns []**

dtype : data-type of the returned vertices, faces, and normals, optional. Default is `float64`.

(returned faces always have type int32.)

----------------
**Returns**



v : array of vertex positions #v by 3

f : #f list of face indices into vertex positions

n : list of vertex normals #v by 3

----------------

**See also**



read_triangle_mesh, read_obj

--------------

**Notes**



None

**Examples**



v, f, n, c = read_off("my_model.off")




igl.read_triangle_mesh = read_triangle_mesh(...) method of builtins.PyCapsule instance

------------------

### **`read_triangle_mesh(filename: str, dtype: numpy.dtype  str  type = 'float64') -> Tuple[object, object]`**

Read mesh from an ascii file with automatic detection of file format.

Supported: obj, off, stl, wrl, ply, mesh.

**Parameters**



filename : string, path to mesh file

dtype : data-type of the returned vertices, optional. Default is `float64`.

(returned faces always have type int32.)

----------------
**Returns**



v : array of vertex positions #v by 3

f : #f list of face indices into vertex positions

----------------

**See also**



read_obj, read_off, read_stl

--------------

**Notes**



None

**Examples**



v, f = read_triangle_mesh("my_model.obj")




igl.read_triangle_mesh = read_triangle_mesh(...) method of builtins.PyCapsule instance

------------------

### **`read_triangle_mesh(filename: str, dtype: numpy.dtype  str  type = 'float64') -> Tuple[object, object]`**

Read mesh from an ascii file with automatic detection of file format.

Supported: obj, off, stl, wrl, ply, mesh.

**Parameters**



filename : string, path to mesh file

dtype : data-type of the returned vertices, optional. Default is `float64`.

(returned faces always have type int32.)

----------------
**Returns**



v : array of vertex positions #v by 3

f : #f list of face indices into vertex positions

----------------

**See also**



read_obj, read_off, read_stl

--------------

**Notes**



None

**Examples**



v, f = read_triangle_mesh("my_model.obj")




igl.remove_duplicate_vertices = remove_duplicate_vertices(...) method of builtins.PyCapsule instance

------------------

### **`remove_duplicate_vertices(v: array, f: array, epsilon: float) -> Tuple[object, object, object, object]`**

REMOVE_DUPLICATE_VERTICES Remove duplicate vertices upto a uniqueness

tolerance (epsilon)

**Parameters**



V  #V by dim list of vertex positions

epsilon  uniqueness tolerance (significant digit), can probably think of

this as a tolerance on L1 distance

----------------
**Returns**



SV  #SV by dim new list of vertex positions

SVI #V by 1 list of indices so SV = V(SVI,:)

SVJ #SV by 1 list of indices so V = SV(SVJ,:)

Wrapper that also remaps given faces (F) --> (SF) so that SF index SV

----------------

**See also**



--------------

**Notes**



None

**Examples**



% Mesh in (V,F)

[SV,SVI,SVJ] = remove_duplicate_vertices(V,1e-7);

% remap faces

SF = SVJ(F);




igl.remove_duplicate_vertices = remove_duplicate_vertices(...) method of builtins.PyCapsule instance

------------------

### **`remove_duplicate_vertices(v: array, f: array, epsilon: float) -> Tuple[object, object, object, object]`**

REMOVE_DUPLICATE_VERTICES Remove duplicate vertices upto a uniqueness

tolerance (epsilon)

**Parameters**



V  #V by dim list of vertex positions

epsilon  uniqueness tolerance (significant digit), can probably think of

this as a tolerance on L1 distance

----------------
**Returns**



SV  #SV by dim new list of vertex positions

SVI #V by 1 list of indices so SV = V(SVI,:)

SVJ #SV by 1 list of indices so V = SV(SVJ,:)

Wrapper that also remaps given faces (F) --> (SF) so that SF index SV

----------------

**See also**



--------------

**Notes**



None

**Examples**



% Mesh in (V,F)

[SV,SVI,SVJ] = remove_duplicate_vertices(V,1e-7);

% remap faces

SF = SVJ(F);




igl.remove_duplicates = remove_duplicates(...) method of builtins.PyCapsule instance

------------------

### **`remove_duplicates(v: array, f: array, epsilon: float) -> Tuple[object, object, object]`**

Merge the duplicate vertices from V, fixing the topology accordingly

**Parameters**



V,F       mesh description

epsilon   minimal distance to consider two vertices identical

----------------
**Returns**



NV, NF    new mesh without duplicate vertices

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.remove_duplicates = remove_duplicates(...) method of builtins.PyCapsule instance

------------------

### **`remove_duplicates(v: array, f: array, epsilon: float) -> Tuple[object, object, object]`**

Merge the duplicate vertices from V, fixing the topology accordingly

**Parameters**



V,F       mesh description

epsilon   minimal distance to consider two vertices identical

----------------
**Returns**



NV, NF    new mesh without duplicate vertices

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.remove_unreferenced = remove_unreferenced(...) method of builtins.PyCapsule instance

------------------

### **`remove_unreferenced(v: array, f: array) -> Tuple[object, object, object, object]`**

Remove unreferenced vertices from V, updating F accordingly

**Parameters**



V  #V by dim list of mesh vertex positions

F  #F by ss list of simplices (Values of -1 are quitely skipped)

----------------
**Returns**



NV  #NV by dim list of mesh vertex positions

NF  #NF by ss list of simplices

IM  #V by 1 list of indices such that: NF = IM(F) and NT = IM(T)

and V(find(IM<=size(NV,1)),:) = NV

J  #RV by 1 list, such that RV = V(J,:)

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.remove_unreferenced = remove_unreferenced(...) method of builtins.PyCapsule instance

------------------

### **`remove_unreferenced(v: array, f: array) -> Tuple[object, object, object, object]`**

Remove unreferenced vertices from V, updating F accordingly

**Parameters**



V  #V by dim list of mesh vertex positions

F  #F by ss list of simplices (Values of -1 are quitely skipped)

----------------
**Returns**



NV  #NV by dim list of mesh vertex positions

NF  #NF by ss list of simplices

IM  #V by 1 list of indices such that: NF = IM(F) and NT = IM(T)

and V(find(IM<=size(NV,1)),:) = NV

J  #RV by 1 list, such that RV = V(J,:)

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.resolve_duplicated_faces = resolve_duplicated_faces(...) method of builtins.PyCapsule instance

------------------

### **`resolve_duplicated_faces(f1: array) -> Tuple[object, object]`**

Resolve duplicated faces according to the following rules per unique face:

------------------

### **`If the number of positively oriented faces equals the number of`**

negatively oriented faces, remove all duplicated faces at this triangle.

------------------

### **`If the number of positively oriented faces equals the number of`**

negatively oriented faces plus 1, keeps one of the positively oriented

face.

------------------

### **`If the number of positively oriented faces equals the number of`**

negatively oriented faces minus 1, keeps one of the negatively oriented

face.

------------------

### **`If the number of postively oriented faces differ with the number of`**

negativley oriented faces by more than 1, the mesh is not orientable.

An exception will be thrown.

**Parameters**



F1  #F1 by 3 array of input faces.

----------------
**Returns**



F2  #F2 by 3 array of output faces without duplicated faces.

J   #F2 list of indices into F1.

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.resolve_duplicated_faces = resolve_duplicated_faces(...) method of builtins.PyCapsule instance

------------------

### **`resolve_duplicated_faces(f1: array) -> Tuple[object, object]`**

Resolve duplicated faces according to the following rules per unique face:

------------------

### **`If the number of positively oriented faces equals the number of`**

negatively oriented faces, remove all duplicated faces at this triangle.

------------------

### **`If the number of positively oriented faces equals the number of`**

negatively oriented faces plus 1, keeps one of the positively oriented

face.

------------------

### **`If the number of positively oriented faces equals the number of`**

negatively oriented faces minus 1, keeps one of the negatively oriented

face.

------------------

### **`If the number of postively oriented faces differ with the number of`**

negativley oriented faces by more than 1, the mesh is not orientable.

An exception will be thrown.

**Parameters**



F1  #F1 by 3 array of input faces.

----------------
**Returns**



F2  #F2 by 3 array of output faces without duplicated faces.

J   #F2 list of indices into F1.

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.shape_diameter_function = shape_diameter_function(...) method of builtins.PyCapsule instance

------------------

### **`shape_diameter_function(v: array, f: array, p: array, n: array, num_samples: int) -> object`**

Compute shape diamater function per given point. In the parlence of the

paper "Consistent Mesh Partitioning and Skeletonisation using the Shape

Diameter Function" [Shapiro et al. 2008], this implementation uses a 180°

cone and a _uniform_ average (_not_ a average weighted by inverse angles).

**Parameters**



V  #V by 3 list of mesh vertex positions

F  #F by 3 list of mesh face indices into V

P  #P by 3 list of origin points

N  #P by 3 list of origin normals

----------------
**Returns**



S  #P list of shape diamater function values between bounding box

diagonal (perfect sphere) and 0 (perfect needle hook)

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.shape_diameter_function = shape_diameter_function(...) method of builtins.PyCapsule instance

------------------

### **`shape_diameter_function(v: array, f: array, p: array, n: array, num_samples: int) -> object`**

Compute shape diamater function per given point. In the parlence of the

paper "Consistent Mesh Partitioning and Skeletonisation using the Shape

Diameter Function" [Shapiro et al. 2008], this implementation uses a 180°

cone and a _uniform_ average (_not_ a average weighted by inverse angles).

**Parameters**



V  #V by 3 list of mesh vertex positions

F  #F by 3 list of mesh face indices into V

P  #P by 3 list of origin points

N  #P by 3 list of origin normals

----------------
**Returns**



S  #P list of shape diamater function values between bounding box

diagonal (perfect sphere) and 0 (perfect needle hook)

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.sort_angles = sort_angles(...) method of builtins.PyCapsule instance

------------------

### **`sort_angles(m: array) -> object`**

Sort angles in ascending order in a numerically robust way.

Instead of computing angles using atan2(y, x), sort directly on (y, x).

**Parameters**

-

M: m by n matrix of scalars. (n >= 2).  Assuming the first column of M

contains values for y, and the second column is x.  Using the rest

of the columns as tie-breaker.

----------------
**Returns**



R: an array of m indices.  M.row(R[i]) contains the i-th smallest

angle.

----------------

**See also**



--------------

**Notes**



None.

**Examples**






igl.sort_angles = sort_angles(...) method of builtins.PyCapsule instance

------------------

### **`sort_angles(m: array) -> object`**

Sort angles in ascending order in a numerically robust way.

Instead of computing angles using atan2(y, x), sort directly on (y, x).

**Parameters**

-

M: m by n matrix of scalars. (n >= 2).  Assuming the first column of M

contains values for y, and the second column is x.  Using the rest

of the columns as tie-breaker.

----------------
**Returns**



R: an array of m indices.  M.row(R[i]) contains the i-th smallest

angle.

----------------

**See also**



--------------

**Notes**



None.

**Examples**






igl.tetrahedralize = tetrahedralize(...) method of builtins.PyCapsule instance

------------------

### **`tetrahedralize(v: array, f: array, switches: str = 'pYQ') -> Tuple[int, object, object, object]`**

Mesh the interior of a surface mesh (V,F) using tetgen.

**Parameters**



v : #v by 3 vertex position array

f : #v array of polygon face indices into V (0-indexed)

switches : string of tetgen options (See tetgen documentation) e.g.

"pq1.414a0.01" tries to mesh the interior of a given surface with quality and area constraints. Will mesh the convex hull constrained to pass through V (ignores F)

----------------
**Returns**



tv  #v by 3 vertex position array

tt  #t by 4 array of tet face indices

tf  #f by 3 array of triangle face indices

----------------

**See also**



None

--------------

**Notes**



**Returns status:**

0 success

1 tetgen threw exception

2 tetgen did not crash but could not create any tets (probably there are

holes, duplicate faces etc.)

-1 other error

**Examples**






igl.tetrahedralize = tetrahedralize(...) method of builtins.PyCapsule instance

------------------

### **`tetrahedralize(v: array, f: array, switches: str = 'pYQ') -> Tuple[int, object, object, object]`**

Mesh the interior of a surface mesh (V,F) using tetgen.

**Parameters**



v : #v by 3 vertex position array

f : #v array of polygon face indices into V (0-indexed)

switches : string of tetgen options (See tetgen documentation) e.g.

"pq1.414a0.01" tries to mesh the interior of a given surface with quality and area constraints. Will mesh the convex hull constrained to pass through V (ignores F)

----------------
**Returns**



tv  #v by 3 vertex position array

tt  #t by 4 array of tet face indices

tf  #f by 3 array of triangle face indices

----------------

**See also**



None

--------------

**Notes**



**Returns status:**

0 success

1 tetgen threw exception

2 tetgen did not crash but could not create any tets (probably there are

holes, duplicate faces etc.)

-1 other error

**Examples**






igl.triangle_triangle_adjacency = triangle_triangle_adjacency(...) method of builtins.PyCapsule instance

------------------

### **`triangle_triangle_adjacency(f: array) -> Tuple[object, object]`**

Constructs the triangle-triangle adjacency matrix for a given

mesh (V,F).

**Parameters**



F  #F by simplex_size list of mesh faces (must be triangles)

----------------
**Returns**



TT   #F by #3 adjacent matrix, the element i,j is the id of the triangle

adjacent to the j edge of triangle i

TTi  #F by #3 adjacent matrix, the element i,j is the id of edge of the

triangle TT(i,j) that is adjacent with triangle i

----------------

**See also**



--------------

**Notes**



NOTE: the first edge of a triangle is [0,1] the second [1,2] and the third

[2,3].  this convention is DIFFERENT from cotmatrix_entries.h

**Examples**






igl.triangle_triangle_adjacency = triangle_triangle_adjacency(...) method of builtins.PyCapsule instance

------------------

### **`triangle_triangle_adjacency(f: array) -> Tuple[object, object]`**

Constructs the triangle-triangle adjacency matrix for a given

mesh (V,F).

**Parameters**



F  #F by simplex_size list of mesh faces (must be triangles)

----------------
**Returns**



TT   #F by #3 adjacent matrix, the element i,j is the id of the triangle

adjacent to the j edge of triangle i

TTi  #F by #3 adjacent matrix, the element i,j is the id of edge of the

triangle TT(i,j) that is adjacent with triangle i

----------------

**See also**



--------------

**Notes**



NOTE: the first edge of a triangle is [0,1] the second [1,2] and the third

[2,3].  this convention is DIFFERENT from cotmatrix_entries.h

**Examples**






igl.triangulate = triangulate(...) method of builtins.PyCapsule instance

------------------

### **`triangulate(v: array, e: array, h: array, flags: str = 'a0.005qQ') -> Tuple[object, object]`**

Triangulate the interior of a polygon using the triangle library.

**Parameters**



v : #v by 2 array of 2D vertex positions

e : #e by 2 array of vertex ids forming unoriented edges of the boundary of the polygon

h : #h by 2 coordinates of points contained inside holes of the polygon

m : optional #v list of markers for input vertices

flags : string of options pass to triangle (see triangle documentation) (default 'a0.005q')

----------------
**Returns**



v2 : #v2 by 2 coordinates of the vertives of the generated triangulation

f2 : #f2 by 3 array of indices forming the faces of the generated triangulation

m2 : (only if you passed in m) #v2 list of markers for output vertices

----------------

**See also**



--------------

**Notes**



**Examples**



v2, f2 = triangulate(v, e, h)




igl.triangulate = triangulate(...) method of builtins.PyCapsule instance

------------------

### **`triangulate(v: array, e: array, h: array, flags: str = 'a0.005qQ') -> Tuple[object, object]`**

Triangulate the interior of a polygon using the triangle library.

**Parameters**



v : #v by 2 array of 2D vertex positions

e : #e by 2 array of vertex ids forming unoriented edges of the boundary of the polygon

h : #h by 2 coordinates of points contained inside holes of the polygon

m : optional #v list of markers for input vertices

flags : string of options pass to triangle (see triangle documentation) (default 'a0.005q')

----------------
**Returns**



v2 : #v2 by 2 coordinates of the vertives of the generated triangulation

f2 : #f2 by 3 array of indices forming the faces of the generated triangulation

m2 : (only if you passed in m) #v2 list of markers for output vertices

----------------

**See also**



--------------

**Notes**



**Examples**



v2, f2 = triangulate(v, e, h)




igl.uniformly_sample_two_manifold_at_vertices = uniformly_sample_two_manifold_at_vertices(...) method of builtins.PyCapsule instance

------------------

### **`uniformly_sample_two_manifold_at_vertices(ow: array, k: int, push: float) -> object`**

Find uniform sampling up to placing samples on mesh vertices

**Parameters**



----------------
**Returns**



----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.uniformly_sample_two_manifold_at_vertices = uniformly_sample_two_manifold_at_vertices(...) method of builtins.PyCapsule instance

------------------

### **`uniformly_sample_two_manifold_at_vertices(ow: array, k: int, push: float) -> object`**

Find uniform sampling up to placing samples on mesh vertices

**Parameters**



----------------
**Returns**



----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.uniformly_sample_two_manifold_internal = uniformly_sample_two_manifold_internal(...) method of builtins.PyCapsule instance

------------------

### **`uniformly_sample_two_manifold_internal(w: array, f: array, k: int, push: float) -> object`**

UNIFORMLY_SAMPLE_TWO_MANIFOLD Attempt to sample a mesh uniformly by

furthest point relaxation as described in "Fast Automatic Skinning

Transformations"

[Jacobson et al. 12] Section 3.3.

**Parameters**



W  #W by dim positions of mesh in weight space

F  #F by 3 indices of triangles

k  number of samplse

push  factor by which corners should be pushed away

----------------
**Returns**



WS  k by dim locations in weights space

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.uniformly_sample_two_manifold_internal = uniformly_sample_two_manifold_internal(...) method of builtins.PyCapsule instance

------------------

### **`uniformly_sample_two_manifold_internal(w: array, f: array, k: int, push: float) -> object`**

UNIFORMLY_SAMPLE_TWO_MANIFOLD Attempt to sample a mesh uniformly by

furthest point relaxation as described in "Fast Automatic Skinning

Transformations"

[Jacobson et al. 12] Section 3.3.

**Parameters**



W  #W by dim positions of mesh in weight space

F  #F by 3 indices of triangles

k  number of samplse

push  factor by which corners should be pushed away

----------------
**Returns**



WS  k by dim locations in weights space

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.unproject = unproject(...) method of builtins.PyCapsule instance

------------------

### **`unproject(win: array, model: array, proj: array, viewport: array) -> object`**

Reimplementation of gluUnproject

**Parameters**



win  #P by 3 or 3-vector (#P=1) of screen space x, y, and z coordinates

model  4x4 model-view matrix

proj  4x4 projection matrix

viewport  4-long viewport vector

----------------
**Returns**



scene  #P by 3 or 3-vector (#P=1) the unprojected x, y, and z coordinates

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.unproject = unproject(...) method of builtins.PyCapsule instance

------------------

### **`unproject(win: array, model: array, proj: array, viewport: array) -> object`**

Reimplementation of gluUnproject

**Parameters**



win  #P by 3 or 3-vector (#P=1) of screen space x, y, and z coordinates

model  4x4 model-view matrix

proj  4x4 projection matrix

viewport  4-long viewport vector

----------------
**Returns**



scene  #P by 3 or 3-vector (#P=1) the unprojected x, y, and z coordinates

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.unproject_in_mesh = unproject_in_mesh(...) method of builtins.PyCapsule instance

------------------

### **`unproject_in_mesh(pos: numpy.ndarray[float32[2, 1]], model: numpy.ndarray[float32[4, 4]], proj: numpy.ndarray[float32[4, 4]], viewport: numpy.ndarray[float32[4, 1]], v: array, f: array) -> Tuple[object, std::__1::vector<igl::Hit, std::__1::allocator<igl::Hit> >]`**

Unproject a screen location (using current opengl viewport, projection, and

model view) to a 3D position _inside_ a given mesh. If the ray through the

given screen location (x,y) _hits_ the mesh more than twice then the 3D

midpoint between the first two hits is return. If it hits once, then that

point is return. If it does not hit the mesh then obj is not set.

**Parameters**



pos        screen space coordinates

model      model matrix

proj       projection matrix

viewport   vieweport vector

V   #V by 3 list of mesh vertex positions

F   #F by 3 list of mesh triangle indices into V

----------------
**Returns**



obj        3d unprojected mouse point in mesh

hits       vector of hits

**Returns number of hits**

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.unproject_in_mesh = unproject_in_mesh(...) method of builtins.PyCapsule instance

------------------

### **`unproject_in_mesh(pos: numpy.ndarray[float32[2, 1]], model: numpy.ndarray[float32[4, 4]], proj: numpy.ndarray[float32[4, 4]], viewport: numpy.ndarray[float32[4, 1]], v: array, f: array) -> Tuple[object, std::__1::vector<igl::Hit, std::__1::allocator<igl::Hit> >]`**

Unproject a screen location (using current opengl viewport, projection, and

model view) to a 3D position _inside_ a given mesh. If the ray through the

given screen location (x,y) _hits_ the mesh more than twice then the 3D

midpoint between the first two hits is return. If it hits once, then that

point is return. If it does not hit the mesh then obj is not set.

**Parameters**



pos        screen space coordinates

model      model matrix

proj       projection matrix

viewport   vieweport vector

V   #V by 3 list of mesh vertex positions

F   #F by 3 list of mesh triangle indices into V

----------------
**Returns**



obj        3d unprojected mouse point in mesh

hits       vector of hits

**Returns number of hits**

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.unproject_onto_mesh = unproject_onto_mesh(...) method of builtins.PyCapsule instance

------------------

### **`unproject_onto_mesh(pos: array, model: array, proj: array, viewport: array, v: array, f: array) -> Tuple[bool, int, object]`**

Unproject a screen location (using current opengl viewport, projection, and

model view) to a 3D position _onto_ a given mesh, if the ray through the

given screen location (x,y) _hits_ the mesh.

**Parameters**



pos        screen space coordinates

model      model matrix

proj       projection matrix

viewport   vieweport vector

V   #V by 3 list of mesh vertex positions

F   #F by 3 list of mesh triangle indices into V

----------------
**Returns**



fid  id of the first face hit

bc  barycentric coordinates of hit

**Returns true if there's a hit**

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.unproject_onto_mesh = unproject_onto_mesh(...) method of builtins.PyCapsule instance

------------------

### **`unproject_onto_mesh(pos: array, model: array, proj: array, viewport: array, v: array, f: array) -> Tuple[bool, int, object]`**

Unproject a screen location (using current opengl viewport, projection, and

model view) to a 3D position _onto_ a given mesh, if the ray through the

given screen location (x,y) _hits_ the mesh.

**Parameters**



pos        screen space coordinates

model      model matrix

proj       projection matrix

viewport   vieweport vector

V   #V by 3 list of mesh vertex positions

F   #F by 3 list of mesh triangle indices into V

----------------
**Returns**



fid  id of the first face hit

bc  barycentric coordinates of hit

**Returns true if there's a hit**

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.unproject_ray = unproject_ray(...) method of builtins.PyCapsule instance

------------------

### **`unproject_ray(pos: array, model: array, proj: array, viewport: array) -> Tuple[object, object]`**

Construct a ray (source point + direction vector) given a screen space

positions (e.g. mouse) and a model-view projection constellation.

**Parameters**



pos  2d screen-space position (x,y)

model  4x4 model-view matrix

proj  4x4 projection matrix

viewport  4-long viewport vector

----------------
**Returns**



s  source of ray (pos unprojected with z=0)

dir  direction of ray (d - s) where d is pos unprojected with z=1

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.unproject_ray = unproject_ray(...) method of builtins.PyCapsule instance

------------------

### **`unproject_ray(pos: array, model: array, proj: array, viewport: array) -> Tuple[object, object]`**

Construct a ray (source point + direction vector) given a screen space

positions (e.g. mouse) and a model-view projection constellation.

**Parameters**



pos  2d screen-space position (x,y)

model  4x4 model-view matrix

proj  4x4 projection matrix

viewport  4-long viewport vector

----------------
**Returns**



s  source of ray (pos unprojected with z=0)

dir  direction of ray (d - s) where d is pos unprojected with z=1

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.upsample = upsample(...) method of builtins.PyCapsule instance

------------------

### **`upsample(v: array, f: array, number_of_subdivs: int = 1) -> Tuple[object, object]`**

Subdivide a mesh without moving vertices: loop subdivision but odd

vertices stay put and even vertices are just edge midpoints

**Parameters**



V  #V by dim  mesh vertices

F  #F by 3  mesh triangles

----------------
**Returns**



NV new vertex positions, V is guaranteed to be at top

NF new list of face indices

----------------

**See also**



--------------

**Notes**



- assumes (V,F) is edge-manifold.

**Examples**






igl.upsample = upsample(...) method of builtins.PyCapsule instance

------------------

### **`upsample(v: array, f: array, number_of_subdivs: int = 1) -> Tuple[object, object]`**

Subdivide a mesh without moving vertices: loop subdivision but odd

vertices stay put and even vertices are just edge midpoints

**Parameters**



V  #V by dim  mesh vertices

F  #F by 3  mesh triangles

----------------
**Returns**



NV new vertex positions, V is guaranteed to be at top

NF new list of face indices

----------------

**See also**



--------------

**Notes**



- assumes (V,F) is edge-manifold.

**Examples**






igl.vector_area_matrix = vector_area_matrix(...) method of builtins.PyCapsule instance

------------------

### **`vector_area_matrix(f: array) -> object`**

Constructs the symmetric area matrix A, s.t. [V.col(0)' V.col(1)'] * A *

[V.col(0); V.col(1)] is the **vector area** of the mesh (V,F).

**Parameters**



f : #f by 3 array of mesh faces (must be triangles)

----------------
**Returns**



a : #vx2 by #vx2 area matrix

----------------

**See also**



None

--------------

**Notes**



None

**Examples**






igl.vector_area_matrix = vector_area_matrix(...) method of builtins.PyCapsule instance

------------------

### **`vector_area_matrix(f: array) -> object`**

Constructs the symmetric area matrix A, s.t. [V.col(0)' V.col(1)'] * A *

[V.col(0); V.col(1)] is the **vector area** of the mesh (V,F).

**Parameters**



f : #f by 3 array of mesh faces (must be triangles)

----------------
**Returns**



a : #vx2 by #vx2 area matrix

----------------

**See also**



None

--------------

**Notes**



None

**Examples**






igl.vertex_components = vertex_components(...) method of builtins.PyCapsule instance

------------------

### **`vertex_components(f: array) -> object`**

Compute connected components of the vertices of a mesh given the mesh' face indices.

**Parameters**



f : #f x dim array of face indices

----------------
**Returns**



An array of component ids (starting with 0)

----------------

**See also**



vertex_components_from_adjacency_matrix

face_components_from_faces

--------------

**Notes**



**Examples**






igl.vertex_components = vertex_components(...) method of builtins.PyCapsule instance

------------------

### **`vertex_components(f: array) -> object`**

Compute connected components of the vertices of a mesh given the mesh' face indices.

**Parameters**



f : #f x dim array of face indices

----------------
**Returns**



An array of component ids (starting with 0)

----------------

**See also**



vertex_components_from_adjacency_matrix

face_components_from_faces

--------------

**Notes**



**Examples**






igl.vertex_components_from_adjacency_matrix = vertex_components_from_adjacency_matrix(...) method of builtins.PyCapsule instance

------------------

### **`vertex_components_from_adjacency_matrix(a: scipy.sparse.csr_matrix  scipy.sparse.csc_matrix) -> Tuple[object, object]`**

Compute connected components of a graph represented by a sparse adjacency

matrix.

**Parameters**



a : n by n sparse adjacency matrix

----------------
**Returns**



A tuple (c, counts) where c is an array of component ids (starting with 0)

and counts is a #components array of counts for each component

----------------

**See also**



vertex_components

face_components

--------------

**Notes**



**Examples**






igl.vertex_components_from_adjacency_matrix = vertex_components_from_adjacency_matrix(...) method of builtins.PyCapsule instance

------------------

### **`vertex_components_from_adjacency_matrix(a: scipy.sparse.csr_matrix  scipy.sparse.csc_matrix) -> Tuple[object, object]`**

Compute connected components of a graph represented by a sparse adjacency

matrix.

**Parameters**



a : n by n sparse adjacency matrix

----------------
**Returns**



A tuple (c, counts) where c is an array of component ids (starting with 0)

and counts is a #components array of counts for each component

----------------

**See also**



vertex_components

face_components

--------------

**Notes**



**Examples**






igl.vertex_triangle_adjacency = vertex_triangle_adjacency(...) method of builtins.PyCapsule instance

------------------

### **`vertex_triangle_adjacency(f: array, n: int) -> Tuple[object, object]`**

vertex_face_adjacency constructs the vertex-face topology of a given mesh (V,F)

**Parameters**



F  #F by 3 list of triangle indices into some vertex list V

n  number of vertices, #V (e.g., F.maxCoeff()+1)

----------------
**Returns**



VF  3*#F list  List of faces indice on each vertex, so that VF(NI(i)+j) =

f, means that face f is the jth face (in no particular order) incident

on vertex i.

NI  #V+1 list  cumulative sum of vertex-triangle degrees with a

preceeding zero. "How many faces" have been seen before visiting this

vertex and its incident faces.

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.vertex_triangle_adjacency = vertex_triangle_adjacency(...) method of builtins.PyCapsule instance

------------------

### **`vertex_triangle_adjacency(f: array, n: int) -> Tuple[object, object]`**

vertex_face_adjacency constructs the vertex-face topology of a given mesh (V,F)

**Parameters**



F  #F by 3 list of triangle indices into some vertex list V

n  number of vertices, #V (e.g., F.maxCoeff()+1)

----------------
**Returns**



VF  3*#F list  List of faces indice on each vertex, so that VF(NI(i)+j) =

f, means that face f is the jth face (in no particular order) incident

on vertex i.

NI  #V+1 list  cumulative sum of vertex-triangle degrees with a

preceeding zero. "How many faces" have been seen before visiting this

vertex and its incident faces.

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.winding_number = winding_number(...) method of builtins.PyCapsule instance

------------------

### **`winding_number(v: array, f: array, o: array) -> object`**

WINDING_NUMBER Compute the sum of solid angles of a triangle/tetrahedron

described by points (vectors) V

**Parameters**



V  n by 3 list of vertex positions

F  #F by 3 list of triangle indices, minimum index is 0

O  no by 3 list of origin positions

----------------
**Returns**



S  no by 1 list of winding numbers

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.winding_number = winding_number(...) method of builtins.PyCapsule instance

------------------

### **`winding_number(v: array, f: array, o: array) -> object`**

WINDING_NUMBER Compute the sum of solid angles of a triangle/tetrahedron

described by points (vectors) V

**Parameters**



V  n by 3 list of vertex positions

F  #F by 3 list of triangle indices, minimum index is 0

O  no by 3 list of origin positions

----------------
**Returns**



S  no by 1 list of winding numbers

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.winding_number_for_point = winding_number_for_point(...) method of builtins.PyCapsule instance

------------------

### **`winding_number_for_point(v: array, f: array, p: array) -> float`**

Compute winding number of a single point

**Parameters**



V  n by dim list of vertex positions

F  #F by dim list of triangle indices, minimum index is 0

p  single origin position

----------------
**Returns**



w  winding number of this point

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.winding_number_for_point = winding_number_for_point(...) method of builtins.PyCapsule instance

------------------

### **`winding_number_for_point(v: array, f: array, p: array) -> float`**

Compute winding number of a single point

**Parameters**



V  n by dim list of vertex positions

F  #F by dim list of triangle indices, minimum index is 0

p  single origin position

----------------
**Returns**



w  winding number of this point

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.write_obj = write_obj(...) method of builtins.PyCapsule instance

------------------

### **`write_obj(filename: str, v: array, f: array) -> bool`**

Write a mesh in an ascii obj file.

**Parameters**



filename : path to outputfile

v : array of vertex positions #v by 3

f : #f list of face indices into vertex positions

----------------
**Returns**



ret : bool if output was successful

----------------

**See also**



read_obj

--------------

**Notes**



None

**Examples**



Mesh in (v, f)

success = write_obj(v, f)




igl.write_obj = write_obj(...) method of builtins.PyCapsule instance

------------------

### **`write_obj(filename: str, v: array, f: array) -> bool`**

Write a mesh in an ascii obj file.

**Parameters**



filename : path to outputfile

v : array of vertex positions #v by 3

f : #f list of face indices into vertex positions

----------------
**Returns**



ret : bool if output was successful

----------------

**See also**



read_obj

--------------

**Notes**



None

**Examples**



Mesh in (v, f)

success = write_obj(v, f)




igl.write_off = write_off(...) method of builtins.PyCapsule instance

------------------

### **`write_off(str: str, v: array, f: array, c: array) -> bool`**

Export geometry and colors-by-vertex

Export a mesh from an ascii OFF file, filling in vertex positions.

Only triangle meshes are supported

**Parameters**



str  path to .off output file

V  #V by 3 mesh vertex positions

F  #F by 3 mesh indices into V

C  double matrix of rgb values per vertex #V by 3

----------------
**Returns**



**Returns true on success, false on errors**

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.write_off = write_off(...) method of builtins.PyCapsule instance

------------------

### **`write_off(str: str, v: array, f: array, c: array) -> bool`**

Export geometry and colors-by-vertex

Export a mesh from an ascii OFF file, filling in vertex positions.

Only triangle meshes are supported

**Parameters**



str  path to .off output file

V  #V by 3 mesh vertex positions

F  #F by 3 mesh indices into V

C  double matrix of rgb values per vertex #V by 3

----------------
**Returns**



**Returns true on success, false on errors**

----------------

**See also**



--------------

**Notes**



None

**Examples**






igl.write_triangle_mesh = write_triangle_mesh(...) method of builtins.PyCapsule instance

------------------

### **`write_triangle_mesh(str: str, v: array, f: array, force_ascii: bool = True) -> bool`**

write mesh to a file with automatic detection of file format.  supported: obj, off, stl, wrl, ply, mesh).

**Parameters**



str  path to file

V  eigen double matrix #V by 3

F  eigen int matrix #F by 3

force_ascii=True  force ascii format even if binary is available

----------------
**Returns**



**Returns true iff success**

----------------

**See also**



--------------

**Notes**



**Examples**






igl.write_triangle_mesh = write_triangle_mesh(...) method of builtins.PyCapsule instance

------------------

### **`write_triangle_mesh(str: str, v: array, f: array, force_ascii: bool = True) -> bool`**

write mesh to a file with automatic detection of file format.  supported: obj, off, stl, wrl, ply, mesh).

**Parameters**



str  path to file

V  eigen double matrix #V by 3

F  eigen int matrix #F by 3

force_ascii=True  force ascii format even if binary is available

----------------
**Returns**



**Returns true iff success**

----------------

**See also**



--------------

**Notes**



**Examples**



























class ARAP

------------------

### **`solve(: igl.pyigl_classes.ARAP, arg0: numpy.ndarray, arg1: numpy.ndarray) -> object`**




class BBW

------------------

### **`solve(: igl.pyigl_classes.BBW, arg0: numpy.ndarray, arg1: numpy.ndarray, arg2: numpy.ndarray[int32[m, 1]], arg3: numpy.ndarray) -> object`**




class SLIM

------------------

### **`energy(: igl.pyigl_classes.SLIM) -> float`**

------------------

### **`solve(: igl.pyigl_classes.SLIM, arg0: int)`**

------------------

### **`vertices(: igl.pyigl_classes.SLIM) -> object`**




