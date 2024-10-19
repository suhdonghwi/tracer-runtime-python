#pragma once
#include <Python.h>
#include <string>
#include <string_view>

#include "../rapidjson/document.h"

#include "span.hpp"

namespace tracer {
class NodeLocation {
private:
  std::string file_id;
  Span span;

public:
  NodeLocation(std::string_view file_id, Span span);

  rapidjson::Value to_json(rapidjson::MemoryPoolAllocator<> &allocator) const;

  static NodeLocation from_pyobject(PyObject *node_location_obj);
};
} // namespace tracer
