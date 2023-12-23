from collections import defaultdict


class Polynomial:

    def __init__(self, coeffs):
        self.__coeffs = defaultdict(int)
        for k in coeffs:
            self.__coeffs[k] = coeffs[k]

    def __getitem__(self, k):
        return self.__coeffs[k]

    def __setitem__(self, k, v):
        self.__coeffs[k] = v

    def __call__(self, x):
        res = 0
        for k in self.__coeffs:
            res += self.__coeffs[k] * (x ** k)
        return res

    def __add__(self, other):
        if isinstance(other, Polynomial):
            p = Polynomial([])
            for k in self.__coeffs:
                p[k] += self[k]
            for k in other.__coeffs:
                p[k] += other[k]
        elif isinstance(other, int) or isinstance(other, float):
            p = Polynomial(self.__coeffs)
            p[0] += other
        else:
            p = None
        return p

    def __sub__(self, other):
        if isinstance(other, Polynomial):
            p = Polynomial([])
            for k in self.__coeffs:
                p[k] = self[k]
            for k in other.__coeffs:
                p[k] -= other[k]
        elif isinstance(other, int) or isinstance(other, float):
            p = Polynomial(self.__coeffs)
            p[0] -= other
        else:
            p = None
        return p

    def __mul__(self, other):
        if isinstance(other, Polynomial):
            p = Polynomial([])
            for k1 in self.__coeffs:
                for k2 in other.__coeffs:
                    p[k1+k2] += self[k1] * other[k2]
        elif isinstance(other, int) or isinstance(other, float):
            p = Polynomial(self.__coeffs)
            for k in p.__coeffs:
                p[k] *= other
        else:
            p = None
        return p

    def __pow__(self, n):
        p = Polynomial({0: 1})
        for i in range(n):
            p *= self
        return p

    def derivative(self):
        p = Polynomial({})
        for c in self.__coeffs:
            if (c > 0):
                p[c-1] = self[c] * c
        return p

    def __str__(self):
        s = []
        for c in reversed(sorted(self.__coeffs.keys())):
            s.append(f"{self.__coeffs[c]}x^{c}")
        return " + ".join(s)


def newton_raphson(p, x, n_iter=20):
    p_prime = p.derivative()
    for i in range(n_iter):
        if p_prime(x) == 0:
            break
        x = x - p(x)/p_prime(x)
    return x


p1 = Polynomial({4: 2, 3: 5, 1: 6, 0: -2})
p2 = Polynomial({3: 1, 2: 0.5, 1: -1, 0: 3})
print(p1)
print(p2)
print(p1 + p2)
print(p1 * p2)
print(p1(3))
print((p1+p2)(20))
print(p1.derivative())
x = newton_raphson(p1, 5)
print(f"p({x}) = {p1(x)}")
