from cphelper.color import color, Color

from cphelper.config.const import debug_level


def debug(message: str) -> None:
    if debug_level >= 2:
        print(color("DEBUG", Color.BLUE) + ": " + message)


def warning(message: str) -> None:
    if debug_level >= 1:
        print(color("WARNING", Color.BOLD_RED) + ": " + message)
