#include <Python.h>

#include "yyjson.h"

PyObject **node_location_object_stack;

yyjson_mut_doc *doc;
yyjson_mut_val *events;

PyObject *event_callback_begin_frame(PyObject *self, PyObject **args);
PyObject *event_callback_end_frame(PyObject *self, PyObject **args);
PyObject *event_callback_begin_stmt(PyObject *self, PyObject **args);
PyObject *event_callback_end_stmt(PyObject *self, PyObject **args);
PyObject *event_callback_begin_expr(PyObject *self, PyObject **args);
PyObject *event_callback_end_expr(PyObject *self, PyObject **args);
