#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8888

int main()
{
    int client_socket, n;
    struct sockaddr_in server_address;
    char message[1024], response[1024];
    
    // create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        printf("Error creating socket\n");
        exit(1);
    }
    
    // set server address
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_address.sin_port = htons(PORT);
    
    // connect to server
    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
    {
        printf("Error connecting to server\n");
        exit(1);
    }
    
    // read message from user
    printf("Enter your message: ");
    fgets(message, sizeof(message), stdin);
    
    // send message to server
    if (write(client_socket, message, strlen(message)) < 0)
    {
        printf("Error sending message\n");
        exit(1);
    }
    
    // read response from server
    memset(response, 0, sizeof(response));
    if (read(client_socket, response, sizeof(response)) < 0)
    {
        printf("Error reading response\n");
        exit(1);
    }
    
    printf("Response from server: %s\n", response);
    
    // close connection
    close(client_socket);
    
    return 0;
}
