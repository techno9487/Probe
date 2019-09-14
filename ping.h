#ifndef _PING_H_
#define _PING_H_

#define PING_ERROR_UNSUPPORTED_FAMILY -1

#include <netinet/ip.h>

int ping4(int sock_fd, struct sockaddr_in* to);
int ping(int sock_fd, struct sockaddr* to);

#endif