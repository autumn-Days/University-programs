import socket

HEADER_SIZE = 64
SERVER_PORT = 5051
DISCONNECT_MSG = "!DISCONNECT"
SERVER_ADRESS = socket.gethostbyname(socket.gethostname())

def sendHeader(clientSocket,msg:str):
    lengthMsg = len(msg)
    clientSocket.sendall(lengthMsg.encode())

def main():
    clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    clientSocket.connect((SERVER_ADRESS, SERVER_PORT))
