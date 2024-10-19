#include <Python.h>

#include "event_callbacks.h"

static PyObject *TracerRuntimeError;

static PyMethodDef Methods[] = {
    {"begin_module", (PyCFunction)event_callback_begin_frame, METH_FASTCALL},
    {
        "end_module",
        (PyCFunction)event_callback_end_frame,
        METH_FASTCALL,
    },
    {
        "begin_func",
        (PyCFunction)event_callback_begin_frame,
        METH_FASTCALL,
    },
    {
        "end_func",
        (PyCFunction)event_callback_end_frame,
        METH_FASTCALL,
    },
    {
        "begin_stmt",
        (PyCFunction)event_callback_begin_stmt,
        METH_FASTCALL,
    },
    {
        "end_stmt",
        (PyCFunction)event_callback_end_stmt,
        METH_FASTCALL,
    },
    {
        "begin_expr",
        (PyCFunction)event_callback_begin_expr,
        METH_FASTCALL,
    },
    {
        "end_expr",
        (PyCFunction)event_callback_end_expr,
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

  doc = yyjson_mut_doc_new(NULL);
  events = yyjson_mut_arr(doc);
  yyjson_mut_doc_set_root(doc, events);

  module = PyModule_Create(&tracer_runtime_module);
  if (module == NULL) {
    return NULL;
  }

  TracerRuntimeError = PyErr_NewException("tracer_runtime.Error", NULL, NULL);
  Py_INCREF(TracerRuntimeError);
  PyModule_AddObject(module, "Error", TracerRuntimeError);
  return module;
}
