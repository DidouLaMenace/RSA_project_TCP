#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "robots.c"

void *processing_technicians(char *message)
{
}

void *processing_experts(char *message)
{
}

char *processing(char *message) {
    // Robots try to process the request
    char *response;

    response = processing_robots(message);

    if (response != NULL) {
        return response;
    } 
    
    // Technicians try to process the request
    response = processing_technicians(message);

    if (response != NULL) {
        return response;
    } 
    
    response = processing_experts(message);

    if (response != NULL) {
        return response;
    }

    return "No one can process the request";
}
