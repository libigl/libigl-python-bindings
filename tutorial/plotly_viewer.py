import numpy as np

import plotly.offline as plotly
import plotly.graph_objs as go


#Necessary for the notebook
plotly.init_notebook_mode(connected=True)


def create_plot_mesh_and_layout(vertices, connectivity, function, colorscale):
    x = vertices[:,0]
    y = vertices[:,1]

    if vertices.shape[1] == 3:
        z = vertices[:,2]
    else:
        z = np.zeros(x.shape, dtype=x.dtype)

    if connectivity.shape[1] == 3:
        f = connectivity
    else:
        #Convert a tet-mesh into face based triangles.
        f = np.ndarray([len(connectivity)*4, 3], dtype=np.int64)
        for i in range(len(connectivity)):
            f[i*4+0] = np.array([connectivity[i][1], connectivity[i][0], connectivity[i][2]])
            f[i*4+1] = np.array([connectivity[i][0], connectivity[i][1], connectivity[i][3]])
            f[i*4+2] = np.array([connectivity[i][1], connectivity[i][2], connectivity[i][3]])
            f[i*4+3] = np.array([connectivity[i][2], connectivity[i][0], connectivity[i][3]])

    mesh = go.Mesh3d(x=x, y=y, z=z,
                     i=f[:,0], j=f[:,1], k=f[:,2],
                     contour=dict(show=True, color='#fff'),
                     hoverinfo="all")

    if function is not None:
        mesh['flatshading']=True
        if len(function.shape) == 1 or function.shape[1] == 1 or function.shape[0] == 1:
            mesh['intensity']=function
            mesh['colorscale']='Viridis' if colorscale is None else colorscale
        else:
            assert(function.shape[1] == 3)
            if function.shape[0] == vertices.shape[0]:
                mesh['vertexcolor']=function
            elif function.shape[0] == f.shape[0]:
                mesh['facecolor']=function
            else:
                assert(False)
    else:
        mesh['color'] = 'rgb(255,235,80)'
        mesh['flatshading']=False


    layout = go.Layout(scene=go.layout.Scene(
        aspectmode='data',

        xaxis=dict(
            autorange=True,
            showgrid=False,
            zeroline=False,
            showline=False,
            ticks='',
            showticklabels=False
        ),
        yaxis=dict(
            autorange=True,
            showgrid=False,
            zeroline=False,
            showline=False,
            ticks='',
            showticklabels=False
        ),
        zaxis=dict(
            autorange=True,
            showgrid=False,
            zeroline=False,
            showline=False,
            ticks='',
            showticklabels=False
        )
    ))

    return mesh, layout


def plot(vertices, connectivity, function=None, colorscale=None, camera=None):
    mesh, layout = create_plot_mesh_and_layout(vertices, connectivity, function, colorscale)
    if camera is not None:
        layout.scene.camera = camera

    fig = go.Figure(data=[mesh], layout=layout)

    plotly.iplot(fig)
