#pragma once

#include <Python.h>
#include <optional>
#include <stack>

#include "../rapidjson/allocators.h"
#include "../rapidjson/document.h"
#include "node_location.hpp"

namespace tracer {
class TraceBuilder {
private:
  rapidjson::MemoryPoolAllocator<> allocator;
  std::stack<rapidjson::Value> frame_trace_stack;

public:
  void start_frame(NodeLocation frame_node_location);
  rapidjson::Value end_frame(std::optional<NodeLocation> caller_node_location);
};
} // namespace tracer
