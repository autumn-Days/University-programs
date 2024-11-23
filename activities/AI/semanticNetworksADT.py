from typing import *
from collections import deque

class Entity:
    def __init__(self, name):
        self.name = name
        self.relationShips: List[Tuple[str, 'Entity']] = []
    def addRelation(self, relation:Tuple[str, 'Entity']):
        self.relationShips.append(relation)
    def BFS(self):
        entities = deque()
        entities.append(self)
        
        while entities :
            currentEntity = entities.popleft()
            relationShips = deque(currentEntity.relationShips)
            while relationShips :
                relation = relationShips.popleft()
                print(f"{currentEntity.name} {relation[0]} {relation[1].name}")                
                if ((relation[1] not in entities) and (len(relation[1].relationShips) != 0)):
                    entities.append(relation[1])


def main():
    Bob = Entity("Bob")
    fido = Entity("fido")
    fang = Entity("fang")

    ratos = Entity("ratos")


    construtor = Entity("construtor")
    queijo = Entity("queijo")
    gato = Entity("gato")
    cachorro = Entity("cachorro")

    Bob.addRelation(("é um", construtor))
    Bob.addRelation(("possui", fido))
    Bob.addRelation(("come", queijo))

    fido.addRelation(("é um", cachorro))
    fido.addRelation(("caça", fang))

    fang.addRelation(("é um", gato))
    fang.addRelation(("caça", ratos))

    ratos.addRelation(("comem", queijo))

    Bob.BFS()

if __name__ == "__main__":
    """
    Output example:
        Bob é um construtor
        Bob possui fido
        Bob come queijo
        fido é um cachorro
        fido caça fang
        fang é um gato
        fang caça ratos
        ratos comem queijo
    """
    main()