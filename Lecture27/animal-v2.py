class Food:

    def __init__(self, name, category, calories):
        self.name = name
        self.category = category
        self.calories = calories


class Animale:

    common_name = "Gatto"
    calories_needed = 300

    def __init__(self, name, age):
        self.name = name
        self.age = age
        self.happiness = 0
        self.calories = 0

    def eat(self, food):
        self.calories += food.calories
        if (self.calories > self.calories_needed):
            print("Ho mangiato troppo")
            self.happiness -= 1

    def interact_with(self, animal):
        self.happiness += 1
        print(f"Sto giocando con {animal.name}")

    def __str__(self):
        return f"Sono un {self.common_name} di nome {self.name}"


class Gatto(Animale):

    common_name = "Gatto"
    calories_needed = 300


class Coniglio(Animale):

    common_name = "Coniglio"
    calories_needed = 200


carota = Food("carota", "vegetale", 40)
bistecca = Food("bistecca", "carne", 270)

attila = Gatto("Attila", 7)
roger = Coniglio("Roger", 2)

attila.eat(bistecca)
roger.eat(carota)

attila.interact_with(roger)
roger.interact_with(attila)

print(attila)
print(roger)
