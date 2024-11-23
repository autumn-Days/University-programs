import socket
import threading
from calculatorService import *
from typing import *

class Info:
    def __init__(self, result:str, socketClient):
        self.bundle = (result, socketClient)

class TCPServer:
    def __init__(self):
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.listInfo: List[Tuple[str, Socket]] = []
        self.server.bind(("127.0.0.1", 5054))
        self.server.listen(100)
        
        print(f"The server has been initiated at 127.0.0.1/5051")

    def __storeInfo(self,result:str, socketClient):
        """
        This method is used for storing all the informarions regarding the
        results of each client
        """
        self.listInfo.append(Info(result, socketClient))

    def __handleRequest(self, socketClient):
        request = socketClient.recv(1024).decode("utf-8").split()
        myCalc = Calc(float(request[0]), float(request[1]), request[2])
        self.__storeInfo(str(myCalc.resolve()), socketClient)

    def getRequest(self):
        #while True:
        clientSocket,clientInfo = self.server.accept()
        print(f"Connection has been established with {clientInfo[0]}/{clientInfo[1]}")
        threadSend = threading.Thread(target=(self.__handleRequest), args=(clientSocket,))
        threadSend.start()

    def sendResponse(self):
        print("entrou")
        for info in self.listInfo:
            info[1].sendall(str(info[0]).encode())

    def close(self):
        self.server.close()

if __name__ == "__main__":
    try :
        server = TCPServer()
        server.getRequest()
        server.sendResponse()
    except KeyboardInterrupt:
        server.close()