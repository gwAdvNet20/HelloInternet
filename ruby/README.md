# Hello Internet! in Ruby

Group Members:
Zach Coveno, Jon Minkin, & Kevin Deems

## Creating a Socket

Need the correct package for socket programming: `require 'socket'`.
Use the `TCPSocket.new hostname, port` function to create a TCP socket for the client in ruby. This will return a socket object.
For creating a server use `TCPServer.open(<port number>)`.

## Connecting to a Server

Creating a socket in Ruby is the same as establishing a connection. Using the `TCPSocket.new`, an object is created and established with the provided data.
For a server to find a client, use `server.accept`, which returns a client object. The client object can provide information like IP and hostname of client.

## Sending and Receiving

Use the `puts()` and `gets()` functions in the socket object to transfer and receive data respectively.

## Clean up

You should `close` a socket when you are done with it.
