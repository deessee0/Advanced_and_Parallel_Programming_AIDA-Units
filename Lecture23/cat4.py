class Cat:

    species = "Felis catus"

    def __init__(self, name, age):
        self.name = name
        self.age = age

    def miagola(self):
        print(f"{self.name}: Miaooo!")

    def identificati(self):
        print(f"Sono {self.name} e sono un gatto di {self.age} anni")


tom = Cat("Tom", 13)
gerry = Cat("Gerry", 17)

tom.miagola()
tom.identificati()
gerry.miagola()
gerry.identificati()
