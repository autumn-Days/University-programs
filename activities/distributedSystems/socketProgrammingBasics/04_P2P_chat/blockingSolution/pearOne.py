"""
The "pear one" will be the one that most resembles the server,
because it will be awainting for a conection request to be mande
"""

import socket

DISCONNET_MSG = "!DISCONNECT"

def main():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(("127.0.0.1", 5051))
    server.listen()
    print("[LISTENING]")
    clientSocket, clientInfo = server.accept()
    while True:

        msgRcv = (clientSocket.recv(1024)).decode("utf-8")
        print("Other:", msgRcv)

        if msgRcv == DISCONNET_MSG:
            break
        
        msgSend = input("You: ")
        clientSocket.sendall(msgSend.encode())

        if msgSend == DISCONNET_MSG:
            break

    server.close()

if __name__ == "__main__":
    main()