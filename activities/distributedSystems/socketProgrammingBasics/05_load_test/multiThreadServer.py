import socket
import threading
from calculatorService import *
from typing import *

class TCPServer:
    def __init__(self):
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.listInfo: List[Tuple[str, socket.socket]] = []
        self.server.bind(("127.0.0.1", 5055))
        self.server.listen(100)
        self.lock = threading.Lock()
        print(f"The server has been initiated at 127.0.0.1/5051")

    def __storeInfo(self,result:str, socketClient):
        """
        This method is used for storing all the informarions regarding the
        results of each client
        """
        self.listInfo.append((result, socketClient))

    #=begin OKAY =end
    def getRequest(self):
        #while True:
        clientSocket,clientInfo = self.server.accept()
        print(f"Connection has been established with {clientInfo[0]}/{clientInfo[1]}")
        threadRequest = threading.Thread(target=self.__handleRequest, args=(clientSocket,))
        threadRequest.start()
    
    #=begin OKAY =end
    def sendResponse(self):
        threadSend = threading.Thread(target=self.__handleSend, daemon=True)
        threadSend.start()
    #=begin OKAY =end
    def close(self):
        self.server.close()

    #private

    #=begin OKAY =end
    def __handleRequest(self, socketClient):
        while True:
            request = socketClient.recv(1024).decode("utf-8").split()
            if request:
                myCalc = Calc(float(request[0]), float(request[1]), request[2])
            with self.lock :
                self.__storeInfo(str(myCalc.resolve()), socketClient)

    #=begin OKAY =end
    def __handleSend(self):
        while True:
            with self.lock:
                for info in self.listInfo:
                    try:
                        info[1].sendall(info[0].encode()) #perhaps I need to specify the enconding with utf-8
                    except BrokenPipeError:
                        print("ERROR! Client disconnected")
                    finally:
                        self.listInfo.remove(info)


if __name__ == "__main__":
    try :
        server = TCPServer()
        server.getRequest()
        server.sendResponse()
    except KeyboardInterrupt:
        server.close()