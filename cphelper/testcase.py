from __future__ import annotations
from dataclasses import dataclass
from functools import total_ordering
from pathlib import Path

from cphelper.color import color, Color
from cphelper.debug import warning
from cphelper.error import TestCaseError
from cphelper.testcasetype import TestCaseType

from cphelper.config.testcasetype import TEST_CASE_TYPE_LIST


@total_ordering
@dataclass
class TestCase:
    """
    Actual testcase, which incldues the directory and id of the testcase, as
    well as the type of the testcase.
    """

    basedir: Path
    """
    Path of the parent of the testcase. For example, fold1/fold2/1.in
    would be fold1/fold2.
    """

    test_type: TestCaseType
    """
    See TestCaseType for more details.
    """

    id: int
    """
    ID of the testcase. Might change to string in the future? (prob not).
    """


    @property
    def color_name(self):
        """
        Full name (in color).
        """

        return self.test_type.color_prefix + color("Testcase", Color.BLUE) \
                 + " " + color(str(self.id), Color.BOLD_YELLOW)


    @property
    def full_id(self) -> str:
        """
        Full name of the testcase.
        ex. c1.in -> c1   (id is only 1)
        """

        return self.test_type.prefix + str(self.id)

    
    @property   
    def input_file(self) -> Path:
        """
        Input file of the testcase.
        """

        return Path(self.basedir / (self.full_id + ".in"))
    

    @property
    def output_file(self) -> Path:
        """
        Output file of the testcase.
        """

        return Path(self.basedir / (self.full_id + ".out"))
    

    @property
    def input_str(self) -> str:
        """
        Contents of the input file.
        """

        return self.input_file.read_text()
    

    @property
    def output_str(self) -> str:
        """
        Contents of the output file.
        """

        return self.output_file.read_text()
    

    def create_io_files(self) -> None:
        """
        Creates the input_file and output_file.
        """

        self.basedir.mkdir(parents=True, exist_ok=True)
        self.input_file.touch()
        self.output_file.touch()
    

    def io_exists(self) -> bool:
        """
        Returns if the input/output files exist.
        """

        return (self.basedir / (self.full_id + ".in" )).exists() and \
               (self.basedir / (self.full_id + ".out")).exists()


    @staticmethod
    def split_full_id(full_id: str) -> tuple[TestCaseType, int] | None:
        """
        Splits an ID into it's respective testcase type and id, if possible.
        Returns the one with lowest priority.

        Ex. split_full_id("c1") -> (TEST_CASE_TYPES["custom"], 1)
        """

        color_full_id = color(full_id, Color.CYAN)

        testcase_types = sorted(
            list(filter(lambda test_type: test_type.fits_prefix(full_id),
                        TEST_CASE_TYPE_LIST)),
            key=lambda test_type: test_type.prefix_priority
        )

        if len(testcase_types) == 0:
            raise TestCaseError("Dont know how we got here ...")
        
        lowest_priority = testcase_types[0].prefix_priority
        testcase_types = list(filter(
            lambda test_type: test_type.prefix_priority == lowest_priority,
            testcase_types))
        
        if len(testcase_types) != 1:
            joined_test_types = ", ".join(color(tct.name, Color.CYAN)
                                          for tct in TEST_CASE_TYPE_LIST)
            warning(f"Too many testcase types ({joined_test_types}) "
                    f"with lowest priority {lowest_priority} "
                    f"fits id: {color_full_id}. Defaulting to "
                    f"{Color.CYAN}{testcase_types[0].name}{Color.RESET}")
        
        return testcase_types[0].split_full_id(full_id)
    
    
    @classmethod
    def to_testcase(cls, basedir: Path, full_id: str) -> TestCase | None:
        """
        Converts a path into a testcase, if possible.
        """
        
        pos = cls.split_full_id(full_id)
        if pos is None:
            return None
        test_type, id = pos

        return cls(basedir, test_type, id)
    

    def __lt__(self, other: TestCase):
        if self.__class__ == other.__class__:
            if self.test_type != other.test_type:
                return self.test_type < other.test_type
            return self.id < other.id


def get_testcases(basedir: Path) -> list[TestCase]:
    """
    Gets all testcases in a directory.
    """

    stems = set(child.stem for child in basedir.iterdir())
    testcases: list[TestCase] = []

    for stem in stems:
        tc = TestCase.to_testcase(basedir, stem)
        if tc is not None and tc.io_exists():
            testcases.append(tc)
    
    return testcases


def new_smallest_id_testcase(basedir: Path, tct: TestCaseType) -> TestCase:
    """
    Generates next smallest test case of certain test case type in directory.

    Ex. test/1.in test/1.out, test/2.in
    will override test/2.in and return TestCase(test, Normal, 2)
    """

    id = 1
    while True:
        tc = TestCase(basedir, tct, id)
        if not tc.io_exists():
            return tc
        id += 1
