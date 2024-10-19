#pragma once

#include <Python.h>
#include <optional>

#include "../rapidjson/allocators.h"
#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"

#include "node_location.hpp"

namespace tracer {
class TraceBuilder {
private:
  rapidjson::MemoryPoolAllocator<> allocator;
  rapidjson::Value events_json = rapidjson::Value(rapidjson::kArrayType);

public:
  void start_frame(const NodeLocation &frame_node_location,
                   const std::optional<NodeLocation> &caller_node_location);
  void end_frame();

  void accept(rapidjson::Writer<rapidjson::StringBuffer> &writer) const;
};
} // namespace tracer
