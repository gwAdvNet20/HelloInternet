# Hello Internet! in Python

**TODO: Document python server functions!**

## Creating a Socket

Use the `socket.socket(socket.AF_INET, socket.SOCK_STREAM)` function to create a TCP socket in python. This will return a socket object.

## Connecting to a Server 

Use the `connect()` function of the socket object to connect to a server. The function takes a tuple with the hostname (or IP) and port.

## Sending and Receiving

Use the `send()` and `recv()` functions in the socket object to transfer data. If sending a string, you need to `encode()` the string first and you should `decode()` it when receiving.

## Clean up

You should `close()` a socket when you are done with it.
