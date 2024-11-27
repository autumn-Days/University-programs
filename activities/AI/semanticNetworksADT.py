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
                    if relation == "subclass":
                        pass
                    else:
                        print(f"{currentEntity.name} {relation} {otherEntity.name}")                
                        if ((otherEntity not in entities) and (len(otherEntity.relationShips) != 0)):
                            entities.append(otherEntity)

    #private

    def __getFeaturesSuperClass(self):
        for superclass in self.relationShips['subclass']:
            for relation, entities in superclass.relationShips.items():
                for entity in entities:
                    if relation == "subclass":
                        entity.__getFeaturesSuperClass()
                    else:
                        print(f"{relation} {entity.name}")



def main():
    Bob = Entity("Bob")
    fido = Entity("fido")
    fang = Entity("fang")

    ratos = Entity("ratos")


    construtor = Entity("construtor")
    queijo = Entity("queijo")
    gato = Entity("gato")
    cachorro = Entity("cachorro")
    homem = Entity("homem")

    Bob.addRelation(("subclass", construtor))
    Bob.addRelation(("subclass", homem))
    Bob.addRelation(("possui", fido))
    Bob.addRelation(("come", queijo))

    fido.addRelation(("subclass", cachorro))
    fido.addRelation(("caça", fang))

    fang.addRelation(("subclass", gato))
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