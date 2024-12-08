#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_BUFFER 1024

int main() {
    int sock = 0;
    struct sockaddr_in server_address;
    char buffer[MAX_BUFFER] = {0};
    
    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    
    // Convert IP address to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("Invalid address or address not supported");
        exit(EXIT_FAILURE);
    }
    
    // Connect to server
    if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    
    // Send a message to the server
    char* message = "Hello from client!";
    send(sock, message, strlen(message), 0);
    
    // Read response from the server
    read(sock, buffer, MAX_BUFFER);
    printf("Server response: %s\n", buffer);
    
    // Close the socket
    close(sock);
    
    return 0;
}

