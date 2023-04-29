#ifndef EXPERTS_H
#define EXPERTS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int socket;
    char *ip;
    int port;
    int status; // 0 to available, 1 to busy
} Expert;

typedef struct element_e {
    Expert *expert;
    struct element_e *next;
} element_e;

typedef struct  {
    element_e *head;
} linked_list_expert;

linked_list_expert *create_linked_list_expert();
Expert *create_expert(int socket, char *ip, int port);
bool e_list_is_empty(linked_list_expert *experts);

void add_expert_to_linked_list(linked_list_expert *experts, Expert *expert);
void remove_expert_by_socket(linked_list_expert *experts, int socket);

Expert *get_expert_by_socket(linked_list_expert *experts, int socket);
Expert *get_expert_by_index(linked_list_expert *experts, int index);

int e_size_linked_list(linked_list_expert *experts);

void e_list_destroy(linked_list_expert *experts);

char* processing_experts(char *message);

#endif