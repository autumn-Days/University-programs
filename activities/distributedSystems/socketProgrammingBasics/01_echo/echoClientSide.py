import socket

serverIP = "127.0.0.1"
serverPort = int(input("What's the server's port number ?"))

#IPv4 and TCP for the client's socket
clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

with clientSocket:
    clientSocket.connect((serverIP, serverPort))
    #converts a string to raw bytes
    clientSocket.sendall(b"hello, sockets!")
    data = clientSocket.recv(1024)

"""
The call for the "decode" method is justified because
the methods "sendall" and "recv" only work with raw bytes.
If this method were not used, the output would be: 
<<Data received b'hello, sockets!'>> not
<<Data received: hello, sockets!>>
"""
print(f"Data received: {data.decode("utf-8")}")
