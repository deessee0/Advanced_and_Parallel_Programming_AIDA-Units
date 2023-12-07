class Stack():
    
    def __init__(self):
        self.data = []
        
    def inserisci(self, x):
        self.data[0] = [x] + self.data
        
    def rimuovi(self):
        x = self.data[0]
        self.data = self.data[1:]
        return x 
    
    def isEmpty(self):
        if self.data == []
            return 1
        else: 
            return 0