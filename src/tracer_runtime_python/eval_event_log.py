import atexit
import orjson
from typing import Any, Dict, List, Optional

# Global state
eval_event_log: List[Dict[str, Any]] = []
source_location_stack: List[Any] = []


def log_init() -> None:
    eval_event_log.clear()
    source_location_stack.clear()


def log_begin_frame(
    frame_source_location: Any, caller_source_location: Optional[Any]
) -> None:
    event = {
        "type": "begin_frame",
        "source_location": frame_source_location,
        "caller_source_location": caller_source_location,
    }
    eval_event_log.append(event)


def log_end_frame() -> None:
    event = {"type": "end_frame"}
    eval_event_log.append(event)


def log_write() -> None:
    file_path = "./eval_event_log.json"
    try:
        with open(file_path, "wb") as f:
            data = orjson.dumps(eval_event_log)
            f.write(data)
    except Exception as e:
        print(f"Failed to write eval event log to file: {e}")


@atexit.register
def on_exit() -> None:
    log_write()
