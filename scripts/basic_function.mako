% for inc in includes:
#include ${inc}
% endfor
% for func in functions:
#include <igl/${func['orgname']}.h>

const char* ds_${func['name']} = R"igl_Qu8mg5v7(
${func['docstring']}
)igl_Qu8mg5v7";

npe_function(${func['name']})
npe_doc(ds_${func['name']})

% for p in func['in_parameters'][:]:
npe_arg(${p['name']}, ${p['type']})
% endfor


npe_begin_code()

% for p in func['out_parameters'][:]:
% if 'dense' in p['type']:
  EigenDense<npe_Scalar_> ${p['name']};
% elif 'sparse' in p['type']:
  EigenSparse<npe_Scalar_> ${p['name']};
% else:
  ${p['type']} ${p['name']};
%endif
% endfor
% for n in func['namespaces']:
  ${n}::\
% endfor
${func['orgname']}(\
% for p in func['all_parameters'][:-1]:
${p['name']}, \
% endfor
${func['all_parameters'][-1]['name']});
% if len(func['out_parameters']) > 1:
  return std::make_tuple(\
% for p in func['out_parameters'][:-1]:
npe::move(${p['name']}), \
% endfor
npe::move(${func['out_parameters'][-1]['name']}));
% elif len(func['out_parameters']) == 1:
  return npe::move(${func['out_parameters'][0]['name']});
% else:
  return ;
% endif

npe_end_code()
% endfor


