#pragma once

#include <cstddef>

namespace tracer {
struct Span {
  std::size_t begin_offset;
  std::size_t end_offset;
};
} // namespace tracer
