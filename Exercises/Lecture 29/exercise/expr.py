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

                if dispatch[stringa[i]].arity == 3:
                    x = pila.pop()
                    y = pila.pop()
                    z = pila.pop()

                    pila.push(dispatch[stringa[i]]([stringa[i], x, y, z]))

                if dispatch[stringa[i]].arity == 4:
                    x = pila.pop()
                    y = pila.pop()
                    z = pila.pop()
                    k = pila.pop()

                    pila.push(dispatch[stringa[i]]([stringa[i], x, y, k]))
            else:
                pila.push(Variable(stringa[i]))

        return pila.pop()

    def evaluate(self, env):
        raise NotImplementedError


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


class Alloc(Expression):
    arity = 1

    def __init__(self, args):
        self.name = args[0]

    def evaluate(self, env):
        env[self.name] = 0
        return 0


class Setq(Expression):
    arity = 2

    def __init__(self, args):
        self.name = args[0]
        self.espressione = args[1]

    def evaluate(self, env):
        valore = self.name.evaluate(env)
        env[self.name] = valore

        return valore


class Valloc(Expression):
    arity = 2

    def __init__(self, args):
        self.name = args[0]
        self.dim = args[1]

    def evaluate(self, env):
        dimensione = self.dim.evaluate(env)
        l = []
        for i in range(0, dimensione):
            l.append(0)
        env[self.name.name] = l

        return 0


class Setv(Expression):
    arity = 3

    def __init__(self, args):
        self.name = args[0]
        self.indice = args[1]
        self.valore = args[2]

    def evaluate(self, env):
        indice = self.indice.evaluate(env)
        valore = self.valore.evaluate(env)

        env[self.name.name][indice] = valore

        return valore


class Prog2(Expression):
    arity = 2

    def __init__(self, args):
        self.espressione1 = args[0]
        self.espressione2 = args[1]

    def evaluate(self, env):
        self.espressione1.evaluate(env)
        return self.espressione2.evaluate(env)

    def __str__(self):
        return f"(prog 2 {self.espressione1} {self.espressione2})"


class Prog3(Expression):
    arity = 3

    def __init__(self, args):
        self.espressione1 = args[0]
        self.espressione2 = args[1]
        self.espressione3 = args[2]

    def evaluate(self, env):
        self.espressione1.evaluate(env)
        self.espressione2.evaluate(env)
        return self.espressione3.evaluate(env)

    def __str__(self):
        return f"(prog 3 {self.espressione1} {self.espressione2} {self.espressione3})"


class Prog4(Expression):
    arity = 4

    def __init__(self, args):
        self.espressione1 = args[0]
        self.espressione2 = args[1]
        self.espressione3 = args[2]
        self.espressione4 = args[3]

    def evaluate(self, env):
        self.espressione1.evaluate(env)
        self.espressione2.evaluate(env)
        self.espressione3.evaluate(env)
        return self.espressione4.evaluate(env)

    def __str__(self):
        return f"(prog 4 {self.espressione1} {self.espressione2} {self.espressione3}  {self.espressione4})"


class If(Operation):
    arity = 3

    def __init__(self, args):
        self.cond = args[0]
        self.y = args[1]
        self.n = args[2]

    def evaluate(self, env):
        if self.cond.evaluate(env):
            return self.y
        else:
            return self.n

    def __str__(self):
        return f"(if {self.cond} {self.y} {self.n})"


class While(Operation):
    arity = 2

    def __init__(self, args):
        self.cond = args[0]
        self.espressione = args[1]

    def evaluate(self, env):
        while self.cond.evaluate(env):
            self.espressione.evaluate(env)
        return None

    def __str__(self):
        return f"(while {self.cond} {self.espressione})"


class For(Operation):
    arity = 4

    def __init__(self, args):
        self.name = args[0]
        self.inizio = args[1]
        self.fine = args[2]
        self.corpo = args[3]

    def evaluate(self, env):
        for i in range(self.inizio.evaluate(env), self.fine.evaluate(env)):
            env[self.name.name] = i
            self.corpo.evaluate(env)
        return None

    def __str__(self):
        return f"(for {self.inizio} da {self.inizio} a {self.fine})"


class Subroutine(Expression):
    arity = 2

    def __init__(self, args):
        self.name = args[0]
        self.body = args[1]

    def evaluate(self, env):
        env[self.name] = self.body
        return None

    def __str__(self):
        return f"(Subroutine {self.name} {self.body})"


class Call(Expression):
    arity = 1

    def __init__(self, args):
        self.name = args[0]

    def evaluate(self, env):
        if self.name.name in env:
            return env[self.name.name].evaluate(env)
        else:
            raise ValueError(f"Non trovata")


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
        return 1 / args[0]


class AbsoluteValue(UnaryOp):
    def op(self, *args):
        return abs(args[0])


class Maggiore(BinaryOp):
    def op(self, *args):
        return args[0] > args[1]


class MaggioreUguale(BinaryOp):
    def op(self, *args):
        return args[0] >= args[1]


class Uguale(BinaryOp):
    def op(self, *args):
        return args[0] == args[1]


class Minore(BinaryOp):
    def op(self, *args):
        return args[0] < args[1]


class MinoreUguale(BinaryOp):
    def op(self, *args):
        return args[0] <= args[1]


class Diverso(BinaryOp):
    def op(self, *args):
        return args[0] != args[1]


d = {
    "+": Addition,
    "*": Multiplication,
    "**": Power,
    "-": Subtraction,
    "/": Division,
    "1/": Reciprocal,
    "abs": AbsoluteValue,
    "alloc": Alloc,
    "setq": Setq,
    "valloc": Valloc,
    "setv": Setv,
    "prog2": Prog2,
    "prog3": Prog3,
    "prog4": Prog4,
    "if": If,
    "while": While,
    "for": For,
    "defsub": Subroutine,
    "call": Call,
    ">": Maggiore,
    ">=": MaggioreUguale,
    "=": Uguale,
    "<": Minore,
    "<=": MinoreUguale,
    "!=": Diverso,
}

example = "2 3 + x * 6 5 - / abs 2 ** y 1/ + 1/"
example2 = "v print i i * i v setv prog2 10 0 i for 10 v valloc prog2"
example3 = "x print f call x alloc x 4 + x setq f defsub prog4"
example4 = "nop i print i x % 0 = if 1000 2 i for 783 x setq x alloc prog3"
example5 = "nop x print prime if nop 0 0 != prime setq i x % 0 = if 1 x - 2 i for 0 0 = prime setq prime alloc prog4 100 2 x for"
e = Expression.from_program(example, d)
due = Expression.from_program(example2, d)
tre = Expression.from_program(example3, d)
quattro = Expression.from_program(example4, d)
cinque = Expression.from_program(example5, d)

print(e)
print(due)
print(tre)
print(quattro)
print(cinque)
