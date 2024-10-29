import socket
from typing import *

def calculate(operation:List[str]):
    fst = int(operation[0])
    snd = int(operation[2])
    operator = operation[1]

    if operator == "+":
        return str(fst+snd)
    elif operator == "-":
        return str(fst-snd)
    elif operator == "*":
        return str(fst*snd)
    elif operator == "/":
        return str(fst/snd)
    

IP = "127.0.0.1"
PORTA = 50011
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server.bind((IP,PORTA))
server.listen()
clientSocket, clientInfo = server.accept()

with clientSocket:
    while True:        
        data = clientSocket.recv(1024)
        data = (data.decode("utf-8").split())
        if not data:
            break
        clientSocket.sendall((calculate(data)).encode())
        server.close()