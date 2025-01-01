#pragma once
#include <Python.h>

#include "libs/yyjson.h"

yyjson_mut_val *source_location_py_to_json(PyObject *source_location_object,
                                           yyjson_mut_doc *doc);
