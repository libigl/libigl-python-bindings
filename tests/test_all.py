import pytest
import numpy as np
# scipy sparse matrices
import scipy.sparse
import time
import warnings
import igl

import igl.triangle
import igl.copyleft
import igl.copyleft.tetgen
import igl.copyleft.cgal
import igl.embree


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

# print(igl.matlab_format(V,"V"))
# print(igl.matlab_format_index(F,"F"))
# print(igl.matlab_format(dV,"dV"))
# print(igl.matlab_format_index(dF,"dF"))


#seed numpy's random number generator

def triangulated_square():
    V = np.array([[0,0,0],[1,0,0],[1,1,0],[0,1,0]],dtype=np.float64)
    F = np.array([[0,1,2],[0,2,3]],dtype=np.int64)
    return V,F

def single_tet():
    V = np.array([[0,0,0],[1,0,0],[0,1,0],[0,0,1]],dtype=np.float64)
    F = np.array([[2,1,0],[1,3,0],[3,2,0],[2,3,1]],dtype=np.int64)
    T = np.array([[0,1,2,3]],dtype=np.int64)
    return V,F,T

def test_edges():
    F = np.array([[0,1,2],[0,2,3]],dtype=np.int64)
    E,oE = igl.orient_halfedges(F)
    ne = E.max()+1
    np.random.seed(42)
    uE = np.random.rand(ne).astype(np.float64)

    uV = igl.average_from_edges_onto_vertices(F,E,oE,uE)
    V = np.array([[0,0,0],[1,0,0],[1,1,0],[0,1,0]],dtype=np.float64)

def test_read_write():
    V,F = triangulated_square()
    igl.write_triangle_mesh("out.obj",V,F)
    igl.write_triangle_mesh("out.off",V,F)
    igl.write_triangle_mesh("out.ply",V,F,encoding=igl.Binary)
    igl.writePLY("out.ply",V,F)
    igl.writeOBJ("out.obj",V,F)
    igl.writeOBJ("out.obj",V,F,V,F,V,F)
    V,F,_ = igl.readOFF("out.off")
    V,_,_,F,_,_ = igl.readOBJ("out.obj")
    V,F = igl.read_triangle_mesh("out.ply")
    igl.writeDMAT("out.dmat",V)
    igl.writeDMAT("out.dmat",V,ascii=True)
    V = igl.readDMAT("out.dmat")
    igl.writeDMAT("out.dmat",V,ascii=False)
    V = igl.readDMAT("out.dmat")

def test_operators():
    V,F = triangulated_square()
    L = igl.cotmatrix(V,F)
    I = np.array([0,1,2,3],dtype=np.int64)
    C = np.array([0,4],dtype=np.int64)
    L,M,P = igl.cotmatrix(V,I,C)
    L = igl.squared_edge_lengths(V,F)
    K = igl.cotmatrix_entries(V,F)
    l = igl.edge_lengths(V,F)
    K = igl.cotmatrix_entries(l=l)
    B1,B2,B3 = igl.local_basis(V,F)
    G = igl.grad(V,F)

    M = igl.massmatrix(V,F)
    M = igl.massmatrix(V,F,type=igl.MASSMATRIX_TYPE_BARYCENTRIC)
    M = igl.massmatrix(V,F,type=igl.MASSMATRIX_TYPE_VORONOI)
    M = igl.massmatrix(V,F,type=igl.MASSMATRIX_TYPE_DEFAULT)

    A = igl.facet_adjacency_matrix(F)
    A = igl.adjacency_matrix(F)
    A = igl.adjacency_matrix(I,C)
    E = igl.edges(F)
    E = igl.edges(I,C)
    E = igl.edges(A)
    n,C,K = igl.connected_components(A)
    C = igl.vertex_components(F)
    nc,C = igl.facet_components(F)

def test_normals_and_distances():
    V,F = triangulated_square()
    I = np.array([0,1,2,3],dtype=np.int64)
    C = np.array([0,4],dtype=np.int64)
    FN,_,_,_ = igl.per_face_normals(V,I,C)
    FN = igl.per_face_normals(V,F)
    FN = igl.per_face_normals(V,F,Z=np.array([0,0,1],dtype=np.float64))
    VN = igl.per_vertex_normals(V,F)
    VN = igl.per_vertex_normals(V,F,      weighting=igl.PER_VERTEX_NORMALS_WEIGHTING_TYPE_UNIFORM)
    VN = igl.per_vertex_normals(V,F,      weighting=igl.PER_VERTEX_NORMALS_WEIGHTING_TYPE_AREA)
    VN = igl.per_vertex_normals(V,F,      weighting=igl.PER_VERTEX_NORMALS_WEIGHTING_TYPE_ANGLE)
    VN = igl.per_vertex_normals(V,F,FN=FN,weighting=igl.PER_VERTEX_NORMALS_WEIGHTING_TYPE_ANGLE)
    dblA = igl.doublearea(V,F)
    l = igl.edge_lengths(V,F)
    dblA = igl.doublearea(l=l)
    dblA = igl.doublearea(l=l,nan_replacement=0.0)
    P = np.array([[0.5,0.5,0.0],[0.5,0.5,0.5]],dtype=np.float64)
    sqrD,I,C = igl.point_mesh_squared_distance(P,V,F)
    W = igl.winding_number(V,F,P)
    W = igl.winding_number(V,F,P[1,:])
    W = igl.fast_winding_number(V,F,P)
    S,I,C,N = igl.signed_distance(P,V,F)
    S,I,C,N = igl.signed_distance(P,V,F,sign_type=igl.SignedDistanceType.SIGNED_DISTANCE_TYPE_FAST_WINDING_NUMBER)
    BC = igl.barycenter(V,F)

def test_harmonic():
    V,F = triangulated_square()
    b = np.array([0,3],dtype=np.int64)
    bc = np.array([[1,0],[0,1]],dtype=np.float64)
    W = igl.bbw(V,F,b,bc)
    W = igl.harmonic(V,F,b,bc,k=1)
    W = igl.harmonic(V,F,b,bc,k=2)
    
def test_tets():
    V,F,T = single_tet()
    F,J,K = igl.boundary_facets(T)
    igl.writeMESH("out.mesh",V,T)
    igl.writeMESH("out.mesh",V,T,F=F)
    V,T,F = igl.readMESH("out.mesh")
    igl.writeMSH("out.msh",V,F,T)
    V,F,T,_,_,_,_,_,_,_ = igl.readMSH("out.msh")

def test_bvh():
    V,F,T = single_tet()
    tree = igl.AABB()
    tree.init(V,T)

    P = np.array([[0.5,0.5,0.0],[0.5,0.5,0.5]],dtype=np.float64)
    # first row of P
    q = P[0,:]
    I = tree.find(V,T,q)
    i = tree.find(V,T,q,first=True)
    
    Q = igl.barycenter(V,T)
    I = igl.in_element(V,T,Q,tree)
    
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


def test_upsample():
    V,F,T = single_tet()
    # upsample so there's something to collapse
    V,F = igl.upsample(V,F,number_of_subdivs=1)
    E,uE,EMAP,uE2E = igl.unique_edge_map_lists(F)
    E,uE,EMAP,uEC,uEE = igl.unique_edge_map(F)
    EF,EI = igl.edge_flaps(F,uE,EMAP)
    uE,EMAP,EF,EI = igl.edge_flaps(F)
    Nv,Nf = igl.circulation(0,True,F,EMAP,EF,EI)
    
    e = 0
    p = V[uE[e,0],:]
    e1,e2,f1,f2 = igl.collapse_edge(e,p,V,F,uE,EMAP,EF,EI)

def test_cut():
    V,F,T = single_tet()
    C = np.ones(F.shape,dtype=bool)
    Vn,Fn,I = igl.cut_mesh(V,F,C)

def test_adjacency():
    V,F,T = single_tet()
    TT,TTi = igl.triangle_triangle_adjacency(F)
    TT,TTi = igl.triangle_triangle_adjacency_lists(F)
    
    VF,NI = igl.vertex_triangle_adjacency(F,n=V.shape[0])
    VF,VFi = igl.vertex_triangle_adjacency(F)
    
    F012 = F;
    F120 = np.roll(F012,1,axis=1)
    FF = np.vstack((F012,F120))
    F,IA,IC = igl.unique_simplices(FF)
    A = np.array([[1,2,3],[1,2,4],[3,2,1],[5,6,7]],dtype=np.int64)
    B = np.array([[1,2,3],[5,6,2],[1,2,4],[3,2,1]],dtype=np.int64)
    IA,LOCB = igl.ismember_rows(A,B)
    A = igl.adjacency_list(F)
    A = igl.adjacency_list(F,sorted=True)

def test_min_quad():
    V,F,T = single_tet()
    A = -igl.cotmatrix(V,F)
    B = np.zeros((V.shape[0],1),dtype=np.float64)
    known = np.array([1,2],dtype=np.int64)
    Y = np.array([-1,1],dtype=np.float64).reshape(-1, 1)
    Aeq = scipy.sparse.csc_matrix(([-1,1],([0,0],[0,3])),shape=(1,V.shape[0]))
    Beq = np.zeros((1,1),dtype=np.float64)
    Z = igl.min_quad_with_fixed(A,B,known,Y,Aeq,Beq,pd=True)
    data = igl.min_quad_with_fixed_data()
    igl.min_quad_with_fixed_precompute(A,known,Aeq,True,data)
    Z = igl.min_quad_with_fixed_solve(data,B,Y,Beq)
    
def test_volume():
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

def test_oriented_facets():
    V,F,T = single_tet()
    E = igl.oriented_facets(F)
    F = igl.oriented_facets(T)
    
    res,BF,EF,EMAP,BE = igl.is_edge_manifold(F)
    res,_,_,_,_ = igl.is_edge_manifold(F)

def test_matlab_format():
    V,F = triangulated_square()
    L = igl.cotmatrix(V,F)
    s = igl.matlab_format(V,"V")
    s = igl.matlab_format_index(F,"F")
    s = igl.matlab_format(L,"L")

def test_polar():
  # random randn 3x3 matrix
  np.random.seed(42)
  A = np.random.randn(3,3).astype(np.float64)
  igl.polar_svd(A)
  out = igl.polar_svd(A)
  R,T,_,_,_ = igl.polar_svd(A)
  R,T,sU,sS,sV = igl.polar_svd(A,include_reflections=True)

def test_remove():
    V,F = triangulated_square()
    SV,SVI,SVJ = igl.remove_duplicate_vertices(V,epsilon=1e-10)
    SV,SVI,SVJ,F = igl.remove_duplicate_vertices(V,F,epsilon=1e-10)

def test_project():
    V,F,_ = single_tet()
    model = np.eye(4).astype(np.float64)
    proj = np.eye(4).astype(np.float64)
    viewport = np.array([0,0,640,480],dtype=np.float64)
    win = igl.project(V,model,proj,viewport)
    scene = igl.unproject(win,model,proj,viewport)
    
    S = np.array([0,0,0],dtype=np.float64)
    D = np.array([0.2,0.2,0.2],dtype=np.float64)
    t,sqrD = igl.project_to_line(V,S,D)
    t,sqrD = igl.project_to_line_segment(V,S,D)

def test_boundary_loop():
    V,F,_ = single_tet()
    S,_ = igl.upsample_matrix(F,n=V.shape[0])
    S,_ = igl.loop_matrix(F,n=V.shape[0])
    V,F = igl.upsample(V,F,number_of_subdivs=1)
    V,F = igl.loop(V,F,number_of_subdivs=1)
    # remove first and last
    F = F[1:-1,:]
    L_all = igl.boundary_loop_all(F)
    L = igl.boundary_loop(F)
    UV = igl.map_vertices_to_circle(V,L)

def test_voxel():
    V,_,_ = single_tet()
    GV,side = igl.voxel_grid(V,s=10)
    GV,side = igl.voxel_grid(V,s=10,offset=0.1,pad_count=2)


def test_sample():
    V,F = igl.icosahedron()
    B,I,X = igl.random_points_on_mesh(10,V,F)
    point_indices, CH,CN,W = igl.octree(X)
    I = igl.knn(X,X,1,point_indices,CH,CN,W)
    B,FI,P = igl.blue_noise(V,F,0.5)

def test_curvature():
    V,F = igl.icosahedron()
    K = igl.gaussian_curvature(V,F)
    PD1,PD2,PV1,PV2,_ = igl.principal_curvature(V,F)
    PD1,PD2,PV1,PV2,_ = igl.principal_curvature(V,F,radius=10,useKring=False)

def test_geodesic():
    V,F = igl.icosahedron()
    VS = np.array([0],dtype=np.int64)
    VT = np.array([1],dtype=np.int64)
    D = igl.exact_geodesic(V,F,VS=VS,VT=VT)

def test_decimate():
    V,F = igl.icosahedron()
    dV,dF,J,I = igl.decimate(V,F)
    dV,dF,J,I = igl.qslim(V,F)

def test_parameterization():
    V,Q,E = igl.quad_grid(3,3);
    V,F = igl.triangulated_grid(3,3);
    # slim needs 3D data even if the problem is 2D
    V = np.c_[V, np.zeros(V.shape[0])]
    V_init = V[:,:2]
    V_init[:,0] = V_init[:,0] * 2
    b = np.array([0,1],dtype=np.int64)
    bc = V[b,:2]
    data = igl.slim_precompute(V,F,V_init,igl.MappingEnergyType.ARAP,b,bc,soft_p=1e10)
    U = igl.slim_solve(data,iter_num=1)
    
    data = igl.ARAPData()
    data.energy = igl.ARAPEnergyType.ARAP_ENERGY_TYPE_SPOKES_AND_RIMS
    V = V[:,:2]
    igl.arap_precomputation(V,F,V.shape[1],b,data)
    U = igl.arap_solve(bc,data,U)
    
    U,Q = igl.lscm(V,F,b,bc)


def test_implicit():
    res = np.array([3,3,3],dtype=np.int64)
    GV = igl.grid(res)
    S = np.sqrt(((GV - np.array([0.5,0.5,0.5],dtype=np.float64))**2).sum(axis=1))-0.25;
    V,F,E2V = igl.marching_cubes(S,GV,res[0],res[1],res[2])
    # unpack keys into (i,j,v) index triplets
    EV = np.array([[k & 0xFFFFFFFF, k >> 32, v] for k, v in E2V.items()], dtype=np.int64)

    h = igl.avg_edge_length(V,F)
    m0,m1,m2 = igl.moments(V,F)
    D = V[:,0]
    vals = np.array([D.min(),D.mean(),D.max()],dtype=np.float64)
    iV,iE,I = igl.isolines(V,F,S,vals)
    iB,iF,iE,I = igl.isolines_intrinsic(F,S,vals)
    
    
def test_kelvinlets():
    V,F = igl.icosahedron()
    x0 = V[0,:]
    f = np.array([0,0,1],dtype=np.float64)
    R = np.eye(3).astype(np.float64)
    U = igl.kelvinlets(V,x0,f,R,epsilon=1.0,falloff=1.0,brushType=igl.GRAB)
    
    SV = V[:,0]
    SF = igl.average_onto_faces(F,SV)
    SV = igl.average_onto_vertices(V,F,SF)

def test_polygons():
    P = [[0,1,2],[2,1,3,4]]
    I,C = igl.polygon_corners(P)
    Q = np.array([[0,1,2,3],[2,1,4,5]],dtype=np.int64)
    I,C = igl.polygon_corners(Q)
    F,J = igl.polygons_to_triangles(I,C)
    
def test_heat():
    V = np.array([[0,0,0],[1,0,0],[0,1,0],[0,0,1]],dtype=np.float64)
    F = np.array([[1,3,0],[3,2,0],[2,3,1]],dtype=np.int64)
    V,F = igl.upsample(V,F,number_of_subdivs=1)
    data = igl.HeatGeodesicsData()
    igl.heat_geodesics_precompute(V,F,t=1e-3,data=data)
    data = igl.HeatGeodesicsData()
    data.use_intrinsic_delaunay = True
    igl.heat_geodesics_precompute(V,F,data)
    gamma = np.array([0],dtype=np.int64)
    D = igl.heat_geodesics_solve(data,gamma)
    l = igl.edge_lengths(V,F)
    iV,iF,E,uE,EMAP,uE2E = igl.intrinsic_delaunay_triangulation(l,F)
    L,il,iF = igl.intrinsic_delaunay_cotmatrix(V,F)
    L = igl.cotmatrix_intrinsic(il,iF)
    M = igl.massmatrix_intrinsic(il,iF)
    
def test_nonmanifold():
    V,F = igl.icosahedron()
    FF,C = igl.bfs_orient(F)
    SF,SVI = igl.split_nonmanifold(F)
    SV,SF,SVI = igl.split_nonmanifold(V,F)

def test_biharmonic():
    V = np.array([[1,0,0],[0,1,0],[0,0,1],[-1,0,0],[0,-1,0],[0,0,-1]],dtype=np.float64)
    T = np.array([ [2,1,5,3], [0,1,5,2], [5,4,0,2], [2,5,4,3]],dtype=np.int64)
    S = [[0],[5]]
    W = igl.biharmonic_coordinates(V,T,S)

def test_bijective():
    # 2D triangulated grid
    V,F = igl.triangulated_grid(3,3)
    ear,ear_opp = igl.ears(F)
    # we don't have igl.flip_ears so construct it by hand
    res = np.array([3,3],dtype=np.int64)
    E,_,_ = igl.boundary_facets(F)
    F = E
    # add a 3rd column of 4s
    F = np.hstack((F,np.ones((F.shape[0],1),dtype=np.int64)*4))
    # boundary b
    b = np.array([0,1,2,3,5,6,7,8],dtype=np.int64)
    bc = V[b,:]
    bc[-1,:] = [0.5,0.5]
    U = igl.bijective_composite_harmonic_mapping(V,F,b,bc)


def test_copyleft():
    V = np.array([[0,0,-1],[2,0,-1],[0,2,-1],[1,1,1]],dtype=np.float64)
    T = np.array([[0,1,2,3]],dtype=np.int64)
    F,_,_ = igl.boundary_facets(T)
    V,F = igl.loop(V,F)
    
    dV,dF,J = igl.copyleft.progressive_hulls(V,F)
    

def test_cgal():
    # tetrahedron
    VA = np.array([[0,0,-1],[2,0,-1],[0,2,-1],[1,1,1]],dtype=np.float64)
    T = np.array([[0,1,2,3]],dtype=np.int64)
    FA,_,_ = igl.boundary_facets(T)
    # flip z
    VB = np.array([[0,0,1],[2,0,1],[0,2,1],[1,1,-1]],dtype=np.float64)
    FB = FA[:,::-1]
    IF,_,_,_,_ = igl.copyleft.cgal.intersect_other(VA,FA,VB,FB)
    IF,_,_,_,_ = igl.copyleft.cgal.intersect_other(VA,FA,VB,FB,detect_only=True,first_only=True)
    VC,FC,J = igl.copyleft.cgal.mesh_boolean(VA,FA,VB,FB,"union")
    H = igl.copyleft.cgal.convex_hull(VC)
    # concatenate A and B meshes
    VC = np.vstack((VA,VB))
    FC = np.vstack((FA,FB+VA.shape[0]))
    VV,FF,IF,J,IM = igl.copyleft.cgal.remesh_self_intersections(VC,FC)
    _,_,IF,_,_ = igl.copyleft.cgal.remesh_self_intersections(VC,FC,detect_only=True,first_only=True)
    
    p = np.array([0,0,0],dtype=np.float64)
    n = np.array([1,1,1],dtype=np.float64)
    VV,FF,J = igl.copyleft.cgal.intersect_with_half_space(VC,FC,p,n)
    equ = np.hstack((n,-n.dot(p)))
    VV,FF,J = igl.copyleft.cgal.intersect_with_half_space(VC,FC,equ)
    
    P = np.array([[0.5,0.5,0.0],[0.5,0.5,0.5]],dtype=np.float64)
    W = igl.copyleft.cgal.fast_winding_number(VA,FA,P)
    W = igl.copyleft.cgal.fast_winding_number(VA,FA,P,expansion_order=2,beta=2.0)
    
    VC,FC,D,J = igl.copyleft.cgal.trim_with_solid(VA,FA,VB,FB)
    
    _,I,X = igl.random_points_on_mesh(1000,VC,FC)
    N = igl.per_face_normals(VC,FC)
    N = N[I,:]
    point_indices, CH,CN,W = igl.octree(X)
    I = igl.knn(X,X,20,point_indices,CH,CN,W)
    A,T = igl.copyleft.cgal.point_areas(X,I,N)
    
def test_embree():
    # octahedron
    V = np.array([[1,0,0],[0,1,0],[0,0,1],[-1,0,0],[0,-1,0],[0,0,-1]],dtype=np.float64)
    F = np.array([[0,1,2], [0,2,4], [0,4,5], [0,5,1], [1,3,2], [1,5,3], [2,3,4], [3,5,4]],dtype=np.int64)
    N = igl.per_vertex_normals(V,F)
    ei = igl.embree.EmbreeIntersector();
    ei.init(V,F)
    S = igl.embree.ambient_occlusion(V,F,V,N,100)
    S = igl.embree.ambient_occlusion(ei,V,N,100)
    N = -N
    S = igl.embree.shape_diameter_function(V,F,V,N,100)
    S = igl.embree.shape_diameter_function(ei,V,N,100)
    origin = np.array([2,2,2],dtype=np.float64)
    direction = np.array([-2,-2,-2],dtype=np.float64)
    hit = ei.intersectRay_first(origin,direction)
    hits = ei.intersectRay(origin,direction)
    hits = ei.intersectRay(origin,direction,tnear=0,tfar=1)
    I,C = igl.embree.reorient_facets_raycast(V,F)

def test_tetgen():
    # octahedron
    V = np.array([[1,0,0],[0,1,0],[0,0,1],[-1,0,0],[0,-1,0],[0,0,-1]],dtype=np.float64)
    F = np.array([[0,1,2], [0,2,4], [0,4,5], [0,5,1], [1,3,2], [1,5,3], [2,3,4], [3,5,4]],dtype=np.int64)
    V,T,F,_,_,_,_,_,_ = igl.copyleft.tetgen.tetrahedralize(V,F,flags="Q")

def test_triangle():
    V = np.array([[0,0],[1,0],[1,1],[0,1]],dtype=np.float64)
    E = np.array([[0,1],[1,2],[2,3],[3,0]],dtype=np.int64)
    V,F,_,_,_ = igl.triangle.triangulate(V,E,flags="Qc")
    V,F,_,_,_ = igl.triangle.triangulate(V,E,flags="Q")
    V,F,_,_,_ = igl.triangle.triangulate(V,E,flags="Qqa0.1")
    V = np.array([[0,0,0],[1,0,0],[0,1,0],[0,0,1]],dtype=np.float64)
    F = np.array([[1,3,0],[3,2,0],[2,3,1]],dtype=np.int64)
    scaf_data = igl.triangle.SCAFData()
    b = np.array([0,1,2],dtype=np.int64)
    bc = np.array([[0,0],[1,0],[0,1]],dtype=np.float64)
    V_init = np.array([[0,0],[1,0],[0,1],[0.1,0.1]],dtype=np.float64)
    soft_p = 0;
    igl.triangle.scaf_precompute(V,F,V_init,igl.ARAP,b,bc,soft_p,scaf_data)
    L,rhs = igl.triangle.scaf_system(scaf_data)
    U = igl.triangle.scaf_solve(1,scaf_data)

def test_misc():
    V,F = igl.icosahedron()
    BV,BF = igl.bounding_box(V,pad=1.0)
    R,C,B = igl.circumradius(V,F)
    R = igl.inradius(V,F)
    K = igl.internal_angles(V,F)
    _,E,EMAP,_,_ = igl.unique_edge_map(F)
    L = igl.crouzeix_raviart_cotmatrix(V,F,E,EMAP)
    M = igl.crouzeix_raviart_massmatrix(V,F,E,EMAP)
    cuts = igl.cut_to_disk(F)
    V,F = igl.cylinder(10,10)
    VD,FD = igl.false_barycentric_subdivision(V,F)
    V,F,T = single_tet()
    theta, cos_theta = igl.dihedral_angles(V,T)
    L = igl.edge_lengths(V,T)
    A = igl.face_areas(V,T)
    theta, cos_theta = igl.dihedral_angles_intrinsic(L,A)
    D = igl.all_pairs_distances(V,V,squared=False)
    D = igl.all_pairs_distances(V,V,squared=True)



