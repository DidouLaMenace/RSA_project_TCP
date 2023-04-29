#ifndef TECHNICIAN_H
#define TECHNICIAN_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int socket;
    char *ip;
    int port;
    int status; // 0 to available, 1 to busy
} Technician;

typedef struct element_t {
    Technician *technician;
    struct element_t *next;
} element_t;

typedef struct  {
    element_t *head;
} linked_list_technician;

linked_list_technician *create_linked_list_technician();
Technician *create_technician(int socket, char *ip, int port);
bool t_list_is_empty(linked_list_technician *technicians);

void add_technician_to_linked_list(linked_list_technician *technicians, Technician *technician);
void remove_technician_by_socket(linked_list_technician *technicians, int socket);

Technician *get_technician_by_socket(linked_list_technician *technicians, int socket);
Technician *get_technician_by_index(linked_list_technician *technicians, int index);

int t_size_linked_list(linked_list_technician *technicians);

void t_list_destroy(linked_list_technician *technicians);

char* processing_technicians(char *message);

#endif