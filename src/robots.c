#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *processing_robots(char *message)
{
    // Check for keywords in message
    if (strstr(message, "reset password") != NULL) {
        return "If you forgot your password, you can follow the link on the login page to reset your password. Make sure to choose a strong and unique password that you can remember. Otherwise, you can contact our support team for assistance. If you just want to change your password, you can do so from your profile page.";
    }
    else if (strstr(message, "change account info") != NULL) {
        return "To change your account information, log in to your account and go to your profile page. From there, you can update your information.";
    }
    else if (strstr(message, "slow internet") != NULL) {
        return "Check for any background downloads or updates that may be hogging the bandwidth, otherwise contact your internet service provider to see if there are any issues in their area.";
    }
    else if (strstr(message, "no internet") != NULL) {
        return "Check if your router is properly connected to the modem and if your device is connected to the correct Wi-Fi network, otherwise contact your internet service provider to see if there are any issues in their area.";
    }
    else if (strstr(message, "intermittent connection") != NULL) {
        return "Check if there are any nearby devices or appliances that may be causing interference with the Wi-Fi signal, otherwise contact your internet service provider to see if there are any issues in their area.";
    }
    else if (strstr(message, "connection drops frequently") != NULL) {
        return "Check if your router firmware is up to date, otherwise contact your internet service provider to see if there are any issues in their area.";
    }
    else if (strstr(message, "can't connect to a specific website") != NULL) {
        return "Check if the website is down for everyone or just you, otherwise contact the website's support team for assistance.";
    }
    else if (strstr(message, "computer won't turn on") != NULL) {
        return "It sounds like you might have a power issue. Try checking to make sure your power cord is properly plugged in, and if that doesn't work, you may need to have your power supply checked.";
    }
    else if (strstr(message, "reset password") != NULL) {
        return "To reset your password, you can go to our website and click on the 'forgot password' link. Follow the prompts to reset your password, and make sure to choose a strong and unique password that you can remember.";
    }
    else if (strstr(message, "can't connect to Wi-Fi") != NULL) {
        return "It seems like there may be an issue with your Wi-Fi connection. Try resetting your router or modem, and make sure you're using the correct password. If that doesn't work, you may need to contact your internet service provider for further assistance.";
    }
    else if (strstr(message, "printer isn't working") != NULL) {
        return "It sounds like there might be a problem with your printer's drivers or settings. Try updating your printer's drivers, and make sure your printer is properly connected to your computer. You can also try restarting your computer and printer to see if that helps.";
    }
    else if (strstr(message, "printer won't print") != NULL) {
        return "It sounds like there might be a problem with your printer's drivers or settings. Try updating your printer's drivers, and make sure your printer is properly connected to your computer. You can also try restarting your computer and printer to see if that helps.";
    }
    else if (strstr(message, "printer won't connect") != NULL) {
        return "It sounds like there might be a problem with your printer's drivers or settings. Try updating your printer's drivers, and make sure your printer is properly connected to your computer. You can also try restarting your computer and printer to see if that helps.";
    }
    else if (strstr(message, "printer won't turn on") != NULL) {
        return "It sounds like there might be a problem with your printer's drivers or settings. Try updating your printer's drivers, and make sure your printer is properly connected to your computer. You can also try restarting your computer and printer to see if that helps.";
    }
    else if (strstr(message, "deleted file")) {
        return "If you've accidentally deleted an important file, don't panic. Check your recycling bin first to see if the file is there. If it's not, you may be able to recover it using file recovery software. If you're not comfortable doing this yourself, you may want to contact a professional data recovery service.";
    }
    else if (strstr(message, "phone keeps freezing")) {
        return "It's possible that there are too many apps running in the background. Try closing all the apps and see if that helps. If not, you can try restarting your phone.";
    }
    else if (strstr(message, "account has been hacked")) {
        return "Please change your password immediately and enable two-factor authentication. Also, check your account settings to make sure there are no unauthorized changes. If you're still concerned, contact our support team for further assistance.";
    }
    else {
        return NULL;
    }
}