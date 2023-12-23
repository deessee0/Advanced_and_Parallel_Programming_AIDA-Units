from copy import copy

def f():
    def g(x):
        return x + 2
    return g


h = f()
print(h(3))


def make_adder(n):
    def adder(m):
        return n + m

    return adder


add3 = make_adder(3)
print(add3(2))


def list_concat(first):
    def concat(second):
        res = copy(first)
        res.append(second)
        return res
    return concat


x = [1, 2, 3]
c = list_concat(x)
print(c([5, 6, 7]))
x[0] = 12
print(c([5, 6, 7]))
