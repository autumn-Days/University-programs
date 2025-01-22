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
        self.stateInitialSide = configuration
        self.stateFinalSide = self.__updateStateFinalSide()#[0,0,False]
        #This is a reference for the previous configuration, so that the path can be traced back
        self.prev = prev
        self.appliedRule = appliedRule
    def solve(self):
        queue = deque()
        queue.append(self)
        while queue:
            currentConfig = queue.popleft()
            if (currentConfig.__isFinished()):
                currentConfig.__showPath()
                break
            elif (currentConfig.__isValidConfig()):
                queue.append(Applier(currentConfig.__applyRule1(), currentConfig, rule01))
                queue.append(Applier(currentConfig.__applyRule2(), currentConfig, rule02))
                queue.append(Applier(currentConfig.__applyRule3(), currentConfig, rule03))
                queue.append(Applier(currentConfig.__applyRule4(), currentConfig, rule04))
                queue.append(Applier(currentConfig.__applyRule5(), currentConfig, rule05))

    #private
    def __applyRule1(self, amountPassagers = 1, typePassager = CANNIBAL_INDEX):
        #Carries one cannibal to the other side of the river
        stateInitialSide = list(self.stateInitialSide) #passing by copy by using "list"
        if not stateInitialSide[2]:
            stateInitialSide[typePassager] += amountPassagers
            stateInitialSide[2] = True
        else :
            stateInitialSide[typePassager] -= amountPassagers
            stateInitialSide[2] = False
        return stateInitialSide

    def __applyRule2(self):
        #carries two cannibals to the other side of the river
        return self.__applyRule1(2,CANNIBAL_INDEX)

    def __applyRule3(self):
        #carries one missionary to the other side of the river
        return self.__applyRule1(1, MISSIONARY_INDEX)

    def __applyRule4(self):
        #carries two missionaries to the other side of the river
        return self.__applyRule1(2, MISSIONARY_INDEX)
    
    def __applyRule5(self):
        stateInitialSide = self.stateInitialSide
        #carries one missionary and one cannibal to the other side of the river
        if stateInitialSide[2] == 0:
            stateInitialSide[MISSIONARY_INDEX] += 1
            stateInitialSide[CANNIBAL_INDEX] += 1
            stateInitialSide[2] = True
        else :
            stateInitialSide[MISSIONARY_INDEX] -= 1
            stateInitialSide[CANNIBAL_INDEX] -= 1
            stateInitialSide[2] = False
        return stateInitialSide

    def __updateStateFinalSide(self):
        a0 = 3 - self.stateInitialSide[0] 
        a1 = 3 - self.stateInitialSide[1]
        a2 = not self.stateInitialSide[2]
        self.stateFinalSide = [a0,a1,a2]

    def __isValidConfig(self):
        self.__updateStateFinalSide()
        return ((self.stateInitialSide[1] >= self.stateInitialSide[0]) or (self.stateFinalSide[1] >= self.stateFinalSide[0]))

    def __isFinished(self):
        self.__updateStateFinalSide()
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