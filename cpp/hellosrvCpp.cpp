#include <unistd.h>
#include <sys/types.h>       /* basic system data types */
#include <sys/socket.h>      /* basic socket definitions */
#include <netinet/in.h>      /* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h>       /* inet(3) functions */
#include <sys/epoll.h>       /* epoll function */
#include <fcntl.h>           /* nonblocking */
#include <sys/resource.h>    /*setrlimit */

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <map>

using namespace std;

#define MAXEPOLLSIZE 10000
#define MAXLINE 1024

//set nonblocking for socket
int setnonblocking(int sockfd)
{
    if (fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)|O_NONBLOCK) == -1) {
        return -1;
    }
    return 0;
}

class Server {
private:
	int listen_port = 12345;
	int listen_backlog = 1024;
        map<int, string> clients_addresses;
public:
	Server(int port, int backlog):
		listen_port(port),
		listen_backlog(backlog) {
	}
	int handle(int connfd) {
		int nread;
		char buf[MAXLINE] = {0};
		nread = read(connfd, buf, MAXLINE);

		if (nread == 0) {
			map<int,string>::iterator it = clients_addresses.find(connfd);
			if (it != clients_addresses.end()) {
				printf("client %s close the connection\n", it->second.c_str());
				clients_addresses.erase(it);
			} else {
				printf("unknown client close the connection\n");
			}
			close(connfd);
			return -1;
		} 
		if (nread < 0) {
			map<int,string>::iterator it = clients_addresses.find(connfd);
			if (it != clients_addresses.end()) {
				printf("read error from client %s\n", (it->second).c_str());
				clients_addresses.erase(it);
			} else {
				printf("unknown client read error\n");
			} 
			close(connfd);
			return -1;
		}   
		char* language = strrchr(buf, ' '); 
		printf("language is %s\n", language);
		string response = "Goodbye " + string(language) + " from Cpp";
		write(connfd, response.c_str(), response.length()); 
		map<int,string>::iterator it = clients_addresses.find(connfd);
		if (it != clients_addresses.end()) {
			printf("close client %s\n", it->second.c_str());
			clients_addresses.erase(it);
		} else {
			printf("close unknown client\n");
		}
		close(connfd);
		return 0;
	}

	//Start listening with epoll
	void start() {
		int listenfd, connfd, kdpfd, nfds, n, nread, curfds,acceptCount = 0;
		struct sockaddr_in servaddr, cliaddr;
		socklen_t socklen = sizeof(struct sockaddr_in);
		struct epoll_event ev;
		struct epoll_event events[MAXEPOLLSIZE];
		struct rlimit rt;
		char buf[MAXLINE];

		rt.rlim_max = rt.rlim_cur = MAXEPOLLSIZE;
		//set resource limits
		if (setrlimit(RLIMIT_NOFILE, &rt) == -1) 
		{
			perror("setrlimit error");
			return;
		}

		//Listening clients with any address and port listen_port
		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET; 
		servaddr.sin_addr.s_addr = htonl (INADDR_ANY);
		servaddr.sin_port = htons (listen_port);

		listenfd = socket(AF_INET, SOCK_STREAM, 0); 
		if (listenfd == -1) {
			perror("can't create socket file");
			return;
		}

		int opt = 1;
		setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

		if (setnonblocking(listenfd) < 0) {
			perror("setnonblock error");
			return;
		}

		if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(struct sockaddr)) == -1) 
		{
			perror("bind error");
			return;
		} 
		if (listen(listenfd, listen_backlog) == -1) 
		{
			perror("listen error");
			return;
		}
		kdpfd = epoll_create(MAXEPOLLSIZE);
		ev.events = EPOLLIN | EPOLLET;
		ev.data.fd = listenfd;
		//register event and tell the relevant file descriptor event type.
		if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, listenfd, &ev) < 0) 
		{
			fprintf(stderr, "epoll set insertion error: fd=%d\n", listenfd);
			return;
		}
		curfds = 1;

		printf("epollserver startup,port %d, max connection is %d, backlog is %d\n", listen_port, MAXEPOLLSIZE, listen_backlog);

		//looping fds to monitor whether it has requests to process 
		for (;;) {
			//Waiting for the trigger of events
			nfds = epoll_wait(kdpfd, events, curfds, -1);
			if (nfds == -1)
			{
				perror("epoll_wait");
				continue;
			}
			for (n = 0; n < nfds; ++n)
			{
				if (events[n].data.fd == listenfd) 
				{
					connfd = accept(listenfd, (struct sockaddr *)&cliaddr,&socklen);
					if (connfd < 0) 
					{
						perror("accept error");
						continue;
					}

					sprintf(buf, "accept form %s:%d\n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
					string client_address = string(inet_ntoa(cliaddr.sin_addr)) + ":" + std::to_string(cliaddr.sin_port);
					clients_addresses.insert(pair<int, string>(connfd, client_address));                
					printf("accepted count(%d):%s", ++acceptCount, buf);

					if (curfds >= MAXEPOLLSIZE) {
						fprintf(stderr, "too many connection, more than %d\n", MAXEPOLLSIZE);
						close(connfd);
						continue;
					} 
					if (setnonblocking(connfd) < 0) {
						perror("setnonblocking error");
						return;
					}
					ev.events = EPOLLIN | EPOLLET;
					ev.data.fd = connfd;
					if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, connfd, &ev) < 0)
					{
						fprintf(stderr, "add socket '%d' to epoll failed: %s\n", connfd, strerror(errno));
						return;
					}
					curfds++;
					continue;
				} else { 
					if (handle(events[n].data.fd) < 0) {
						epoll_ctl(kdpfd, EPOLL_CTL_DEL, events[n].data.fd,&ev);
						curfds--;


					}
				}
			}
		}
		close(listenfd);
	}
	virtual ~Server() {
	} 
};

int main(int argc, char* argv[]) {
	if (argc < 3) {
		printf("Usage %s listen_port listen_backlog\n", argv[0]);
		return 1;
	} 
	int listen_port = atoi(argv[1]);
	int listen_backlog = atoi(argv[2]);	
	if (listen_port > 65535 || listen_port < 0)
	{
		printf("Please input valid port(0-65535)\n");
		return 0;
	}
	Server* s = new Server(listen_port, listen_backlog);
	s->start();
	return 0;
}
