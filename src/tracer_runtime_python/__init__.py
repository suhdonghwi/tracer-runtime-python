"""
tracer_runtime_python package
Mirrors the public API from the C extension.
"""

# 1) Import the log initialization so that it happens on import
from .execution_log import execution_log_init

# 2) Import callbacks
from .execution_callbacks import (
    callback_begin_frame,
    callback_end_frame,
    callback_begin_stmt,
    callback_end_stmt,
    callback_begin_expr,
    callback_end_expr,
)

# 3) Map original C names to these Python callback functions
begin_module = callback_begin_frame
end_module = callback_end_frame

begin_func = callback_begin_frame
end_func = callback_end_frame

begin_stmt = callback_begin_stmt
end_stmt = callback_end_stmt

begin_expr = callback_begin_expr
end_expr = callback_end_expr

# 4) Initialize the log once the package is loaded
execution_log_init()
