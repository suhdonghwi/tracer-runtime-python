#define STB_DS_IMPLEMENTATION
#include "libs/stb_ds.h"
#include "libs/yyjson.h"

#include "event_callbacks.h"
#include "globals.h"

yyjson_mut_val *pyobject_to_node_location_json(PyObject *node_location_object) {
  char *file_id;
  Py_ssize_t begin_offset, end_offset;

  PyArg_ParseTuple(node_location_object, "snn", &file_id, &begin_offset,
                   &end_offset);

  yyjson_mut_val *node_location = yyjson_mut_obj(event_logs_json_doc);
  yyjson_mut_obj_add_str(event_logs_json_doc, node_location, "file_id",
                         file_id);
  yyjson_mut_obj_add_uint(event_logs_json_doc, node_location, "begin_offset",
                          (uint32_t)begin_offset);
  yyjson_mut_obj_add_uint(event_logs_json_doc, node_location, "end_offset",
                          (uint32_t)end_offset);

  return node_location;
}

PyObject *event_callback_begin_frame(PyObject *self, PyObject **args) {
  yyjson_mut_val *event = yyjson_mut_obj(event_logs_json_doc);
  yyjson_mut_obj_add_str(event_logs_json_doc, event, "type", "begin_frame");

  PyObject *frame_node_location_object = args[0];
  yyjson_mut_val *frame_node_location =
      pyobject_to_node_location_json(frame_node_location_object);

  yyjson_mut_obj_add_val(event_logs_json_doc, event, "node_location",
                         frame_node_location);

  if (arrlen(node_location_object_stack) > 0) {
    PyObject *last_node_location_object = arrlast(node_location_object_stack);
    yyjson_mut_val *caller_node_location =
        pyobject_to_node_location_json(last_node_location_object);

    yyjson_mut_obj_add_val(event_logs_json_doc, event, "caller_node_location",
                           caller_node_location);
  } else {
    yyjson_mut_obj_add_null(event_logs_json_doc, event, "caller_node_location");
  }

  yyjson_mut_arr_append(event_logs_json, event);
  Py_RETURN_NONE;
}

PyObject *event_callback_end_frame(PyObject *self, PyObject **args) {
  yyjson_mut_val *event_json = yyjson_mut_obj(event_logs_json_doc);
  yyjson_mut_obj_add_str(event_logs_json_doc, event_json, "type", "end_frame");

  yyjson_mut_arr_append(event_logs_json, event_json);

  if (arrlen(node_location_object_stack) == 0) {
    yyjson_write_err err;
    yyjson_mut_write_file("/tmp/trace.json", event_logs_json_doc, 0, NULL,
                          &err);
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
