def calculator(elem1:float, elem2:float, op:str):
    if op == '+':
        return elem1+elem2
    elif op == '-':
        return elem1-elem2
    elif op == '*':
        return elem1*elem2
    elif op == '/':
        if elem2 == 0:
            pass
        return elem1/elem2
    else:
        pass