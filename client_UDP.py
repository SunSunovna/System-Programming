from socket import *
import sys

host = 'localhost'
port = 4200
addr = (host,port)

udp_socket = socket(AF_INET, SOCK_DGRAM)


while(1):
    data = input()
    if not data : 
        udp_socket.close() 
        sys.exit(1)
    if (data=='q'):
        break
    #encode - перекодирует введенные данные в байты, decode - обратно
    data = str.encode(data)
    udp_socket.sendto(data, addr)
    data = bytes.decode(data)
    data = udp_socket.recv(1024)
    print("Answer:", bytes.decode(data))

udp_socket.close()