#include <Python.h>

#include "event_callbacks.h"
#include "event_log.h"

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

static PyModuleDef tracer_runtime_python_module = {
    PyModuleDef_HEAD_INIT,
    "tracer_runtime_python",
    "An example Python C extension module.",
    -1,
    Methods,
};

PyMODINIT_FUNC PyInit_tracer_runtime_python() {
  event_log_init();

  return PyModule_Create(&tracer_runtime_python_module);
}
