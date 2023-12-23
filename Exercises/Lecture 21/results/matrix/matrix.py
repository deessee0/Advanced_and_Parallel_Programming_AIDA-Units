import random
import time

n = 1000
A = [random.random() for _ in range(n*n)]
B = [random.random() for _ in range(n*n)]
C = [0 for _ in range(n*n)]


def matmul(A, B, C, n):
    for i in range(n):
        for j in range(n):
            for k in range(n):
                C[i * n + j] += A[i * n + k] * B[k * n + j]


time_start = time.perf_counter()
matmul(A, B, C, n)
time_end = time.perf_counter()
print(f"Millisecondi necessari: {(time_end - time_start)*1000}")
