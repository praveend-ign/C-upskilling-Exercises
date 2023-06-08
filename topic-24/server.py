# program to implement server code in python
# with new thread to receive data for each connection
# from the client

# import socket programming library
import socket

# import thread module
from _thread import *
import threading

print_lock = threading.Lock()
buffer_size = 1024

# thread function  
def client_communication_thread(client):
    while True:
        # data received from client
        data = client.recv(buffer_size)
        if not data:
            print('no data received')
            print_lock.release()
            break
        elif data == "exit":
            print('client sent exit')
            print_lock.release()
            break

        print(data)
        resp_str = "ok"
        client.send(resp_str.encode('ascii'))

    client.close()

def Main():
    host = '127.0.0.1'
    # reserve a port which is not in use
    port = 12345
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((host, port))
    print("socket binded to port", port)

    # listen incoming connections upto 5 backlogs
    server.listen(5)
    print("server socket is listening")

    while True:
        # establish connection with client
        c, addr = server.accept()

        # lock acquired by client
        print_lock.acquire()
        print('connected to :', addr[0], ':', addr[1])

        # start a new thread
        start_new_thread(client_communication_thread, (c,))

    server.close()

if __name__ == '__main__':
    Main()

