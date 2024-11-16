#pragma once

#include <Python.h>

void event_log_init();

void event_log_begin_frame(PyObject *frame_node_location_object,
                           PyObject *caller_node_location_object);
void event_log_end_frame();

void event_log_write();
