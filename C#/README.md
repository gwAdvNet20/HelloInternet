## team member
Mingyu Ma, Hamza Umar

## dependencies
csc.exe, used to compile c# code.
Mono, used to run c# program on Linux system.
Both are included in setup.sh to install. Fair warning it takes a while to install Mono.

## compile command
To compile the c# server, run `csc hellosrvC#.cs`.
To compile the c# client, run `csc helloC#.cs`.

## run command
To run the c# server, run `mono hellosrvC#.exe` with command line input.
To run the c# client, run `mono helloC#.exe` with command line input.

## creating a socket
Use `Socket(AddressFamily, SocketType, ProtocolType)` to create a socket.
AddressFamily is a enumeration used to specify the addressing scheme that a socket will use to resolve an address.
SocketType is also a enumeration that provides several options for defining the type of socket, basically decides what type of data transmission you prefered for this socket.
ProtocolType is also a enumeration that is used to inform the Windows Socket API the type of protocal you wish to use.

## connecting to a server
Use `Connect(EndPoint)` to connect to a remote host.
An EndPoint is an abstract type that basically defines a remote host.
In this particular case we use IPEndPoint class which takes an IP address and a port number as input to create the EndPoint.

## sending and receiving
Use `Send(Byte[])` and `Receive(Byte[])` to send and receive message.
In C# all message is send and received in Byte type, so must convert between Byte[] type and string type in order to send and receive message.

## clean up
Use `Shutdown(SocketShutdown)` and `Close()` to disable all socket sends and receives and then close it.