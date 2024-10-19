from pathlib import Path

from setuptools import Extension
from setuptools import setup


module = Extension(
    "tracer_runtime",
    sources=[Path(f).as_posix() for f in Path("src").rglob("*.c") if f.is_file()],
    extra_compile_args=["-Wall", "-Werror", "-O3"],
)

setup(
    name="tracer_runtime",
    version="1.0.0",
    description="An example Python C extension module",
    ext_modules=[module],
    test_suite="tests",
)
