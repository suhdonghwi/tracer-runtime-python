import sys

from .eval_event_callbacks import callback_stdout


class StdoutInterceptor:
    def write(self, data: str):
        callback_stdout(data)

    def flush(self):
        pass


def initialize() -> None:
    sys.stdout = StdoutInterceptor()
    pass
