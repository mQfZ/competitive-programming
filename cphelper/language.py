from dataclasses import dataclass
from pathlib import Path
from typing import Callable


def default_snippet_expansion(snippets_dict: dict[Path, str],
                              lib_dir: Path, file: Path) -> None:
    """
    Default snippet expansion.
    """

    snippets_dict[file] = file.read_text().strip()


def default_comment_remover(file: Path):
    """
    Default comment remover.
    """
    
    return None


@dataclass(frozen=True)
class Language:
    """
    Library that tells information about snippets, snippet generation, lib, etc.
    """

    lang: str
    """
    Name of the language.
    """

    basedir: Path
    """
    Base directory name of the language itself.
    """

    suffix: str
    """
    Snippet suffix of the snippets.
    """

    template_directory_name: str = "template"
    """
    Name for directory that holds the templates.
    """

    library_directory_name: str = "lib"
    """
    Directory that holds the languages library.
    """

    snippet_expansion: Callable[[dict[Path, str], Path, Path], None] = \
        default_snippet_expansion
    """
    Snippet expansion function.
    The callable inside is the recursive function, the Path is the file,
    the return is the snippet for the file.
    """

    comment_remover: Callable[[Path], None] = \
        default_comment_remover
    """
    Automatically removes comments from a file.
    """

    
    @property
    def template_directory(self):
        return self.basedir / self.template_directory_name
    

    @property
    def library_directory(self):
        return self.basedir / self.library_directory_name
