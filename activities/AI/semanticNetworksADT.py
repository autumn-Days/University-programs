from typing import *

class Entity:
    def __init__(self, name):
        self.name = name
        self.relationShips: List[Tuple[str, Entity]] = []
    def addRelation(self, relation:Tuple[str, Entity]):
        self.relationShips.append(relation)
    def BFS(self):
        queue = self.relationShips
        currentName = self.name
        for relation in relationShips:
            print(f"{currentName} {relation[0]} {relation[1].name}")
            queue.append(relation[1])