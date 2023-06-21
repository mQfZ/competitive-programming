class Color:
    """
    Terminal color codes.
    """

    RESET = "\033[0m"

    BLACK = "\033[0;30m"
    RED = "\033[0;31m"
    GREEN = "\033[0;32m"
    YELLOW = "\033[0;33m"
    BLUE = "\033[0;34m"
    PURPLE = "\033[0;35m"
    CYAN = "\033[0;36m"
    WHITE = "\033[0;37m"

    BOLD_BLACK = "\033[0;30m"
    BOLD_RED = "\033[0;31m"
    BOLD_GREEN = "\033[0;32m"
    BOLD_YELLOW = "\033[0;33m"
    BOLD_BLUE = "\033[0;34m"
    BOLD_PURPLE = "\033[0;35m"
    BOLD_CYAN = "\033[0;36m"
    BOLD_WHITE = "\033[0;37m"


def color(message: str, color: str) -> str:
    return color + message + Color.RESET
