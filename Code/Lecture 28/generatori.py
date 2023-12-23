def simple_gen():
    yield 1
    yield 2
    yield 3


x = simple_gen()
print(next(x))
print(next(x))
print(next(x))


def squares(n_elems):
    for n in range(n_elems):
        yield n**2


s = squares(10)
for i in s:
    print(i)
