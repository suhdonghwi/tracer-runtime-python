#include "node_location.hpp"
#include "span.hpp"

namespace tracer {
NodeLocation::NodeLocation(const char *file_id, Span span)
    : file_id(file_id), span(span) {}

NodeLocation::NodeLocation(PyObject *node_location_obj) : span(0, 0) {
  const char *file_id;
  int begin_offset, end_offset;

  PyArg_ParseTuple(node_location_obj, "sii", &file_id, &begin_offset,
                   &end_offset);

  this->file_id = file_id;
  this->span = Span(begin_offset, end_offset);
}
} // namespace tracer
