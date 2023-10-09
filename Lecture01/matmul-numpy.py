import time
import numpy as np

n = 512
m = 512
p = 512

a = np.random.rand(n, p)
b = np.random.rand(p, m)

start = time.time()
c = np.dot(a, b)
end = time.time()

print(f"Time required {end-start}s")
