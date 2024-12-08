// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080  // Port to listen on
#define MAX_BUF 1024  // Maximum buffer size for receiving messages

int main() {
    int sockfd;
    char buffer[MAX_BUF];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    
    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    // Set server address properties
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Bind to any interface
    server_addr.sin_port = htons(PORT);  // Port to bind to
    
    // Bind socket to the address
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d...\n", PORT);
    
    // Loop to receive and send messages
    while (1) {
        int n = recvfrom(sockfd, (char *)buffer, MAX_BUF, 0, (struct sockaddr *)&client_addr, &addr_len);
        if (n < 0) {
            perror("Receive failed");
            continue;
        }
        buffer[n] = '\0';  // Null-terminate the received message
        printf("Received message: %s\n", buffer);
        
        // Send a response back to the client
        const char *response = "Message received!";
        sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&client_addr, addr_len);
    }

    close(sockfd);
    return 0;
}

