class A:

    def __init__(self):
        print("inizializzazione di A")

    def m(self):
        print("Metodo di A")


class B(A):

    def __init__(self):
        print("inizializzazione di B")

    def m(self):
        print("Metodo di B")


class C(A):

    def __init__(self):
        print("inizializzazione di C")

    def m(self):
        print("Metodo di C")


class D(C, B):

    def __init__(self):
        print("inizializzazione di D")
