#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>

#include "robots.c"
#include "technician.h"
#include "experts.c"
#include "utils.c"
#include "technician.c"

#define NUMBER_MAX_OF_TECHNICIANS 10
#define PORT 8888

// Technician : Create list for technicians
linked_list_technician *technicians;


// Processing client's request with multi-threading to treat several clients at the same time
void *client_threading(void *arg)
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

    if (strlen(message) >= MAX_SIZE_ANSWER)
    {
        response = "Your message is too long. Please try again.";
    }
    else {
        printf("Received message from client %s:%d : %s\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port),message);

        // Process message
        response = processing_robots(message);

        if (response != NULL) {
            char responsefrom[MAX_SIZE_ANSWER] = "Response from robot : ";
            response = strncat(responsefrom,response,2*MAX_SIZE_ANSWER);
        } 
        else {
            response = processing_technicians(message);
            if (response != NULL) {
                char responsefrom[MAX_SIZE_ANSWER] = "Response from technician : ";
                response = strncat(responsefrom,response,2*MAX_SIZE_ANSWER);
            }
            else {
                response = processing_experts(message);
                if (response != NULL) {
                    char responsefrom[MAX_SIZE_ANSWER] = "Response from expert : ";
                    response = strncat(responsefrom,response,2*MAX_SIZE_ANSWER);
                }
                else {
                    response = NULL;
                }
            }
        }
    }

    if (response == NULL) {
        response = "No response from robot, technician or expert. Please try again later.";
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

// Sending client's request to all technicians
char* processing_technicians(char *message) {
    int socket_technician = -1;
    int index_technician = -1;
    int nb_technician = size_linked_list(technicians);
    Technician *t;

    printf("%d technicians available\n",nb_technician);

    if (nb_technician == 0) {
        return "No technician available. Please try again later.";
    }

    // Allocated memory for response of technician 
    char *response_from_technicians = malloc(sizeof(char) * MAX_SIZE_ANSWER);
    if (response_from_technicians == NULL) {
        printf("Error allocating memory for response\n");
        exit(1);
    }

    // If no technician is available, add the request to the queue and wait for a technician
    while (socket_technician == -1 || index_technician == -1) {
        for (int i = 0 ; i < nb_technician ; i++)
        {
            t = get_technician_by_index(technicians, i);
            if (t->status == 0) {
                socket_technician = t->socket;
                index_technician = i;
                t->status = 1;
                break;
            }
        }
    }
    

    if (send(socket_technician, message, strlen(message), 0) < 0) {
        printf("Error sending message to technician\n");
        exit(1);
    }

    printf("Sent message to technician %d\n",socket_technician);

    if (recv(socket_technician, response_from_technicians, MAX_SIZE_ANSWER, 0) < 0) {
        printf("Error receiving message from technician\n");
        exit(1);
    }

    // Processing command EXIT and NULL from technician
    if (strcmp(response_from_technicians,"EXIT") == 0)
    {
        remove_technician_by_socket(technicians,socket_technician);
        return processing_technicians(message);
    }

    if (strcmp(response_from_technicians,"NULL") == 0) 
    {
        return NULL;
    }

    clear_str(response_from_technicians);

    printf("Response from technician %d : %s\n",socket_technician,response_from_technicians);
    
    // Now the technician is available
    t->status = 0;

    return response_from_technicians;
}

int main()
{
    int server_socket, client_socket, n;
    struct sockaddr_in server_address, client_address;
    char auth_message[1024];

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

    printf("Waiting for incoming connections...\n");

    technicians = create_linked_list_technician();

    while(1)
    {
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

        printf("Authentification message : %s\n", auth_message);

        clear_str(auth_message);

        // We process the request from a client
        if (strcmp(auth_message, "client") == 0) {
            printf("Client connected\n");
            // Create thread for client
            pthread_t client_thread;
            int *socket_thread = malloc(sizeof(int));
            *socket_thread = client_socket;
            if (pthread_create(&client_thread, NULL, client_threading, (void *)socket_thread) < 0)
            {
                printf("Error creating thread\n");
                close(client_socket);
                free(socket_thread);
                continue;
            }

            pthread_detach(client_thread);
        }
        // We set up the interface for the technician
        else if (strcmp(auth_message, "technician") == 0) {
            printf("Technician connected\n");

            if (size_linked_list(technicians) >= NUMBER_MAX_OF_TECHNICIANS) 
            {
                printf("Error: too many technicians\n");
                continue;
            }

            Technician *t = create_technician(client_socket, inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
            add_technician_to_linked_list(technicians, t);
            //add_technician(client_socket,inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
        }
        // We set up the interface for the expert
        else if (strcmp(auth_message, "expert") == 0) {
            printf("Expert connected\n");
        }
        else {
            printf("Unknown user\n");
        }
    }
    
    list_destroy(technicians);
    close(server_socket);
    return 0;
}
