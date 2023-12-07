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
        self.key = key
        self.value = value
        self.sx = None  
        self.dx = None  

    def search(self, key):
        if self.key is None:  
            return None
        if self.key == key:
            return self.value  
        elif key < self.key and self.sx is not None:
            return self.sx.search(key) 
        elif self.dx is not None:
            return self.dx.search(key)  
        return None 

    def insert(self, key, value):
        if self.key is None:  
            self.key = key
            self.value = value
            return
        if key < self.key:
            if self.sx is None:
                self.sx = Node(key, value)
            else:
                self.sx.insert(key, value)
        elif key > self.key:
            if self.dx is None:
                self.dx = Node(key, value)
            else:
                self.dx.insert(key, value)          
                     
    def __str__(self):
        if self is None:
            return "None"
        left = str(self.sx) if self.sx is not None else "None"
        right = str(self.dx) if self.dx is not None else "None"
        return f'({self.key} {left} {right})'


class BinarySearchTree:

    def __init__(self):
        self.root = None

    def insert(self, key, value):
        if self.root is None:
            self.root = Node(key, value)
        else:
            self.root.insert(key, value)

    def search(self, key):
        if self.root is not None:
            return self.root.search(key)
        return None

    def __str__(self):
        return str(self.root) if self.root is not None else "Empty"


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
