import socket

UDP_IP = "127.0.0.1"
UDP_PORT = 13251
MESSAGE = "Hello, World!"

print("UDP target IP:", UDP_IP)
print("UDP target port:", UDP_PORT)
print("message:", MESSAGE)

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
for i in range(1,10,1):
    sock.sendto(bytes(str(i), "utf-8"), (UDP_IP, UDP_PORT))