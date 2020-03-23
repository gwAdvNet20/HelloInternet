# Hello Internet in Python-Juypter Notebook  

## Group Members
-Tuhina Dasgupta
-Linnea Dierksheide
-Becky Shanley 

## Install  
-Juypter Notebook (5+)  
-Python 3+  
(might be helpful to have brew (Mac) to manage all of this) but pip is part of setup.sh and does the same thing 

## Setup & Creating Socket
Run the setup.sh script to install & launch this exercise. 
Use the socket.socket(socket.AF_INET, socket.SOCK_STREAM) function to create a TCP socket in python. This will return a socket object.

## Connecting to Socket
Use the socket.connect() function of the socket object to connect to a server. The function takes a tuple with the hostname (or IP address) and port.

## Sending & Receiving
Use the socket.send() and socket.recv() functions in the socket object to transfer data.

## Cleanup  
You should socket.close() a socket when you are done with it.
