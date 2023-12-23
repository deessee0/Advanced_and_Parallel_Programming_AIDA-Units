import random
from ctypes import cdll, c_bool, c_float, c_int, pointer, POINTER, Structure


class CTreeNode(Structure):
    pass


CTreeNode._fields_ = [("key", c_int),
                      ("value", c_float),
                      ("left", POINTER(CTreeNode)),
                      ("right", POINTER(CTreeNode))]


class CTree:

    code = None

    def __init__(self):
        if CTree.code is None:
            CTree.code = cdll.LoadLibrary("libtree.so")
            CTree.code.insert.argtypes = [POINTER(CTreeNode), c_int, c_float]
            CTree.code.insert.restype = POINTER(CTreeNode)
            CTree.code.search.argtypes = [POINTER(CTreeNode),
                                          c_int, POINTER(c_float)]
            CTree.code.search.restype = c_bool
            CTree.code.destroy.argtypes = [POINTER(CTreeNode)]
        self.root = POINTER(CTreeNode)()

    def search(self, key):
        pass

    def insert(self, key, value):
        pass

    def __str__(self):
        pass

    def __del__(self):
        CTree.code.destroy(self.root)


class Node:

    def __init__(self, key, value):
        pass

    def search(self, key):
        pass

    def insert(self, key, value):
        pass

    def __str__(self):
        pass


class BinarySearchTree:

    def __init__(self):
        pass

    def search(self, key):
        pass

    def insert(self, key, value):
        pass

    def __str__(self):
        pass


if __name__ == "__main__":
    bst = BinarySearchTree()
    for i in range(0, 20):
        bst.insert(random.randint(0, 30), random.random())
    for i in range(0, 10):
        k = random.randint(0, 30)
        print(f"Searching for {k}: {bst.search(k)}")
    print(bst)

    # Decommentare per la parte extra
    # cbst = CTree()
    # for i in range(0, 20):
    #     cbst.insert(random.randint(0, 30), random.random())
    # for i in range(0, 10):
    #     k = random.randint(0, 30)
    #     print(f"Searching for {k}: {cbst.search(k)}")
    # print(cbst)
