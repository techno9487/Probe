#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include "dns.h"

int dns_query(char* domain,int family,struct addrinfo* result)
{
    struct addrinfo hints, *res;
    memset(&hints,0,sizeof hints);

    hints.ai_family = family;
    hints.ai_socktype = SOCK_DGRAM;

    int error;
    error = getaddrinfo(domain,NULL,&hints,&res);
    if(error) {
        return error;
    }

    if(res != NULL && result != NULL) {
        memcpy(result,res,sizeof(struct addrinfo));
    }
    
    freeaddrinfo(res);
    return 0;
}