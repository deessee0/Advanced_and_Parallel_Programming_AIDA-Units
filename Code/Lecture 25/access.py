class Queue:

    def __init__(self):
        self.__data = []

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

    def __do_stuff(self):
        self.__data = [1, 2, 3]


q = Queue()
q.enqueue(3)

# Effetti del name mangling

print(q._Queue__data)
q._Queue__do_stuff()
