#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *processing_robots(char *message)
{
    // Check for keywords in message
    if (strstr(message, "reset") != NULL && strstr(message, "password") != NULL) {
        return "Please follow the instructions at this link to reset your password: example.com/reset";
    }
    else if (strstr(message, "change account info") != NULL) {
        return "To change your account information, log in to your account and navigate to the settings page.";
    }
    else if (strstr(message, "change password") != NULL) {
        return "To change your password, log in to your account and navigate to the settings page.";
    }
    else if (strstr(message, "change email") != NULL) {
        return "To change your email, log in to your account and navigate to the settings page.";
    }
    else if (strstr(message, "change phone number") != NULL) {
        return "To change your phone number, log in to your account and navigate to the settings page.";
    }
    else if (strstr(message, "change address") != NULL) {
        return "To change your address, log in to your account and navigate to the settings page.";
    }
    else if (strstr(message, "change payment info") != NULL) {
        return "To change your payment information, log in to your account and navigate to the settings page.";
    }
    else if (strstr(message, "network") != NULL && strstr(message, "connection") != NULL) {
        return "Sorry to hear you're having network issues. I'll forward your request to our level 2 technicians for further troubleshooting. Please wait while I transfer you.";
    }
    else {
        return NULL;
    }
}
