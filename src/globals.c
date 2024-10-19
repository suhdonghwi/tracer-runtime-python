#include "globals.h"

void init_event_logs_json() {
  event_logs_json_doc = yyjson_mut_doc_new(NULL);
  event_logs_json = yyjson_mut_arr(event_logs_json_doc);
  yyjson_mut_doc_set_root(event_logs_json_doc, event_logs_json);
}
