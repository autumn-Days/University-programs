import socket

IP = "127.0.0.1"

#IPv4 and TCP socket for the server side
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

with server:
    #it uses the localhost and selects an available port number
    server.bind((IP, 0))
    print(f"The port number of the server is: {server.getsockname()[1]}")
    server.listen()
    """
    returns the client's socket and a tuple of type
    (str, int) conteining the IP adress and the port
    number of the client.
    """
    clientSocket, clientInfo = server.accept()
    with clientSocket:
        print(f"connected by {clientInfo[0]}/{clientInfo[1]}")
        while True:
            #data will receiver 1024 bytes from the client's socket
            data = clientSocket.recv(1024)
            if not data:
                break
            #The data received will be sended back to the client
            clientSocket.sendall(data)
