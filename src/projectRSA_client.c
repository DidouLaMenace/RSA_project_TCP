#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

#include "utils.c"
#include "technician.h"

#define SERVER_IP "127.0.0.1"
#define PORT 8888

// Signal to know if the technician tap Ctrl+C or Ctrl+Z
int signal_end = 0;

void signal_handler(int signum)
{
    // if (signum == SIGINT || signum == SIGTSTP)
    // {
    //     printf("\nYou pressed Ctrl+C or Ctrl+Z\n");
    //     signal(signum, SIG_DFL);  // reset the signal to its default behavior
    //     signal_end = 1;
    // }
}

int main(int argc, char *argv[])
{
    int client_socket, technician_socket, expert_socket, n;
    struct sockaddr_in client_address, server_address, technician_server, expert_server;
    char message_from_client[1024], response_to_client[1024];
    char message_to_technician[1024], response_from_technician[1024];
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
        fgets(message_from_client, sizeof(message_from_client), stdin);

        // Send message to server
        if (write(client_socket, message_from_client, strlen(message_from_client)) < 0)
        {
            printf("Error sending message\n");
            exit(1);
        }

        // Read response from server
        memset(response_to_client, 0, sizeof(response_to_client));
        if (read(client_socket, response_to_client, sizeof(response_to_client)) < 0)
        {
            printf("Error reading response\n");
            exit(1);
        }

        
        printf("%s\n", response_to_client);
        
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

        // Connect to technician serve
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

        // Set up file descriptor set for select()
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        FD_SET(technician_socket, &read_fds);

        while(1) {
            // Check for available input
            fd_set tmp_fds = read_fds;
            struct timeval timeout = {0, 0};  // Set timeout to 0 seconds and 0 microseconds
            int ready = select(technician_socket + 1, &tmp_fds, NULL, NULL, &timeout);
            if (ready < 0) {
                printf("Error in select()\n");
                exit(1);
            } else if (ready == 0) {
                // No input available, continue loop
                continue;
            }

            if (FD_ISSET(STDIN_FILENO, &tmp_fds))
            {
                fgets(response_from_technician, sizeof(response_from_technician), stdin);

                clear_str(response_from_technician);

                signal(SIGINT, signal_handler);
                signal(SIGTSTP, signal_handler);

                if (signal_end == 1) 
                {
                    printf("You are disconnected\n");
                    char end[3] = "END";
                    send(technician_socket, end, strlen(end), 0);
                    break;
                }

                if (strcmp(response_from_technician, "EXIT") == 0)
                {
                    printf("You are disconnected\n");
                    char end[3] = "END";
                    send(technician_socket, end, strlen(end), 0);
                    break;
                }
            }
            
            if (FD_ISSET(technician_socket, &tmp_fds))
            {
                // Read response from server
                memset(message_to_technician, 0, sizeof(message_to_technician));
                if (read(technician_socket, message_to_technician, sizeof(message_to_technician)) < 0)
                {
                    printf("Error reading response\n");
                    exit(1);
                }

                printf("Request from client : %s\n", message_to_technician);

                // Write the response
                printf("Enter your response: ");
                fgets(response_from_technician, sizeof(response_from_technician), stdin);

                clear_str(response_from_technician);

                while (strlen(response_from_technician) >= MAX_SIZE_ANSWER)
                {
                    printf("ERROR : Your response is too long, please try again\n");
                    printf("Enter your response: ");
                    fgets(response_from_technician, sizeof(response_from_technician), stdin);
                    clear_str(response_from_technician);
                }

                // Send message to server
                send(technician_socket, response_from_technician, strlen(response_from_technician), 0);
            }
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
