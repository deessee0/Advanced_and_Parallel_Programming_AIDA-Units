from itertools import product, chain, pairwise, permutations, combinations, repeat

a = [1, 2, 3, 4]
b = [5, 6, 7, 8]
c = [9, 10, 11, 12, 13, 14, 15]

print("Concatenazione di iteratori")
for i in chain(a, b, c):
    print(i)


print("Prodotto di iteratori")
for i, j in product(a, b):
    print(f"{i}, {j}")

print("Iterazione sulle coppie di valori")
for i, j in pairwise(a):
    print(f"{i}, {j}")

print("Iterazione sulle permutazioni")
for i in permutations(a):
    print(i)

print("Iterazione sulle combinazioni")
for i in combinations(a, r=2):
    print(i)

print("Ripetizione di uno stesso valore")
for i in repeat("ciao", 10):
    print(i)
