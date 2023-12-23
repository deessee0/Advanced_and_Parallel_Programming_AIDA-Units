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
        res = c_float()
        found = CTree.code.search(self.root, c_int(key), pointer(res))
        if found:
            return res.value
        return None

    def insert(self, key, value):
        self.root = CTree.code.insert(self.root, c_int(key), c_float(value))

    def __str__(self):
        def print_node(node):
            if not node:
                return "None"
            # s = f"{node.contents.key}:{node.contents.value}"
            s = f"{node.contents.key}"
            if node.contents.left or node.contents.right:
                left = print_node(node.contents.left)
                right = print_node(node.contents.right)
                s = f"({s} {left} {right})"
            return s

        return print_node(self.root)

    def __del__(self):
        CTree.code.destroy(self.root)


class Node:

    def __init__(self, key, value):
        self.value = value
        self.key = key
        self.left = None
        self.right = None

    def search(self, key):
        if self.key == key:
            return self.value
        if self.key < key:  # go right
            if self.right is not None:
                return self.right.search(key)
        if self.key > key:  # go left
            if self.left is not None:
                return self.left.search(key)
        return None

    def insert(self, key, value):
        if self.key == key:
            self.value = value
        if self.key < key:  # go right
            if self.right is None:
                self.right = Node(key, value)
            else:
                self.right.insert(key, value)
        if self.key > key:  # go left
            if self.left is None:
                self.left = Node(key, value)
            else:
                self.left.insert(key, value)

    def __str__(self):
        # s = f"{self.key}:{self.value}"
        s = f"{self.key}"
        if self.right is not None or self.left is not None:
            s = f"({s} {str(self.left)} {str(self.right)})"
        return s


class BinarySearchTree:

    def __init__(self):
        self.root = None

    def search(self, key):
        if self.root is None:
            return None
        return self.root.search(key)

    def insert(self, key, value):
        if self.root is None:
            self.root = Node(key, value)
        else:
            self.root.insert(key, value)

    def __str__(self):
        if self.root is None:
            return "Empty tree"
        else:
            return str(self.root)


if __name__ == "__main__":
    bst = BinarySearchTree()
    for i in range(0, 20):
        bst.insert(random.randint(0, 30), random.random())
    for i in range(0, 10):
        k = random.randint(0, 30)
        print(f"Searching for {k}: {bst.search(k)}")
    print(bst)

    cbst = CTree()
    for i in range(0, 20):
        cbst.insert(random.randint(0, 30), random.random())
    for i in range(0, 10):
        k = random.randint(0, 30)
        print(f"Searching for {k}: {cbst.search(k)}")
    print(cbst)
