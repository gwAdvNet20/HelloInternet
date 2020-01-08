#!/usr/bin/env python3

import socket

serverIP = "localhost" 
serverPort = 8080

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((serverIP, serverPort))
msg = "Hello in Python\n"
print("Sending: ", msg)
s.send(msg.encode())
response = s.recv(128)
print("Received:", response.decode())
s.close()
