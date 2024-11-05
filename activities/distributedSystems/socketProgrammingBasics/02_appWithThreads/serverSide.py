import socket

DISCONNECT_MSG = "!DISCONNECT"
PORT = 5050
"""
This last libray will make it possible for the server to receive multiple connections
from a lot of different clients, all thanks to parallel programming
"""
import threading

def getIp():
    """
    This function is responsible to get the IP adress of the local host
    and it is pretty important to portability.
    """
    return socket.gethostbyname(socket.gethostname())


def handleClient(clientSocket, clientInfo):
    """
    The objective of this function is to handle each client that
    tries to connect to the server. That is, it will basically
    start a new thread so that, for each client, this function will
    be running
    """
    print(f"NEW CONNECTION STABLISHED: {clientInfo[0]}")
    isItConnected = True
    """
    Since we do not know the length of the message, it is a good idea
    to actually receive the size of the payload first in a header of
    fixed size. After that, it is possible to "allocate" an specific
    amount of bytes for the message that is going to be received
    """
    HEADER_SIZE = 64 
    while isItConnected:
        msgLength = clientSocket.recv(HEADER_SIZE).decode("utf-8")
        msg = clientSocket.recv(int((msgLength).decode("utf-8")))
        print(f"{clientInfo[0]}: {msg}")
        if msg == DISCONNECT_MSG:
            isItConnected = not isItConnected
    clientSocket.close()

def main():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((getIp(), PORT))

    server.listen()
    print(f"[LISTENING] The server is listening on {getIp()}/{PORT}")
    while True:
        clientSocket, clientInfo = server.accept()
        myThread = threading.thread(target=handleClient, args=(clientSocket, clientInfo))
        """
        In the previous line, the thread was created, but wasn't yet executed. By doing
        myThread.start() the thread start executing.
        """
        myThread.start()
        """
        This part will be responsible for showing how many connections the server is 
        dealing with
        """
        print("Number of connetions made:", myThread.activeCount())

if __name__ == "__main__":
    main()