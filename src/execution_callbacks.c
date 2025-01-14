#define STB_DS_IMPLEMENTATION
#include "libs/stb_ds.h"

#include "execution_callbacks.h"
#include "execution_log.h"

static PyObject **source_location_object_stack;

PyObject *callback_begin_frame(PyObject *self, PyObject **args) {
  PyObject *frame_source_location_object = args[0];

  PyObject *caller_source_location_object = NULL;
  if (arrlen(source_location_object_stack) > 0) {
    caller_source_location_object = arrlast(source_location_object_stack);
  }

  execution_log_begin_frame(
      frame_source_location_object,
      caller_source_location_object
  );
  Py_RETURN_NONE;
}

PyObject *callback_end_frame(PyObject *self, PyObject **args) {
  execution_log_end_frame();

  Py_RETURN_NONE;
}

PyObject *callback_begin_stmt(PyObject *self, PyObject **args) {
  PyObject *source_location_object = args[0];
  arrpush(source_location_object_stack, source_location_object);

  Py_RETURN_NONE;
}

PyObject *callback_end_stmt(PyObject *self, PyObject **args) {
  arrpop(source_location_object_stack);

  Py_RETURN_NONE;
}

PyObject *callback_begin_expr(PyObject *self, PyObject **args) {
  PyObject *source_location_object = args[0];

  Py_INCREF(source_location_object);
  arrpush(source_location_object_stack, source_location_object);

  Py_INCREF(source_location_object);
  return source_location_object;
}

PyObject *callback_end_expr(PyObject *self, PyObject **args) {
  PyObject *popped_source_location_object =
      arrpop(source_location_object_stack);
  Py_DECREF(popped_source_location_object);

  PyObject *expr_result_object = args[1];

  Py_INCREF(expr_result_object);
  return expr_result_object;
}
