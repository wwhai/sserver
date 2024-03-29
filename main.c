#include "sserver.h"
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>
#include "thpool.h"
#define LOG_USE_COLOR 1
//
int main(int argc, char *argv[])
{
    int arg;
    opterr = 0;
    char ip[15];
    int port;
    thpool = thpool_init(16);

    while ((arg = getopt(argc, argv, "h:p:")) != -1)
    {
        switch (arg)
        {
        case 'h':
            strcpy(ip, optarg);
            break;
        case 'p':
            *(&port) = atoi(optarg);
            break;
        default:
            log_error("Unknown option: '%c', Usage is: sserver -h ${Host} -p ${Port}. \n", (char)optopt);
            exit(1);
        }
    }
    if (strlen(ip) < 7 || port < 1)
    {
        log_error("Start server error, Usage is: sserver -h ${Host} -p ${Port}. \n");
        exit(1);
    }

    start_tcp_server(ip, port);
    thpool_wait(thpool);
    thpool_destroy(thpool);
    return 0;
}