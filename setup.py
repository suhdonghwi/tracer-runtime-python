from setuptools import Extension
from setuptools import setup


module = Extension("tracer_runtime_", sources=["spam.c"], extra_compile_args=["-Wall"])

setup(
    name="_tracer_runtime",
    version="1.0.0",
    description="An example Python C extension module",
    url="https://github.com/jalan/spam",
    ext_modules=[module],
    test_suite="tests",
)
