from cphelper.color import color, Color
from cphelper.testcasetype import TestCaseType


TEST_CASE_TYPE_LIST = [
    TestCaseType(
        name="normal",
        prefix="", color_prefix=f"",
        priority=1, prefix_priority=2
    ),
    TestCaseType(
        name="custom",
        prefix="c", color_prefix=f"{color('Custom', Color.CYAN)} ",
        priority=2, prefix_priority=1
    )
]
"""
List of current testcase Types that are implemented (thinking of more).
"""


TEST_CASE_TYPE = {
    testcase_type.name: testcase_type
        for testcase_type in TEST_CASE_TYPE_LIST
}
"""
Dictionary of testcase types with the key being the name.
"""


DEFAULT_TEST_CASE_TYPE = TEST_CASE_TYPE["custom"]
"""
Default test case type for a generated test case from a counter test case.
"""
