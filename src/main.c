#include <Python.h>

#include "execution_callbacks.h"
#include "execution_log.h"

static PyMethodDef Methods[] = {
    {"begin_module", (PyCFunction)callback_begin_frame, METH_FASTCALL},
    {
        "end_module",
        (PyCFunction)callback_end_frame,
        METH_FASTCALL,
    },
    {
        "begin_func",
        (PyCFunction)callback_begin_frame,
        METH_FASTCALL,
    },
    {
        "end_func",
        (PyCFunction)callback_end_frame,
        METH_FASTCALL,
    },
    {
        "begin_stmt",
        (PyCFunction)callback_begin_stmt,
        METH_FASTCALL,
    },
    {
        "end_stmt",
        (PyCFunction)callback_end_stmt,
        METH_FASTCALL,
    },
    {
        "begin_expr",
        (PyCFunction)callback_begin_expr,
        METH_FASTCALL,
    },
    {
        "end_expr",
        (PyCFunction)callback_end_expr,
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
  execution_log_init();
  Py_AtExit(execution_log_write);

  return PyModule_Create(&tracer_runtime_python_module);
}
