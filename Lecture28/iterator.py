class MySet:

    def __init__(self):
        self._data = []

    def add(self, x):
        if x not in self._data:
            self._data.append(x)

    def __iter__(self):
        self._pos = 0
        return self

    def __next__(self):
        if self._pos >= len(self._data):
            raise StopIteration
        else:
            res = self._data[self._pos]
            self._pos += 1
            return res


s = MySet()
s.add(100)
s.add(89)
s.add(42)

for x in s:
    print(x)

x = iter(s)
print(next(x))
