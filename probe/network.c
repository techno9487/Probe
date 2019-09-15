#include "network.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>

#include "dns.h"

int sockfd;
struct sockaddr addr_server;

int network_init(char* host, int port)
{
    if ( char_to_addr(host, &addr_server) != 0 ) {
        return -1;
    }

    switch(addr_server.sa_family)
    {
        case AF_INET:
            sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
            struct sockaddr_in* addr_v4 = (struct sockaddr_in*)&addr_server;
            addr_v4->sin_port = htons(port);
            break;
        case AF_INET6:
            sockfd = socket(AF_INET6,SOCK_DGRAM,IPPROTO_UDP);
            struct sockaddr_in6* addr_v6 = (struct sockaddr_in6*)&addr_server;
            addr_v6->sin6_port = htons(port);
        default:
            return -3;
            break;
    }
    
    if ( sockfd < 0 ) {
        return -2;
    }

    return 0;
}

void network_close()
{
    close(sockfd);
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