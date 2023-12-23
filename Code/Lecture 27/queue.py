class EmptyQueueError(Exception):
    pass


class Queue:

    def __init__(self):
        self.data = []

    def add(self, x):
        self.data.append(x)

    def remove(self):
        if self.data == []:
            raise EmptyQueueError()
        x = self.data[0]
        self.data = self.data[1:] 
        return x

    def empty(self):
        return self.data == []


q1 = Queue()
q2 = Queue()

try:
    q1.remove()
except EmptyQueueError:
    pass

q1.add(3)
q1.add(4)

q2.add(1)

print(q2.remove())

while (not q1.empty()):
    print(q1.remove())
