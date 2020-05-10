import socket

while(1):
    sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    sock.connect(("127.0.0.1", 4200))
    message = input()
    if (message=='q'):
        break

    sock.send(message.encode("utf-8"))

    data = sock.recv(1024)
    print ("answer:",data.decode("utf-8"))
sock.close()

