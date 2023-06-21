import os
from pathlib import Path
import re
import subprocess
import textwrap
from typing import Any

from cphelper.color import color, Color

from cphelper.config.const import VSCODE_BINARY


def multireplace(string: str, replacements: dict[str, str],
                 ignore_case: bool = False) -> str:
    """
    Given a string and a replacement map, it returns the replaced string.
    """
    
    if not replacements:
        return string
    
    if ignore_case:
        def normalize_old(s: str) -> str:
            return s.lower()

        re_mode = re.IGNORECASE
    else:
        def normalize_old(s: str) -> str:
            return s
        re_mode = 0

    replacements = {normalize_old(key): val
                    for key, val in replacements.items()}
    rep_sorted = sorted(replacements, key=len, reverse=True)
    rep_escaped = map(re.escape, rep_sorted)
    pattern = re.compile("|".join(rep_escaped), re_mode)
    return pattern.sub(
        lambda match: replacements[normalize_old(match.group(0))], string)


def recursive_replace(o: Any, replacements: dict[str, str] = dict()) -> Any:
    """
    Recursively replaces all strings in a class.

    So far, str, set, list, dict, Path have been implemented.
    """

    if isinstance(o, str):
        return multireplace(o, replacements)
    
    if isinstance(o, set):
        return set(recursive_replace(e, replacements)
                   for e in o) #  type: ignore
    
    if isinstance(o, list):
        return [recursive_replace(e, replacements)
                for e in o]  # type: ignore
    
    if isinstance(o, dict):
        return {recursive_replace(k, replacements):
                recursive_replace(v, replacements)
                for k, v in o.items()}  # type: ignore
    
    if isinstance(o, Path):
        return Path(recursive_replace(o.name, replacements))
    
    return o


def multiglob(basedir: Path, globs: list[str]) -> list[Path]:
    """
    Globs multiple patterns instead of only one.
    """

    files_grabbed: list[Path] = []
    for glob in globs:
        files_grabbed.extend(basedir.glob(glob))
    
    return files_grabbed


def strip_output(s: str) -> list[str]:
    """
    Strips output of all strings of length > 0.
    """

    split = list(filter(lambda x: len(x) > 0, s.split('\n')))
    return [x.strip() for x in split]


def is_different(output_str: str, correct_str: str) -> bool:
    """
    Checks whether there is a difference between output and correct.
    """

    output = strip_output(output_str)
    correct = strip_output(correct_str)

    return output != correct


def print_different(output_str: str, correct_str: str) -> None:
    """
    Print difference between output and correct.
    """

    output = strip_output(output_str)
    correct = strip_output(correct_str)
    
    if output == correct:
        print(color("Correct!", Color.GREEN))
        return
    
    half_width = int(os.get_terminal_size().columns / 2) - 1
    
    if len(output) > len(correct):
        correct.extend([""] * (len(output) - len(correct)))

    if len(correct) > len(output):
        output.extend([""] * (len(correct) - len(output)))
    
    print('{0:{1}} {2}'.format(color("Output", Color.RED),
                               half_width + 12,
                               color("Correct", Color.GREEN)))
    
    for i in range(0, len(correct)):
        lhs = textwrap.wrap(output[i], width=half_width - 1)
        rhs = textwrap.wrap(correct[i], width=half_width - 1)

        if len(lhs) > len(rhs):
            rhs.extend([""] * (len(lhs) - len(rhs)))

        elif len(lhs) < len(rhs):
            lhs.extend([""] * (len(rhs) - len(lhs)))

        for j in range(0, len(lhs)):
            print('{0:{1}} | {2}'.format(lhs[j], half_width - 1, rhs[j]))

        if len(lhs) > 1:
            print()


def open_with_vscode(files: list[Path]) -> None:
    """
    Open Files with VSCode.
    """

    process = [VSCODE_BINARY]
    process.extend(str(file) for file in files)
    
    subprocess.run(process)


def open_with_neovim(server: str, files: list[Path]) -> None:
    """
    Open Files with NeoVim.
    """

    process = ["nvim", "--server", server, "--remote-send", "<C-\\><C-N><C-w><C-p>"]

    subprocess.run(process)
    
    process = ["nvim", "--server", server, "--remote"]
    process.extend(str(file) for file in files)

    subprocess.run(process)
    
    process = ["nvim", "--server", server, "--remote-send", "<C-w><C-p>i"]

    subprocess.run(process)

