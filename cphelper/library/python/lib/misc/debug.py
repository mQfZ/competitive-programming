class Debug:
    sys = __import__('sys')
    inspect = __import__('inspect')

    def __init__(self):
        pass

    class ANSI:
        DEBUG = '\033[02m'
        EXPRESSION = '\033[36m'
        VALUE = '\033[01m'
        TYPE = '\033[32m'
        RESET = '\033[0m'

    @staticmethod
    def stderr(*args, **kwargs):
        print(*args, file=Debug.sys.stderr, **kwargs)

    @staticmethod
    def getname(obj):
        for name in globals():
            if globals()[name] is obj:
                return name
        return False
    
    @staticmethod
    def gettype(obj):
        return type(obj).__name__

    def dbg(self, *arg):
        caller = self.inspect.getframeinfo(self.inspect.stack()[1][0])
        for obj in arg:
            obj_name = self.getname(obj)
            obj_type = self.gettype(obj)
            m = ""

            m += self.ANSI.DEBUG + '[' + str(caller.lineno) + ']' \
                + self.ANSI.RESET + ' '

            if obj_name is not False:
                m += self.ANSI.EXPRESSION + obj_name \
                    + self.ANSI.RESET + ' = ' + self.ANSI.VALUE + str(obj) \
                    + self.ANSI.RESET
            else:
                m += self.ANSI.VALUE + str(obj) + self.ANSI.RESET

            m += ' (' + self.ANSI.TYPE + obj_type + self.ANSI.RESET + ')'

            self.stderr(m)

        self.stderr()

dbg = Debug().dbg
