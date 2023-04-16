#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8888

int main()
{
    int server_socket, client_socket, level, n;
    struct sockaddr_in server_address, client_address;
    char message[1024], response[1024];
    
    // create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        printf("Error creating socket\n");
        exit(1);
    }
    
    // set server address
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);
    
    // bind socket to server address
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
    {
        printf("Error binding socket\n");
        exit(1);
    }
    
    // listen for incoming connections
    listen(server_socket, 3);
    
    while(1)
    {
        printf("Waiting for incoming connections...\n");
        
        // accept incoming connection
        n = sizeof(client_address);
        client_socket = accept(server_socket, (struct sockaddr*)&client_address, (socklen_t*)&n);
        if (client_socket < 0)
        {
            printf("Error accepting connection\n");
            exit(1);
        }
        
        printf("Connection accepted from %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
        
        // read incoming message
        memset(message, 0, sizeof(message));
        if (read(client_socket, message, sizeof(message)) < 0)
        {
            printf("Error reading message\n");
            exit(1);
        }
        
        printf("Received message from client: %s\n", message);
        
        // process message based on level
        level = message[0] - '0';
        switch (level)
        {
            case 1:
                // process message with robot
                // TODO: implement robot processing
                strcpy(response, "Response from robot");
                break;
            case 2:
                // forward message to level 2 technicians
                // TODO: implement level 2 processing
                strcpy(response, "Response from level 2 technicians");
                break;
            case 3:
                // forward message to level 3 experts
                // TODO: implement level 3 processing
                strcpy(response, "Response from level 3 experts");
                break;
            default:
                strcpy(response, "Invalid level");
                break;
        }
        
        // send response back to client
        if (write(client_socket, response, strlen(response)) < 0)
        {
            printf("Error sending response\n");
            exit(1);
        }
        
        printf("Response sent to client: %s\n", response);
        
        // close connection
        close(client_socket);
    }
    
    return 0;
}
