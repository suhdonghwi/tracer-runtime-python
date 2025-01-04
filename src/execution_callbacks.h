#pragma once

#include <Python.h>

PyObject *callback_begin_frame(PyObject *self, PyObject **args);
PyObject *callback_end_frame(PyObject *self, PyObject **args);
PyObject *callback_begin_stmt(PyObject *self, PyObject **args);
PyObject *callback_end_stmt(PyObject *self, PyObject **args);
PyObject *callback_begin_expr(PyObject *self, PyObject **args);
PyObject *callback_end_expr(PyObject *self, PyObject **args);
