from pathlib import Path

from cphelper.commandrule import CommandRule

from cphelper.config.language import LANGUAGE


COMMAND_RULE_LIST = [
    CommandRule(
        name = "cppheader",
        suffix = ".h",
        pattern_priority = False,
        language = LANGUAGE["cpp"],
        compile_command = [
            "g++-13",

            # Type
            "-xc++-header",

            # Version
            "-std=c++20",

            # Define Local
            "-DLOCAL",

            # Compile File
            "${FILE}",

            # Output Binary
            "-o", "${FILE}.gch"
        ],
        binary_file = Path("${FILE}.gch"),
        run_command = None
    ),
    CommandRule(
        name = "cppheader-debug",
        suffix = ".h",
        pattern_priority = False,
        language = LANGUAGE["cpp"],
        compile_command = [
            "g++-13",

            # Type
            "-xc++-header",

            # Version
            "-std=c++20",

            # Basic Warnings
            "-O2", "-Wall", "-Wextra",

            # Extra Warnings
            "-pedantic", "-Wshadow", "-Wformat=2", "-Wfloat-equal",
            "-Wconversion", "-Wlogical-op", "-Wshift-overflow=2",
            "-Wduplicated-cond", "-Wcast-qual", "-Wcast-align",
            
            # Disabled Warnings
            "-Wno-sign-conversion", "-Wno-unused-parameter",
            "-Wno-unused-result", "-Wno-unused-variable",
            
            # Extra Debug
            "-D_FORTIFY_SOURCE=2", "-D_GLIBCXX_DEBUG",
            "-D_GLIBCXX_DEBUG_PEDANTIC",
            
            # Define Local
            "-DLOCAL",

            # Compile File
            "${FILE}",

            # Output Binary
            "-o", "${FILE}.gch"
        ],
        binary_file = Path("${FILE}.gch"),
        run_command = None
    ),
    CommandRule(
        name = "cpp",
        suffix = ".cpp",
        pattern_priority = False,
        language = LANGUAGE["cpp"],
        compile_command = [
            # Compiler
            "g++-13",

            # Type
            "-xc++",

            # Version
            "-std=c++20",

            # Include
            "-I${LIBRARY_DIR}",
            "-I${LIBRARY_DIR}/header",
            "-I${LIBRARY_DIR}/header/bits/normal",
            
            # Define Local
            "-DLOCAL",
            
            # Compile File
            "${FILE}",

            # Output Binary
            "-o", "${STEM}.bin"
        ],
        binary_file = Path("${STEM}.bin"),
        run_command = ["${STEM}.bin"],
    ),
    CommandRule(
        name = "cpp-debug",
        suffix = ".cpp",
        pattern_priority = True,
        language = LANGUAGE["cpp"],
        compile_command = [
            # Compiler
            "g++-13",

            # Type
            "-xc++",

            # Version
            "-std=c++20",

            # Basic Warnings
            "-O2", "-Wall", "-Wextra",

            # Extra Warnings
            "-pedantic", "-Wshadow", "-Wformat=2", "-Wfloat-equal",
            "-Wconversion", "-Wlogical-op", "-Wshift-overflow=2",
            "-Wduplicated-cond", "-Wcast-qual", "-Wcast-align",
            
            # Disabled Warnings
            "-Wno-sign-conversion", "-Wno-unused-parameter",
            "-Wno-unused-result", "-Wno-unused-variable",
            
            # Include
            "-I${LIBRARY_DIR}",
            "-I${LIBRARY_DIR}/header",
            "-I${LIBRARY_DIR}/header/bits/debug",

            # Extra Debug
            "-D_FORTIFY_SOURCE=2", "-D_GLIBCXX_DEBUG",
            "-D_GLIBCXX_DEBUG_PEDANTIC",
            
            # Define Local
            "-DLOCAL",

            # Compile File
            "${FILE}",

            # Output Binary
            "-o", "${STEM}.bin"
        ],
        binary_file = Path("${STEM}.bin"),
        run_command = ["${STEM}.bin"]
    ),
    CommandRule(
        name = "python",
        suffix = ".py",
        pattern_priority = True,
        language = LANGUAGE["python"],
        compile_command = None,
        binary_file = None,
        run_command = ["python3", "${FILE}"]
    )
]
"""
List of all currently loaded CommandRules.
"""


COMMAND_RULE: dict[str, CommandRule] = {
    command_rule.name: command_rule for command_rule in COMMAND_RULE_LIST
}
"""
Dictionary of all loaded CommandRule (the key is the name).
"""
