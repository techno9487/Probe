#include "network.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>

#include "dns.h"

int sockfd;
struct sockaddr addr_server;

int network_init(char* host, int port)
{
    if ( char_to_addr(host, &addr_server) != 0 ) {
        return -1;
    }

    sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if ( sockfd < 0 ) {
        return -2;
    }

    

    return 0;
}

int char_to_addr(char* host, struct sockaddr* addr)
{
    struct sockaddr_in* addr_v4 = (struct sockaddr_in*)addr;
    if ( inet_pton(AF_INET, host, &addr_v4->sin_addr) == 1 ) {
        addr->sa_family = AF_INET;
        return 0;
    }

    struct sockaddr_in6* addr_v6 = (struct sockaddr_in6*)addr;
    if ( inet_pton(AF_INET6, host, &addr_v6->sin6_addr) == 1 ) {
        addr->sa_family = AF_INET6;
        return 0;
    }

    return -1;
}