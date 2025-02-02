from typing import Any, Optional

from .eval_event_log import (
    log_begin_frame,
    log_end_frame,
    source_location_stack,
)


def callback_begin_frame(frame_source_location: Any) -> None:
    caller_source_location: Optional[Any] = None
    if source_location_stack:
        caller_source_location = source_location_stack[-1]

    log_begin_frame(frame_source_location, caller_source_location)


def callback_end_frame(frame_source_location: Any) -> None:
    log_end_frame()


def callback_begin_stmt(source_location: Any) -> None:
    source_location_stack.append(source_location)


def callback_end_stmt(source_location: Any) -> None:
    source_location_stack.pop()


def callback_begin_expr(source_location: Any) -> Any:
    source_location_stack.append(source_location)
    return source_location


def callback_end_expr(source_location: Any, expr_result: Any) -> Any:
    source_location_stack.pop()
    return expr_result
