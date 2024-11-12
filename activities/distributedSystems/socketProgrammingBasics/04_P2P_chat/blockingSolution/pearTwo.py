"""
The pear two reassembles the traditional client and it is responsible for
sending the first message
"""
import socket

DISCONNET_MSG = "!DISCONNECT"

def main():
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    client.connect(("127.0.0.1", 5051))
    while True:
        msgSend = input("you: ")
        client.sendall(msgSend.encode())

        if msgSend == DISCONNET_MSG:
            break

        msg = client.recv(1024).decode("utf-8")
        print("Other:", msg)
        
        if msg == DISCONNET_MSG:
            break
    client.close()

if __name__ == "__main__":
    main()