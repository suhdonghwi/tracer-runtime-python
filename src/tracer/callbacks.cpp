#include <Python.h>
#include <fstream>
#include <optional>
#include <stack>

#include "../rapidjson/stringbuffer.h"
#include "../rapidjson/writer.h"

#include "callbacks.hpp"
#include "trace_builder.hpp"

namespace tracer {
namespace callbacks {

std::stack<PyObject *> node_location_stack;
TraceBuilder trace_builder;

PyObject *begin_expr(PyObject *self, PyObject *const *args, Py_ssize_t nargs) {
  PyObject *node_location_obj = args[0];

  node_location_stack.push(node_location_obj);

  Py_INCREF(node_location_obj);
  return node_location_obj;
}

PyObject *end_expr(PyObject *self, PyObject *const *args, Py_ssize_t nargs) {
  PyObject *expr_result_obj = args[1];

  node_location_stack.pop();

  Py_INCREF(expr_result_obj);
  return expr_result_obj;
}

PyObject *begin_stmt(PyObject *self, PyObject *const *args, Py_ssize_t nargs) {
  PyObject *node_location_obj = args[0];

  node_location_stack.push(node_location_obj);

  Py_RETURN_NONE;
}

PyObject *end_stmt(PyObject *self, PyObject *const *args, Py_ssize_t nargs) {
  node_location_stack.pop();

  Py_RETURN_NONE;
}

PyObject *begin_frame(PyObject *self, PyObject *const *args, Py_ssize_t nargs) {
  PyObject *frame_node_location_obj = args[0];
  auto frame_node_location =
      NodeLocation::from_pyobject(frame_node_location_obj);

  auto caller_node_location =
      node_location_stack.empty()
          ? std::nullopt
          : std::optional<NodeLocation>(
                NodeLocation::from_pyobject(node_location_stack.top()));

  trace_builder.start_frame(frame_node_location, caller_node_location);

  Py_RETURN_NONE;
}

PyObject *end_frame(PyObject *self, PyObject *const *args, Py_ssize_t nargs) {
  trace_builder.end_frame();

  if (node_location_stack.empty()) {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

    trace_builder.accept(writer);

    std::ofstream file("trace.json");
    file << buffer.GetString();
  }

  Py_RETURN_NONE;
}

} // namespace callbacks
} // namespace tracer
