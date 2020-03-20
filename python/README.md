# HelloInternet in Python
## Katie Bramlett and Sreya Nalla
### 1/28/20

**Assignment: Create a client in Python to connect to a universal server.**

## Creating a Socket
- Call the socket() function in the server file -- which returns a socket that is not in the state of accepting connections, and is not bound to an address or port.
- Then, take in an address and a port from command line arguments entered by the user.
- For the client file, the user will run the file with 2 command line arguments: IP address and port number.
- For the server file, the user will run the file with 1 command line argument: just the port number.
- Now, with the bind() function, the address and port are paired and the socket is bound to them at the server.
- The server socket needs to move to a new state where it waits for client connections.

## Connecting to a Server
- Now, the server socket enters the wait state with the listen() function, where the server waits for any incoming client connections.
- Client must now call the connect() function to connect to the server socket.
- The IP address and the port number of the server must be specified.
- Next, by calling the accept() function, the server socket creates a pair containing a socket connected to a specific client through the IP address of that client.

## Sending and Receiving
- Using the socket for the client connection, both the client and the server can send and receive data from each other using the send() and recv() functions.
- When sending a string, the encode() function must be used.
- When receiving the string, the decode() function must then be used.

## Clean Up
- Socket must be closed on both ends after the sending/receiving is complete.
