#pragma once
#include <Python.h>

#include "libs/yyjson.h"

yyjson_mut_val *node_location_pyobject_to_json(PyObject *node_location_object, yyjson_mut_doc *doc);
