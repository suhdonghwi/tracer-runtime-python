#include <Python.h>
#include "yyjson.h"

PyObject **node_location_object_stack;

yyjson_mut_doc *event_logs_json_doc;
yyjson_mut_val *event_logs_json;

void init_event_logs_json();

