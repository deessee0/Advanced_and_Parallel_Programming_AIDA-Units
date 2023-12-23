import ctypes


code = ctypes.cdll.LoadLibrary("code.so")

a = 2
b = 4
x = code.sum(a, b)
print(f"{a} + {b} = {x}\n")

a = 2
b = 2.3
code.multiply.restype = ctypes.c_float
x = code.multiply(a, ctypes.c_float(b))
print(f"{a} * {b} = {x}\n")

code.multiply.argtypes = [ctypes.c_int, ctypes.c_float]
x = code.multiply(a, b)
print(f"{a} * {b} = {x}\n")

code.swap.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int)]
a = ctypes.c_int(4)
b = ctypes.c_int(5)
print(f"a = {a}, b = {b}\n")
code.swap(ctypes.pointer(a), ctypes.pointer(b))
print(f"a = {a}, b = {b}\n")
