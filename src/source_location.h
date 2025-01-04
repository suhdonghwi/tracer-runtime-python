#pragma once
#include <Python.h>

#include "libs/yyjson.h"

yyjson_mut_val *source_location_py_to_json(
    yyjson_mut_doc *doc,
    PyObject *source_location_object
);
