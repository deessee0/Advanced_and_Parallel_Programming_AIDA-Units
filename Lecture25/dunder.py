class Dual:

    def __init__(self, a, b):
        self.a = a
        self.b = b

    def __add__(self, other):
        if isinstance(other, Dual):
            ra = self.a + other.a
            rb = self.b + other.b
        else:
            ra = self.a + other
            rb = self.b
        return Dual(ra, rb)

    def __sub__(self, other):
        if isinstance(other, Dual):
            ra = self.a - other.a
            rb = self.b - other.b
        else:
            ra = self.a - other
            rb = self.a
        return Dual(ra, rb)

    def __mul__(self, other):
        if isinstance(other, Dual):
            ra = self.a * other.a
            rb = self.a * other.b + self.b * other.a
        else:
            ra = self.a * other
            rb = self.b * other
        return Dual(ra, rb)
  
    def __str__(self):
        return f"{self.a} + {self.b}ε"


x = Dual(3, 1)
y = 3
z = -2
w = x * x * x + x*y + x*x*z + 8
fun = "x³ + xy + x²z + 8"
print(f"La derivata {fun} rispetto a x valutata in {x.a} è {w.b}")


class DefaultDict:

    def __init__(self, default):
        self.__default = default
        self.__content = {}

    @classmethod
    def from_dict(cls, d, default):
        dd = cls(default)
        dd.__content = d
        return dd

    def __getitem__(self, k):
        if k in self.__content:
            return self.__content[k]
        else:
            return self.__default

    def __setitem__(self, k, v):
        self.__content[k] = v

    def __delitem__(self, k):
        if k in self.__content:
            del self.__content[k]

    def __contains__(self, k):
        return k in self.__content


print("Esempio di DefaultDict")
d = DefaultDict(0)
d[1] = 20
d[4] = 12
for i in range(0, 10):
    print(d[i])

print("DefaultDict da dizionario")
tmp = {3: 4, 7: 8}
d2 = DefaultDict.from_dict(tmp, 0)
for i in range(0, 10):
    print(d2[i])


class LinearFunction:

    def __init__(self, m, q):
        self.m = m
        self.q = q

    def __call__(self, x):
        return self.m * x + self.q


print("Utilizzo di una classe come funzione")
f = LinearFunction(2.4, 3)
print(f(4))
