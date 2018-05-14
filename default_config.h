#ifndef DEFAULT_CONFIG_H
#define DEFAULT_CONFIG_H
/*Buffer of line in request*/
#define  LINE_BUFSIZE 256
/*Buffer of response page*/
#define RESPONSE_BUFSIZE 1024
/*Buffer of request page*/
#define REQUEST_BUFSIZE 1024
/*Buffer of DATE header*/
#define TIME_BUFSIZE 1024
/* Port to listen on. */
#define DEFAULT_SERVER_PORT 8000
/* Connection backlog (# of backlogged connections to accept). */
#define CONNECTION_BACKLOG 8
/* Number of worker threads.  Should match number of CPU cores reported in /proc/cpuinfo. */
#define DEFAULT_NUM_THREADS 4
/* for linux /var/www/html 
   for macos /library/webserver/documents */
#define DEFAULT_DOCUMENT_ROOT "/library/webserver/documents"

#endif //DEFAULT_CONFIG_H
