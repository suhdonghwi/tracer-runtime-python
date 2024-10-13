from setuptools import Extension
from setuptools import setup


module = Extension(
    "tracer_runtime",
    sources=["src/main.cpp", "src/tracer/events.cpp"],
    extra_compile_args=["-Wall", "-std=c++20", "-O3"],
    language="c++",
)

setup(
    name="tracer_runtime",
    version="1.0.0",
    description="An example Python C extension module",
    ext_modules=[module],
    test_suite="tests",
)
