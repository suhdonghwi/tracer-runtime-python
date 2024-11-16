
#include "event_log.h"
#include "node_location.h"

static yyjson_mut_doc *event_log_json_doc;
static yyjson_mut_val *event_log_json;

void event_log_init() {
  event_log_json_doc = yyjson_mut_doc_new(NULL);
  event_log_json = yyjson_mut_arr(event_log_json_doc);
  yyjson_mut_doc_set_root(event_log_json_doc, event_log_json);
}

void event_log_begin_frame(PyObject *frame_node_location_object,
                           PyObject *caller_node_location_object) {
  yyjson_mut_val *frame_node_location_json = node_location_pyobject_to_json(
      frame_node_location_object, event_log_json_doc);

  yyjson_mut_val *caller_node_location_json = NULL;
  if (caller_node_location_object != NULL) {
    caller_node_location_json = node_location_pyobject_to_json(
        caller_node_location_object, event_log_json_doc);
  }

  yyjson_mut_val *event_item_json = yyjson_mut_obj(event_log_json_doc);
  yyjson_mut_obj_add_str(event_log_json_doc, event_item_json, "type",
                         "begin_frame");

  yyjson_mut_obj_add_val(event_log_json_doc, event_item_json, "node_location",
                         frame_node_location_json);

  if (caller_node_location_json == NULL) {
    yyjson_mut_obj_add_null(event_log_json_doc, event_item_json,
                            "caller_node_location");
  } else {
    yyjson_mut_obj_add_val(event_log_json_doc, event_item_json,
                           "caller_node_location", caller_node_location_json);
  }

  yyjson_mut_arr_append(event_log_json, event_item_json);
}

void event_log_end_frame() {
  yyjson_mut_val *event_json = yyjson_mut_obj(event_log_json_doc);
  yyjson_mut_obj_add_str(event_log_json_doc, event_json, "type", "end_frame");

  yyjson_mut_arr_append(event_log_json, event_json);
}

void event_log_write() {
  const char *file_path = "./event_log.json";

  yyjson_write_err err;
  bool write_success =
      yyjson_mut_write_file(file_path, event_log_json_doc, 0, NULL, &err);

  if (!write_success) {
    fprintf(stderr, "Failed to write event log to file: %s\n", err.msg);
  }
}
