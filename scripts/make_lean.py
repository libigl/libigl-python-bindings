import sys
import os
import fileinput

if __name__ == '__main__':
    # Modify Cmake inplace
    with fileinput.FileInput("../CMakeLists.txt", inplace=True) as file:
        for line in file:
            print(line.replace('set_target_properties(pyigl PROPERTIES COMPILE_FLAGS "-fvisibility=hidden -msse2")', 'set_target_properties(pyigl PROPERTIES COMPILE_FLAGS "-fvisibility=hidden -msse2 -H")'), end='')
    
    # Create tmpdir, run Cmake and make
    os.makedirs("../tmp_build", exist_ok=True)
    os.chdir("../tmp_build")
    os.system("cmake ..")
    deps = os.popen("make -j 4").read()
    print(len(deps))
    # Remove not included files


#import os, glob
#with open("deps.txt") as f:
#    lines = f.readlines()
#igl_deps = []
#for l in lines:
#    if "/home/skoch9/Repos/pyigl/libigl/include/igl/" in l:
#        s = l.split(" ")
#        if len(s) == 2:
#            s = s[1].strip()
#        else:
#            s = s[0].strip()
#        igl_deps.append(s)
#igl_deps = sorted(list(set(igl_deps)))
#files = glob.glob("/home/skoch9/Repos/pyigl/libigl/include/igl/**/*", recursive=True)
#deps = []
#for f in files:
#    if os.path.isfile(f) and f not in igl_deps:
#        os.remove(f)
##len(files), len(deps), len(igl_deps)
##for dep in igl_deps:
##    print(dep)
