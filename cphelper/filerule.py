from __future__ import annotations
import dataclasses
from dataclasses import dataclass
import fnmatch
from pathlib import Path

from cphelper.color import color, Color
from cphelper.commandrule import CommandRule
from cphelper.debug import warning
from cphelper.error import RuleError
from cphelper.util import recursive_replace

from cphelper.config.commandrule import COMMAND_RULE_LIST


@dataclass(frozen=True)
class FileRule(CommandRule):
    """
    Same as CommandRule, but all the ${} variables have been replaced with
    a specific file. See CommandRule for more details over variables.
    """

    file: Path
    """
    File that the rule uses to reference (the file that the editor is on
    when code is being ran).
    """


    def __post_init__(self):
        replace_dict = {
            "${LIBRARY_DIR}": str(self.language.basedir),
            "${FILE}": str(self.file),
            "${STEM}": str(self.file.parent / self.file.stem),
            "${SUFFIX}": self.file.suffix,
        }

        for field in dataclasses.fields(self):
            attribute = getattr(self, field.name)
            object.__setattr__(self, field.name, recursive_replace(attribute,
                                                                  replace_dict))


    @classmethod
    def from_file(cls, file: Path,
                  command_rule: CommandRule | None) -> FileRule:
        """
        Generates a FileRole from a CommandRule and a file.
        """

        if isinstance(command_rule, FileRule):
            raise RuleError("Cannot create FileRule from another FileRule")

        if command_rule is None:
            priority: dict[bool, list[CommandRule]] = {True: [], False: []}
            color_file = color(str(file), Color.CYAN)

            for command_rule in COMMAND_RULE_LIST:
                if fnmatch.fnmatch(str(file), "*" + command_rule.suffix):
                    priority[command_rule.pattern_priority] \
                        .append(command_rule)
                
            if len(priority[True]) == 1:
                command_rule = priority[True][0]
            
            elif len(priority[True]) > 1:
                command_rule = priority[True][0]
                joined_rules = ", ".join(color(rule.name, Color.CYAN)
                                         for rule in priority[True])

                warning(f"Too many command rules ({joined_rules}) "
                        f"with priority for file: {color_file}.")
            
            else:
                warning(f"No command rules with priority for "
                        f"file: {color_file}. Defaulting to "
                        f"non-priority command rules.")

                if len(priority[False]) == 1:
                    command_rule = priority[False][0]
                
                elif len(priority[False]) > 1:
                    command_rule = priority[False][0]
                    joined_rules = ", ".join(color(rule.name, Color.CYAN)
                                         for rule in priority[False])

                    warning(f"Too many command rules ({joined_rules}) "
                            f"with non-priority for file: {color_file}.")
                
                else:
                    raise RuleError(f"No command rules for file: "
                                    f"{color_file}.")

        passed = {field.name: getattr(command_rule, field.name)
                  for field in dataclasses.fields(command_rule)}
        return cls(file=file, **passed)
