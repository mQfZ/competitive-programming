import json
from pathlib import Path

from cphelper.commandrule import CommandRule
from cphelper.filerule import FileRule
from cphelper.language import Language
from cphelper.testcase import TestCase
from cphelper.util import open_with_neovim, open_with_vscode

from cphelper.config.const import DEFAULT_MAIN_FILE_STEM, VSCODE_SNIPPETS_FILE
from cphelper.config.language import LANGUAGE_LIST


def template_to_str(language: Language, template: str):
    """
    Converts a rule and language into a Path to the template.
    """
    
    return Path(language.template_directory /
                (template + language.suffix)).read_text()


def generate_files(files: list[Path], command_rule: CommandRule | None,
                   template: str, override: bool = False,
                   neovim_server: str | None = None,
                   vscode_open: bool = False):
    """
    Generate files.
    If a command rule is provided, then all files will use that command rule.
    Otherwise, use the file to guess the command rule.
    """

    file_template_tuple: list[tuple[Path, str]] = []

    for file in files:
        rule = FileRule.from_file(file, command_rule)
        template_content = template_to_str(rule.language, template)
        file_template_tuple.append((file, template_content))
        
    for file, template_content in file_template_tuple:
        if not file.exists() or override:
            file.parent.mkdir(parents=True, exist_ok=True)
            file.write_text(template_content)

    if neovim_server is not None:
        open_with_neovim(neovim_server, files)

    if vscode_open:
        open_with_vscode(files)


def generate_contest(basedir: Path, command_rule: CommandRule, template: str,
                     paths: list[str], override: bool = False,
                     neovim_server: str | None = None,
                     vscode_open: bool = False):
    """
    Generate contest.
    """
    
    file_template_tuple: list[tuple[Path, str]] = []
    
    for path in paths:
        path = basedir / path

        file = path / (DEFAULT_MAIN_FILE_STEM + command_rule.language.suffix)
        template_content = template_to_str(command_rule.language, template)
        file_template_tuple.append((file, template_content))
    
    basedir.mkdir(parents=True, exist_ok=True)

    for file, template_content in file_template_tuple:
        file.parent.mkdir(exist_ok=True)
        if not file.exists() or override:
            file.write_text(template_content)

    files = [file[0] for file in file_template_tuple]

    if neovim_server is not None:
        open_with_neovim(neovim_server, files)
    
    if vscode_open:
        open_with_vscode(files)


def generate_inputs(testcases: list[TestCase],
                    neovim_server: str | None = None,
                    vscode_open: bool = False):
    """
    Generate inputs. (.in, .out)
    """

    files: list[Path] = []
    for testcase in testcases:
        testcase.create_io_files()
        files.append(testcase.input_file)
        files.append(testcase.output_file)
    
    if neovim_server is not None:
        open_with_neovim(neovim_server, files)

    if vscode_open:
        open_with_vscode(files)


def generate_snippets():
    """
    Generate all snippets.
    """

    neovim_snippets = {}
    vscode_snippets = {}

    for library in LANGUAGE_LIST:
        for snippet in library.library_directory.glob("**/*"):
            if not snippet.is_file():
                continue

            snippets_obj = {}

            library.snippet_expansion(snippets_obj, library.library_directory,
                                      snippet)

            if library.lang not in neovim_snippets:
                neovim_snippets[library.lang] = {}

            neovim_snippets[library.lang][snippet.stem] = {
                "prefix": snippet.stem,
                "body": snippets_obj[snippet]
            }

            vscode_snippets[library.lang + " " + snippet.stem] = {
                "prefix": [snippet.stem],
                "scope": library.lang,
                "body": snippets_obj[snippet]
            }

    VSCODE_SNIPPETS_FILE.write_text(
            json.dumps(vscode_snippets, indent=4, sort_keys=True))
