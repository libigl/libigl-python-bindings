import os
import re
import sys
import platform
import subprocess

from packaging.version import Version
from setuptools import setup, Extension, find_packages
from setuptools.command.build_ext import build_ext

__version__ = '0.0.1'

class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=''):
        Extension.__init__(self, name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)


class CMakeBuild(build_ext):
    def run(self):
        try:
            out = subprocess.check_output(['cmake', '--version'])
        except OSError:
            raise RuntimeError(
                "CMake must be installed to build the following extensions: , ".join(e.name for e in self.extensions))

        # self.debug = True

        cmake_version = Version(re.search(r'version\s*([\d.]+)', out.decode()).group(1))
        if cmake_version < Version('3.2.0'):
            raise RuntimeError("CMake >= 3.2.0 is required")

        for ext in self.extensions:
            self.build_extension(ext)


    def build_extension(self, ext):
        extdir = os.path.join(os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name))),"igl")

        cmake_args = ['-DPYIGL_OUTPUT_DIRECTORY=' + extdir,
                      '-DPYTHON_EXECUTABLE=' + sys.executable]


        cfg = 'Debug' if self.debug else 'Release'
        build_args = ['--config', cfg]
        cmake_args += ['-DCMAKE_BUILD_TYPE=' + cfg]
        # cmake_args += ['-DDEBUG_TRACE=ON']

        if platform.system() == "Windows":
            cmake_generator = os.environ.get('CMAKE_GENERATOR', '')
            if cmake_generator != "NMake Makefiles" and "Ninja" not in cmake_generator:
                if sys.maxsize > 2**32:
                    cmake_args += ['-A', 'x64']
                # build_args += ['--', '/m']
        else: 
            if "MAX_JOBS" in os.environ:
                build_args += ['--', f"-j{os.environ['MAX_JOBS']}"]
            else:
                build_args += ['--', '-j8']


        tmp = os.environ.get("AR", "")
        if "arm64-apple" in tmp:
            tmp = os.environ.get("CMAKE_ARGS", "")
            if tmp:
                cmake_args += tmp.split(" ")

            tmp = os.environ.get("CC", "")
            print("C compiler", tmp)
            if tmp:
                cmake_args += ["-DCMAKE_C_COMPILER={}".format(tmp)]

            tmp = os.environ.get("CXX", "")
            print("CXX compiler", tmp)
            if tmp:
                cmake_args += ["-DCMAKE_CXX_COMPILER={}".format(tmp)]
        else:
            tmp = os.getenv('CC_FOR_BUILD', '')
            if tmp:
                print("Setting c compiler to", tmp)
                cmake_args += ["-DCMAKE_C_COMPILER=" + tmp]

            tmp = os.getenv('CXX_FOR_BUILD', '')
            if tmp:
                print("Setting cxx compiler to", tmp)
                cmake_args += ["-DCMAKE_CXX_COMPILER="+ tmp]

        env = os.environ.copy()
        env['CXXFLAGS'] = '{} -DVERSION_INFO=\\"{}\\"'.format(env.get('CXXFLAGS', ''),self.distribution.get_version())



        tmp = os.getenv("target_platform", "")
        if tmp:
            print("target platfrom", tmp)
            if "arm" in tmp:
                cmake_args += ["-DCMAKE_OSX_ARCHITECTURES=arm64"]

        # print(cmake_args)
        # tmp = os.getenv('CMAKE_ARGS', '')

        # if tmp:
        #     tmp = tmp.split(" ")
        #     print("tmp", tmp)
        #     cmake_args += tmp

        # cmake_args += ["-DCMAKE_OSX_ARCHITECTURES" , "arm64"]
        # print(cmake_args)

        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)
        subprocess.check_call(['cmake', ext.sourcedir] + cmake_args, cwd=self.build_temp, env=env)

        subprocess.check_call(['cmake', '--build', '.'] + build_args, cwd=self.build_temp)

        print()  # Add an empty line for cleaner output


with open("README.md", "r") as fh:
    long_description = fh.read()


# https://stackoverflow.com/a/7071358/148668
import re
VERSIONFILE="igl/_version.py"
verstrline = open(VERSIONFILE, "rt").read()
VSRE = r"^__version__ = ['\"]([^'\"]*)['\"]"
mo = re.search(VSRE, verstrline, re.M)
if mo:
    verstr = mo.group(1)
else:
    raise RuntimeError("Unable to find version string in %s." % (VERSIONFILE,))

setup(
    name="libigl",
    version=verstr,
    author="libigl",
    author_email="",
    description="libigl Python Bindings",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://libigl.github.io/libigl-python-bindings/",
    ext_modules=[CMakeExtension('pyigl')],
    install_requires=[ 'numpy', 'scipy' ],
    cmdclass=dict(build_ext=CMakeBuild),
    packages=find_packages(),
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License"
    ],
    test_suite="tests"
)
