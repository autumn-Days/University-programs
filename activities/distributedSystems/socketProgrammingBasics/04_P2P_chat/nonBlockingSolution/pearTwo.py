"""
The pear two reassembles the traditional client and it is responsible for
sending the first message
"""
import socket
import threading

DISCONNET_MSG = "!DISCONNECT"

def receiveMsgs(clientSocket):
    while True:
        try:
            clientSocket.recv(1024).decode("utf-8")
            if msg:
                print(msg)
            else:
                break
        except:
            break

def sendMsgs(clientSocket):
    while True:
        try:
            msg = input("you: ")
            clientSocket.sendall(msg.encode())
            if msg == DISCONNECT_MSG:
                clientSocket.close()
                break
        except:
            break


def startClient():
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect(("127.0.0.1", 5050))
    print("[CONNECTION STABLISHED] 127.0.0.1/5050")

    messagesReceived = threading.Thread(target=receiveMsgs, args=(client,))
    messagesReceived.start()

    messagesSent = threading.Thread(target=sendMsgs, args=(client,))
    messagesSent.start()

def main():
    startClient()

if __name__ == "__main__":
    main()