#pragma once

#include <Python.h>

namespace tracer {
namespace events {

PyObject *begin_expr(PyObject *self, PyObject *const *args, Py_ssize_t nargs);
PyObject *end_expr(PyObject *self, PyObject *const *args, Py_ssize_t nargs);
PyObject *begin_stmt(PyObject *self, PyObject *const *args, Py_ssize_t nargs);
PyObject *end_stmt(PyObject *self, PyObject *const *args, Py_ssize_t nargs);
PyObject *begin_frame(PyObject *self, PyObject *const *args, Py_ssize_t nargs);
PyObject *end_frame(PyObject *self, PyObject *const *args, Py_ssize_t nargs);

} // namespace events
} // namespace tracer
