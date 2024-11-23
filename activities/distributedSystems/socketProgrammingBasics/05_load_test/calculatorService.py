class Calc:
    def __init__(self, n1, n2, op):
        self.n1 = n1
        self.n2 = n2
        self.op = op
    def sum(self):
        return self.n1+self.n2
    def sub(self):
        return self.n1 - self.n2
    def mult(self):
        return self.n1*self.n2
    def div(self):
        try :
            return self.n1/self.n2
        except ZeroDivisionError:
            return "ERRO! Divisão por zero"
    def resolve(self):
        if self.op == "+":
            return self.sum()
        elif self.op == "-":
            return self.sub()
        elif self.op == "*":
            return self.mult()
        else:
            return self.div()