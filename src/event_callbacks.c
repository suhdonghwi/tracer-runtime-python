#define STB_DS_IMPLEMENTATION
#include "libs/stb_ds.h"
#include "libs/yyjson.h"

#include "event_callbacks.h"
#include "event_log.h"
#include "node_location.h"

PyObject **node_location_object_stack;

PyObject *event_callback_begin_frame(PyObject *self, PyObject **args) {
  PyObject *frame_node_location_object = args[0];
  yyjson_mut_val *frame_node_location_json = node_location_pyobject_to_json(
      frame_node_location_object, event_log_json_doc);

  yyjson_mut_val *caller_node_location_json = NULL;

  if (arrlen(node_location_object_stack) > 0) {
    PyObject *last_node_location_object = arrlast(node_location_object_stack);
    caller_node_location_json = node_location_pyobject_to_json(
        last_node_location_object, event_log_json_doc);
  }

  event_log_begin_frame(frame_node_location_json, caller_node_location_json);
  Py_RETURN_NONE;
}

PyObject *event_callback_end_frame(PyObject *self, PyObject **args) {
  event_log_end_frame();

  if (arrlen(node_location_object_stack) == 0) {
    event_log_write("./event_log.json");
  }

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
