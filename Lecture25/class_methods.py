class Queue:

    def __init__(self):
        self.__data = []

    @classmethod
    def from_list(cls, lst):
        q = cls()
        q.__data = lst
        return q

    def enqueue(self, x):
        self.__data.append(x)

    def dequeue(self):
        x = self.__data[0]
        self.__data = self.__data[1:]
        return x

    def isempty(self):
        return self.__data == []

    def __str__(self):
        return str(self.__data)


x = [1, 2, 5, 7, 4]
q = Queue.from_list(x)

print(x)
