#include "trace_builder.hpp"
#include "node_location.hpp"

namespace tracer {
void TraceBuilder::start_frame(NodeLocation frame_node_location) {
  rapidjson::Value file_id_json(frame_node_location.file_id, allocator);
  rapidjson::Value begin_offset_json(frame_node_location.span.begin_offset);
  rapidjson::Value end_offset_json(frame_node_location.span.end_offset);

  rapidjson::Value node_location_json(rapidjson::kArrayType);
  node_location_json.PushBack(file_id_json, allocator);
  node_location_json.PushBack(begin_offset_json, allocator);
  node_location_json.PushBack(end_offset_json, allocator);

  rapidjson::Value children_json(rapidjson::kArrayType);

  rapidjson::Value new_frame_trace(rapidjson::kObjectType);
  new_frame_trace.AddMember("node_location", node_location_json, allocator);
  new_frame_trace.AddMember("children", children_json, allocator);

  frame_trace_stack.push(std::move(new_frame_trace));
}

rapidjson::Value
TraceBuilder::end_frame(std::optional<NodeLocation> caller_node_location) {
  auto popped_frame_trace = std::move(frame_trace_stack.top());
  frame_trace_stack.pop();

  if (!caller_node_location.has_value()) {
    return popped_frame_trace;
  }

  auto &parent_frame_trace = frame_trace_stack.top();

  rapidjson::Value caller_span_json(rapidjson::kArrayType);
  caller_span_json.PushBack(caller_node_location.value().span.begin_offset,
                            allocator);
  caller_span_json.PushBack(caller_node_location.value().span.end_offset,
                            allocator);

  rapidjson::Value child_trace_json(rapidjson::kObjectType);
  child_trace_json.AddMember("span", caller_span_json, allocator);
  child_trace_json.AddMember("trace", popped_frame_trace, allocator);

  parent_frame_trace["children"].PushBack(child_trace_json, allocator);

  return popped_frame_trace;
}

} // namespace tracer
