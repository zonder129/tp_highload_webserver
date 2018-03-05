#include "config.h"
#include <string.h>
#include "time.h"
#include <stdio.h>

void create_response (char *status,
                       char *status_msg, char* response) {
    sprintf(response, "HTTP/1.1 %s %s\n", status, status_msg);
    sprintf(response + strlen(response), "Server: The zonder129 Web server\n");
    char buf[TIME_BUFSIZE];
    time_t now = time(NULL);
    struct tm tm = *gmtime(&now);
    strftime(buf, sizeof(buf), "%a, %d, %b, %Y %H:%M:%S %Z", &tm);
    sprintf(response + strlen(response), "Date: %s\r\n", buf);
    sprintf(response + strlen(response), "Connection: close\r\n");
}