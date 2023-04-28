#include "technician.h"

linked_list_technician *create_linked_list_technician()
{
    linked_list_technician *technicians = (linked_list_technician *) malloc(sizeof(linked_list_technician));
    if (technicians == NULL) {
        printf("Error allocating memory for technicians\n");
        exit(1);
    }
    technicians->head = NULL;
    return technicians;
}

Technician *create_technician(int socket, char *ip, int port)
{
    Technician *technician = (Technician *) malloc(sizeof(Technician));
    if (technician == NULL) {
        printf("Error allocating memory for technician\n");
        exit(1);
    }
    technician->socket = socket;
    technician->ip = ip;
    technician->port = port;
    technician->status = 0;
    return technician;
}

bool list_is_empty(linked_list_technician *technicians)
{
    return technicians->head == NULL;
}

void add_technician_to_linked_list(linked_list_technician *technicians, Technician *technician)
{
    element *new_element = (element *) malloc(sizeof(element));
    if (new_element == NULL) {
        printf("Error allocating memory for new element\n");
        exit(1);
    }
    new_element->technician = technician;
    new_element->next = NULL;

    if (list_is_empty(technicians)) {
        technicians->head = new_element;
    } else {
        element *current_element = technicians->head;
        while (current_element->next != NULL) {
            current_element = current_element->next;
        }
        current_element->next = new_element;
    }
}

void remove_technician_by_socket(linked_list_technician *technicians, int socket)
{
    if (list_is_empty(technicians)) {
        return;
    }

    element *current_element = technicians->head;
    element *previous_element = NULL;

    while (current_element != NULL) {
        if (current_element->technician->socket == socket) {
            if (previous_element == NULL) {
                technicians->head = current_element->next;
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

Technician *get_technician_by_socket(linked_list_technician *technicians, int socket)
{
    if (list_is_empty(technicians)) {
        return NULL;
    }

    element *current_element = technicians->head;

    while (current_element != NULL) {
        if (current_element->technician->socket == socket) {
            return current_element->technician;
        }
        current_element = current_element->next;
    }
    return NULL;
}

Technician *get_technician_by_index(linked_list_technician *technicians, int index)
{
    if (list_is_empty(technicians)) {
        return NULL;
    }

    element *current_element = technicians->head;
    int i = 0;

    while (current_element != NULL) {
        if (i == index) {
            return current_element->technician;
        }
        current_element = current_element->next;
        i++;
    }
    return NULL;
}

int size_linked_list(linked_list_technician *technicians)
{
    if (list_is_empty(technicians)) {
        return 0;
    }

    element *current_element = technicians->head;
    int i = 0;

    while (current_element != NULL) {
        current_element = current_element->next;
        i++;
    }
    return i;
}

void list_destroy(linked_list_technician *technicians)
{
    if (list_is_empty(technicians)) {
        return;
    }

    element *current_element = technicians->head;
    element *next_element = NULL;

    while (current_element != NULL) {
        next_element = current_element->next;
        free(current_element);
        current_element = next_element;
    }
    free(technicians);
}