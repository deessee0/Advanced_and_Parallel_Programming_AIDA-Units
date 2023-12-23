from joblib import Parallel, delayed


def f(x):
    res = 0
    for i in range(10000):
        res += i * x
    return res


n = 100

[f(i) for i in range(n)]

Parallel(n_jobs=4)(delayed(f)(i) for i in range(n))
