#SM3201204 Di Salvia Nicandro Alberto

# Definizione di eccezioni personalizzate per gestire errori specifici durante l'esecuzione del codice


class EmptyStackException(Exception):
    pass


class BadExpressionException(Exception):
    pass


class MissingVariableException(Exception):
    pass


##################################################
# Struttura dati


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


###################################################


# Classe astratta Expression per rappresentare espressioni
class Expression:
    # Il costruttore è astratto per impedire la creazione diretta di istanze di questa classe,
    # poiché Expression serve come base per sottoclassi che rappresentano specifiche espressioni.
    def __init__(self):
        raise NotImplementedError()

    @classmethod
    def from_program(cls, text: str, dispatch: dict):
        """
        Metodo di classe per costruire un albero di espressione da una stringa di programma.
        Utilizza un dizionario di dispatch per mappare le stringhe alle classi di operazioni.
        """
        pila = Stack()
        stringa = text.split("\n")
        # Il ciclo seguente analizza il programma linea per linea e elemento per elemento.
        # Identifica numeri, operazioni (tramite il dizionario di dispatch) e variabili,
        # costruendo passo dopo passo l'albero di espressione.
        for riga in stringa:
            for elem in riga.split():
                if elem.isdigit():
                    pila.push(Constant(int(elem)))
                elif elem in dispatch:
                    operation = dispatch[elem]
                    if operation.arity == 0:
                        args = []
                    else:
                        args = [pila.pop() for i in range(operation.arity)]
                    pila.push(operation(args))
                else:
                    pila.push(Variable(elem))
        if len(pila.data) != 1:
            raise BadExpressionException()
        return pila.pop()

    # Metodo astratto per valutare l'espressione. Deve essere implementato dalle sottoclassi,
    # che definiranno come l'espressione deve essere valutata in base all'ambiente fornito.
    def evaluate(self, env):
        raise NotImplementedError()


# Classe Variable per rappresentare variabili nelle espressioni
class Variable(Expression):
    def __init__(self, nome):
        self.nome = nome

    def evaluate(self, env):
        """
        Valuta la variabile nell'ambiente dato. Solleva un'eccezione se la variabile non è definita.
        """
        if self.nome not in env:
            raise MissingVariableException(f"La variabile '{self.nome}' non esiste")
        return env[self.nome]

    def __str__(self):
        return f"{self.nome}"


# Classe Constant per rappresentare costanti nelle espressioni
class Constant(Expression):
    def __init__(self, value):
        self.value = value

    def evaluate(self, env):
        return self.value

    def __str__(self):
        return f"{self.value}"


# Classe Operation come base per le operazioni (astratta)
class Operation(Expression):
    def __init__(self, args):
        self.args = args

    def evaluate(self, env):
        """
        Valuta l'operazione nell'ambiente dato.
        Distingue tra operazioni unarie e binarie.
        """
        if isinstance(self, UnaryOp):
            return self.op(self.args[0].evaluate(env))
        elif isinstance(self, BinaryOp):
            return self.op(self.args[0].evaluate(env), self.args[1].evaluate(env))

    def op(self, *args):
        raise NotImplementedError()  # Metodo per eseguire l'operazione specifica (astratto)

    def __str__(self):
        """
        Rappresentazione stringa dell'operazione basata sulla sua arità.
        """
        if type(self).arity == 2:
            return f"({self.args[0]} {self.args[1]})"
        elif type(self).arity == 1:
            return f"({self.args[0]})"


###########################################################################


# La classe BinaryOp estende la classe Operation per rappresentare operazioni binarie,
# cioè operazioni che richiedono due operandi.
class BinaryOp(Operation):
    arity = 2


# La classe UnaryOp estende la classe Operation per rappresentare operazioni unarie,
# cioè operazioni che richiedono un solo operando
class UnaryOp(Operation):
    arity = 1


###########################################################################


# La classe Alloc estende Expression per rappresentare l'allocazione di una variabile nell'ambiente.
# L'operazione ha un'arità di 1, indicando che richiede un solo argomento: il nome della variabile da allocare.
class Alloc(Expression):
    arity = 1

    def __init__(self, args):
        self.name = args[0].nome

    def evaluate(self, env):
        env[self.name] = 0
        return 0


# La classe Setq estende Expression per rappresentare l'assegnazione di un valore a una variabile.
# L'operazione ha un'arità di 2, indicando che richiede due argomenti: il nome della variabile e l'espressione da valutare e assegnare.
class Setq(Expression):
    arity = 2

    def __init__(self, args):
        self.name = args[0].nome
        self.espressione = args[1]

    def evaluate(self, env):
        valore = self.espressione.evaluate(env)
        env[self.name] = valore

        return valore


# La classe Valloc estende Expression per rappresentare l'allocazione di un array nella variabile specificata.
# L'operazione ha un'arità di 2, indicando che richiede due argomenti: il nome della variabile e la dimensione dell'array.
class Valloc(Expression):
    arity = 2

    def __init__(self, args):
        self.name = args[0].nome
        self.dim = args[1]

    def evaluate(self, env):
        dimensione = self.dim.evaluate(env)
        l = []
        for i in range(dimensione):
            l.append(0)
        env[self.name] = l

        return 0


# La classe Setv estende Expression per rappresentare l'assegnazione di un valore a un elemento specifico di un array.
# L'operazione ha un'arità di 3, indicando che richiede tre argomenti: il nome dell'array, l'indice e il valore da assegnare.
class Setv(Expression):
    arity = 3

    def __init__(self, args):
        self.name = args[0].nome
        self.indice = args[1]
        self.valore = args[2]

    def evaluate(self, env):
        i = self.indice.evaluate(env)
        valore = self.valore.evaluate(env)

        env[self.name][i] = valore

        return valore


# La classe Prog2 estende Expression per rappresentare una sequenza di due espressioni eseguite in ordine.
# L'operazione ha un'arità di 2, indicando che richiede due espressioni come argomenti.


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


# Come sopra
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


# Come sopra
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


class If(Expression):
    arity = 3

    def __init__(self, args):
        self.cond = args[0]
        self.y = args[1]
        self.n = args[2]

    def evaluate(self, env):
        if self.cond.evaluate(env):
            return self.y.evaluate(env)
        else:
            return self.n.evaluate(env)

    def __str__(self):
        return f"(if {self.cond} {self.y} {self.n})"


class While(Expression):
    arity = 2

    def __init__(self, args):
        self.cond = args[0]
        self.espressione = args[1]

    def evaluate(self, env):
        while self.cond.evaluate(env):
            self.espressione.evaluate(env)
        return 0

    def __str__(self):
        return f"(while {self.cond} {self.espressione})"


class For(Expression):
    arity = 4

    def __init__(self, args):
        self.name = args[0].nome
        self.inizio = args[1]
        self.fine = args[2]
        self.corpo = args[3]

    def evaluate(self, env):
        for i in range(self.inizio.evaluate(env), self.fine.evaluate(env)):
            env[self.name] = i
            self.corpo.evaluate(env)
        return

    def __str__(self):
        return f"(for {self.inizio} da {self.inizio} a {self.fine})"


class Subroutine(Expression):
    arity = 2

    def __init__(self, args):
        self.name = args[0].nome
        self.body = args[1]

    def evaluate(self, env):
        env[self.name] = self.body
        return

    def __str__(self):
        return f"(Subroutine {self.name} {self.body})"


class Call(Expression):
    arity = 1

    def __init__(self, args):
        self.nome = args[0].nome

    def evaluate(self, env):
        if self.nome in env:
            return env[self.nome].evaluate(env)
        else:
            raise ValueError(f"Non trovata")

    def __str__(self):
        return f"(call {self.nome})"


class Print(Expression):
    arity = 1

    def __init__(self, args):
        self.nome = args[0]

    def evaluate(self, env):
        out = self.nome.evaluate(env)
        print(out)
        return out

    def __str__(self):
        return f"(print {self.nome})"


class Noop(Expression):
    arity = 0

    def __init__(self, args):
        pass

    def evaluate(self, env):
        return 0

    def __str__(self):
        return "(nop)"


###########################################################################


class Addition(BinaryOp):

    def op(self, x, y):
        return x + y

    def __str__(self):
        return f"(+ {self.args[0]} {self.args[1]})"


class Subtraction(BinaryOp):

    def op(self, x, y):
        return x - y

    def __str__(self):
        return f"(- {self.args[0]} {self.args[1]})"


class Division(BinaryOp):

    def op(self, x, y):
        return x / y

    def __str__(self):
        return f"(/ {self.args[0]} {self.args[1]})"


class Multiplication(BinaryOp):

    def op(self, x, y):
        return x * y

    def __str__(self):
        return f"(* {self.args[0]} {self.args[1]})"


class Power(BinaryOp):

    def op(self, x, y):
        return x**y

    def __str__(self):
        return f"(** {self.args[0]}  {self.args[1]})"


class Modulus(BinaryOp):

    def op(self, x, y):
        return x % y

    def __str__(self):
        return f"(% {self.args[0]} {self.args[1]})"


class GreaterThan(BinaryOp):

    def op(self, x, y):
        return x > y

    def __str__(self):
        return f"(> {self.args[0]} {self.args[1]})"


class GreaterEqual(BinaryOp):

    def op(self, x, y):
        return x >= y

    def __str__(self):
        return f"(>= {self.args[0]} {self.args[1]})"


class Equal(BinaryOp):

    def op(self, x, y):
        return x == y

    def __str__(self):
        return f"(= {self.args[0]} {self.args[1]})"


class NotEqual(BinaryOp):

    def op(self, x, y):
        return x != y

    def __str__(self):
        return f"(!= {self.args[0]} {self.args[1]})"


class LessThan(BinaryOp):

    def op(self, x, y):
        return x < y

    def __str__(self):
        return f"(< {self.args[0]} {self.args[1]})"


class LessEqual(BinaryOp):

    def op(self, x, y):
        return x <= y

    def __str__(self):
        return f"(<= {self.args[0]} {self.args[1]})"


class Reciprocal(UnaryOp):

    def op(self, x):
        return 1 / x

    def __str__(self):
        return f"(1/ {self.args[0]})"


class AbsoluteValue(UnaryOp):

    def op(self, x):
        return abs(x)

    def __str__(self):
        return f"(abs{self.args[0]})"


###########################################################################

# dispatch

d = {
    "+": Addition,
    "*": Multiplication,
    "**": Power,
    "-": Subtraction,
    "/": Division,
    "%": Modulus,
    "1/": Reciprocal,
    "abs": AbsoluteValue,
    ">": GreaterThan,
    ">=": GreaterEqual,
    "=": Equal,
    "!=": NotEqual,
    "<": LessThan,
    "<=": LessEqual,
    "alloc": Alloc,
    "valloc": Valloc,
    "setq": Setq,
    "setv": Setv,
    "prog2": Prog2,
    "prog3": Prog3,
    "prog4": Prog4,
    "if": If,
    "while": While,
    "for": For,
    "defsub": Subroutine,
    "call": Call,
    "print": Print,
    "nop": Noop,
}

###########################################################################

example = "2 3 + x * 6 5 - / abs 2 ** y 1/ + 1/"
# e = Expression.from_program(example, d)
# res = e.evaluate({"x": 3, "y": 7})
# print(res)

example2 = "v print i i * i v setv prog2 10 0 i for 10 v valloc prog2"
example3 = "x print f call x alloc x 4 + x setq f defsub prog4"
example4 = "nop i print i x % 0 = if 1000 2 i for 783 x setq x alloc prog3"
example5 = "nop x print prime if nop 0 0 != prime setq i x % 0 = if 1 x - 2 i for 0 0 = prime setq prime alloc prog4 100 2 x for"
example6 = (
    "v print i j * 1 i - 10 * 1 j - + v setv 11 1 j for 11 1 i for 100 v valloc prog3"
)
example7 = "x print 1 3 x * + x setq 2 x / x setq 2 x % 0 = if prog2 1 x != while 50 x setq x alloc prog3"

k = Expression.from_program(example7, d)
ciao = k.evaluate({})
###########################################################################
