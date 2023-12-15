from copy import copy, deepcopy


class Person:

    def __init__(self, name, age, cats):
        self.name = name
        self.age = age
        self.cats = cats


a = Person("Giangianni", 32, ["Attila", "Tigre"])

b = a

c = copy(a)

d = deepcopy(a)
