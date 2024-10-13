#pragma once
#include <Python.h>

#include "span.hpp"

namespace tracer {
class NodeLocation {
public:
  const char *file_id;
  Span span;

  NodeLocation(const char *file_id, Span span);
  NodeLocation(PyObject *node_location_obj);
};
} // namespace tracer
