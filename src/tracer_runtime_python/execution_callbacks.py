from typing import Any, Optional

from .execution_log import (
    execution_log_begin_frame,
    execution_log_end_frame,
    source_location_stack,
)


def callback_begin_frame(frame_source_location: Any) -> None:
    """
    C signature: PyObject *callback_begin_frame(PyObject *self, PyObject **args)

    In Python: Accept a 'frame_source_location' object, look up
    the caller (top of stack if present), and log a 'begin_frame'.
    """
    caller_source_location: Optional[Any] = None
    if source_location_stack:
        caller_source_location = source_location_stack[-1]

    execution_log_begin_frame(frame_source_location, caller_source_location)


def callback_end_frame(frame_source_location: Any) -> None:
    """
    C signature: PyObject *callback_end_frame(PyObject *self, PyObject **args)
    """
    execution_log_end_frame()


def callback_begin_stmt(source_location: Any) -> None:
    """
    C signature: PyObject *callback_begin_stmt(PyObject *self, PyObject **args)

    Push source location onto the stack.
    """
    source_location_stack.append(source_location)


def callback_end_stmt(source_location: Any) -> None:
    """
    C signature: PyObject *callback_end_stmt(PyObject *self, PyObject **args)

    Pop source location from stack.
    """
    source_location_stack.pop()


def callback_begin_expr(source_location: Any) -> Any:
    """
    C signature: PyObject *callback_begin_expr(PyObject *self, PyObject **args)

    Push location onto stack. Return it (in C, the function returns Py_None or PyObject).
    Here, we just return the passed source_location.
    """
    source_location_stack.append(source_location)
    return source_location


def callback_end_expr(source_location: Any, expr_result: Any) -> Any:
    """
    C signature: PyObject *callback_end_expr(PyObject *self, PyObject **args)

    Pop the stack and return the expr_result object.
    """
    source_location_stack.pop()
    return expr_result
