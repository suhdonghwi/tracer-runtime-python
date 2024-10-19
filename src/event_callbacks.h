#pragma once

#include <Python.h>

PyObject *event_callback_begin_frame(PyObject *self, PyObject **args);
PyObject *event_callback_end_frame(PyObject *self, PyObject **args);
PyObject *event_callback_begin_stmt(PyObject *self, PyObject **args);
PyObject *event_callback_end_stmt(PyObject *self, PyObject **args);
PyObject *event_callback_begin_expr(PyObject *self, PyObject **args);
PyObject *event_callback_end_expr(PyObject *self, PyObject **args);
