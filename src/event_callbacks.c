#include "yyjson.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#include "event_callbacks.h"

PyObject **node_location_object_stack;

PyObject *event_callback_begin_frame(PyObject *self, PyObject **args) {
  yyjson_mut_val *event = yyjson_mut_obj(doc);
  yyjson_mut_obj_add_str(doc, event, "type", "begin_frame");

  {
    PyObject *frame_node_location_object = args[0];

    char *file_id;
    Py_ssize_t begin_offset, end_offset;

    PyArg_ParseTuple(frame_node_location_object, "snn", &file_id, &begin_offset,
                     &end_offset);

    yyjson_mut_val *frame_node_location = yyjson_mut_obj(doc);
    yyjson_mut_obj_add_str(doc, frame_node_location, "file_id", file_id);
    yyjson_mut_obj_add_uint(doc, frame_node_location, "begin_offset",
                            (uint32_t)begin_offset);
    yyjson_mut_obj_add_uint(doc, frame_node_location, "end_offset",
                            (uint32_t)end_offset);

    yyjson_mut_obj_add_val(doc, event, "node_location", frame_node_location);
  }

  if (arrlen(node_location_object_stack) > 0) {
    PyObject *last_node_location_object = arrlast(node_location_object_stack);

    char *file_id;
    Py_ssize_t begin_offset, end_offset;

    PyArg_ParseTuple(last_node_location_object, "snn", &file_id, &begin_offset,
                     &end_offset);

    yyjson_mut_val *caller_node_location = yyjson_mut_obj(doc);
    yyjson_mut_obj_add_str(doc, caller_node_location, "file_id", file_id);
    yyjson_mut_obj_add_uint(doc, caller_node_location, "begin_offset",
                            (uint32_t)begin_offset);
    yyjson_mut_obj_add_uint(doc, caller_node_location, "end_offset",
                            (uint32_t)end_offset);

    yyjson_mut_obj_add_val(doc, event, "caller_node_location",
                           caller_node_location);
  } else {
    yyjson_mut_obj_add_null(doc, event, "caller_node_location");
  }

  yyjson_mut_arr_append(events, event);
  Py_RETURN_NONE;
}

PyObject *event_callback_end_frame(PyObject *self, PyObject **args) {
  yyjson_mut_val *event = yyjson_mut_obj(doc);
  yyjson_mut_obj_add_str(doc, event, "type", "end_frame");

  yyjson_mut_arr_append(events, event);

  if (arrlen(node_location_object_stack) == 0) {
    yyjson_write_flag flg = YYJSON_WRITE_PRETTY | YYJSON_WRITE_ESCAPE_UNICODE;
    yyjson_write_err err;
    yyjson_mut_write_file("/tmp/trace.json", doc, flg, NULL, &err);
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
