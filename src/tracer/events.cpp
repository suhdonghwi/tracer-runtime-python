#include <Python.h>
#include <stack>

#include "../rapidjson/document.h"

#include "events.hpp"

namespace tracer {
namespace events {

std::stack<PyObject *> node_stack;
rapidjson::Document document;
std::stack<rapidjson::Value> frame_stack;

PyObject *begin_expr(PyObject *self, PyObject *const *args, Py_ssize_t nargs) {
  PyObject *node_location_obj = args[0];

  node_stack.push(node_location_obj);

  Py_INCREF(node_location_obj);
  return node_location_obj;
}

PyObject *end_expr(PyObject *self, PyObject *const *args, Py_ssize_t nargs) {
  PyObject *expr_result_obj = args[1];

  node_stack.pop();

  Py_INCREF(expr_result_obj);
  return expr_result_obj;
}

PyObject *begin_stmt(PyObject *self, PyObject *const *args, Py_ssize_t nargs) {
  PyObject *node_location_obj = args[0];

  node_stack.push(node_location_obj);

  Py_RETURN_NONE;
}

PyObject *end_stmt(PyObject *self, PyObject *const *args, Py_ssize_t nargs) {
  node_stack.pop();

  Py_RETURN_NONE;
}

PyObject *begin_frame(PyObject *self, PyObject *const *args, Py_ssize_t nargs) {
  PyObject *frame_node_location_obj = args[0];

  const char *file_id;
  int begin, end;

  if (!PyArg_ParseTuple(frame_node_location_obj, "sii", &file_id, &begin,
                        &end)) {
    return NULL;
  }

  rapidjson::Value file_id_json(file_id, document.GetAllocator());
  rapidjson::Value begin_json(begin);
  rapidjson::Value end_json(end);

  rapidjson::Value node_location_json(rapidjson::kArrayType);
  node_location_json.PushBack(file_id_json, document.GetAllocator());
  node_location_json.PushBack(begin_json, document.GetAllocator());
  node_location_json.PushBack(end_json, document.GetAllocator());

  rapidjson::Value children_json(rapidjson::kArrayType);

  rapidjson::Value new_frame(rapidjson::kObjectType);
  new_frame.AddMember("node_location", node_location_json,
                      document.GetAllocator());
  new_frame.AddMember("children", children_json, document.GetAllocator());

  frame_stack.push(std::move(new_frame));

  Py_RETURN_NONE;
}

PyObject *end_frame(PyObject *self, PyObject *const *args, Py_ssize_t nargs) {
  if (node_stack.empty()) {
    printf("end_frame: node_stack is empty\n");
    Py_RETURN_NONE;
  }

  PyObject *caller_node_location_obj = node_stack.top();

  auto frame_json = std::move(frame_stack.top());
  frame_stack.pop();

  const char *file_id;
  int begin, end;

  if (!PyArg_ParseTuple(caller_node_location_obj, "sii", &file_id, &begin,
                        &end)) {
    return NULL;
  }

  rapidjson::Value begin_json(begin);
  rapidjson::Value end_json(end);

  rapidjson::Value span_json(rapidjson::kArrayType);
  span_json.PushBack(begin_json, document.GetAllocator());
  span_json.PushBack(end_json, document.GetAllocator());

  rapidjson::Value child_trace_json(rapidjson::kObjectType);
  child_trace_json.AddMember("span", span_json, document.GetAllocator());
  child_trace_json.AddMember("trace", frame_json, document.GetAllocator());

  frame_stack.top()["children"].PushBack(child_trace_json,
                                         document.GetAllocator());

  Py_RETURN_NONE;
}

} // namespace events
} // namespace tracer
