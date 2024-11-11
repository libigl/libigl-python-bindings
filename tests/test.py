import igl
import numpy as np
# scipy sparse matrices
import scipy.sparse
# timing
import time
import warnings


#def rand_sparse(n,density):
#    n_features = n
#    n_samples = n
#    rng1 = np.random.RandomState(42)
#    rng2 = np.random.RandomState(43)
#
#    nnz = int(n_samples*n_features*density)
#
#    row = rng1.randint(n_samples, size=nnz)
#    cols = rng2.randint(n_features, size=nnz)
#    data = rng1.rand(nnz)
#
#    S = scipy.sparse.coo_matrix((data, (row, cols)), shape=(n_samples, n_features))
#    return S.tocsc()
#
#def time_noop():
#    def helper(N,I,SN,SI):
#        igl.noop(SN=SN)
#        # start timer
#        runs = 100
#        start = time.time()
#        for i in range(runs):
#            igl.noop(SN=SN)
#        # end timer
#        end = time.time()
#        return (end - start)/runs
#    n = 10000
#    m = 10
#    N64_f = np.asfortranarray(np.random.randn(n,m).astype(np.float64))
#    I64_f = np.asfortranarray(np.random.randn(n,m).astype(np.int64))
#    # random sparse matrix
#    SN64 = rand_sparse(n,1.0/(n))
#    # print number of nonzeros
#    SI64 = (rand_sparse(n,1.0/(n))*1000).astype(np.int64)
#    print(f"noop<{n},{m}>: {helper(N64_f,I64_f,SN64,SI64)} secs")
#
#time_noop()

# seed numpy's random number generator
np.random.seed(42)

F = np.array([[0,1,2],[0,2,3]],dtype=np.int64)
E,oE = igl.orient_halfedges(F)
ne = E.max()+1
uE = np.random.rand(ne).astype(np.float64)

uV = igl.average_from_edges_onto_vertices(F,E,oE,uE)
V = np.array([[0,0,0],[1,0,0],[1,1,0],[0,1,0]],dtype=np.float64)
l = igl.edge_lengths(V,F)
igl.write_triangle_mesh("out.obj",V,F)
igl.write_triangle_mesh("out.off",V,F)
igl.write_triangle_mesh("out.ply",V,F,encoding="binary")
igl.writePLY("out.ply",V,F)
igl.writeOBJ("out.obj",V,F)
igl.writeOBJ("out.obj",V,F,V,F,V,F)
V,F,_ = igl.readOFF("out.off")
V,_,_,F,_,_ = igl.readOBJ("out.obj")
V,F = igl.read_triangle_mesh("out.ply")
L = igl.cotmatrix(V,F)
I = np.array([0,1,2,3],dtype=np.int64)
C = np.array([0,4],dtype=np.int64)
L,M,P = igl.cotmatrix_polygon(V,I,C)
A = igl.adjacency_matrix(F)
A = igl.adjacency_matrix_polygon(I,C)
E = igl.edges(F)
E = igl.edges(I,C)
E = igl.edges(A)

M = igl.massmatrix(V,F)
M = igl.massmatrix(V,F,type="barycentric")
M = igl.massmatrix(V,F,type="voronoi")
M = igl.massmatrix(V,F,type="full")
FN = igl.per_face_normals(V,F)
FN = igl.per_face_normals(V,F,Z=np.array([0,0,1],dtype=np.float64))
FN,_,_,_ = igl.per_face_normals(V,I,C)
VN = igl.per_vertex_normals(V,F)
VN = igl.per_vertex_normals(V,F,weighting="uniform")
VN = igl.per_vertex_normals(V,F,weighting="area")
VN = igl.per_vertex_normals(V,F,weighting="angle")
VN = igl.per_vertex_normals(V,F,weighting="angle",FN=FN)

dblA = igl.doublearea(V,F)
dblA = igl.doublearea(l=l)
dblA = igl.doublearea(l=l,nan_replacement=0.0)
P = np.array([[0.5,0.5,0.0],[0.5,0.5,0.5]],dtype=np.float64)
sqrD,I,C = igl.point_mesh_squared_distance(P,V,F)
W = igl.winding_number(V,F,P)
W = igl.winding_number(V,F,P[1,:])
W = igl.fast_winding_number(V,F,P)
S,I,C,N = igl.signed_distance(P,V,F)
S,I,C,N = igl.signed_distance(P,V,F,sign_type="fast_winding_number")

BC = igl.barycenter(V,F)

b = np.array([0,3],dtype=np.int64)
bc = np.array([[1,0],[0,1]],dtype=np.float64)
W = igl.bbw(V,F,b,bc)
W = igl.harmonic(V,F,b,bc,k=1)
W = igl.harmonic(V,F,b,bc,k=2)


V = np.array([[0,0,0],[1,0,0],[0,1,0],[0,0,1]],dtype=np.float64)
T = np.array([[0,1,2,3]],dtype=np.int64)
F,J,K = igl.boundary_facets(T)
igl.writeMESH("out.mesh",V,T)
igl.writeMESH("out.mesh",V,T,F=F)
V,T,F = igl.readMESH("out.mesh")

tree = igl.AABB()
tree.init(V,T)
# first row of P
q = P[0,:]
I = tree.find(V,T,q)
i = tree.find(V,T,q,first=True)

tree = igl.AABB()
tree.init(V,F)
sqrD,_,_ = tree.squared_distance(V,F,P)

O = np.array([[2,1,1],[0.2,0.2,-1]],np.float64);
D = V.mean(axis=0)-O
I,T,UV = tree.intersect_ray_first(V,F,O,D)
hits = tree.intersect_ray(V,F,O,D)
o = O[0,:]
d = D[0,:]
hit = igl.ray_mesh_intersect(o,d,V,F,first=True)
hits = igl.ray_mesh_intersect(o,d,V,F)


E,uE,EMAP,uE2E = igl.unique_edge_map_lists(F)
E,uE,EMAP,uEC,uEE = igl.unique_edge_map(F)
EF,EI = igl.edge_flaps(F,uE,EMAP)
uE,EMAP,EF,EI = igl.edge_flaps(F)
Nv,Nf = igl.circulation(0,True,F,EMAP,EF,EI)



TT,TTi = igl.triangle_triangle_adjacency(F)
TT,TTi = igl.triangle_triangle_adjacency_lists(F)

VF,NI = igl.vertex_triangle_adjacency(F,n=V.shape[0])
VF,VFi = igl.vertex_triangle_adjacency(F)

F012 = F;
F120 = np.roll(F012,1,axis=1)
FF = np.vstack((F012,F120))
F,IA,IC = igl.unique_simplices(FF)


L = igl.cotmatrix(V,F)
# convert nonzeros to 1s to int64
A = (L != 0).astype(np.int64)
# subtract diagonal
A = A - scipy.sparse.diags(A.diagonal())
n,C,K = igl.connected_components(A)


A = -igl.cotmatrix(V,F)
B = np.zeros((V.shape[0],1),dtype=np.float64)
known = np.array([1,2],dtype=np.int64)
Y = np.array([-1,1],dtype=np.float64).reshape(-1, 1)
Aeq = scipy.sparse.csc_matrix(([-1,1],([0,0],[0,3])),shape=(1,V.shape[0]))
Beq = np.zeros((1,1),dtype=np.float64)
Z = igl.min_quad_with_fixed(A,B,known,Y,Aeq,Beq,pd=True)
Z = igl.MinQuadWithFixed(A,known,Aeq,True).solve(B,Y,Beq)

V = np.array([[0,0,0],[1,0,0],[0,1,0],[0,0,1]],dtype=np.float64)
T = np.array([[0,1,2,3]],dtype=np.int64)
L = igl.edge_lengths(V,T)
vol = igl.volume(V,T)
vol = igl.volume(L=L)
vol = igl.volume(A=V[T[:,0],:],B=V[T[:,1],:],C=V[T[:,2],:],D=V[T[:,3],:])

F,_,_ = igl.boundary_facets(T)
# remove last face
F = F[:-1,:]
B = igl.is_border_vertex(F)
I,C = igl.on_boundary(F)
I,C = igl.on_boundary(T)
F = np.array([[2,1,3]],dtype=np.int64)
NV,NF,I,J = igl.remove_unreferenced(V,F)

L = igl.squared_edge_lengths(V,F)
C = igl.cotmatrix_entries(V,F)
l = igl.edge_lengths(V,F)
C = igl.cotmatrix_entries(l=l)
E = igl.oriented_facets(F)
F = igl.oriented_facets(T)

res,BF,EF,EMAP,BE = igl.is_edge_manifold(F)
res,_,_,_,_ = igl.is_edge_manifold(F)

L = igl.cotmatrix(V,F)
s = igl.matlab_format(V,"V")
s = igl.matlab_format_index(F,"F")
s = igl.matlab_format(L,"L")

B1,B2,B3 = igl.local_basis(V,F)

G = igl.grad(V,F)

# random randn 3x3 matrix
A = np.random.randn(3,3).astype(np.float64)
igl.polar_svd(A)
out = igl.polar_svd(A)
R,T,_,_,_ = igl.polar_svd(A)
R,T,sU,sS,sV = igl.polar_svd(A,include_reflections=True)

SV,SVI,SVJ = igl.remove_duplicate_vertices(V,epsilon=1e-10)
SV,SVI,SVJ,F = igl.remove_duplicate_vertices(V,F,epsilon=1e-10)

GV = igl.grid(np.array([2,2,2],dtype=np.int64))

model = np.eye(4).astype(np.float64)
proj = np.eye(4).astype(np.float64)
viewport = np.array([0,0,640,480],dtype=np.float64)
win = igl.project(V,model,proj,viewport)
scene = igl.unproject(win,model,proj,viewport)

S = np.array([0,0,0],dtype=np.float64)
D = np.array([0.2,0.2,0.2],dtype=np.float64)
t,sqrD = igl.project_to_line(V,S,D)
t,sqrD = igl.project_to_line_segment(V,S,D)

S,_ = igl.upsample_matrix(F,n=V.shape[0])
S,_ = igl.loop_matrix(F,n=V.shape[0])
V,F = igl.upsample(V,F,number_of_subdivs=1)
V,F = igl.loop(V,F,number_of_subdivs=1)
# remove first and last
F = F[1:-1,:]
L = igl.boundary_loop(F)

A = igl.adjacency_list(F)
A = igl.adjacency_list(F,sorted=True)

GV,side = igl.voxel_grid(V,s=10)
GV,side = igl.voxel_grid(V,s=10,offset=0.1,pad_count=2)

C = igl.vertex_components(F)
B,I,X = igl.random_points_on_mesh(1000,V,F)

igl.writeDMAT("out.dmat",V)
igl.writeDMAT("out.dmat",V,ascii=True)
V = igl.readDMAT("out.dmat")
igl.writeDMAT("out.dmat",V,ascii=False)
V = igl.readDMAT("out.dmat")

K = igl.gaussian_curvature(V,F)
PD1,PD2,PV1,PV2,_ = igl.principal_curvature(V,F)
PD1,PD2,PV1,PV2,_ = igl.principal_curvature(V,F,radius=10,useKring=False)

VS = np.array([0],dtype=np.int64)
VT = np.array([1],dtype=np.int64)
D = igl.exact_geodesic(V,F,VS=VS,VT=VT)


try:
    import igl.triangle
    V = np.array([[0,0],[1,0],[1,1],[0,1]],dtype=np.float64)
    E = np.array([[0,1],[1,2],[2,3],[3,0]],dtype=np.int64)
    V,T,_,_,_ = igl.triangle.triangulate(V,E,flags="Qc")
    V,T,_,_,_ = igl.triangle.triangulate(V,E,flags="Q")
    V,T,_,_,_ = igl.triangle.triangulate(V,E,flags="Qqa0.1")
except ImportError:
    warnings.warn("igl.triangle not available")
    pass

try:
    import igl.copyleft.tetgen
    # octahedron
    V = np.array([[1,0,0],[0,1,0],[0,0,1],[-1,0,0],[0,-1,0],[0,0,-1]],dtype=np.float64)
    F = np.array([[0,1,2], [0,2,4], [0,4,5], [0,5,1], [1,3,2], [1,5,3], [2,3,4], [3,5,4]],dtype=np.int64)
    V,T,F,_,_,_,_,_,_ = igl.copyleft.tetgen.tetrahedralize(V,F,flags="Q")
except ImportError:
    warnings.warn("igl.copyleft.tetgen not available")
    pass

try:
    import igl.copyleft.cgal
    # tetrahedron
    VA = np.array([[0,0,-1],[2,0,-1],[0,2,-1],[1,1,1]],dtype=np.float64)
    T = np.array([[0,1,2,3]],dtype=np.int64)
    FA,_,_ = igl.boundary_facets(T)
    # flip z
    VB = np.array([[0,0,1],[2,0,1],[0,2,1],[1,1,-1]],dtype=np.float64)
    FB = FA[:,::-1]
    VC,FC,J = igl.copyleft.cgal.mesh_boolean(VA,FA,VB,FB,"union")
except ImportError:
    warnings.warn("igl.copyleft.tetgen not available")
    pass
