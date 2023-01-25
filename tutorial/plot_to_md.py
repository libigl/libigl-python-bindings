import meshplot
import json

first = True
meshplot.website()

def mp_to_md(self):
    global first
    if first:
        first = False
        res = self.to_html(imports=True, html_frame=False)
    else:
        res = self.to_html(imports=False, html_frame=False)

    return res

def lis_to_md(self):
    res = ""
    for row in self:
        for e in row:
            res += e.to_html()
    return res


def sp_to_md(self):
    global first
    if first:
        first = False
        res = self.to_html(imports=True, html_frame=False)
    else:
        res = self.to_html(imports=False, html_frame=False)

    return res

get_ipython().display_formatter.formatters["text/html"].for_type(meshplot.Viewer, mp_to_md)
get_ipython().display_formatter.formatters["text/html"].for_type(meshplot.Subplot, sp_to_md)

#get_ipython().display_formatter.formatters["text/html"].for_type(list, lis_to_md)
