#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <event2/buffer.h>

#include "http_parser.h"

#define BUFSIZE 1024
#define MAXERRS 16

extern char **environ; /* the environment */
int http_parse(http_t *http_request, struct evbuffer *client_buffer) {

    struct evbuffer *event_buffer = client_buffer;
    struct stat sbuf;     /* file status */
    size_t line_size = LINE_BUFSIZE;

    printf("HTTP PARSE START\n");

    /* get the HTTP request line */
    strcpy(http_request->buf, evbuffer_readln(event_buffer, &line_size, EVBUFFER_EOL_ANY));
    sscanf(http_request->buf, "%s %s %s\n", http_request->method, http_request->uri, http_request->version);

    printf("GET HTTP REQUEST\n");


    /* server only supports the GET and HEAD methods */
    if (strcmp(http_request->method, "GET") != 0 && strcmp(http_request->method, "HEAD") != 0) {
      return NOT_ALLOWED_HTTP_METHOD;
    }

    printf("ALLOWED METHODS\n");


//    /* read (and ignore) the HTTP headers */
//    strcpy(http_request->buf, evbuffer_readln(event_buffer, &line_size, EVBUFFER_EOL_ANY));
//    printf("READ HEADER\n");
//    while(strcmp(http_request->buf, "\r\n") != 0) {
//        printf("READING SMTH\n");
//        strcpy(http_request->buf, evbuffer_readln(event_buffer, &line_size, EVBUFFER_EOL_ANY));
//        printf("SMTH READED\n");
//    }
//
//    printf("HEADERS PARSED\n");

    /* parse the uri [crufty] */
    if (!strstr(http_request->uri, "cgi-bin")) { /* static content */
        strcpy(http_request->cgiargs, "");
        strcpy(http_request->filename, ".");
        strcat(http_request->filename, http_request->uri);
        if (http_request->uri[strlen(http_request->uri)-1] == '/') {
            strcat(http_request->filename, "index.html");
        }
    }

    /* make sure the file exists */
    if (stat(http_request->filename, &sbuf) < 0) {
      return FILE_NOT_EXIST;
    }

    /* serve static content */
    if (strstr(http_request->filename, ".html"))
        strcpy(http_request->filetype, "text/html");
    else if (strstr(http_request->filename, ".css"))
        strcpy(http_request->filetype, "text/css");
    else if (strstr(http_request->filename, ".js"))
        strcpy(http_request->filetype, "application/javascript");
    else if (strstr(http_request->filename, ".gif"))
        strcpy(http_request->filetype, "image/gif");
    else if (strstr(http_request->filename, ".swf"))
        strcpy(http_request->filetype, "application/x-shockwave-flash");
    else if (strstr(http_request->filename, ".jpeg"))
        strcpy(http_request->filetype, "image/jpeg");
    else if (strstr(http_request->filename, ".jpg"))
        strcpy(http_request->filetype, "image/jpg");
    else if (strstr(http_request->filename, ".png"))
        strcpy(http_request->filetype, "image/png");

    http_request->filesize = (size_t) sbuf.st_size;
    if (!(S_ISREG(sbuf.st_mode))) {
        return FILE_IS_EXECUTABLE;
    }

    return ALL_OK;
  }
