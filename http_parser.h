#ifndef HTTP_PARSER_H
#define HTTP_PARSER_H
#include "config.h"
#include <string.h>

#define ALL_OK 1
#define NOT_ALLOWED_HTTP_METHOD -1
#define FILE_NOT_EXIST -2
#define FILE_IS_EXECUTABLE -3
#define ESCAPING_ROOT -4

typedef struct http {
    char method[REQUEST_BUFSIZE];  /* request method */
    char uri[REQUEST_BUFSIZE];     /* request uri */
    char version[REQUEST_BUFSIZE]; /* request method */
    char filename[REQUEST_BUFSIZE];/* path derived from uri */
    char filetype[REQUEST_BUFSIZE];/* path derived from uri */
    char cgiargs[REQUEST_BUFSIZE]; /* cgi argument list */
    char buf[REQUEST_BUFSIZE];     /* temporary buffer */
    size_t filesize;
} http_t;

int http_parse(http_t* http_request, struct evbuffer * client_buffer);
#endif //HTTP_PARSER_H
