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
from typing import *

def generateFirstPopulation():
    population:List[int] = []


def function2optimize(cromossome:int):
    return math.sin(int(cromossome,2))
