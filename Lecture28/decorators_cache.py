from functools import wraps

caches = {}


def cached(f):
    name = f.__name__
    if name not in caches:
        caches[name] = {}
    @wraps(f)
    def with_cache(x):
        if x in caches[name]:
            return caches[name][x]
        res = f(x)
        caches[name][x] = res
        return res
    return with_cache


@cached
def f(x):
    for i in range(100_000_000):
        x += i
    return x
