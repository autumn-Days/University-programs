import socket
import threading
from calculator import *

class TCPServer:
    def __init__(self):
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.bind(("127.0.0.1", 5050))
        self.server.listen()
        print(f"The server has been initiated at 127.0.0.1/5050")

    def __storeInfo(self,result:str, socketClient):
        self.result = result
        self.socketClient = socketClient

    def getRequest(self):
        clientSocket,clientInfo = self.server.accept()

        print(f"Connection has been established with {clientInfo}")

        request = clientSocket.recv(1024).decode("utf-8").split()
        myCalc = Calc(float(request[0]), float(request[1]), request[2])
        self.__storeInfo(str(myCalc.resolve()), clientSocket)
        return self.result

    def sendResponse(self,response):
        self.socketClient.sendall(str(self.result).encode())

if __name__ == "__main__":
    server = TCPServer()
    server.getRequest()
    server.sendResponse("response")