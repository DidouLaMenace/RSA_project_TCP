#include "expert.h"

linked_list_expert *create_linked_list_expert()
{
    linked_list_expert *experts = (linked_list_expert *) malloc(sizeof(linked_list_expert));
    if (experts == NULL) {
        printf("Error allocating memory for experts\n");
        exit(1);
    }
    experts->head = NULL;
    return experts;
}

Expert *create_expert(int socket, char *ip, int port)
{
    Expert *expert = (Expert *) malloc(sizeof(Expert));
    if (expert == NULL) {
        printf("Error allocating memory for experts\n");
        exit(1);
    }
    expert->socket = socket;
    expert->ip = ip;
    expert->port = port;
    expert->status = 0;
    return expert;
}

bool e_list_is_empty(linked_list_expert *experts)
{
    return experts->head == NULL;
}

void add_expert_to_linked_list(linked_list_expert *experts, Expert *expert)
{
    element_e *new_element = (element_e *) malloc(sizeof(element_e));
    if (new_element == NULL) {
        printf("Error allocating memory for new element\n");
        exit(1);
    }
    new_element->expert = expert;
    new_element->next = NULL;

    if (e_list_is_empty(experts)) {
        experts->head = new_element;
    } else {
        element_e *current_element = experts->head;
        while (current_element->next != NULL) {
            current_element = current_element->next;
        }
        current_element->next = new_element;
    }
}

void remove_expert_by_socket(linked_list_expert *experts, int socket)
{
    if (e_list_is_empty(experts)) {
        return;
    }

    element_e *current_element = experts->head;
    element_e *previous_element = NULL;

    while (current_element != NULL) {
        if (current_element->expert->socket == socket) {
            if (previous_element == NULL) {
                experts->head = current_element->next;
            } else {
                previous_element->next = current_element->next;
            }
            free(current_element);
            return;
        }
        previous_element = current_element;
        current_element = current_element->next;
    }
}

Expert *get_expert_by_socket(linked_list_expert *experts, int socket)
{
    if (e_list_is_empty(experts)) {
        return NULL;
    }

    element_e *current_element = experts->head;

    while (current_element != NULL) {
        if (current_element->expert->socket == socket) {
            return current_element->expert;
        }
        current_element = current_element->next;
    }
    return NULL;
}

Expert *get_expert_by_index(linked_list_expert *experts, int index)
{
    if (e_list_is_empty(experts)) {
        return NULL;
    }

    element_e *current_element = experts->head;
    int i = 0;

    while (current_element != NULL) {
        if (i == index) {
            return current_element->expert;
        }
        current_element = current_element->next;
        i++;
    }
    return NULL;
}

int e_size_linked_list(linked_list_expert *experts)
{
    if (e_list_is_empty(experts)) {
        return 0;
    }

    element_e *current_element = experts->head;
    int i = 0;

    while (current_element != NULL) {
        current_element = current_element->next;
        i++;
    }
    return i;
}

void e_list_destroy(linked_list_expert *experts)
{
    if (e_list_is_empty(experts)) {
        return;
    }

    element_e *current_element = experts->head;
    element_e *next_element = NULL;

    while (current_element != NULL) {
        next_element = current_element->next;
        free(current_element);
        current_element = next_element;
    }
    free(experts);
}