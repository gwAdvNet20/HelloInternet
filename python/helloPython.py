# SOCKET CLIENT
import socket
import sys

# Set IP address and port number as command line arguments
IPaddr = str(sys.argv[1]); 
portNum = int(sys.argv[2]);

# S = socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to IP address at port number
s.connect((IPaddr, portNum))

# Declare message to send
msg = "Hello in Python\n"

# Print message to client
print("Sending message: ", msg)

# Send message to server
s.send(msg.encode())

# Receive and print
data = s.recv(1024)
print("Received message: ", data.decode())

# Close socket
s.close()
