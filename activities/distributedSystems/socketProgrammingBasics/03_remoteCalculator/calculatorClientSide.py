import socket

SERVER_IP = "127.0.0.1"
PORTA = 50011

clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

with clientSocket:
    clientSocket.connect((SERVER_IP, PORTA))
    clientSocket.sendall((input("Qual a operação que você deseja realizar?\n")).encode())
    print(((clientSocket.recv(1024)).decode("utf-8")))