

d = {}

try:
    d[10] = d[10] + 1
except KeyError:
    d[10] = 0


def g(d1, d2, x):
    try:
        d1[x] = d2[x]
    except KeyError:
        print("Catturata l'eccezione in g")


def f(d1, d2, x):
    try:
        g(d1, d2, x)
    except KeyError:
        print("Catturata l'eccezione in f")


f(d, d, 100)
