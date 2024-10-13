#include <Python.h>

#include <stack>

static PyObject *TracerRuntimeError;

static std::stack<PyObject *> node_stack;

static PyObject *begin_expr(PyObject *self, PyObject *const *args,
                            Py_ssize_t nargs) {
  PyObject *node_location = args[0];

  node_stack.push(node_location);

  Py_INCREF(node_location);
  return node_location;
}

static PyObject *end_expr(PyObject *self, PyObject *const *args,
                          Py_ssize_t nargs) {
  PyObject *node_location = args[0];
  PyObject *expr_result = args[1];

  node_stack.pop();

  Py_INCREF(expr_result);
  return expr_result;
}

static PyObject *begin_stmt(PyObject *self, PyObject *const *args,
                            Py_ssize_t nargs) {
  PyObject *node_location = args[0];
  node_stack.push(node_location);

  Py_RETURN_NONE;
}

static PyObject *end_stmt(PyObject *self, PyObject *const *args,
                          Py_ssize_t nargs) {
  node_stack.pop();

  Py_RETURN_NONE;
}

static PyObject *begin_frame(PyObject *self, PyObject *const *args,
                             Py_ssize_t nargs) {
  PyObject *node_location = args[0];

  node_stack.push(node_location);

  Py_RETURN_NONE;
}

static PyObject *end_frame(PyObject *self, PyObject *const *args,
                           Py_ssize_t nargs) {
  PyObject *node_location = args[0];

  node_stack.pop();

  Py_RETURN_NONE;
}

static PyObject *noop(PyObject *self, PyObject *args) { Py_RETURN_NONE; }

static PyMethodDef Methods[] = {
    {"begin_module", (PyCFunction)begin_frame, METH_FASTCALL},
    {
        "end_module",
        (PyCFunction)end_frame,
        METH_FASTCALL,
    },
    {
        "begin_func",
        (PyCFunction)begin_frame,
        METH_FASTCALL,
    },
    {
        "end_func",
        (PyCFunction)end_frame,
        METH_FASTCALL,
    },
    {
        "begin_stmt",
        (PyCFunction)begin_stmt,
        METH_FASTCALL,
    },
    {
        "end_stmt",
        (PyCFunction)end_stmt,
        METH_FASTCALL,
    },
    {
        "begin_expr",
        (PyCFunction)begin_expr,
        METH_FASTCALL,
    },
    {
        "end_expr",
        (PyCFunction)end_expr,
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
