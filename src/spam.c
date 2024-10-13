#include <Python.h>

#include <stdlib.h>

#include "cJSON.h"

static PyObject *TracerRuntimeError;

static PyObject *begin_expr(PyObject *self, PyObject *args) {
  const char *file_id;
  PyObject *range_tuple = NULL;
  int begin, end;

  if (!PyArg_ParseTuple(args, "(s(ii))", &file_id, &begin, &end)) {
    return NULL;
  }

  PyObject *arg = NULL;
  PyArg_ParseTuple(args, "O", &arg);

  Py_INCREF(arg);
  return arg;
}

static PyObject *end_expr(PyObject *self, PyObject *args) {
  const char *file_id;
  PyObject *range_tuple = NULL;
  int begin, end;
  PyObject *expr_result = NULL;

  if (!PyArg_ParseTuple(args, "(s(ii))O", &file_id, &begin, &end,
                        &expr_result)) {
    return NULL;
  }

  Py_INCREF(expr_result);
  return expr_result;
}

static PyObject *others(PyObject *self, PyObject *args) {
  const char *file_id;
  PyObject *range_tuple = NULL;
  int begin, end;

  // Parse the arguments: expecting a tuple (string, tuple of two integers)
  if (!PyArg_ParseTuple(args, "(s(ii))", &file_id, &begin, &end)) {
    return NULL;
  }

  Py_RETURN_NONE;
}

static PyMethodDef Methods[] = {
    {"begin_module", begin_expr, METH_VARARGS},
    {
        "end_module",
        others,
        METH_VARARGS,
    },
    {
        "begin_func",
        others,
        METH_VARARGS,
    },
    {
        "end_func",
        others,
        METH_VARARGS,
    },
    {
        "begin_stmt",
        others,
        METH_VARARGS,
    },
    {
        "end_stmt",
        others,
        METH_VARARGS,
    },
    {
        "begin_expr",
        begin_expr,
        METH_VARARGS,
    },
    {
        "end_expr",
        end_expr,
        METH_VARARGS,
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
