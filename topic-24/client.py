# program to implement client code
# in python using socket library to
# send data to server

import socket

buffer_size = 1024

def Main():
    # server IP address is local host in our case
    serveraddr = '127.0.0.1'

    # initialize the port on which we want to connect
    port = 12345

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # connect to server running on local computer
    s.connect((serveraddr, port))

    while True:
        # get string from the user
        message = input("enter any string #")
        # send the message to server
        s.send(message.encode('ascii'))
        if message == "" or message == "exit":
            break
        response = s.recv(buffer_size)
        if str(response.decode('ascii')) == "ok":
            print("received ok from server")
    # close the socket
    s.close()

if __name__ == '__main__':
    Main()

