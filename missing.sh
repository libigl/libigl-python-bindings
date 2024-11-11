#!/bin/bash
#
already=$(ls src/*.cpp | sed -e "s/src\/\(.*\).cpp$/\1/g")
skip="
ARAPEnergyType
EPS
Hit
IGL_ASSERT
LinSpaced
PI
cat
colon
cumsum
decimate_callback_types
find
get_seconds
igl_inline
list_to_matrix
matrix_to_list
min_quad_with_fixed.impl
parallel_for
pathinfo
placeholders
quadric_binary_plus_operator
redux
repdiag
repmat
rotation_matrix_from_directions
setdiff
slice
sort
sortrows
sparse
speye
sum
tinyply
unique
unique_rows
verbose
decimate_trivial_callbacks
edges
for_each
generate_default_urbg
max_size
min
min_size
collapse_edge
max
mode
main
gl
opengl/glfw/Viewer
C_STR
STR
"
# combine these into exclude
exclude=$(echo -e "$already\n$skip" | sort | uniq)

# but don't include any from exclude

# Run grep and filter out excluded files
include_igl=$(grep -hor '#include "[^"]\+"' /Users/alecjacobson/Repos/libigl/include/igl/ | sed 's/#include "\(.*\).h"/\1/')
# remove any .cpp includes
include_igl=$(echo "$include_igl" | grep -v -F ".cpp")
# remove any number of "../" from the beginning of the line
include_igl=$(echo "$include_igl" | sed -e 's#^\(\.\./\)*##')
# stray includes
include_igl=$(echo "$include_igl" | grep -v -F "#include")

tutorial_igl=$(grep -hor '#include <[^>]\+>' /Users/alecjacobson/Repos/libigl/tutorial/ | sed -n 's/#include <igl\/\(.*\).h>/\1/p')
tests_igl=$(grep -hor '#include <[^>]\+>' /Users/alecjacobson/Repos/libigl/tests/ | sed -n 's/#include <igl\/\(.*\).h>/\1/p')
# append to include_igl
all=$(echo -e "$include_igl\n$tutorial_igl\n$tests_igl")
#
echo "$all" | grep -v -F -w -f <(echo "$exclude") | sort | uniq -c | sort -n
