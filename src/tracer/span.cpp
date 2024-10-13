#include "span.hpp"

namespace tracer {
Span::Span(int begin_offset, int end_offset)
    : begin_offset(begin_offset), end_offset(end_offset) {}
} // namespace tracer
