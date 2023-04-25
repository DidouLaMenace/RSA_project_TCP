#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "utils.c"

#define SERVER_IP "127.0.0.1"
#define PORT 8888

int main(int argc, char *argv[])
{
    int client_socket, technician_socket, expert_socket, n;
    struct sockaddr_in client_address, server_address, technician_server, expert_server;
    char message[1024], response[1024];
    char auth_message[1024];

    if (argc != 2)
    {
        printf("Usage: %s <client|technician|experts>\n", argv[0]);
        exit(1);
    }
    
    // Set server address
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_address.sin_port = htons(PORT);

    // Set auth message
    sprintf(auth_message, "%s", argv[1]);

    // Processing client part
    if (strcmp(auth_message, "client") == 0)
    {
        // Create socket
        client_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (client_socket == -1)
        {
            printf("Error creating socket\n");
            exit(1);
        }


        // Connect to server
        if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
        {
            printf("Error connecting to server\n");
            exit(1);
        }

        if (write(client_socket, auth_message, strlen(auth_message)) < 0)
        {
            printf("Error sending message\n");
            exit(1);
        }

        printf("Enter your message: ");
        fgets(message, sizeof(message), stdin);

        // Send message to server
        if (write(client_socket, message, strlen(message)) < 0)
        {
            printf("Error sending message\n");
            exit(1);
        }

        // Read response from server
        memset(response, 0, sizeof(response));
        if (read(client_socket, response, sizeof(response)) < 0)
        {
            printf("Error reading response\n");
            exit(1);
        }

        printf("%s\n", response);

        // Close connection
        close(client_socket);
    }
    // Processint technician part
    else if (strcmp(auth_message, "technician") == 0)
    {
        printf("You are connected to the server as a technician\n");
        
        // Create socket
        technician_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (technician_socket == -1)
        {
            printf("Error creating socket\n");
            exit(1);
        }

        // Set technician server address
        technician_server.sin_family = AF_INET;
        technician_server.sin_addr.s_addr = inet_addr(SERVER_IP);
        technician_server.sin_port = htons(PORT);

        // Connect to technician server
        if (connect(technician_socket, (struct sockaddr*)&technician_server, sizeof(technician_server)) < 0)
        {
            printf("Error connecting to technician server\n");
            exit(1);
        }

        if (write(technician_socket, auth_message, strlen(auth_message)) < 0)
        {
            printf("Error sending message\n");
            exit(1);
        }

        while(1) {
            // Read response from server
            memset(response, 0, sizeof(response));
            if (read(technician_socket, response, sizeof(response)) < 0)
            {
                printf("Error reading response\n");
                exit(1);
            }

            printf("%s\n", response);
        }

        // Close connection
        close(technician_socket);

    }
    // Processing experts part
    else if (strcmp(auth_message, "experts") == 0)
    {
        printf("You are connected to the server as an expert\n");
    }
    else
    {
        printf("Error\n");
        exit(1);
    }

    return 0;
}
