class Matrix:
    
    def __init__(self, nrow, ncol, iVal):
        self.nrow = nrow
        self.ncol = ncol
        self.data = [[iVal for _ in range(ncol)] for _ in range(nrow)]
        
    def get_at(self, i, j):
        return self.data[i][j]
    
    def set_at(self, i, j, x):
        self.data[i][j] = x
        
    def multiply(self, m):
        if self.ncol != m.nrow:
            raise ValueError("Matrix dimensions do not match for multiplication")

        newM = Matrix(self.nrow, m.ncol, 0)
        
        for i in range(self.nrow):
            for j in range(m.ncol):
                for k in range(self.ncol): # or m.nrow, they are the same
                    val = newM.get_at(i, j)
                    val += self.get_at(i, k) * m.get_at(k, j)
                    newM.set_at(i, j, val)
                    
        return newM

# Example usage
M = Matrix(3, 3, 0)
M.multiply(M)  # This should work now without errors
