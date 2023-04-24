#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>

#include "robots.c"
#include "technicians.c"
#include "experts.c"

#define MAX_SIZE_ANSWER 1000
#define PORT 8888

// Get the authentification message from the client without the \0 and any space
void clear_str(char* str)
{
    int start = 0;
    int end = strlen(str) - 1;

    // Trim leading whitespace
    while (isspace(str[start]))
    {
        start++;
    }

    // Trim trailing whitespace
    while ((end >= start) && isspace(str[end]))
    {
        end--;
    }

    // Move remaining characters to start of string
    int i;
    for (i = start; i <= end; i++)
    {
        str[i - start] = str[i];
    }
    str[i - start] = '\0';  // Null-terminate the trimmed string
}

void *client_handler(void *arg)
{
    int client_socket = *(int *)arg;
    char message[1024];
    char *response;

    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);

    if (getpeername(client_socket, (struct sockaddr*)&client_address, &client_address_len) < 0)
    {
        printf("Error getting client address\n");
        exit(1);
    }

    // Read incoming message
    memset(message, 0, sizeof(message));
    if (read(client_socket, message, sizeof(message)) < 0)
    {
        printf("Error reading message\n");
        exit(1);
    }

    clear_str(message);
    
    printf("Received message from client %s:%d : %s\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port),message);

    // Process message
    response = processing_robots(message);

    if (response != NULL) {
        char responsefrom[MAX_SIZE_ANSWER] = "Response from robot : ";
        response = strncat(responsefrom,response,MAX_SIZE_ANSWER+MAX_SIZE_ANSWER);
    } 
    else {
        response = "after";
    }

    // Send response to client
    if (write(client_socket, response, strlen(response)) < 0)
    {
        printf("Error sending response\n");
        exit(1);
    }

    printf("Response sent to client %s:%d : %s\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port), response);

    // Close connection
    close(client_socket);

    return NULL;
}


int main()
{
    int server_socket, new_socket, client_socket, technician_socket, expert_socket, n;
    struct sockaddr_in server_address, client_address;
    char message[1024];
    char auth_message[1024];
    char *response;
    
    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        printf("Error creating socket\n");
        exit(1);
    }
    
    // Server Address by default 127.0.0.1, number of port choose randomly
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);
    
    // Bind socket to server address
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
    {
        printf("Error binding socket\n");
        exit(1);
    }
    
    // Listen for incoming connections
    listen(server_socket, 3);

    while(1)
    {
        // printf("\nWaiting for incoming connections...\n");
        
        // Accept incoming connection
        n = sizeof(client_address);
        client_socket = accept(server_socket, (struct sockaddr*)&client_address, (socklen_t*)&n);
        if (client_socket < 0)
        {
            printf("Error accepting connection\n");
            exit(1);
        }

        printf("\nConnection accepted from %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
        
        // Read Authentification message
        memset(auth_message, 0, sizeof(auth_message));
        if (read(client_socket, auth_message, sizeof(auth_message)) < 0)
        {
            printf("Error reading message\n");
            exit(1);
        }

        printf("Authentification message : %s", auth_message);

        clear_str(auth_message);

        if (strcmp(auth_message, "client") == 0) {
            printf("Client connected\n");
        }
        else if (strcmp(auth_message, "technician") == 0) {
            printf("Technician connected\n");
        }
        else if (strcmp(auth_message, "expert") == 0) {
            printf("Expert connected\n");
        }
        else {
            printf("Unknown user\n");
        }

        // Create thread for client
        pthread_t client_thread;
        int *socket_thread = malloc(sizeof(int));
        *socket_thread = client_socket;
        if (pthread_create(&client_thread, NULL, client_handler, (void *)socket_thread) < 0)
        {
            printf("Error creating thread\n");
            close(client_socket);
            free(socket_thread);
            continue;
        }

        pthread_detach(client_thread);




        // // Read incoming message
        // memset(message, 0, sizeof(message));
        // if (read(client_socket, message, sizeof(message)) < 0)
        // {
        //     printf("Error reading message\n");
        //     exit(1);
        // }
        
        // printf("Received message from client: %s\n", message);
        
        // // Process message
        // response = processing_robots(message);

        // if (response != NULL) {
        //     char responsefrom[MAX_SIZE_ANSWER] = "Response from robot : ";
        //     response = strncat(responsefrom,response,MAX_SIZE_ANSWER+MAX_SIZE_ANSWER);
        // } 
        // else {
        //     response = "after";
        // }
        // // else {
        // //     response = processing_technicians(message);

        // //     if (response != NULL) {
        // //         char responsefrom[MAX_SIZE_ANSWER] = "Response from a technician : ";
        // //         response = strncat(responsefrom,response,MAX_SIZE_ANSWER+MAX_SIZE_ANSWER);
        // //     } 
        // //     else {
        // //         response = processing_experts(message);

        // //         if (response != NULL) {
        // //             char responsefrom[MAX_SIZE_ANSWER] = "Response from an expert : ";
        // //             response = strncat(responsefrom,response,MAX_SIZE_ANSWER+MAX_SIZE_ANSWER);
        // //         }
        // //         else {
        // //             response = "No one can process the request";
        // //         }
        // //     }
        // // }
        
        // // Send response to client
        // if (write(client_socket, response, strlen(response)) < 0)
        // {
        //     printf("Error sending response\n");
        //     exit(1);
        // }
        

        // printf("Response sent to client: %s\n", response);
        
        // // Close connection
        // close(client_socket);
    }
    
    close(server_socket);
    return 0;
}
