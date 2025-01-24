# -*- coding: utf-8 -*-
"""
Created on Thu Jan 23 10:46:48 2025

@author: Just_
"""

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

#auxiliary functions

def fill(cromossome:str) -> str:
    """
    If the conversion of int of base ten to int with base 2
    results in a number that doesn't uses the four bits needed
    for the crossover (thanks to the way "bin" was implemented)
    it will just cut the right leading zeros needed for the cros-
    over. So, as a solution, this function adds the zeros that
    were cutted of. Example:
        
    bin(5) -> 0b101, but it was wished it to be, 0b1010, so this
    function just adds the missing zero.
    """
    missingBits = 4 - len(cromossome)
    
    for i in range(missingBits):
        cromossome += "0"

    return cromossome

#Important functions

def function2optimize(cromossome:int):
    return math.sin(cromossome)

def generateFirstPopulation() -> List[int]:
    population:List[int] = []
    cromossome = ""
    while len(population) != 4:
        for gene in range (4):
            cromossome += str(random.randint(0,1))
        population.append(int(cromossome,2))
        cromossome = ""
    return population

def crossOver(parent01:int, parent02:int) -> int:
    
    fstHalfP1 = fill(str((bin(parent01)))[2:])
    fstHalfP1 = fstHalfP1[:2]

    sndHalfP2 = fill(str((bin(parent02)))[2:])
    sndHalfP2 = sndHalfP2[2:] 
    
    return int(fstHalfP1 + sndHalfP2,2)

def getGoodParents(population:List[int]) -> List[Tuple[int,int]]:
    cromossomesFeatness:List[Tuple[int,int]] = []

    for cromossome in population :
        featness = function2optimize(cromossome)
        """
        It is needed to invert the signal of the featness because the heapq
        implements a minimum heap, so when it pops the element, it will take
        the smallest one.
        """
        cromossomesFeatness.append((-featness,cromossome))

    heapq.heapify(cromossomesFeatness)
    
    parent01 = heapq.heappop(cromossomesFeatness)[1]
    parent02 = heapq.heappop(cromossomesFeatness)[1]

    return parent01, parent02

def __genNewPopulation(parent01:int, parent02:int, newPopulation) -> List[int]:
    if len(newPopulation) == 2:
        newPopulation.append(crossOver(parent01, parent02))
        newPopulation.append(crossOver(parent02, parent01))
        return newPopulation
    child01 = crossOver(parent01,parent02)
    child02 = crossOver(parent02, parent01)
    
    newPopulation.append(child01)
    newPopulation.append(child02)
    
    return __genNewPopulation(child01, child02, newPopulation)
    
def genNewPopulation(parent01:int, parent02:int) -> List[int]:
    return __genNewPopulation(parent01, parent02, [])

def isOptimalCromossome(cromossome:int) -> bool:
    #This function test if the cromossome gives the best value for sin(x)
    return function2optimize(cromossome) >= 0.9

def getValues(population:List[int]) -> List[Tuple[int,int]]:
    populationWithValue = []
    for cromossome in population:
        populationWithValue.append((-function2optimize(cromossome), cromossome))
    return populationWithValue

def isGoalReached(population:List[int]) -> bool:
    population = getValues(population)
    bestCromossome = heapq.heappop(population)[1]
    return isOptimalCromossome(bestCromossome)

def main():
    population = generateFirstPopulation()
    generation = 0
    while not isGoalReached(population):
        parent01, parent02 = getGoodParents(population)
        population = genNewPopulation(parent01, parent02)
    return generation

if __name__ == "__main__":
    main()