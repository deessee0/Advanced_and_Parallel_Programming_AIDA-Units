from functools import reduce, partial

f = lambda x: x + 2

print(f(3))

g = lambda x, y: x + 2*y

print(g(3,4))


lst = list(range(20))

map_res = map(lambda x: x + 3, lst)
print(list(map_res))

filter_res = filter(lambda x: x % 2 == 0, lst)
print(list(filter_res))

reduce_res = reduce(lambda x, y: x + y, lst)
print(reduce_res)


def somma(x, y):
    return x + y


somma3 = partial(somma, 3)
print(somma3(5))
