/**
* Probe is a service that sits in places on your network to monitor the health of services
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>

#include "dns.h"
#include "ping.h"
#include "network.h"

int main(int argc, char* argv[])
{
    if ( network_init("192.168.0.1",666) < 0 ) {
        printf("Failed to init network\n");
        return -1;
    }

    //TODO: Daemon loop and signal handling

    network_close();

    return 0;
}