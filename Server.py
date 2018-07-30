import socket
import time
import threading

s = socket.socket()
s.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)

s.bind(('127.0.0.1', 2002))
s.listen(5)
cons = []
while True:
    con,addr = s.accept()
    #cons.append(con)
    print con
    while True:
        data = con.recv(1024)
        if not data:
            con.close()
            break;
        for x in xrange(1,10):
            print("receive data: ")
            print data
            str = "%c%c%c%c%c%s" % (0x1E, 0x11,33,0x30,0x44,"\n")
            print("send data: ")
            print(str)
            time.sleep(0.5)
            con.send(str)
s.close()
