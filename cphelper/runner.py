from __future__ import annotations
from pathlib import Path
import subprocess
import sys

from cphelper.color import color, Color
from cphelper.debug import debug
from cphelper.error import RuleError
from cphelper.commandrule import CommandRule
from cphelper.filerule import FileRule
from cphelper.testcase import get_testcases, TestCase, new_smallest_id_testcase
from cphelper.util import is_different, print_different, open_with_neovim, \
        open_with_vscode

from cphelper.config.testcasetype import DEFAULT_TEST_CASE_TYPE


class Runner:
    """
    Uses a file and command rule to generate a file rule and testcases.
    Then uses that to run code.
    """

    def __init__(self, file: Path, command_rule: CommandRule | None = None):
        self.file = file
        self.command_rule_name = command_rule.name if command_rule \
                                        is not None else 'default'
        
        debug(f"Creating runner from file: {color(str(file), Color.CYAN)} "
              f"and command rule: "
              f"{color(self.command_rule_name, Color.CYAN)}")

        self.rule = FileRule.from_file(file, command_rule)
        self.testcases = get_testcases(file.parent)
        self.testcases.sort()
    

    def prehook(self):
        """
        Code to run prior to compiling/running.
        """

        debug(f"Running prehook for {color(self.file.name, Color.CYAN)} ...")

        if self.rule.compile_command is not None:
            if self.rule.binary_file is not None:
                self.rule.binary_file.unlink(missing_ok=True)
    

    def compile(self):
        """
        Compiles a file into a binary using the compiler rules.
        """

        if self.rule.compile_command is not None:
            debug(f"Compiling {color(self.file.name, Color.CYAN)} ... ")

            out = subprocess.run(self.rule.compile_command, text=True)

            if out.returncode != 0:
                raise RuleError(f"Error while compiling with rule: "
                                f"{color(self.rule.name, Color.CYAN)}")
            
        else:
            debug(f"No compiling rule for file "
                  f"{color(self.file.name, Color.CYAN)} ...")
    

    def run(self, input: str | None = None, capture_stdout: bool = False,
            capture_stderr: bool = False) -> subprocess.CompletedProcess[str]:
        """
        Run file.
        """
        
        stdout = subprocess.PIPE if capture_stdout else sys.stdout
        stderr = subprocess.PIPE if capture_stderr else sys.stderr 

        if self.rule.run_command is not None:
            debug(f"Running {color(self.file.name, Color.CYAN)} ...")

            if input is None:
                out = subprocess.run(self.rule.run_command, stdout=stdout,
                                    stderr=stderr, text=True)
            else:
                out = subprocess.run(self.rule.run_command, input=input,
                                     stdout=stdout, stderr=stderr, text=True)
            
            if out.returncode != 0:
                print(f"{Color.BOLD_RED}Error{Color.RESET}: Return Code: " \
                      f"{out.returncode}", file=sys.stderr)

            return out
        
        else:
            raise RuleError(f"Command rule: "
                            f"{color(self.rule.name, Color.CYAN)} "
                            f"does not have a run command.")
    

    def run_input(self, times: int = 1):
        """
        Run with user input.
        """

        for i in range(1, times + 1):
            print(f"{color('Input', Color.BLUE)} "\
                  f"{color(str(i), Color.BOLD_YELLOW)}:")
            self.run()
            print()
    

    def run_testcase(self, testcase: TestCase):
        """
        Run single testcase.
        """

        print(testcase.color_name + ": ")
        out = self.run(input=testcase.input_str, capture_stdout=True,
                       capture_stderr=False)
        print(out.stdout)
        print()


    def run_testcases(self):
        """
        Run all testcases.
        """

        for testcase in self.testcases:
            self.run_testcase(testcase)
    

    def check_testcase(self, testcase: TestCase):
        """
        Check single testcase.
        """

        print(testcase.color_name + ": ")
        out = self.run(input=testcase.input_str, capture_stdout=True,
                       capture_stderr=False)
        print_different(out.stdout, str(testcase.output_str))
        print()
    

    def check_testcases(self) -> None:
        """
        Check all testcases.
        """

        for testcase in self.testcases:
            self.check_testcase(testcase)


    def counter_testcase(self, correct: Runner, generator: Runner,
                         neovim_server: str | None = None,
                         vscode_open: bool = False):
        """
        Generate counter testcase.
        """

        debug("Generating counter testcases ... ")
        debug(f"\n"
              f"Main file                 : {str(self.file.name)}\n"
              f"Correct (brute force) file: {str(correct.file.name)}\n"
              f"Generator file            : {str(generator.file.name)}")
        times = 0
        while True:
            generator_out = generator.run(capture_stdout=True)
            gen_text = generator_out.stdout

            main_out = self.run(input=gen_text, capture_stdout=True)
            correct_out = correct.run(input=gen_text, capture_stdout=True)

            times += 1
            print(f"Iteration: {color(str(times), Color.CYAN)}")

            if is_different(main_out.stdout, correct_out.stdout):
                break
        
        parent = self.file.parent

        tc = new_smallest_id_testcase(parent, DEFAULT_TEST_CASE_TYPE)
        tc.create_io_files()
        tc.input_file.write_text(gen_text)
        tc.output_file.write_text(correct_out.stdout)

        self.check_testcase(tc)

        files = [tc.input_file, tc.output_file]

        if neovim_server is not None:
            open_with_neovim(neovim_server, files)

        if vscode_open:
            open_with_vscode(files)
    

    def posthook(self):
        """
        Code to run after all commands are finished.
        """

        debug(f"Running posthook for {color(self.file.name, Color.CYAN)} ...")

        if self.rule.compile_command is not None:
            if self.rule.binary_file is not None:
                self.rule.binary_file.unlink(missing_ok=True)
