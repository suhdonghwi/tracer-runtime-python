#pragma once

namespace tracer {
class Span {
public:
  int begin_offset;
  int end_offset;

  Span(int begin_offset, int end_offset);
};
} // namespace tracer
