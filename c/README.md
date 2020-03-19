# Hello Internet in C

## Collaborators

Huadong Hu, Hamid Reza, Siqi Wang

## Quick Start

Launch terminal (seperate sessions on one machine) and compile the file: `gcc hellosrvC.c -o server` and `gcc helloC.c -o client`.

To connect the C client to a server, ensure that the server is running first before running client. Run the server: `./server <port>` with argument of the port server is listening. Then run the client: `./client <ip> <port>` with arguments of server ip and port.

## Relavant Socket API

### Creating a Socket

Use `socket(AF_INET, SOCK_STREAM, 0)` function to create a TCP socket in C. This will return a socket descriptor, an integer. `AF_INET` specify communication domain. `SOCK_STREAM` defines reliable connection. `0` is the default protocol, TCP.

### Bind and Listen

Use `bind(sock, &address, size)` function to associates and reserves a port for use by the socket. Use `listen(sock, queueLimit)` function to instruct TCP protocol to listen for connections. `queueLimit` is the active participants that can “wait” for a connection.

### Connecting to a Server

The client establishes a connection with the server by calling `connect(sock, &serv_addr, addrLen)`. Return `0` if succeed, `-1` otherwise.

### Sending and Receiving

Use `send(sock, msg, msgLen, 0)` and `read(sock, recvBuf, bufLen)` function to exchange data with stream socket. `recvBuf` stores received bytes.

### Close a Socket

Use `close(sock)` function to close a connection.