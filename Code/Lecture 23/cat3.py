class Cat:

    species = "Felis catus"

    def __init__(self, name, age):
        self.name = name
        self.age = age


tom = Cat("Tom", 13)
print(tom.name)

gerry = Cat("Gerry", 17)
print(gerry.name)


print(Cat.species)
tom.species = "gatto"
print(tom.species)
print(gerry.species)
Cat.species = "gattino"
print(tom.species)
print(gerry.species)
