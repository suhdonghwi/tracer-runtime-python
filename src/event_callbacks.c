#define STB_DS_IMPLEMENTATION
#include "libs/stb_ds.h"

#include "event_callbacks.h"
#include "execution_log.h"

static PyObject **node_location_object_stack;

PyObject *event_callback_begin_frame(PyObject *self, PyObject **args) {
  PyObject *frame_node_location_object = args[0];

  PyObject *caller_node_location_object = NULL;
  if (arrlen(node_location_object_stack) > 0) {
    caller_node_location_object = arrlast(node_location_object_stack);
  }

  execution_log_begin_frame(frame_node_location_object,
                            caller_node_location_object);
  Py_RETURN_NONE;
}

PyObject *event_callback_end_frame(PyObject *self, PyObject **args) {
  execution_log_end_frame();

  Py_RETURN_NONE;
}

PyObject *event_callback_begin_stmt(PyObject *self, PyObject **args) {
  PyObject *node_location_object = args[0];
  arrpush(node_location_object_stack, node_location_object);

  Py_RETURN_NONE;
}

PyObject *event_callback_end_stmt(PyObject *self, PyObject **args) {
  arrpop(node_location_object_stack);

  Py_RETURN_NONE;
}

PyObject *event_callback_begin_expr(PyObject *self, PyObject **args) {
  PyObject *node_location_object = args[0];
  arrpush(node_location_object_stack, node_location_object);

  Py_INCREF(node_location_object);
  return node_location_object;
}

PyObject *event_callback_end_expr(PyObject *self, PyObject **args) {
  arrpop(node_location_object_stack);

  PyObject *expr_result_object = args[1];

  Py_INCREF(expr_result_object);
  return expr_result_object;
}
