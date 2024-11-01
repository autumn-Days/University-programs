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

def main():
    serverSocket = socket.socket((getIp(),))

if __name__ == "__main__":
    main()