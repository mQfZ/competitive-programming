from pathlib import Path


debug_level = 1
"""
1 -> Errors, Warnings.
2 -> Errors, Warnings, Debug.
"""

BASE_DIR = Path(__file__).parents[2]
"""Base directory of the Competitive Programming directory."""

CP_LIBRARY_DIR = BASE_DIR / "cphelper" / "library"
"""Directory of the Competitive Programming library."""

VSCODE_SNIPPETS_FILE = BASE_DIR / ".vscode" / "cp.code-snippets"
"""VSCode snippets file."""


MAIN_FILE_STEM_LIST = ["main"]
"""
File name stems that could be a main file.
"""

DEFAULT_MAIN_FILE_STEM = "main"
"""
Default main file stem that files will generate with.
"""


CORRECT_FILE_STEM_LIST = ["correct", "brute"]
"""
File name stems that could be a correct (brute force) file.
"""


GENERATOR_FILE_STEM_LIST = ["generator", "gen"]
"""
File name stems that could be a generator file.
"""


VSCODE_BINARY = \
    "/Applications/Visual Studio Code.app/Contents/Resources/app/bin/code"
"""
Location of VSCode Binary.
"""
