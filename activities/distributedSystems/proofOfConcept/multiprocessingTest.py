"""
•This code aims in testing the multiprocessing module.
•The module in question creates as many process as wished.
•The example illustrates that, although a process "A" can
start before a process "B", the former can still finish
it task before the first
•Feeling:
    A random number of seconds will be choosed for m
"""

from multiprocessing import Process
from threading import Thread
from time import *
from random import *

def sleeper(name:str) -> bool:
    startTime = gmtime()
    sleepTime = randint(1,10)
    print(f"{startTime.tm_min}:{startTime.tm_sec} - The process {name} is going to sleep for {sleepTime}")
    sleep(sleepTime)
    endTime = gmtime()
    print(f"{endTime.tm_min}:{endTime.tm_sec} - The process {name} has awaken")

def multiProcessSolution():
    p1 = Process(target=sleeper, args=("Bob",))
    p2 = Process(target=sleeper, args=("Alice",))
    p1.start(); p2.start()
    p1.join(); p2.join()

def multiThreadSolution():
    p1 = Thread(target=sleeper, args=("Stu",))
    p2 = Thread(target=sleeper, args=("Alen",))
    p1.start(); p2.start()
    p1.join(); p2.join()

def main():
    print("-=-=-=-=-=-=-=-=-=-=-=-=-=")
    multiProcessSolution()
    print("-=-=-=-=-=-=-=-=-=-=-=-=-=")
    multiThreadSolution()

if __name__ == "__main__":
    main()

"""
-=-=-=-=-=-=-=-=-=-=-=-=-=
32:48 - The process Bob is going to sleep for 10
32:48 - The process Alice is going to sleep for 1
32:49 - The process Alice has awaken
32:58 - The process Bob has awaken
-=-=-=-=-=-=-=-=-=-=-=-=-=
32:58 - The process Stu is going to sleep for 1
32:58 - The process Alen is going to sleep for 4
32:59 - The process Stu has awaken
33:2 - The process Alen has awaken
@autumn-Days ➜ .../University-programs/act
"""