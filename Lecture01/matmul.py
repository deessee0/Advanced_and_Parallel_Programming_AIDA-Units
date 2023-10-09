import time
import random


def make_random_matrix(n, m):
    return [[random.random()
             for i in range(0, m)]
            for j in range(0, n)]


def make_empty_matrix(n, m):
    return [[0
             for i in range(0, m)]
            for j in range(0, n)]


def matmul(A, B, C):
    """Compute the product of A and B and put the result in C"""
    n = len(A)
    m = len(B[0])
    p = len(A[0])
    for i in range(0, n):
        for j in range(0, m):
            for k in range(0, p):
                C[i][j] += A[i][k] * B[k][j]
    return


n = 512
m = 512
p = 512

A = make_random_matrix(n, p)
B = make_random_matrix(p, m)
C = make_empty_matrix(n, m)

start = time.time()
matmul(A, B, C)
end = time.time()

print(f"time required: {end - start}s")

# print(C)
