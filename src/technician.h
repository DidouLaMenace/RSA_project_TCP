#ifndef TECHNICIAN_HANDLER_H
#define TECHNICIAN_HANDLER_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int socket;
    char *ip;
    int port;
} Technician;

char* processing_technicians(char *message);
void add_technician(int socket,char *ip, int port);

#endif