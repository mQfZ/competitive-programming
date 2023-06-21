from __future__ import annotations
from dataclasses import dataclass
from functools import total_ordering


@total_ordering
@dataclass
class TestCaseType:
    """
    Types of testcases that are able to be generated, ran, and solved.
    """

    name: str
    """
    Name of the testcase type.
    ex. "normal"
    """

    prefix: str
    """
    Prefix of the testcase type. Generally the first letter of the name,
    but normal is "" because 1.in is a normal testcase.
    ex. "c"
    """

    color_prefix: str
    """
    Prefix to printing a real testcase when ran.
    ex. "Custom " (with color)
    """

    priority: int
    """
    Priority when printing out testcases. The smaller, the higher priority.
    ex. 1
    """

    prefix_priority: int
    """
    Priority when checking a testcase for determining which testcase type it
    is. For example, c1 would technically pass the type of a normal test
    case (all would because the prefix is empty). However, because prefix
    priority of custom testcases is 1, whereas normal is 2, it would return
    a custom testcase.
    ex. 1
    """


    def fits_prefix(self, full_id: str) -> bool:
        """
        Checks if full_id can possibly be of this testcase.
        """

        return full_id.startswith(self.prefix)
    

    def split_full_id(self, full_id: str) -> tuple[TestCaseType, int] | None:
        """
        Splits full_id into it's testcase type and id, respectively.
        If not possible, returns None
        Ex. Custom: split_full_id("c1") -> custom, 1
        Ex. Custom: split_full_id("casdf") -> None  (starts w/ c, but not int)
        Ex. Custom: split_full_id("asdf") -> None
        """

        if not self.fits_prefix(full_id):
            return None
        
        id = full_id[len(self.prefix):]
        if not id.isdigit():
            return None
        
        return self, int(id)

    
    def __lt__(self, other: TestCaseType):
        if self.__class__ == other.__class__:
            return self.priority < other.priority
        return NotImplemented
