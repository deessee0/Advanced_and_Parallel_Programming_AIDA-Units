class A(Exception):
    pass


class B(A):
    pass


try:
    raise B()
except A:
    print("Catturata A")
except B:
    print("Catturata B")
