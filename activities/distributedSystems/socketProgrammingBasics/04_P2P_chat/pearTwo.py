import socket

DISCONNET_MSG = "!DISCONNECT"

def main():
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.bind(("127.0.0.1", 5050))

    client.connect("127.0.0.1", 5051)
    while True:
        client.sendall(input("Me: ").encode())
        msgRcv = (clientSocket.recv(1024)).decode("utf-8")
        print(msgRcv)
        if msgRcv == DISCONNET_MSG:
            break
        msgSend = clientSocket.sendall((input("")).encode())
    server.close()

if __name__ == "__main__":
    main()