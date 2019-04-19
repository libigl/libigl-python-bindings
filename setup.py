import os
import re
import sys
# import sysconfig
import platform
import subprocess

import sysconfig

from distutils.version import LooseVersion
from setuptools import setup, Extension, find_packages
from setuptools.command.build_ext import build_ext


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

        cmake_version = LooseVersion(re.search(r'version\s*([\d.]+)', out.decode()).group(1))
        if cmake_version < '3.2.0':
            raise RuntimeError("CMake >= 3.2.0 is required")

        for ext in self.extensions:
            self.build_extension(ext)


    def build_extension(self, ext):
        extdir = os.path.join(os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name))),"igl")

        cmake_args = ['-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=' + extdir,
                      '-DPYTHON_EXECUTABLE=' + sys.executable,
                      '-DLIBIGL_PYTHON_TESTS=OFF']


        cfg = 'Debug' if self.debug else 'Release'
        build_args = ['--config', cfg]
        cmake_args += ['-DCMAKE_BUILD_TYPE=' + cfg]

        if platform.system() == "Windows":
            cmake_args += ['-DCMAKE_LIBRARY_OUTPUT_DIRECTORY_{}={}'.format(cfg.upper(), extdir)]
            if sys.maxsize > 2**32:
                cmake_args += ['-A', 'x64']
            cmake_args += ['-T', 'llvm']
            if self.debug:
                cmake_args += ['-D', 'PYTHON_LIBRARY={}\\libs\\python{}.lib\\;PYTHON_LIBRARY={}\\libs\\python{}_d.lib'.format(sysconfig.get_path('data'),  sysconfig.get_config_var('py_version_short').replace('.',''), sysconfig.get_path('data'),  sysconfig.get_config_var('py_version_short').replace('.',''))]
            else:
                cmake_args += ['-D', 'PYTHON_LIBRARY={}\\libs\\python{}.lib'.format(sysconfig.get_path('data'),  sysconfig.get_config_var('py_version_short').replace('.',''))]
            build_args += ['--', '/m']
        else:
            build_args += ['--', '-j2']

        env = os.environ.copy()
        env['CXXFLAGS'] = '{} -DVERSION_INFO=\\"{}\\"'.format(env.get('CXXFLAGS', ''),self.distribution.get_version())

        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)
        subprocess.check_call(['cmake', ext.sourcedir] + cmake_args, cwd=self.build_temp, env=env)

        subprocess.check_call(['cmake', '--build', '.'] + build_args, cwd=self.build_temp)

        print()  # Add an empty line for cleaner output


with open("README.md", "r") as fh:
    long_description = fh.read()


setup(
    name="igl",
    version="0.1",
    author="libigl",
    author_email="",
    description="libigl Python Bindings",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://libigl.github.io/",
    ext_modules=[CMakeExtension('igl')],
    cmdclass=dict(build_ext=CMakeBuild),
    packages=find_packages(),
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License"
    ],
    test_suite="tests"
)
