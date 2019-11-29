from .Viewer import Viewer
import numpy as np
from ipywidgets import Output, HBox
import uuid

rendertype = "JUPYTER" # "OFFLINE"
def jupyter():
    global rendertype
    rendertype = "JUPYTER"

def offline():
    global rendertype
    rendertype = "OFFLINE"

def website():
    global rendertype
    rendertype = "WEBSITE"

class Subplot():
    def __init__(self, data, view, s):
        if data == None:
            self.rows = []
            self.hboxes = []
        else:
            self.rows = data.rows
            
        if s[0] != 1 or s[1] != 1:
            if data == None: # Intialize subplot array
                cnt = 0
                for r in range(s[0]):
                    row = []
                    for c in range(s[1]):
                        row.append(Output())
                        cnt += 1
                    self.rows.append(row)

                for r in self.rows:
                    hbox = HBox(r)
                    if rendertype == "JUPYTER":
                        display(hbox)
                    self.hboxes.append(hbox)

            out = self.rows[int(s[2]/s[1])][s[2]%s[1]]
            if rendertype == "JUPYTER":
                with out:
                    display(view._renderer)
            self.rows[int(s[2]/s[1])][s[2]%s[1]] = view
            
    def save(self, filename=""):
        if filename == "":
            uid = str(uuid.uuid4()) + ".html"
        else:
            filename = filename.replace(".html", "")
            uid = filename + '.html'
        
        s = ""
        imports = True
        for r in self.rows:
            for v in r:
                s1 = v.to_html(imports=imports, html_frame=False)
                s = s + s1
                imports = False
            
        s = "<html>\n<body>\n" + s + "\n</body>\n</html>"
        with open(uid, "w") as f:
            f.write(s)
        print("Plot saved to file %s."%uid)  

    def to_html(self, imports=True, html_frame=True):
        s = ""
        for r in self.rows:
            for v in r:
                s1 = v.to_html(imports=imports, html_frame=html_frame)
                s = s + s1
                imports = False

        return s

def plot(v, f=None, c=None, uv=None, shading={}, size=[], plot=None, return_plot=True, filename=""):#, return_id=False):
    if len(size) == 2:
        shading["width"] = size[0]
        shading["height"] = size[1]
    else:
        shading["width"] = 700
        shading["height"] = 700
    if not plot:
        view = Viewer(shading)
    else:
        view = plot
        view.reset()
    if type(f) == type(None): # Plot pointcloud
        obj_id = view.add_points(v, c, shading=shading)
    elif type(f) == np.ndarray and len(f.shape) == 2 and f.shape[1] == 2: # Plot edges
        obj_id = view.add_edges(v, f, shading=shading)
    else: # Plot mesh
        obj_id = view.add_mesh(v, f, c, uv=uv, shading=shading)

    if not plot and rendertype == "JUPYTER":
        display(view._renderer)

    if rendertype == "OFFLINE":
        view.save(filename)

    if return_plot or rendertype == "WEBSITE":
        return view

def subplot(v, f=None, c=None, uv=None, shading={}, size=[], s=[1, 1, 0], data=None):
    if len(size) == 2:
        shading["width"] = size[0]
        shading["height"] = size[1]
    else:
        shading["width"] = 370
        shading["height"] = 370
    view = Viewer(shading)
    if type(f) == type(None): # Plot pointcloud
        obj_id = view.add_points(v, c, shading=shading)
    elif type(f) == np.ndarray and len(f.shape) == 2 and f.shape[1] == 2: # Plot edges
        obj_id = view.add_edges(v, f, shading=shading)
    else: # Plot mesh
        obj_id = view.add_mesh(v, f, c, uv=uv, shading=shading)
        
    subplot = Subplot(data, view, s)
    if data == None or rendertype == "WEBSITE":
        return subplot
