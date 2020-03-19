#include  <unistd.h>
#include  <sys/types.h>       /* basic system data types */
#include  <sys/socket.h>      /* basic socket definitions */
#include  <netinet/in.h>      /* sockaddr_in{} and other Internet defns */
#include  <arpa/inet.h>       /* inet(3) functions */
#include <netdb.h>            /*gethostbyname function */

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <string>

#define MAXLINE 1024
using namespace std;

class Client {
public:
	//Initialization of Client
	Client() {
	}

	//Build a TCP connection with a server
	void start(string server_ip, int server_port) {
		char buf[MAXLINE];
		int connfd;
		struct sockaddr_in servaddr;
		connfd = socket(AF_INET, SOCK_STREAM, 0);

		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(server_port);
		inet_pton(AF_INET, server_ip.c_str(), &servaddr.sin_addr);

		//connect a specified server
		if (connect(connfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
			perror("connect error\n");
		} else {
			printf("connected to server %s:%d\n", server_ip.c_str(), server_port);
			write_read(connfd);     /* do it all */
		}
	}

	~Client() {
	}

private:
	//send a msg to the server and read the response from the server
	void write_read(int connfd) {
		int n = 0;
		char send_buffer[] = "Hello in Cpp";
		printf("Sending \" %s \"\n", send_buffer);
		n = write(connfd, send_buffer, strlen(send_buffer));
		if (n < 0) { 
			perror("ERROR writing to socket\n");
		} 
                char recv_buffer[1024] = {0}; 
		n = read(connfd, recv_buffer, 1024);
		if (n < 0) 
			perror("ERROR reading from socket\n");
		else {
			printf("Received: \" %s \"\n", recv_buffer);
		}
		close(connfd);	
	}
};

int main(int argc, char* argv[]) {
	if (argc < 3) {
		printf("Usage: %s server_ip server_port\n", argv[0]);
		return 1;
	}
	string server_ip = string(argv[1]);
	int server_port = atoi(argv[2]);
	Client* c = new Client();
	c->start(server_ip, server_port); 
	return 0;
}

