#ifndef TECHNICIAN_HANDLER_H
#define TECHNICIAN_HANDLER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int socket;
    char *ip;
    int port;
    int status; // 0 to available, 1 to busy
} Technician;

typedef struct element {
    Technician *technician;
    struct element *next;
} element;

typedef struct  {
    element *head;
} linked_list_technician;

linked_list_technician *create_linked_list_technician();
Technician *create_technician(int socket, char *ip, int port);
bool list_is_empty(linked_list_technician *technicians);

void add_technician_to_linked_list(linked_list_technician *technicians, Technician *technician);
void remove_technician_by_socket(linked_list_technician *technicians, int socket);

Technician *get_technician_by_socket(linked_list_technician *technicians, int socket);
Technician *get_technician_by_index(linked_list_technician *technicians, int index);

int size_linked_list(linked_list_technician *technicians);

void list_destroy(linked_list_technician *technicians);

char* processing_technicians(char *message);
//void add_technician(int socket,char *ip, int port);

#endif