import socket

class TCPClient():
    def __init__(self):
        self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client.connect(("127.0.0.1", 5055))
    def sendRequest(self,request:str):
        self.client.sendall(request.encode())
    def getResponse(self):
        msg = self.client.recv(1024).decode("utf-8")
        return msg
    def close(self ):
        self.client.close()

def main():
    client = TCPClient()
    client.sendRequest(input("Qual a operação ?"))
    response = client.getResponse()
    print(response)
    client.close()

if __name__ == "__main__":
    main()