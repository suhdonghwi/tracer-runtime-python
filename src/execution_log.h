#pragma once

#include <Python.h>

void execution_log_init();

void execution_log_begin_frame(
    PyObject *frame_source_location_object,
    PyObject *caller_source_location_object
);
void execution_log_end_frame();

void execution_log_write();
