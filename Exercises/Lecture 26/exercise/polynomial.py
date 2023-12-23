from collections import defaultdict


class Polynomial:

    def __init__(self, coeffs):
        pass

    def __getitem__(self, k):
        pass

    def __setitem__(self, k, v):
        pass

    def __call__(self, x):
        pass

    def __add__(self, other):
        pass

    def __sub__(self, other):
        pass

    def __mul__(self, other):
        pass

    def __pow__(self, n):
        pass

    def derivative(self):
        pass

    def __str__(self):
        pass


def newton_raphson(p, x, n_iter=20):
    pass


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
