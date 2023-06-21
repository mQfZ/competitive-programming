class CPHelperError(Exception):
    """
    Base Competitive Programming helper error.
    """

    pass


class RuleError(CPHelperError):
    """
    Error while processing a file rule.
    """

    pass


class TestCaseError(CPHelperError):
    """
    Error while processing a testcase.
    """
