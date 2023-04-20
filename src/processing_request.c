#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "robots.c"

#define MAX_SIZE_ANSWER 1000

char *processing_technicians(char *message)
{
    return message;
}

void *processing_experts(char *message)
{
}

char *processing(char *message) {
    // Robots try to process the request
    char *response;

    response = processing_robots(message);

    if (response != NULL) {
        char responsefrom[MAX_SIZE_ANSWER] = "Response from robot : ";
        response = strncat(responsefrom,response,MAX_SIZE_ANSWER);
        return response;
    } 
    
    // Technicians try to process the request
    response = processing_technicians(message);

    if (response != NULL) {
        char responsefrom[MAX_SIZE_ANSWER] = "Response from a technician : ";
        response = strncat(responsefrom,response,MAX_SIZE_ANSWER+MAX_SIZE_ANSWER);
        return response;
    } 
    
    response = processing_experts(message);

    if (response != NULL) {
        char responsefrom[MAX_SIZE_ANSWER] = "Response from an expert : ";
        response = strncat(responsefrom,response,MAX_SIZE_ANSWER+MAX_SIZE_ANSWER);
        return response;
    }

    return "No one can process the request";
}
