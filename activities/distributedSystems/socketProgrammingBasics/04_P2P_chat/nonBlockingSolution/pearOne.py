"""
The "pear one" will be the one that most resembles the server,
because it will be awainting for a conection request to be mande
"""

import socket
import threading

DISCONNET_MSG = "!DISCONNECT"
clients = []

def send2all(msg, senderSocket):
    for client in clients:
        if client != senderSocket:
            try:
                client.sendall(msg.encode())
            except:
                client.close()
                clients.remove(client)

def handleClient(clientSocket, clientInfo):
    print(f"[NEW CONNECTION] {clientInfo}")
    isConnected = True
    while isConnected:
        try:
            msg = clientSocket.recv(1024).decode("utf-8")
            if msg:
                msg = (f"{clientInfo}: {msg}")
                print(msg)
                send2all(msg, clientSocket)
                if msg == DISCONNECT_MSG:
                    isConnected = False
            else:
                isConnected = False
        except:
            isConnected = False
    clientSocket.close()
    clients.remove(clientSocket)
    
def initServer():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(("127.0.0.1", 5050))
    server.listen()

    print("[LISTENING]")
    while True:
        clientSocket, clientInfo = server.accept()
        clients.append(clientSocket)

        myThread = threading.Thread(target=handleClient, args=(clientSocket, clientInfo))
        myThread.start()
        print(f"[ACTIVE CONNECTIONS] {threading.active_count() - 1}")

def main():
    print("[Initializing]")
    initServer()

if __name__ == "__main__":
    main()