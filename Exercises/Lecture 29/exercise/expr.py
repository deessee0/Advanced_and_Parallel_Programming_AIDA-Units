class EmptyStackException(Exception):
    pass


class Stack:

    def __init__(self):
        self.data = []

    def push(self, x):
        self.data.append(x)

    def pop(self):
        if self.data == []:
            raise EmptyStackException
        res = self.data[-1]
        self.data = self.data[0:-1]
        return res

    def __str__(self):
        return " ".join([str(s) for s in self.data])


class Expression:

    def __init__(self):
        raise NotImplementedError()

    @classmethod
    def from_program(cls, text, dispatch):
        pass

    def evaluate(self, env):
        raise NotImplementedError()


class MissingVariableException(Exception):
    pass


class Variable(Expression):

    def __init__(self, name):
        self.name = name

    def evaluate(self, env):
        pass

    def __str__(self):
        pass


class Constant(Expression):

    def __init__(self, value):
        self.value = value

    def evaluate(self, env):
        pass

    def __str__(self):
        pass


class Operation(Expression):

    def __init__(self, args):
        self.args = args

    def evaluate(self, env):
        pass

    def op(self, *args):
        raise NotImplementedError()

    def __str__(self):
        pass


class BinaryOp(Operation):
    pass


class UnaryOp(Operation):
    pass


class Addition(BinaryOp):
    pass


class Subtraction(BinaryOp):
    pass


class Division(BinaryOp):
    pass


class Multiplication(BinaryOp):
    pass


class Power(BinaryOp):
    pass


class Modulus(BinaryOp):
    pass


class Reciprocal(UnaryOp):
    pass


class AbsoluteValue(UnaryOp):
    pass


d = {"+": Addition, "*": Multiplication, "**": Power, "-": Subtraction,
     "/": Division, "1/": Reciprocal, "abs": AbsoluteValue}
example = "2 3 + x * 6 5 - / abs 2 ** y 1/ + 1/"
e = Expression.from_program(example, d)
print(e)
res = e.evaluate({"x": 3, "y": 7})
print(res)

# Ouput atteso:
# (1/ (+ (1/ y) (** 2 (abs (/ (- 5 6) (* x (+ 3 2)))))))
# 0.84022932953024
