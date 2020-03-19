Team Members: Xiaosu Lyu, Cuidi Wei, Ziyue Li
# HelloInternet
Say Hello to a remote friend in all the languages!
## Compile server
g++ -std=c++11 hellosrvCpp.cpp  -o hellosrvCpp
## Compile client
g++ -std=c++11 helloCpp.cpp -o helloCpp
## Run
Start server with listen port and backlog
   ```
   ./hellosrvCpp 12345 1024
   epollserver startup,port 12345, max connection is 10000, backlog is 1024
   ```
   Start client with the server ip and port
   ```
   ./helloCpp 127.0.0.1 12345
   connected to server 127.0.0.1:12345
   Sending " Hello in Cpp "
   Received: " Goodbye  Cpp from Cpp "
   ```
The client first connects to the server, then send a message "Hello in Cpp" to the server, and the server will response it with "Goodbye  Cpp from Cpp".
On the server platform, it will print the following infomation:
```
  accepted count(1):accept form 127.0.0.1:48288
  language is  Cpp
  close client 127.0.0.1:48288
```
You can use other client with other programming language to connect to this server and get the same result. For example, start the server with port 8080, and then start the python client helloPython.py in HelloInternet/python, the server will output the following message:
```
xiaosuGW@node0:~/HelloInternet/cpp$ ./hellosrvCpp 8080 1024
epollserver startup,port 8080, max connection is 10000, backlog is 1024
accepted count(1):accept form 127.0.0.1:55999
language is  Python

close client 127.0.0.1:55999
```
## Create a Socket
Use `int socket(int domain, int type, int protocol)` function to create a TCP socket in C. This will return a socket fd.
## Connecting to a Server
Use `int connect(int sockfd, const struct sockaddr *addr,socklen_t addrlen)` to connect to a server.
## Bind address 
Use ` int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen)` to assign a specified address to the socket fd returned by `nt socket(int domain, int type, int protocol)` function.
## Listen 
Use ` int listen(int sockfd, int backlog)` to listen to client comming.
## Accept comming client
Use `int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)` to accept the incomming clients
## Epoll
Use `epoll_create, epoll_ctl, epoll_wait` to monitor the READ and WRITE events from the clients.
## Read and write message
Use `ssize_t read(int fd, void *buf, size_t count)` and `ssize_t write(int fd, const void *buf, size_t count)` to read and write message to the peer side.



