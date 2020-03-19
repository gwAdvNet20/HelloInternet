// Client side C program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 

int main(int argc, char const *argv[]) 
{ 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *hello = "Hello in C";
    char buffer[1024] = {0};

    // Check STDIN format
    if(argc < 3) {
        printf("Usage: %s server_ip server_port\n", argv[0]);
		return -1;
    }

    // Create a socket, if success return a socket descriptor, else print out ERROR message.
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n ERROR. Socket creation error \n"); 
        return -1; 
    }
    // Set field of struct data, serv_addr
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    // Connect to server. 
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    {
        printf("\n Connection Failed...\n"); 
        return -1; 
    }

    // Send msg to server
    send(sock , hello , strlen(hello) , 0);
    
    // Receive msg from server
    valread = read(sock , buffer, sizeof(buffer));
    // Print out msg
    printf("%s\n",buffer);

    // Close socket
    close(sock);
    return 0; 
}