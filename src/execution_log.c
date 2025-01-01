#include "execution_log.h"
#include "source_location.h"

static yyjson_mut_doc *execution_log_json_doc;
static yyjson_mut_val *execution_log_json;

void execution_log_init() {
  execution_log_json_doc = yyjson_mut_doc_new(NULL);
  execution_log_json = yyjson_mut_arr(execution_log_json_doc);
  yyjson_mut_doc_set_root(execution_log_json_doc, execution_log_json);
}

void execution_log_begin_frame(PyObject *frame_source_location_object,
                               PyObject *caller_source_location_object) {
  yyjson_mut_val *frame_source_location_json = source_location_py_to_json(
      frame_source_location_object, execution_log_json_doc);

  yyjson_mut_val *caller_source_location_json = NULL;
  if (caller_source_location_object != NULL) {
    caller_source_location_json = source_location_py_to_json(
        caller_source_location_object, execution_log_json_doc);
  }

  yyjson_mut_val *event_item_json = yyjson_mut_obj(execution_log_json_doc);
  yyjson_mut_obj_add_str(execution_log_json_doc, event_item_json, "type",
                         "begin_frame");

  yyjson_mut_obj_add_val(execution_log_json_doc, event_item_json,
                         "source_location", frame_source_location_json);

  if (caller_source_location_json == NULL) {
    yyjson_mut_obj_add_null(execution_log_json_doc, event_item_json,
                            "caller_source_location");
  } else {
    yyjson_mut_obj_add_val(execution_log_json_doc, event_item_json,
                           "caller_source_location",
                           caller_source_location_json);
  }

  yyjson_mut_arr_append(execution_log_json, event_item_json);
}

void execution_log_end_frame() {
  yyjson_mut_val *event_json = yyjson_mut_obj(execution_log_json_doc);
  yyjson_mut_obj_add_str(execution_log_json_doc, event_json, "type",
                         "end_frame");

  yyjson_mut_arr_append(execution_log_json, event_json);
}

void execution_log_write() {
  const char *file_path = "./execution_log.json";

  yyjson_write_err err;
  bool write_success =
      yyjson_mut_write_file(file_path, execution_log_json_doc, 0, NULL, &err);

  if (!write_success) {
    fprintf(stderr, "Failed to write event log to file: %s\n", err.msg);
  }
}
