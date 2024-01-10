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
        pila = Stack()
        stringa = text.split()
        op = dispatch.keys()

        for i in range(0, len(stringa)):
            if stringa[i].isdigit():
                new = Constant(int(stringa[i]))
                pila.push(new)

            elif stringa[i] in op:
                if dispatch[stringa[i]].arity == 1:
                    x = pila.pop()

                    pila.push(dispatch[stringa[i]]([stringa[i], x]))

                if dispatch[stringa[i]].arity == 2:
                    x = pila.pop()
                    y = pila.pop()

                    pila.push(dispatch[stringa[i]]([stringa[i], x, y]))
            else:
                pila.push(Variable(stringa[i]))

        if len(pila.data) != 1:
            print(f"Pila finale: {pila}")
            raise ValueError("La pila non contiene un solo elemento!")

        return pila.pop()

    def evaluate(self, env):
        raise NotImplementedError()


class MissingVariableException(Exception):
    pass


class Variable(Expression):
    def __init__(self, name):
        self.name = name
    
    def evaluate(self, env):
        if self.name not in env:
            raise MissingVariableException(f"La variabile '{self.name}' non esiste")
        return env[self.name]

    def __str__(self):
        return str(self.name)


class Constant(Expression):
    def __init__(self, value):
        self.value = value

    def evaluate(self, env):
        return self.value

    def __str__(self):
        return str(self.value)


class Operation(Expression):
    def __init__(self, args):
        self.args = args

    def evaluate(self, env):
        if isinstance(self, UnaryOp):
            # Per operazioni unarie, passa un singolo argomento
            return self.op(self.args[1].evaluate(env))
        else:
            # Per operazioni binarie, passa due argomenti
            return self.op(self.args[1].evaluate(env), self.args[2].evaluate(env))

    def op(self, *args):
        raise NotImplementedError()

    def __str__(self):
        if type(self).arity == 2:
            return f"({self.args[0]} {self.args[1]} {self.args[2]})"
        else:
            return f"({self.args[0]} {self.args[1]})"


class BinaryOp(Operation):
    arity = 2


class UnaryOp(Operation):
    arity = 1


class Addition(BinaryOp):
    def op(self, *args):
        return args[0] + args[1]


class Subtraction(BinaryOp):
    def op(self, *args):
        return args[0] - args[1]


class Division(BinaryOp):
    def op(self, *args):
        return args[0] / args[1]


class Multiplication(BinaryOp):
    def op(self, *args):
        return args[0] * args[1]


class Power(BinaryOp):
    def op(self, *args):
        return args[0] ** args[1]


class Modulus(BinaryOp):
    def op(self, *args):
        return args[0] % args[1]


class Reciprocal(UnaryOp):
    def op(self, *args):
        print(args)
        return 1 / args[0]


class AbsoluteValue(UnaryOp):
    def op(self, *args):
        return abs(args[0])


d = {
    "+": Addition,
    "*": Multiplication,
    "**": Power,
    "-": Subtraction,
    "/": Division,
    "1/": Reciprocal,
    "abs": AbsoluteValue
}

example = "2 3 + x * 6 5 - / abs 2 ** y 1/ + 1/"
e = Expression.from_program(example, d)
print(e)
res = e.evaluate({"x": 3, "y": 7})
print(res)

# Ouput atteso:
# (1/ (+ (1/ y) (** 2 (abs (/ (- 5 6) (* x (+ 3 2)))))))
# 0.84022932953024
