#!/bin/bash
#
already=$(ls src/*.cpp | sed -e "s/src\/\(.*\).cpp$/\1/g")
skip="igl_inline
EPS
verbose
colon
sort
placeholders
list_to_matrix
parallel_for
PI"
# combine these into exclude
exclude=$(echo -e "$already\n$skip" | sort | uniq)
echo $exclude

# but don't include any from exclude

# Run grep and filter out excluded files
grep -ho '#include "[^"]\+"' "$1"/*.{h,cpp} | \
  sed 's/#include "\(.*\).h"/\1/' | \
grep -v -F -w -f <(echo "$exclude") | \
sort | uniq -c | sort -n
