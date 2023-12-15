from functools import wraps


def wrap_function(f):
    def wrapped(*args, **kwargs):
        print("Sto per chiamare la funzione")
        x = f(*args, **kwargs)
        print("Ho chiamato la funzione")
        return x
    return wrapped


@wrap_function
def adder(x, y):
    return x + y


adder(2, 3)


def logger(f):
    def add_logger(*args, **kwargs):
        with open("log.txt", "a") as log:
            log.write(f"calling with args {args} and {kwargs}\n")
            res = f(*args, **kwargs)
            log.write(f"result: {res}\n")
            return res
    return add_logger


@logger
def list_product(lst):
    p = 1
    for x in lst:
        p *= x
    return p


list_product([1, 2, 3, 4, 5])
list_product([22, 44])


def better_logger(filename):
    def logger(f):
        @wraps(f)
        def add_logger(*args, **kwargs):
            with open(filename, "a") as log:
                log.write(f"calling with args {args} and {kwargs}\n")
                res = f(*args, **kwargs)
                log.write(f"result: {res}\n")
                return res
        return add_logger
    return logger


@better_logger("mylog.txt")
def list_product2(lst):
    p = 1
    for x in lst:
        p *= 2*x
    return p


list_product2([1, 2, 3, 4, 5])
list_product2([22, 44])
