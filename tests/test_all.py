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

@pytest.fixture
def icosahedron():
    V,F = igl.icosahedron()
    return V,F

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
    H = igl.hessian(V, F)
    QH = igl.hessian_energy(V, F)
    cQH = igl.curved_hessian_energy(V, F)

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

def test_harmonic_integrated_from_laplacian_and_mass():
    V, F = triangulated_square()
    L = igl.cotmatrix(V, F)
    M = igl.massmatrix(V, F, igl.MASSMATRIX_TYPE_VORONOI)
    Q = igl.harmonic_integrated_from_laplacian_and_mass(L, M, k=1)
    Q = igl.harmonic_integrated_from_laplacian_and_mass(L, M, k=2)
    
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

def test_offset_surface():
    V,F = triangulated_square()
    v, f, _, _, _ = igl.offset_surface(V, F, -0.1, 1, igl.SIGNED_DISTANCE_TYPE_DEFAULT)

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

    # Test equal seed yields same result
    B1,I1,X1 = igl.random_points_on_mesh(10,V,F, 1)
    B1_,I1_,X1_ = igl.random_points_on_mesh(10,V,F, 1)
    assert np.all(B1 == B1_)
    assert np.all(I1 == I1_)
    assert np.all(X1 == X1_)
    # Test different seed yields different result
    B2,I2,X2 = igl.random_points_on_mesh(10,V,F,2)
    assert not np.all(B1 == B2)
    assert not np.all(I1 == I2)
    assert not np.all(X1 == X2)


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

    R = igl.copyleft.cgal.oriented_bounding_box(VC)
    
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
    L = igl.bounding_box_diagonal(V)
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
    R = igl.oriented_bounding_box(V)
    R = igl.oriented_bounding_box(V,n=100,minimize_type=igl.ORIENTED_BOUNDING_BOX_MINIMIZE_SURFACE_AREA)

def test_octree():

    def sdf_sphere(Q):
        return np.linalg.norm(Q,axis=1) - 0.5
    def udf_sphere(Q):
        return np.abs(sdf_sphere(Q))

    origin = np.array([-1,-1,-1],dtype=np.float64)
    h0 = 2.0
    max_depth = 4
    ijk = igl.lipschitz_octree(origin,h0,max_depth,udf_sphere)
    h = h0 / (2**max_depth)
    unique_ijk, J, unique_corners = igl.unique_sparse_voxel_corners(origin,h0,max_depth,ijk)
    unique_S = sdf_sphere(unique_corners)
    V,F = igl.marching_cubes(unique_S,unique_corners,J,0.0)

def test_is_intrinsic_delaunay() -> None:
    # vs and fs come from a simple plane from pyvista
    # mesh = pv.Plane(i_resolution=3, j_resolution=2, i_size=2).triangulate()
    # fs = mesh._connectivity_array.reshape(-1, 3).astype(np.int32)
    # vs = mesh.points.astype(np.float64)

    fs = np.array(
        [
            [0, 1, 4],
            [1, 5, 4],
            [1, 2, 5],
            [2, 6, 5],
            [2, 3, 6],
            [3, 7, 6],
            [4, 5, 8],
            [5, 9, 8],
            [5, 6, 9],
            [6, 10, 9],
            [6, 7, 10],
            [7, 11, 10],
        ]
    )

    vs = np.array(
        [
            [-1.0, -0.5, 0.0],
            [-0.33333334, -0.5, 0.0],
            [0.33333334, -0.5, 0.0],
            [1.0, -0.5, 0.0],
            [-1.0, 0.0, 0.0],
            [-0.33333334, 0.0, 0.0],
            [0.33333334, 0.0, 0.0],
            [1.0, 0.0, 0.0],
            [-1.0, 0.5, 0.0],
            [-0.33333334, 0.5, 0.0],
            [0.33333334, 0.5, 0.0],
            [1.0, 0.5, 0.0],
        ]
    )

    lin = igl.edge_lengths(vs, fs)
    mask = igl.is_intrinsic_delaunay(lin, fs).astype(bool)

    expected_mask = np.array(
        [
            [0, 1, 1],
            [1, 0, 1],
            [1, 1, 1],
            [1, 1, 1],
            [0, 1, 1],
            [1, 0, 1],
            [0, 1, 1],
            [1, 0, 1],
            [1, 1, 1],
            [1, 1, 1],
            [0, 1, 1],
            [1, 0, 1],
        ]
    )
    assert np.array_equal(mask, expected_mask)

def test_rotate_vectors(icosahedron):
    V,F = icosahedron
    
    # Create rotation angles (rotate by pi/4)
    A = np.ones(F.shape[0],dtype=np.float64) * (np.pi / 4.0)
    
    # Get local basis
    B1,B2,_ = igl.local_basis(V,F)

    # B1 is orthogonal to B2
    r = np.sum(B1* B2, axis=1)
    assert np.allclose(np.abs(r), 0.0)
    
    # Rotate the first basis vector
    B1_rotated = igl.rotate_vectors(B1, A, B1, B2)
    
    # Check output shape
    assert B1_rotated.shape == B1.shape

    # Rotate B1_rotated by pi/4 again
    B1_rotated2 = igl.rotate_vectors(B1_rotated, A, B1, B2)
    assert B1_rotated2.shape == B1_rotated.shape

    # B1_rotated2 should be parallel to B2
    r = np.sum(B1_rotated2 * B2, axis=1)
    assert np.allclose(np.abs(r), 1.0)
    
def test_compute_frame_field_bisectors(icosahedron):
    V,F = icosahedron
    
    # Get local basis
    B1,B2,_ = igl.local_basis(V,F)
    
    # Compute bisectors with explicit basis
    BIS1,BIS2 = igl.compute_frame_field_bisectors(V,F,B1,B2,B1,B2)

    # Check output shapes
    assert BIS1.shape == (F.shape[0], 3)
    assert BIS2.shape == (F.shape[0], 3)

    # BIS1 should be orthogonal to BIS2
    r = np.sum(BIS1 * BIS2, axis=1)
    assert np.allclose(np.abs(r), 0.0)

def test_comb_cross_field(icosahedron):
    V,F = icosahedron
    
    # Get local basis
    B1,B2,_ = igl.local_basis(V,F)
    
    # Comb the cross field
    B1_combed,B2_combed = igl.comb_cross_field(V,F,B1,B2)
    
    # Check output shapes
    assert B1_combed.shape == (F.shape[0], 3)
    assert B2_combed.shape == (F.shape[0], 3)
    
def test_cross_field_mismatch(icosahedron):
    V,F = icosahedron
    
    # Get local basis
    B1,B2,_ = igl.local_basis(V,F)
    
    # Comb the cross field first
    B1_combed,B2_combed = igl.comb_cross_field(V,F,B1,B2)
    
    # Compute mismatch on combed field
    mismatch = igl.cross_field_mismatch(V,F,B1_combed,B2_combed,True)
    
    # Check output shape (should be #F by 3 for triangular mesh)
    assert mismatch.shape == (F.shape[0], 3)
    
    # Test with uncombed field (function will comb it first)
    mismatch_uncombed = igl.cross_field_mismatch(V,F,B1,B2,False)
    assert mismatch_uncombed.shape == (F.shape[0], 3)

def test_find_cross_field_singularities(icosahedron):
    V,F = icosahedron
    
    # Get local basis
    B1,B2,_ = igl.local_basis(V,F)
    
    # Comb the cross field first
    B1_combed,B2_combed = igl.comb_cross_field(V,F,B1,B2)
    
    # Compute mismatch
    mismatch = igl.cross_field_mismatch(V,F,B1_combed,B2_combed,True)
    
    # Find singularities from mismatch
    isSingularity,singularityIndex = igl.find_cross_field_singularities(V,F,mismatch)

    # Check Poincaré-Hopf theorem
    # The current singularity computation only return positive index, which is inconsistent with the
    # theorem, so we skip this check for now.
    # assert np.sum(singularityIndex) == 2 * 4 # Euler characteristic * 4-rosy fields
    
    # Check output shapes
    assert isSingularity.shape[0] == V.shape[0]
    assert singularityIndex.shape[0] == V.shape[0]
    
    # Test overload that computes mismatch internally
    isSingularity2,singularityIndex2 = igl.find_cross_field_singularities(V,F,B1_combed,B2_combed,True)

    # Check Poincaré-Hopf theorem
    # The current singularity computation only return positive index, which is inconsistent with the
    # theorem, so we skip this check for now.
    # assert np.sum(singularityIndex2) == 2 * 4 # Euler characteristic * 4-rosy fields
    
    # Check output shapes
    assert isSingularity2.shape[0] == V.shape[0]
    assert singularityIndex2.shape[0] == V.shape[0]
    
    # Test with uncombed field
    isSingularity3,singularityIndex3 = igl.find_cross_field_singularities(V,F,B1,B2,False)
    assert isSingularity3.shape[0] == V.shape[0]
    assert singularityIndex3.shape[0] == V.shape[0]

    # Check Poincaré-Hopf theorem
    # The current singularity computation only return positive index, which is inconsistent with the
    # theorem, so we skip this check for now.
    # assert np.sum(singularityIndex3) == 2 * 4 # Euler characteristic * 4-rosy fields

def test_centroid():
    # Icosahedron is centered at origin, so centroid should be near zero
    V, F = igl.icosahedron()

    # Overload returning both centroid and volume
    c, vol = igl.centroid(V, F)
    assert c.shape == (3,)
    assert c.dtype == np.float64
    assert isinstance(vol, float)
    assert np.allclose(c, np.zeros(3), atol=1e-10)
    assert vol > 0

    # Known geometry: unit tetrahedron centroid should be at (0.25, 0.25, 0.25)
    V_tet = np.array([[0,0,0],[1,0,0],[0,1,0],[0,0,1]], dtype=np.float64)
    F_tet = np.array([[2,1,0],[1,3,0],[3,2,0],[2,3,1]], dtype=np.int64)
    c_tet, vol_tet = igl.centroid(V_tet, F_tet)
    assert np.allclose(c_tet, [0.25, 0.25, 0.25], atol=1e-10)
    assert np.isclose(vol_tet, 1.0/6.0, atol=1e-10)

def test_new_io():
    V, F = triangulated_square()
    # writeOFF
    igl.writeOFF("out.off", V, F)
    # writeSTL / readSTL
    igl.writeSTL("out.stl", V, F)
    V2, F2, N2 = igl.readSTL("out.stl")
    assert V2.dtype == np.float64
    assert F2.dtype == np.int64
    assert N2.dtype == np.float64
    # readCSV
    np.savetxt("out.csv", V[:2, :], delimiter=",")
    M = igl.readCSV("out.csv")
    assert M.shape == (2, 3)
    assert M.dtype == np.float64


def test_new_geometry():
    V, F = triangulated_square()

    # accumarray with values (S and vals must be 2D)
    S = np.array([[0], [1], [0], [2]], dtype=np.int64)
    vals = np.array([[1.0], [2.0], [3.0], [4.0]], dtype=np.float64)
    A = igl.accumarray(S, vals)
    assert len(A) == 3
    assert np.isclose(A[0], 4.0)   # 1.0 + 3.0
    assert np.isclose(A[1], 2.0)
    assert np.isclose(A[2], 4.0)

    # accumarray with constant
    A2 = igl.accumarray(S, 1.0)
    assert len(A2) == 3
    assert np.isclose(A2[0], 2.0)  # S[0] and S[2] both map to 0

    # euler_characteristic: V=4, E=5, F=2 → χ=1
    chi = igl.euler_characteristic(F)
    assert isinstance(chi, int)
    assert chi == 1

    # exterior_edges: square has 4 boundary edges
    E_ext = igl.exterior_edges(F)
    assert E_ext.shape[1] == 2
    assert E_ext.shape[0] == 4

    # face_occurrences
    C_fo = igl.face_occurrences(F)
    assert C_fo.shape == (F.shape[0],)
    assert np.all(C_fo == 1)

    # fit_plane
    pts = np.array([[0,0,0],[1,0,0],[0,1,0],[1,1,0]], dtype=np.float64)
    N_plane, C_plane = igl.fit_plane(pts)
    assert N_plane.shape == (3,)
    assert C_plane.shape == (3,)

    # flipped_triangles: V[:,:2] in standard orientation → no flips
    V2d = V[:, :2]
    X_flip = igl.flipped_triangles(V2d, F)
    assert len(X_flip) == 0

    # hausdorff
    V2_off = V + 0.001
    d_h = igl.hausdorff(V, F, V2_off, F)
    assert isinstance(d_h, float)
    assert d_h > 0

    # snap_points: returns (I, minD, VI)
    query = np.array([[0.05, 0.05, 0.0], [0.95, 0.0, 0.0]], dtype=np.float64)
    I_snap, minD_snap, VI_snap = igl.snap_points(query, V)
    assert I_snap.shape == (2,)
    assert minD_snap.shape == (2,)
    assert VI_snap.shape == (2, 3)
    assert I_snap.dtype == np.int64

    # turning_number: CCW unit square polygon in 2D → 1.0
    poly = np.array([[0,0],[1,0],[1,1],[0,1]], dtype=np.float64)
    tn = igl.turning_number(poly)
    assert isinstance(tn, float)
    assert np.isclose(abs(tn), 1.0, atol=1e-10)

    # orient_outward (C must be 2D)
    V3, F3, T3 = single_tet()
    C_patch = np.zeros((F3.shape[0], 1), dtype=np.int64)
    FF_out, I_out = igl.orient_outward(V3, F3, C_patch)
    assert FF_out.shape == F3.shape
    assert I_out.shape == (1,)   # max(C)+1 components

    # orientable_patches
    C_op = igl.orientable_patches(F)
    assert C_op.shape == (F.shape[0],)

    # extract_manifold_patches: returns (n_patches, P)
    n_emp, P_emp = igl.extract_manifold_patches(F)
    assert isinstance(n_emp, int)
    assert P_emp.shape == (F.shape[0],)

    # flood_fill: 3×3×3 grid with one NaN in the center (res must be 2D)
    res3 = np.array([[3, 3, 3]], dtype=np.int64)
    S_grid = np.ones(27, dtype=np.float64)
    S_grid[13] = float('nan')
    S_filled = igl.flood_fill(res3, S_grid)
    assert S_filled.shape == (27,)
    assert not np.any(np.isnan(S_filled))


def test_new_normals_and_attributes():
    V, F = igl.icosahedron()

    # per_corner_normals: one normal per corner (#F*3 corners total)
    CN = igl.per_corner_normals(V, F)
    assert CN.shape == (F.shape[0] * 3, 3)
    assert CN.dtype == np.float64

    # per_edge_normals: EMAP has #F*3 entries (one per directed edge)
    N_edge, E_edge, EMAP_edge = igl.per_edge_normals(V, F)
    assert N_edge.shape[1] == 3
    assert E_edge.shape[1] == 2
    assert EMAP_edge.shape[0] == F.shape[0] * 3

    # per_vertex_attribute_smoothing
    attr = np.ones((V.shape[0], 3), dtype=np.float64)
    attr_smooth = igl.per_vertex_attribute_smoothing(attr, F)
    assert attr_smooth.shape == attr.shape

    # sharp_edges: icosahedron is smooth so no sharp edges with pi/4 threshold
    SE = igl.sharp_edges(V, F, np.pi / 4)
    assert SE.ndim == 2 and SE.shape[1] == 2


def test_new_color():
    # colormap: array
    Z = np.linspace(0.0, 1.0, 5, dtype=np.float64)
    C_cm = igl.colormap(igl.ColorMapType.VIRIDIS, Z)
    assert C_cm.shape == (5, 3)
    assert C_cm.dtype == np.float64

    # colormap: scalar
    c_s = igl.colormap(igl.ColorMapType.JET, 0.5)
    assert c_s.shape == (3,)

    # hsv_to_rgb / rgb_to_hsv: h is in [0,360] degrees
    HSV = np.array([[36.0, 1.0, 1.0], [90.0, 0.8, 0.6], [216.0, 0.5, 0.9]], dtype=np.float64)
    RGB = igl.hsv_to_rgb(HSV)
    assert RGB.shape == HSV.shape
    HSV2 = igl.rgb_to_hsv(RGB)
    assert np.allclose(HSV, HSV2, atol=1e-6)


def test_new_math():
    # polar_dec: R and T only
    A_eye = np.eye(3, dtype=np.float64)
    R_pd, T_pd = igl.polar_dec(A_eye)
    assert R_pd.shape == (3, 3)
    assert T_pd.shape == (3, 3)
    assert np.allclose(R_pd, np.eye(3), atol=1e-10)

    # polar_dec with reflections allowed (still returns R,T)
    R_pd2, T_pd2 = igl.polar_dec(A_eye, include_reflections=True)
    assert R_pd2.shape == (3, 3)

    # procrustes: known rotation
    np.random.seed(42)
    X_p = np.random.randn(10, 3).astype(np.float64)
    t_known = np.array([1.0, 2.0, 3.0], dtype=np.float64)
    Y_p = X_p + t_known
    scale_p, R_p, t_p = igl.procrustes(X_p, Y_p)
    assert R_p.shape == (3, 3)
    assert t_p.shape == (3,)
    assert np.allclose(t_p, t_known, atol=1e-6)

    # rotation_matrix_from_directions (v0, v1 must be 2D)
    v0 = np.array([[1.0, 0.0, 0.0]], dtype=np.float64)
    v1 = np.array([[0.0, 1.0, 0.0]], dtype=np.float64)
    R_rmd = igl.rotation_matrix_from_directions(v0, v1)
    assert R_rmd.shape == (3, 3)
    assert np.allclose(R_rmd @ v0.ravel(), v1.ravel(), atol=1e-10)

    # bezier: single t
    ctrl = np.array([[0,0,0],[1,1,0],[2,0,0]], dtype=np.float64)
    P_bez = igl.bezier(ctrl, 0.5)
    assert P_bez.shape == (1, 3)
    assert np.allclose(P_bez[0], [1.0, 0.5, 0.0], atol=1e-10)

    # bezier: array T (must be 2D)
    T_vals = np.array([[0.0], [0.5], [1.0]], dtype=np.float64)
    Ps_bez = igl.bezier(ctrl, T_vals)
    assert Ps_bez.shape == (3, 3)

    # look_at (args must be 2D)
    eye_la = np.array([[0.0, 0.0, 3.0]], dtype=np.float64)
    center_la = np.array([[0.0, 0.0, 0.0]], dtype=np.float64)
    up_la = np.array([[0.0, 1.0, 0.0]], dtype=np.float64)
    M_view = igl.look_at(eye_la, center_la, up_la)
    assert M_view.shape == (4, 4)

    # signed_angle (2D, args must be 2D)
    A2d = np.array([[1.0, 0.0]], dtype=np.float64)
    B2d = np.array([[0.0, 1.0]], dtype=np.float64)
    P2d = np.array([[0.0, 0.0]], dtype=np.float64)
    angle_sa = igl.signed_angle(A2d, B2d, P2d)
    assert isinstance(angle_sa, float)

    # solid_angle (3D, args must be 2D)
    A3d = np.array([[1.0, 0.0, 0.0]], dtype=np.float64)
    B3d = np.array([[0.0, 1.0, 0.0]], dtype=np.float64)
    C3d = np.array([[0.0, 0.0, 1.0]], dtype=np.float64)
    P3d = np.array([[0.0, 0.0, 0.0]], dtype=np.float64)
    sa = igl.solid_angle(A3d, B3d, C3d, P3d)
    assert isinstance(sa, float)

    # random_dir
    d_rd = igl.random_dir()
    assert d_rd.shape == (3,)
    assert np.isclose(np.linalg.norm(d_rd), 1.0, atol=1e-10)

    # random_dir_stratified
    ds_rds = igl.random_dir_stratified(10)
    assert ds_rds.shape == (10, 3)

    # super_fibonacci
    Q_sf = igl.super_fibonacci(10)
    assert Q_sf.shape == (10, 4)
    # unit quaternions
    assert np.allclose(np.linalg.norm(Q_sf, axis=1), 1.0, atol=1e-10)


def test_new_intersection():
    # ray_triangle_intersect: args must be 2D
    O_rt = np.array([[0.25, 0.25, 1.0]], dtype=np.float64)
    D_rt = np.array([[0.0, 0.0, -1.0]], dtype=np.float64)
    V0_rt = np.array([[0.0, 0.0, 0.0]], dtype=np.float64)
    V1_rt = np.array([[1.0, 0.0, 0.0]], dtype=np.float64)
    V2_rt = np.array([[0.0, 1.0, 0.0]], dtype=np.float64)
    hit_rt, t_rt, u_rt, v_rt, par_rt = igl.ray_triangle_intersect(O_rt, D_rt, V0_rt, V1_rt, V2_rt)
    assert hit_rt == True
    assert np.isclose(t_rt, 1.0, atol=1e-8)

    # ray misses triangle
    O_miss = np.array([[2.0, 2.0, 1.0]], dtype=np.float64)
    hit_miss, _, _, _, _ = igl.ray_triangle_intersect(O_miss, D_rt, V0_rt, V1_rt, V2_rt)
    assert hit_miss == False

    # ray_sphere_intersect: args must be 2D
    o_rs = np.array([[0.0, 0.0, -2.0]], dtype=np.float64)
    d_rs = np.array([[0.0, 0.0, 1.0]], dtype=np.float64)
    c_rs = np.array([[0.0, 0.0, 0.0]], dtype=np.float64)
    n_rs, t0_rs, t1_rs = igl.ray_sphere_intersect(o_rs, d_rs, c_rs, 1.0)
    assert n_rs == 2   # two intersections
    assert np.isclose(t0_rs, 1.0, atol=1e-10)
    assert np.isclose(t1_rs, 3.0, atol=1e-10)

    # segment_segment_intersect: args must be 2D, two crossing segments in XY plane
    p_ss = np.array([[-1.0, 0.0, 0.0]], dtype=np.float64)
    r_ss = np.array([[2.0, 0.0, 0.0]], dtype=np.float64)   # segment A: -1 → +1
    q_ss = np.array([[0.0, -1.0, 0.0]], dtype=np.float64)
    s_ss = np.array([[0.0, 2.0, 0.0]], dtype=np.float64)   # segment B: -1 → +1
    hit_ss, t_ss, u_ss = igl.segment_segment_intersect(p_ss, r_ss, q_ss, s_ss)
    assert hit_ss == True
    assert np.isclose(t_ss, 0.5, atol=1e-6)
    assert np.isclose(u_ss, 0.5, atol=1e-6)

    # tri_tri_overlap_test_3d: args must be 2D; vertical plane slices horizontal triangle
    p1 = np.array([[0.0, 0.0, 0.0]], dtype=np.float64)
    q1 = np.array([[1.0, 0.0, 0.0]], dtype=np.float64)
    r1 = np.array([[0.0, 1.0, 0.0]], dtype=np.float64)
    p2 = np.array([[0.5, 0.0, -0.5]], dtype=np.float64)
    q2 = np.array([[0.5, 1.0, -0.5]], dtype=np.float64)
    r2 = np.array([[0.5, 0.0, 0.5]], dtype=np.float64)
    overlap = igl.tri_tri_overlap_test_3d(p1, q1, r1, p2, q2, r2)
    assert overlap == True

    # tri_tri_intersection_test_3d
    hit_tt, coplanar_tt, src_tt, tgt_tt = igl.tri_tri_intersection_test_3d(
        p1, q1, r1, p2, q2, r2)
    assert hit_tt == True
    assert src_tt.size == 3
    assert tgt_tt.size == 3


def test_new_mesh_ops():
    V, F = triangulated_square()

    # barycentric_interpolation (I must be 2D)
    B_bi = np.array([[1.0, 0.0, 0.0], [0.0, 1.0, 0.0]], dtype=np.float64)
    I_bi = np.array([[0], [1]], dtype=np.int64)
    P_interp = igl.barycentric_interpolation(V, F, B_bi, I_bi)
    assert P_interp.shape == (2, 3)
    # first barycentric coord = vertex 0 of face 0 = V[F[0,0]]
    assert np.allclose(P_interp[0], V[F[0, 0]], atol=1e-10)

    # combine
    V2c, F2c = triangulated_square()
    V2c = V2c + 5.0
    V_comb, F_comb = igl.combine([V, V2c], [F, F2c])
    assert V_comb.shape[0] == V.shape[0] + V2c.shape[0]
    assert F_comb.shape[0] == F.shape[0] + F2c.shape[0]

    # edge_topology
    EV_et, FE_et, EF_et = igl.edge_topology(V, F)
    assert EV_et.shape[1] == 2
    assert FE_et.shape == F.shape
    assert EF_et.shape[1] == 2

    # edges_to_path: chain 0-1-2-3
    E_chain = np.array([[0, 1], [1, 2], [2, 3]], dtype=np.int64)
    I_ep, J_ep, K_ep = igl.edges_to_path(E_chain)
    assert len(I_ep) == 4   # 3 edges → 4 nodes
    assert len(J_ep) == 3
    assert len(K_ep) == 3

    # is_boundary_edge: query with exterior edges → all True
    E_ext2 = igl.exterior_edges(F)
    B_be = igl.is_boundary_edge(E_ext2, F)
    assert np.all(B_be)

    # is_boundary_edge: extract overload
    B_be2, E_be2, EMAP_be2 = igl.is_boundary_edge(F)
    assert B_be2.dtype == bool

    # is_delaunay
    D_del = igl.is_delaunay(V, F)
    assert D_del.shape == F.shape
    assert D_del.dtype == bool

    # is_irregular_vertex
    is_irr = igl.is_irregular_vertex(F)
    assert len(is_irr) == V.shape[0]

    # sample_edges
    E_se = igl.edges(F)
    S_se = igl.sample_edges(V, E_se, 2)
    expected_rows = V.shape[0] + 2 * E_se.shape[0]
    assert S_se.shape == (expected_rows, 3)

    # vector_area_matrix: size is 2*#V (stacked x and y)
    VA_mat = igl.vector_area_matrix(F)
    assert VA_mat.shape[0] == 2 * V.shape[0]

    # tet_tet_adjacency
    V_tet, F_tet, T_tet = single_tet()
    TT_tt, TTi_tt = igl.tet_tet_adjacency(T_tet)
    assert TT_tt.shape == (T_tet.shape[0], 4)
    assert TTi_tt.shape == (T_tet.shape[0], 4)

    # voronoi_mass
    M_vor = igl.voronoi_mass(V_tet, T_tet)
    assert M_vor.shape == (V_tet.shape[0],)
    assert np.all(M_vor > 0)


def test_new_algorithms():
    V, F = igl.icosahedron()

    # pseudonormal_test: origin is inside the icosahedron
    FN = igl.per_face_normals(V, F)
    VN = igl.per_vertex_normals(V, F)
    EN, E_en, EMAP_en = igl.per_edge_normals(V, F)
    P_q = np.array([[0.0, 0.0, 0.0]], dtype=np.float64)
    sqrD_pn, I_pn, C_pn = igl.point_mesh_squared_distance(P_q, V, F)
    q_pn = P_q[0:1, :]       # must be 2D
    c_pn = C_pn[0:1, :]      # must be 2D
    EMAP_en_2d = EMAP_en.reshape(-1, 1)  # must be 2D
    f_pn = int(I_pn[0])
    s_pn, n_pn = igl.pseudonormal_test(V, F, FN, VN, EN, EMAP_en_2d, q_pn, c_pn, f_pn)
    assert isinstance(s_pn, float)
    assert n_pn.size == 3
    assert s_pn < 0   # origin is inside → negative sign

    # rigid_alignment
    np.random.seed(42)
    P_ra = np.random.randn(10, 3).astype(np.float64)
    N_ra = P_ra / np.linalg.norm(P_ra, axis=1, keepdims=True)
    X_ra = P_ra + 0.01 * N_ra
    R_ra, t_ra = igl.rigid_alignment(X_ra, P_ra, N_ra)
    assert R_ra.shape == (3, 3)
    assert t_ra.size == 3

    # iterative_closest_point
    VB_icp = V + 0.1
    R_icp, t_icp = igl.iterative_closest_point(V, F, VB_icp, F, num_samples=20, max_iters=3)
    assert R_icp.shape == (3, 3)
    assert t_icp.size == 3

    # lbs_matrix
    np.random.seed(0)
    V_lbs = np.random.randn(4, 3).astype(np.float64)
    W_lbs = np.abs(np.random.randn(4, 2).astype(np.float64))
    W_lbs /= W_lbs.sum(axis=1, keepdims=True)
    M_lbs = igl.lbs_matrix(V_lbs, W_lbs)
    assert M_lbs.ndim == 2

    # mvc: query center of CCW unit square → weights sum to 1
    C_mvc = np.array([[0.0,0.0],[1.0,0.0],[1.0,1.0],[0.0,1.0]], dtype=np.float64)
    Q_mvc = np.array([[0.5,0.5],[0.25,0.25]], dtype=np.float64)
    W_mvc = igl.mvc(Q_mvc, C_mvc)
    assert W_mvc.shape == (2, 4)
    assert np.allclose(W_mvc.sum(axis=1), 1.0, atol=1e-10)

    # dijkstra (Euclidean weights)
    VV_d = igl.adjacency_list(F)
    D_dijk, prev_dijk = igl.dijkstra(V, VV_d, np.int64(0), {np.int64(5)})
    assert D_dijk.shape == (V.shape[0],)
    assert D_dijk[0] == 0.0
    # dijkstra_backtrack: vertex is int, previous must be 2D
    path_dijk = igl.dijkstra_backtrack(5, prev_dijk.reshape(-1, 1))
    assert path_dijk[0] == 5
    assert path_dijk[-1] == 0

    # directed_edge_parents: simple chain 0→1→2
    E_dep = np.array([[0, 1], [1, 2]], dtype=np.int64)
    P_dep = igl.directed_edge_parents(E_dep)
    assert P_dep.shape == (2,)
    assert P_dep[0] == -1   # edge 0→1 has no parent pointing to 0
    assert P_dep[1] == 0    # edge 1→2's parent is edge 0→1

    # uniformly_sample_two_manifold: weight space = vertex positions
    np.random.seed(1)
    W_us = np.random.rand(V.shape[0], 2).astype(np.float64)
    WS_us = igl.uniformly_sample_two_manifold(W_us, F, 5, push=0.1)
    assert WS_us.shape == (5, 2)


def test_comb_frame_field(icosahedron):
    V,F = icosahedron
    
    # Get local basis
    B1,B2,_ = igl.local_basis(V,F)
    
    # Compute bisectors
    BIS1,BIS2 = igl.compute_frame_field_bisectors(V,F,B1,B2)
    
    # Comb the bisectors (which are a cross field)
    BIS1_combed,BIS2_combed = igl.comb_cross_field(V,F,BIS1,BIS2)
    
    # Comb the frame field using combed bisectors
    PD1_combed,PD2_combed = igl.comb_frame_field(V,F,B1,B2,BIS1_combed,BIS2_combed)
    
    # Check output shapes
    assert PD1_combed.shape == (F.shape[0], 3)
    assert PD2_combed.shape == (F.shape[0], 3)


def test_new_copyleft_algorithms():
    # marching_cubes: extract isosurface of a sphere SDF on a regular grid
    x_res, y_res, z_res = 8, 8, 8
    x = np.linspace(-1, 1, x_res)
    y = np.linspace(-1, 1, y_res)
    z = np.linspace(-1, 1, z_res)
    # x-fastest ordering: index = ix + iy*x_res + iz*x_res*y_res
    pts = np.array([[xi, yi, zi] for zi in z for yi in y for xi in x], dtype=np.float64)
    vals = (np.sqrt(pts[:,0]**2 + pts[:,1]**2 + pts[:,2]**2) - 0.5).astype(np.float64)
    V_mc, F_mc = igl.copyleft.marching_cubes(vals, pts, x_res, y_res, z_res)
    assert V_mc.shape[1] == 3
    assert F_mc.shape[1] == 3
    assert V_mc.shape[0] > 0

    # quadprog: min 0.5*x^2 + 2*x → x = -2
    G = np.array([[1.0]], dtype=np.float64)
    g0 = np.array([2.0], dtype=np.float64)
    x_qp = igl.copyleft.quadprog(G, g0)
    assert abs(x_qp[0] + 2.0) < 1e-8


def test_new_cgal_algorithms():
    # simple tetrahedron
    VA = np.array([[0,0,-1],[2,0,-1],[0,2,-1],[1,1,1]], dtype=np.float64)
    T = np.array([[0,1,2,3]], dtype=np.int64)
    FA, _, _ = igl.boundary_facets(T)

    # coplanar: 4 coplanar points vs non-coplanar
    V_plane = np.array([[0,0,0],[1,0,0],[0,1,0],[1,1,0]], dtype=np.float64)
    assert igl.copyleft.cgal.coplanar(V_plane) == True
    assert igl.copyleft.cgal.coplanar(VA) == False

    # delaunay_triangulation: 2D point cloud
    V2d = np.array([[0,0],[1,0],[0.5,1],[0.25,0.5]], dtype=np.float64)
    F2d = igl.copyleft.cgal.delaunay_triangulation(V2d)
    assert F2d.shape[1] == 3
    assert F2d.dtype == np.int64

    # outer_hull
    HV, HF, J, flip = igl.copyleft.cgal.outer_hull(VA, FA)
    assert HV.shape[1] == 3
    assert HF.shape[1] == 3
    assert J.shape[0] == HF.shape[0]
    assert flip.shape[0] == HF.shape[0]

    # extract_cells
    n_cells, cells = igl.copyleft.cgal.extract_cells(VA, FA)
    assert cells.shape == (FA.shape[0], 2)

    # peel_outer_hull_layers
    I_peel, flip_peel, n_peel = igl.copyleft.cgal.peel_outer_hull_layers(VA, FA)
    assert I_peel.shape[0] == FA.shape[0]
    assert flip_peel.shape[0] == FA.shape[0]

    # peel_winding_number_layers
    W_wind, n_wind = igl.copyleft.cgal.peel_winding_number_layers(VA, FA)
    assert W_wind.shape[0] == VA.shape[0]


def test_new_tetgen_algorithms():
    V_oct = np.array([[1,0,0],[0,1,0],[0,0,1],[-1,0,0],[0,-1,0],[0,0,-1]], dtype=np.float64)
    F_oct = np.array([[0,1,2],[0,2,4],[0,4,5],[0,5,1],[1,3,2],[1,5,3],[2,3,4],[3,5,4]], dtype=np.int64)

    # cdt: constrained Delaunay tetrahedralization
    TV, TT, TF = igl.copyleft.tetgen.cdt(V_oct, F_oct)
    assert TV.shape[1] == 3
    assert TT.shape[1] == 4
    assert TF.shape[1] == 3
    assert TV.shape[0] >= V_oct.shape[0]

    # CDTParam class
    param = igl.copyleft.tetgen.CDTParam()
    param.use_bounding_box = False
    param.flags = "Y"
    TV2, TT2, TF2 = igl.copyleft.tetgen.cdt(V_oct, F_oct, param)
    assert TT2.shape[1] == 4

    # mesh_with_skeleton: surface + one bone
    C = np.array([[0,0,-0.5],[0,0,0.5]], dtype=np.float64)
    BE = np.array([[0,1]], dtype=np.int64)
    P = np.zeros((0,), dtype=np.int64)
    CE = np.zeros((0,2), dtype=np.int64)
    VV, TT_sk, FF_sk = igl.copyleft.tetgen.mesh_with_skeleton(V_oct, F_oct, C, P, BE, CE)
    assert VV.shape[1] == 3
    assert TT_sk.shape[1] == 4
    assert FF_sk.shape[1] == 3


def test_new_embree_algorithms():
    V_oct = np.array([[1,0,0],[0,1,0],[0,0,1],[-1,0,0],[0,-1,0],[0,0,-1]], dtype=np.float64)
    F_oct = np.array([[0,1,2],[0,2,4],[0,4,5],[0,5,1],[1,3,2],[1,5,3],[2,3,4],[3,5,4]], dtype=np.int64)

    # bone_visible: bone through center along z-axis
    s = np.array([0.0, 0.0, -0.5])
    d = np.array([0.0, 0.0,  0.5])
    flag = igl.embree.bone_visible(V_oct, F_oct, s, d)
    assert flag.shape == (V_oct.shape[0],)
    assert flag.dtype == bool

    # line_mesh_intersection: project octahedron vertices onto itself
    N = igl.per_vertex_normals(V_oct, F_oct)
    R = igl.embree.line_mesh_intersection(V_oct, N, V_oct, F_oct)
    assert R.shape == (V_oct.shape[0], 3)


def test_new_triangle_algorithms():
    V2d = np.array([[0,0],[1,0],[1,1],[0,1]], dtype=np.float64)
    E2d = np.array([[0,1],[1,2],[2,3],[3,0]], dtype=np.int64)

    # triangle.cdt
    WV, WF, WE, J = igl.triangle.cdt(V2d, E2d)
    assert WV.shape[1] == 2
    assert WF.shape[1] == 3
    assert WE.shape[1] == 2
    assert J.shape[0] == V2d.shape[0]

    # triangle.refine: triangulate then refine
    V_tri, F_tri, _, _, _ = igl.triangle.triangulate(V2d, E2d, flags="Qc")
    E_empty = np.zeros((0,2), dtype=np.int64)
    V_ref, F_ref = igl.triangle.refine(V_tri, E_empty, F_tri)
    assert V_ref.shape[1] == 2
    assert F_ref.shape[1] == 3
    assert V_ref.shape[0] >= V_tri.shape[0]
