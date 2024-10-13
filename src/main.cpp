#include <Python.h>

#include "tracer/callbacks.hpp"

static PyObject *TracerRuntimeError;

static PyMethodDef Methods[] = {
    {"begin_module", (PyCFunction)tracer::callbacks::begin_frame,
     METH_FASTCALL},
    {
        "end_module",
        (PyCFunction)tracer::callbacks::end_frame,
        METH_FASTCALL,
    },
    {
        "begin_func",
        (PyCFunction)tracer::callbacks::begin_frame,
        METH_FASTCALL,
    },
    {
        "end_func",
        (PyCFunction)tracer::callbacks::end_frame,
        METH_FASTCALL,
    },
    {
        "begin_stmt",
        (PyCFunction)tracer::callbacks::begin_stmt,
        METH_FASTCALL,
    },
    {
        "end_stmt",
        (PyCFunction)tracer::callbacks::end_stmt,
        METH_FASTCALL,
    },
    {
        "begin_expr",
        (PyCFunction)tracer::callbacks::begin_expr,
        METH_FASTCALL,
    },
    {
        "end_expr",
        (PyCFunction)tracer::callbacks::end_expr,
        METH_FASTCALL,
    },
    {NULL, NULL, 0, NULL}, // sentinel
};

static PyModuleDef tracer_runtime_module = {
    PyModuleDef_HEAD_INIT,
    "tracer_runtime",
    "An example Python C extension module.",
    -1,
    Methods,
};

PyMODINIT_FUNC PyInit_tracer_runtime() {
  PyObject *module;

  module = PyModule_Create(&tracer_runtime_module);
  if (module == NULL) {
    return NULL;
  }

  TracerRuntimeError = PyErr_NewException("tracer_runtime.Error", NULL, NULL);
  Py_INCREF(TracerRuntimeError);
  PyModule_AddObject(module, "Error", TracerRuntimeError);
  return module;
}
