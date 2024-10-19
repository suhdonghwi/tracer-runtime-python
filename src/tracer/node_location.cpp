#include "node_location.hpp"
#include "span.hpp"

namespace tracer {
NodeLocation::NodeLocation(std::string_view file_id, Span span)
    : file_id(file_id), span(span) {}

rapidjson::Value
NodeLocation::to_json(rapidjson::MemoryPoolAllocator<> &allocator) const {
  rapidjson::Value node_location_json(rapidjson::kArrayType);
  node_location_json.PushBack(file_id, allocator);
  node_location_json.PushBack(span.begin_offset, allocator);
  node_location_json.PushBack(span.end_offset, allocator);

  return node_location_json;
}

NodeLocation NodeLocation::from_pyobject(PyObject *node_location_obj) {
  const char *file_id;
  std::size_t begin_offset, end_offset;

  PyArg_ParseTuple(node_location_obj, "snn", &file_id, &begin_offset,
                   &end_offset);

  return NodeLocation(file_id, Span(begin_offset, end_offset));
}
} // namespace tracer
