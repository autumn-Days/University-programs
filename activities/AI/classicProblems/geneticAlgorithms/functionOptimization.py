"""
This problem was proposed by Ben Copin in its book "Artificial Intelligence Iluminated" and
its basic idea is that we need to optimize the function sin(x), where x is in [1,15], for
this we will have a population of 4 cromossomes.

Each cromossome is an array of 4 genes which can be equal to 0 or 1, that is, the cromossomes
are binary numbers of length 4, which just gives, at maximum 2^15. Then, the binary number the
cromossome is representing is converted to decimal and given as input to sin(x).

The fitness function is given by (50*(sin(x)+1)), where x is the value of the cromossome converted
to decimal. The cromossomes will then cross over and its children, its children will then crossover
as well these 2 generations will substiture the previous generation.

For this problem it will be no mutations.
"""

import math
import random
import heapq
from typing import *

def generateFirstPopulation() -> List[int]:
    population:List[int] = []
    cromossome = ""
    while len(population) != 4:
        for gene in range (4):
            cromossome += str(random.randint(0,1))
        population.append(int(cromossome,2))
        cromossome = ""
    return population

def function2optimize(cromossome:int):
    return math.sin(int(cromossome,2))

def crossOver(parent01:int, parent02:int) -> int:
    fstHalfP1 = str(parent01)[:2] 
    sndHalfP2 = str(parent02)[2:]
    child = fstHalfP1 + sndHalfP2
    return int(child,2)


def getGoodParents(population:List[int]) -> List[Tuple[int,int]]:
    cromossomesFeatness:List[Tuple[int,int]] = []

    for cromossome in population :
        featness = function2optimize(cromossome)
        cromossomesFeatness.append((featness,cromossome))

    heapq.heapify(cromossomesFeatness)

    parent01 = -heap.heappop(cromossomesFeatness)
    parent02 = -heap.heappop(cromossomesFeatness)

    return parent01, parent02

def __genNewPopulation(parent01:int, parent02:int, population) -> List[int]:
    if len(population == 4):
        return population
    
    

def genNewPopulation(parent01:int, parent02:int) -> List[int]:
    return __genNewPopulation(parent01, parent02, [])

print(generateFirstPopulation())

print(crossOver(int("1111",2),int("1111",2)))