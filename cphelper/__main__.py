import argparse
from pathlib import Path
import shlex

from cphelper.color import color, Color
from cphelper.error import TestCaseError
from cphelper.filerule import FileRule
from cphelper.misc import generate_contest, generate_files, generate_inputs, \
        generate_snippets
from cphelper.runner import Runner
from cphelper.testcase import TestCase
from cphelper.util import multiglob

from cphelper.config.const import CORRECT_FILE_STEM_LIST, \
        GENERATOR_FILE_STEM_LIST
from cphelper.config.commandrule import COMMAND_RULE


def validate_file(arg: str):
    if not (file := Path(arg)).is_file():
        raise FileNotFoundError(f"The file {color(arg, Color.CYAN)} does not "
                                f"exist.")
    return file


def main():
    global debug_level

    parser = argparse.ArgumentParser(
        description="Competitive Programming Helper")
    
    parser.add_argument("-d", "--debug",
        type=int, choices=[1, 2], default=1,
        help="Sets debug level. 1 -> Warnings only, 2 -> Debug + Warnings")


    main_file_parser = argparse.ArgumentParser(add_help=False)
    main_file_parser.add_argument("-mf", "--main-file",
        type=validate_file, required=True,
        help="Path of main file that will be ran again the command rule. "
             "File must exist.")
    main_file_parser.add_argument("-mr", "--main-rule",
        choices=COMMAND_RULE.keys(), nargs="?",
        help="Comamnd rule that the main file uses. If not specified, then "
             "the program will guess based on the file's extension and "
             "patterns from all the known CommandRule.")

    basedir_parser = argparse.ArgumentParser(add_help=False)
    basedir_parser.add_argument("-b", "--basedir",
        nargs="?", type=Path, default=Path(),
        help="Base directory that all files should be generated from. For "
             "example, src/cses/1222 means that all files will be generated "
             "in that directory.")
    
    split_parser = argparse.ArgumentParser(add_help=False)
    split_parser.add_argument("-s", "--split", action="store_true",
        help="Split paths (because VSCode can't).")

    template_parser = argparse.ArgumentParser(add_help=False)
    template_parser.add_argument("-t", "--template", default="empty",
        help="Stem of template file to generate files with.")
    
    override_parser = argparse.ArgumentParser(add_help=False)
    override_parser.add_argument("-o", "--override", action="store_true",
        help="Override already generated files.")
    
    open_files_parser = argparse.ArgumentParser(add_help=False)
    open_files_parser.add_argument("-n", "--neovim-server", type=str,
        help="Server to open files in NeoVim.")
    open_files_parser.add_argument("-v", "--vscode-open", 
        action="store_true", help="Open files in VSCode.")
    

    subparser = parser.add_subparsers(help="Sub Commands", dest="command")

    subparser.add_parser("compile", parents=[main_file_parser],
        help="Compile main file.")

    input_parser = subparser.add_parser("input", parents=[main_file_parser],
        help="Run main file against input from stdin.")
    input_parser.add_argument("-t", "--times", type=int, default=1,
                              help="Numbe or times to run")

    subparser.add_parser("run", parents=[main_file_parser],
        help="Run main file against input from test cases.")
    
    subparser.add_parser("check", parents=[main_file_parser],
        help="Check main file against input from test cases.")
    
    counter_test_case_parser = subparser.add_parser("countertc",
        parents=[main_file_parser, open_files_parser],
        help="Generate counter testcase.")
    counter_test_case_parser.add_argument("-cf", "--correct-file",
        type=validate_file, required=False,
        help="Path of correct (brute force) file. If not specified, then it "
             "will be searched for using the main file.")
    counter_test_case_parser.add_argument("-cr", "--correct-rule",
        choices=COMMAND_RULE.keys(), nargs="?",
        help="Command rule that the correct file uses. If not specified, then "
             "the program will guess based on the correct file's extension and "
             "patterns from all the known CommandRule.")
    counter_test_case_parser.add_argument("-gf", "--generator-file",
        type=validate_file, required=False,
        help="Path of generator file. If not specified, then it "
             "will be searched for using the main file.")
    counter_test_case_parser.add_argument("-gr", "--generator-rule",
        choices=COMMAND_RULE.keys(), nargs="?",
        help="Command rule that the generator file uses. If not specified, "
             "then the program will guess based on the generator file's "
             "extension and patterns from all the known CommandRule.")
    
    generate_file_parser = subparser.add_parser("genfile",
        parents=[basedir_parser, split_parser, template_parser, override_parser,
                 open_files_parser],
        help="Generate files from path.")
    generate_file_parser.add_argument("-r", "--rule",
        choices=COMMAND_RULE.keys(), nargs="?",
        help="Comamnd rule that all the generate files will use. If not "
             "specified, then the program will guess based on the file's "
             "extension and patterns from all the known CommandRule.")
    generate_file_parser.add_argument("paths",
        nargs="*", type=str,
        help="Path(s) for the file generator to create (ex. test/main.cpp).")

    generate_input_parser = subparser.add_parser("geninput",
        parents=[basedir_parser, split_parser, open_files_parser],
        help="Generate input/output files.")
    generate_input_parser.add_argument("paths", type=str, nargs="+",
        help="Path(s) for input generator (ex. p1/1 p2/c2)")
    
    generate_contest_parser = subparser.add_parser("gencontest",
        parents=[basedir_parser, split_parser, template_parser, override_parser,
                 open_files_parser],
        help="Generate contest.")
    generate_contest_parser.add_argument("-r", "--rule",
        choices=COMMAND_RULE.keys(), nargs="?", required=True,
        help="Comamnd rule that all the generate files will use. Must be "
             "specified, as this cannot be inferred.")
    generate_contest_parser.add_argument("paths", type=str, nargs="+",
        help="Paths for each problem directory. (ex. A B C D E)")
    
    subparser.add_parser("gensnippets", help="Generate snippets.")
    
    subparser.add_parser("removecomments", parents=[main_file_parser],
        help="Remove comments from a file.")
    
    args = parser.parse_args()


    debug_level = args.debug


    if args.command == "compile":
        main_rule = COMMAND_RULE[args.main_rule] \
            if args.main_rule is not None else None
        runner = Runner(args.main_file, main_rule)
        runner.prehook()
        try:
            runner.compile()
        except (Exception, KeyboardInterrupt) as e:
            runner.posthook()
            raise e
    
    elif args.command == "input":
        main_rule = COMMAND_RULE[args.main_rule] \
            if args.main_rule is not None else None
        runner = Runner(args.main_file, main_rule)
        runner.prehook()
        try:
            runner.compile()
            runner.run_input(args.times)
        except (Exception, KeyboardInterrupt) as e:
            runner.posthook()
            raise e
        runner.posthook()
    
    elif args.command == "run":
        main_rule = COMMAND_RULE[args.main_rule] \
            if args.main_rule is not None else None
        runner = Runner(args.main_file, main_rule)
        runner.prehook()
        try:
            runner.compile()
            runner.run_testcases()
        except (Exception, KeyboardInterrupt) as e:
            runner.posthook()
            raise e
        runner.posthook()

    elif args.command == "check":
        main_rule = COMMAND_RULE[args.main_rule] \
            if args.main_rule is not None else None
        runner = Runner(args.main_file, main_rule)
        runner.prehook()
        try:
            runner.compile()
            runner.check_testcases()
        except (Exception, KeyboardInterrupt) as e:
            runner.posthook()
            raise e
        runner.posthook()
    
    elif args.command == "countertc":
        if args.correct_file is None:
            correct_file_globs = [x + ".*" for x in CORRECT_FILE_STEM_LIST]
            canidates = multiglob(args.main_file.parent, correct_file_globs)
            color_globs = ", ".join(color(x, Color.CYAN)
                                        for x in correct_file_globs)
            if len(canidates) == 0:
                parser.error(f"No canidates for correct (brute force) file in "
                             f"directory "
                             f"{color(str(args.main_file.parent), Color.CYAN)} "
                             f"using globs {color_globs}.")
            
            if len(canidates) == 2:
                color_canidates = ", ".join(color(str(x), Color.CYAN)
                                        for x in canidates)
                parser.error(f"Too many canidates {color_canidates} for "
                             f"correct (brute force) file in directory "
                             f"{color(str(args.main_file.parent), Color.CYAN)}."
                             )
            
            args.correct_file = canidates[0]
        
        if args.generator_file is None:
            generator_file_globs = [x + ".*" for x in GENERATOR_FILE_STEM_LIST]
            canidates = multiglob(args.main_file.parent, generator_file_globs)
            color_globs = ", ".join(color(x, Color.CYAN)
                                        for x in generator_file_globs)
            if len(canidates) == 0:
                parser.error(f"No canidates for generator file in directory "
                             f"{color(str(args.main_file.parent), Color.CYAN)} "
                             f"using globs {color_globs}.")
            
            if len(canidates) == 2:
                color_canidates = ", ".join(color(str(x), Color.CYAN)
                                        for x in canidates)
                parser.error(f"Too many canidates {color_canidates} for "
                             f"generator file in directory "
                             f"{color(str(args.main_file.parent), Color.CYAN)}."
                             )
            
            args.generator_file = canidates[0]
        
        main_rule = COMMAND_RULE[args.main_rule] \
            if args.main_rule is not None else None
        correct_rule = COMMAND_RULE[args.correct_rule] \
            if args.correct_rule is not None else None
        generator_rule = COMMAND_RULE[args.generator_rule] \
            if args.generator_rule is not None else None

        main_runner = Runner(args.main_file, main_rule)
        correct_runner = Runner(args.correct_file, correct_rule)
        generator_runner = Runner(args.generator_file, generator_rule)

        main_runner.prehook()
        correct_runner.prehook()
        generator_runner.prehook()

        try:
            main_runner.compile()
            correct_runner.compile()
            generator_runner.compile()
            main_runner.counter_testcase(correct_runner, generator_runner,
                                         args.neovim_server, args.vscode_open)

        except (Exception, KeyboardInterrupt) as e:
            main_runner.posthook()
            correct_runner.posthook()
            generator_runner.posthook()
            raise e

        main_runner.posthook()
        correct_runner.posthook()
        generator_runner.posthook()
    
    elif args.command == "genfile":
        if args.split:
            args.paths = shlex.split(str(args.paths[0]))
        
        rule = COMMAND_RULE[args.rule] if args.rule is not None else None
        
        files = [args.basedir / p for p in args.paths]
        generate_files(files, rule, args.template, args.override,
                       args.neovim_server, args.vscode_open)

    elif args.command == "geninput":
        if args.split:
            args.paths = shlex.split(str(args.paths[0]))

        testcases: list[TestCase] = []
        for path in args.paths:
            tc = TestCase.to_testcase(args.basedir, path)
            if tc is None:
                raise TestCaseError(f"Testcase with path: "
                                    f"{color(path, Color.CYAN)} "
                                    f"cannot be generated.")
                
            else:
                testcases.append(tc)
        generate_inputs(testcases, args.neovim_server, args.vscode_open) 


    elif args.command == "gencontest":
        if args.split:
            args.paths = shlex.split(str(args.paths[0]))
        
        rule = COMMAND_RULE[args.rule]
        
        generate_contest(args.basedir, rule, args.template, args.paths,
                         args.override, args.neovim_server, args.vscode_open)
    
    elif args.command == "gensnippets":
        generate_snippets()

    elif args.command == "removecomments":
        main_rule = COMMAND_RULE[args.main_rule] \
            if args.main_rule is not None else None

        file_rule = FileRule.from_file(args.main_file, main_rule)
        file_rule.language.comment_remover(args.main_file)


if __name__ == "__main__":
    main()


# TODO: Fix error, warning, debug messages


