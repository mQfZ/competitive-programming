from pathlib import Path

from cphelper.color import color, Color
from cphelper.language import Language

from cphelper.config.const import CP_LIBRARY_DIR


def cpp_snippet_expansion(snippets_dict: dict[Path, str], lib_dir: Path,
                          file: Path) -> None:
    """
    C++ snippet expansion.
    """

    if file in snippets_dict:
        return
    
    if not file.exists():
        raise FileNotFoundError(f"File: {color(str(file), Color.CYAN)} "
                                f"cannot be imported as it does not exist.")
    
    content = file.read_text()[:-1].split("\n")

    new: list[str] = []
    for i in range(len(content)):
        line = content[i]

        if (line in ["#include <bits/stdc++.h>",
                    "using namespace std;",
                    "#pragma once"]
                    and not (file.parent.name == "headers" and
                            file.parent.parent.name == "miscellaneous")) \
                or line.endswith("noimport"):
            continue
        
        if line.strip().startswith("#include <lib"):
            path = lib_dir / line.strip()[14:-1]
            if path not in snippets_dict:
                cpp_snippet_expansion(snippets_dict, lib_dir, path)
                new.extend(snippets_dict[path].split("\n"))
            continue
        
        new.append(line)

    snippets_dict[file] = "\n".join(new).strip()


def cpp_comment_remover(file: Path):
    content = file.read_text()[:-1].split("\n")
    new: list[str] = []

    comment = False

    for line in content:
        st = line.strip()
        
        if st.startswith("/**"):
            comment = True
            if new[-1] == "":
                new.pop()
            continue
            
        if st.startswith("*/"):
            comment = False
            continue
            
        if comment:
            continue

        if st.startswith("//"):
            continue

        new.append(line)
    
    with file.open("w") as f:
        f.write("\n".join(new))


LANGUAGE_LIST = [
    Language(
        lang="cpp",
        basedir=CP_LIBRARY_DIR / "cpp",
        suffix=".cpp",
        snippet_expansion=cpp_snippet_expansion,
        comment_remover=cpp_comment_remover
    ),
    Language(
        lang="python",
        suffix=".py",
        basedir=CP_LIBRARY_DIR / "python"
    )
]
"""
List that holds the languages.
"""


LANGUAGE = {language.lang: language for language in LANGUAGE_LIST}
"""
Dictionary that holds the language.
"""
