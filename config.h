#ifndef CONFIG_H
#define CONFIG_H
/*Buffer of line in request*/
#define  LINE_BUFSIZE 256
/*Buffer of response page*/
#define RESPONSE_BUFSIZE 1024
/*Buffer of request page*/
#define REQUEST_BUFSIZE 1024
/*Buffer of DATE header*/
#define TIME_BUFSIZE 1024
/* Port to listen on. */
#define SERVER_PORT 8000
/* Connection backlog (# of backlogged connections to accept). */
#define CONNECTION_BACKLOG 8
/* Socket read and write timeouts, in seconds. */
#define SOCKET_READ_TIMEOUT_SECONDS 1
#define SOCKET_WRITE_TIMEOUT_SECONDS 1
/* Number of worker threads.  Should match number of CPU cores reported in /proc/cpuinfo. */
#define NUM_THREADS 2
#define DOCUMENT_ROOT "/var/www/html"
#endif //CONFIG_H
