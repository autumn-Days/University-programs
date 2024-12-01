from typing import *

CANNIBAL_INDEX = 0
MISSIONARY_INDEX = 1

class Applier:
    def __init__(self, configuration = [3,3,True]):
        """
        •There are two sides of the river. The missionaries and the cannibals start at the "initial side"
        of the river and need to go to the "final side" of it, that is, the other side of the river.
        •The "state" tells how many cannibals, missionaries are on the side of the river, also the last
        parameter tells whether or not the boat is on that side. 
        """
        self.stateFinalSide = [0,0,False]
        self.stateInitialSide = configuration

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

    def isFinished(self):
        return self.stateFinalSide == [3,3,True]

class Node:
    def __init__(self):
        self.currentConfiguration = Applier()
        children:List['Node'] = None #just like a B-tree
        parents:List['Node'] = None #just like a B-tree

class Tree:
    """
    The general idea is that, for every node, every possible combination
    will be tested. The 
    """
    def __init__(self):
        self.root = None
        self.visited:List[str] = None # (0|1|2).(0|1|2).(0|1|2)
    
    def BFS(self)
        return self.__BFS()
        
    #private
    def __BFS (self, parentNode):
        #generate all the children
        self.children.append(self.root.currentConfiguration.__applyRule1())
        self.children.append(self.root.currentConfiguration.__applyRule2())
        self.children.append(self.root.currentConfiguration.__applyRule3())
        self.children.append(self.root.currentConfiguration.__applyRule4())
        self.children.append(self.root.currentConfiguration.__applyRule5())
        return validPath

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