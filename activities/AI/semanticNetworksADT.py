from typing import *
from collections import deque

class Entity:
    def __init__(self, name):
        self.name = name
        self.relationShips: Dict[str, 'Entity']= {}

    def addRelation(self, relation:Tuple[str, 'Entity']):
        try :
            self.relationShips[relation[0]].append(relation[1])
        except KeyError:
            self.relationShips[relation[0]] = [relation[1]]

    def BFS(self):
        entities = deque()
        entities.append(self)
        currentRelations = None

        while entities :
            currentEntity = entities.popleft()
            currentRelations = currentEntity.relationShips
            for relation,otherEntities in currentRelations.items():
                for otherEntity in otherEntities :
                    print(f"{currentEntity.name} {relation} {otherEntity.name}")                
                    if ((otherEntity not in entities) and (len(otherEntity.relationShips) != 0)):
                        entities.append(otherEntity)


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