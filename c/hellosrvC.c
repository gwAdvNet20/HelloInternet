// Server side C program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket, valread, addrlen;
    struct sockaddr_in address, client; //Define server address
    char buffer[1024] = {0};
    char *hello = "Goodbye in C";
    addrlen = sizeof(client);

    // Check STDIN format
    if(argc < 2) {
        printf("Usage: %s server_port\n", argv[0]);
		return -1;
    }
       
    // Create a socket, if success return a socket descriptor, else print out ERROR message.
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY); // Use local address as server address
    address.sin_port = htons(atoi(argv[1])); 
    
    
    // Bind and listen on the given port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    { 
        perror("Bind failed\n");
        exit(EXIT_FAILURE);
    }
    
    // Listen for incoming requests
    if (listen(server_fd, 3) < 0) 
    { 
        perror("Failed to listen...\n");
        exit(EXIT_FAILURE);
    }
    // Accept a request
    if ((new_socket = accept(server_fd, (struct sockaddr *)&client, (socklen_t*)&addrlen)) < 0) 
    { 
        perror("Server accept failed\n"); 
        exit(EXIT_FAILURE); 
    }
    // Read msg from request
    valread = read(new_socket, buffer, 1024);
    // Print out the msg on screen
    printf("%s\n",buffer);

    // Send msg to the client
    send(new_socket, hello , strlen(hello), 0);
    return 0;
} 