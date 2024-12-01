from threading import *
from multiprocessing import *
from time import *
from random import *

shared_value = 100

def modifyShared_value(processName, threadId):
    incrementOrDecrement = randint(0,1) 
    value2add = randint(1,20)
    global shared_value
    if incrementOrDecrement:
        shared_value += value2add
    else:
        shared_value -= value2add
    print(f"Thread{processName}.{threadId} setted 'shared_value' to {shared_value}")

def createProcess(processName:str) -> None:
    amountChildren = randint(1,4)#aka, amount threads
    print(f"The process {processName} has started and it has {amountChildren} children")
    threadList = []
    for i in range(amountChildren):
        threadList.append(Thread(target=modifyShared_value, args=(processName, i)))
    for s in threadList: s.start()
    for s in threadList: s.join()

def main():
    createProcess("Bob")
    createProcess("Alice")
    createProcess("Dilan")

if __name__ == "__main__":
    """
    The process Bob has started and it has 2 children
    ThreadBob.0 setted 'shared_value' to 94
    ThreadBob.1 setted 'shared_value' to 98
    The process Alice has started and it has 1 children
    ThreadAlice.0 setted 'shared_value' to 85
    The process Dilan has started and it has 4 children
    ThreadDilan.0 setted 'shared_value' to 80
    ThreadDilan.1 setted 'shared_value' to 64
    ThreadDilan.2 setted 'shared_value' to 56
    ThreadDilan.3 setted 'shared_value' to 73
    """
    main()

