from distutils.core import setup, Extension
from Cython.Build import cythonize

ext = Extension(name="wrapper",
        sources=["wrapper.pyx", "utils.c"],
        )

setup(ext_modules=cythonize(ext))
