#include "event_log.h"

void event_log_init() {
  event_log_json_doc = yyjson_mut_doc_new(NULL);
  event_log_json = yyjson_mut_arr(event_log_json_doc);
  yyjson_mut_doc_set_root(event_log_json_doc, event_log_json);
}

void event_log_begin_frame(yyjson_mut_val *frame_node_location_json,
                           yyjson_mut_val *caller_node_location_json) {
  yyjson_mut_val *event_json = yyjson_mut_obj(event_log_json_doc);
  yyjson_mut_obj_add_str(event_log_json_doc, event_json, "type", "begin_frame");

  yyjson_mut_val *node_location_json = yyjson_mut_obj(event_log_json_doc);
  yyjson_mut_obj_add_val(event_log_json_doc, node_location_json,
                         "node_location", frame_node_location_json);

  if (caller_node_location_json == NULL) {
    yyjson_mut_obj_add_null(event_log_json_doc, node_location_json,
                            "caller_node_location");
  } else {
    yyjson_mut_obj_add_val(event_log_json_doc, node_location_json,
                           "caller_node_location", caller_node_location_json);
  }

  yyjson_mut_arr_append(event_log_json, event_json);
}

void event_log_end_frame() {
  yyjson_mut_val *event_json = yyjson_mut_obj(event_log_json_doc);
  yyjson_mut_obj_add_str(event_log_json_doc, event_json, "type", "end_frame");

  yyjson_mut_arr_append(event_log_json, event_json);
}

void event_log_write(const char *file_path) {
  yyjson_write_err err;
  yyjson_mut_write_file(file_path, event_log_json_doc, 0, NULL, &err);
}
