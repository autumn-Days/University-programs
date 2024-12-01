from typing import *
from collections import deque

CANNIBAL_INDEX = 0
MISSIONARY_INDEX = 1

rule01 = "Rule 01"
rule02 = "Rule 02"
rule03 = "Rule 03"
rule04 = "Rule 04"
rule05 = "Rule 05"

class Applier:
    def __init__(self, configuration = [3,3,True], prev=None, appliedRule = None):
        """
        •There are two sides of the river. The missionaries and the cannibals start at the "initial side"
        of the river and need to go to the "final side" of it, that is, the other side of the river.
        •The "state" tells how many cannibals, missionaries are on the side of the river, also the last
        parameter tells whether or not the boat is on that side. 
        """
        self.stateFinalSide = [0,0,False]
        self.stateInitialSide = configuration
        #This is a reference for the previous configuration, so that the path can be traced back
        self.prev = prev
        self.appliedRule = appliedRule
    def solve(self):
        queue = deque()
        queue.append(self)
        while not queue:
            currentConfig = queue.popleft()
            if (currentConfig.__isFinished()):
                currentConfig.__showPath()
                break
            queue.append(Applier(currentConfig.__applyRule1(), currentConfig, rule01))
            queue.append(Applier(currentConfig.__applyRule2(), currentConfig, rule02))
            queue.append(Applier(currentConfig.__applyRule3(), currentConfig, rule03))
            queue.append(Applier(currentConfig.__applyRule4(), currentConfig, rule04))
            queue.append(Applier(currentConfig.__applyRule5(), currentConfig, rule05))

    #private
    def __applyRule1(self, amountPassagers = 1, typePassager = CANNIBAL_INDEX):
        #Carries one cannibal to the other side of the river
        if not self.stateInitialSide[2]:
            self.stateInitialSide[typePassager] += amountPassagers
            self.stateInitialSide[2] = True
        else :
            self.stateInitialSide[typePassager] -= amountPassagers
            self.stateInitialSide[2] = False
        self.__updateStateFinalSide()

    def __applyRule2(self):
        #carries two cannibals to the other side of the river
        self.__applyRule1(2,CANNIBAL_INDEX)

    def __applyRule3(self):
        #carries one missionary to the other side of the river
        self.__applyRule1(1, MISSIONARY_INDEX)

    def __applyRule4(self):
        #carries two missionaries to the other side of the river
        self.__applyRule1(2, MISSIONARY_INDEX)
    
    def __applyRule5(self):
        #carries one missionary and one cannibal to the other side of the river
        if self.stateFinalSide[2] == 0:
            self.stateFinalSide[MISSIONARY_INDEX] += 1
            self.stateFinalSide[CANNIBAL_INDEX] += 1
            self.stateFinalSide[1] = 1
        else :
            self.stateFinalSide[MISSIONARY_INDEX] -= 1
            self.stateFinalSide[CANNIBAL_INDEX] -= 1
            self.stateFinalSide[1] = 0
        self.__updateStateFinalSide()

    def __updateStateFinalSide(self):
        a0 = 3 - self.stateInitialSide[0] 
        a1 = 3 - self.stateInitialSide[1]
        a2 = not self.stateInitialSide[2]
        self.stateFinalSide = [a0,a1,a2]

    def __isValidConfig(self):
        return ((self.stateInitialSide[1] >= self.stateInitialSide[0]) or (self.stateFinalSide[1] >= self.__updateStateFinalSide[0]))

    def __isFinished(self):
        return self.stateFinalSide == [3,3,True]

    def __showPath(self, currentConfig):
        listPath = []
        while currentConfig.appliedRule:
            listPath.append(currentConfig.appliedRule)
            curretConfig = currentConfig.prev
        listPath.reverse()
        print(listPath)

solver = Applier()
solver.solve()

"""
Some tests:
(3,3,1)
    a1: (2,3,1)
        a1
        ...
        a5
    a2: (1,3,1)
        a1
        ...
        a5
    a3: (3,2,1)
        a1
        ...
        a5
    a4: (3,1,1)
        a1
        ...
        a5
    a5: (2,2,1)
"""