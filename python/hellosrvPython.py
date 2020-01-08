#!/usr/bin/env python3

import socket

HOST = '0.0.0.0'  # Listen on all interfaces
PORT = 8080
msg = 'Goodbye in Python'

print('Starting Python hellosrv')

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind((HOST, PORT))
    s.listen()
    while True:
        conn, addr = s.accept()
        with conn:
            print('Connection from ', addr)
            data = conn.recv(1024)
            print(data.decode())
            conn.sendall(msg.encode())
            conn.close()
