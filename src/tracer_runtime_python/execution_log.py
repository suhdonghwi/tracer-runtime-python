import atexit
import orjson
from typing import Any, Dict, List, Optional

# Global state
execution_log: List[Dict[str, Any]] = []
source_location_stack: List[Any] = []


def execution_log_init() -> None:
    """
    Initialize (or reset) the global log and stack.
    This mimics the C function `execution_log_init()`.
    """
    execution_log.clear()
    source_location_stack.clear()


def execution_log_begin_frame(
    frame_source_location: Any, caller_source_location: Optional[Any]
) -> None:
    """
    Log an event of type 'begin_frame'.
    Corresponds to `execution_log_begin_frame(...)` in C.
    """
    event = {
        "type": "begin_frame",
        "source_location": frame_source_location,
        "caller_source_location": caller_source_location,
    }
    execution_log.append(event)


def execution_log_end_frame() -> None:
    """
    Log an event of type 'end_frame'.
    Corresponds to `execution_log_end_frame()` in C.
    """
    event = {"type": "end_frame"}
    execution_log.append(event)


def execution_log_write() -> None:
    """
    Write the entire execution log to `./execution_log.json` using orjson.
    Corresponds to `execution_log_write()` in C.
    """
    file_path = "./execution_log.json"
    try:
        with open(file_path, "wb") as f:
            data = orjson.dumps(execution_log)
            f.write(data)
    except Exception as e:
        print(f"Failed to write execution log to file: {e}")


@atexit.register
def on_exit() -> None:
    """
    Automatically write the log when the Python interpreter exits.
    This replaces `Py_AtExit(execution_log_write)` from the C code.
    """
    execution_log_write()
