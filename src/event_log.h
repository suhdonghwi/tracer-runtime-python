#pragma once

#include "libs/yyjson.h"

yyjson_mut_doc *event_log_json_doc;

void event_log_init();

void event_log_begin_frame(yyjson_mut_val *frame_node_location_json,
                           yyjson_mut_val *caller_node_location_json);
void event_log_end_frame();

void event_log_write(const char *file_path);
