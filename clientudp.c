// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080  // Port to connect to
#define MAX_BUF 1024  // Maximum buffer size for receiving messages

int main() {
    int sockfd;
    char buffer[MAX_BUF];
    struct sockaddr_in server_addr;
    
    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    // Set server address properties
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);  // Port to communicate with
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Localhost address
    
    // Message to send to the server
    const char *message = "Hello, Server!";
    
    // Send message to the server
    sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Message sent to server: %s\n", message);
    
    // Receive response from the server
    int n = recvfrom(sockfd, (char *)buffer, MAX_BUF, 0, NULL, NULL);
    if (n < 0) {
        perror("Receive failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    buffer[n] = '\0';  // Null-terminate the received message
    
    printf("Server response: %s\n", buffer);
    
    // Close socket
    close(sockfd);
    return 0;
}

