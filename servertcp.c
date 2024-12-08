#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_BUFFER 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    char buffer[MAX_BUFFER] = {0};
    socklen_t addr_len = sizeof(address);  // Corrected the socklen_t variable

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket to address
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    // Accept a connection from a client
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addr_len)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    // Read data from client
    read(new_socket, buffer, MAX_BUFFER);
    printf("Client message: %s\n", buffer);

    // Send a response back to the client
    char* message = "Hello from server!";
    send(new_socket, message, strlen(message), 0);

    // Close the sockets
    close(new_socket);
    close(server_fd);

    return 0;
}

