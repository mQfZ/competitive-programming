from dataclasses import dataclass
from pathlib import Path

from cphelper.language import Language


@dataclass(frozen=True)
class CommandRule:
    """
    A rule that a file uses to compile and run. Comes with other important
    information that is necessary to identify the command rule. Strings may
    include ${} variables that are affected by the file, which is not included
    in the file rule.
    """

    name: str
    """
    Name of the rule.
    ex. "python"
    """

    suffix: str
    """
    Suffix of the file that satisifes the rule.
    ex. ".py"
    """

    pattern_priority: bool
    """
    True if it takes priority over other rules, False if not.
    """

    language: Language
    """
    Library that stores information about the language.
    ex. Language["cpp"]
    """

    compile_command: list[str] | None
    """
    Command passed to subprocess.run when file compiles (if any).
    ex. ["g++", "${FILE}", "-o", "./${STEM}.bin"]
    """

    binary_file: Path | None
    """
    Binary file generated by the compile_command (if any).
    ex. Path("${STEM}.bin")
    """

    run_command: list[str] | None
    """
    Command passed to subprocess.run when file runs (if any).
    ex. ["python3", "${FILE}"]
    """
