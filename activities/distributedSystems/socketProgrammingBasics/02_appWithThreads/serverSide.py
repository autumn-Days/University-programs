import socket
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

def getGate():
    return socket.gethostbyname(socket.)

def handleClient():
    """
    The objective of this function is to handle each client that
    tries to connect to the server. That is, it will basically
    start a new thread
    """


def main():
    PORT = 5050
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(getIp(), PORT)

    server.listen()

    with server:
        clientSocket, clientInfo = server.connect()
        myThread = threading.thread(target=handleClient, args=(clientSocket, clientInfo))

if __name__ == "__main__":
    main()