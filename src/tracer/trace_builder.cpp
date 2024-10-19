#include "trace_builder.hpp"
#include "node_location.hpp"

namespace tracer {
void TraceBuilder::start_frame(
    const NodeLocation &frame_node_location,
    const std::optional<NodeLocation> &caller_node_location) {
  auto frame_node_location_json = frame_node_location.to_json(allocator);

  rapidjson::Value event_json(rapidjson::kObjectType);

  event_json.AddMember("node_location", frame_node_location_json, allocator);
  event_json.AddMember("type", "start_frame", allocator);

  if (caller_node_location.has_value()) {
    auto caller_node_location_json = caller_node_location->to_json(allocator);
    event_json.AddMember("caller_node_location", caller_node_location_json,
                         allocator);
  }

  events_json.PushBack(event_json, allocator);
}

void TraceBuilder::end_frame() {
  rapidjson::Value event_json(rapidjson::kObjectType);

  event_json.AddMember("type", "end_frame", allocator);
  events_json.PushBack(event_json, allocator);
}

void TraceBuilder::accept(
    rapidjson::Writer<rapidjson::StringBuffer> &writer) const {
  events_json.Accept(writer);
}

} // namespace tracer
