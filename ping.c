#include "ping.h"

#include <sys/socket.h>
#include <netinet/ip_icmp.h> 
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

int ping_sq;

struct ping4_pkt {
    struct icmphdr hdr;
    char msg[64];
};

unsigned short checksum(void *b, int len) 
{    unsigned short *buf = b; 
    unsigned int sum=0; 
    unsigned short result; 
  
    for ( sum = 0; len > 1; len -= 2 ) 
        sum += *buf++; 
    if ( len == 1 ) 
        sum += *(unsigned char*)buf; 
    sum = (sum >> 16) + (sum & 0xFFFF); 
    sum += (sum >> 16); 
    result = ~sum; 
    return result; 
} 

int ping4(int sock_fd, struct sockaddr_in* to) 
{    
    /* SETSOCKOPT with TTL currently buggy with WSL
    int ttl = 64;
    if( !setsockopt(sock_fd,IPPROTO_IP,IP_TTL,&ttl, sizeof(ttl)) ) {
        fprintf(stderr, "Failed to set socket TTL: %d\n",errno);
        return -1;
    }
    */

    //Set timeout
    struct timeval timeout;
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;

    if(setsockopt(sock_fd,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof timeout) < 0) {
        fprintf(stderr, "Failed to set timeout, error: %d\n",errno);
        return -1;
    }

    struct ping4_pkt pkt;
    bzero(&pkt, sizeof pkt);

    pkt.hdr.type = ICMP_ECHO;
    pkt.hdr.un.echo.id = getpid();
    pkt.hdr.un.echo.sequence = ping_sq++;

    pkt.hdr.checksum = checksum(&pkt,sizeof pkt);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    if(!sendto(sock_fd,&pkt,sizeof pkt,0,(struct sockaddr*)to,sizeof(*to))) {
        fprintf(stderr, "Packet sending failure\n");
        return -2;
    }

    struct sockaddr_in r_addr;
    unsigned int addr_len = sizeof r_addr;
    if( recvfrom(sock_fd, &pkt, sizeof pkt, 0, (struct sockaddr*)&r_addr, &addr_len) == -1) {
        if (errno == EWOULDBLOCK) {
            fprintf(stderr, "Timeout\n");
            return -3;
        }
        fprintf(stderr, "Error receving ICMP reply\n");
        return -2;
    }

    clock_gettime(CLOCK_MONOTONIC_RAW,&end);
    int delta_us = (end.tv_nsec-start.tv_nsec)*pow(10,-6);

    if(!(pkt.hdr.type ==69 && pkt.hdr.code==0))  
    { 
        printf("Error..Packet received with ICMP type %d code %d\n",  
                pkt.hdr.type, pkt.hdr.code); 
    }

    return delta_us;
}

/**
 * Sends the right ping depending on the address family, attmepts more than once then averages for a better result.
 */
int ping(int sockfd, struct sockaddr* to)
{
    //Sanity check
    if (to == NULL) {
        return -1;
    }

    int i, combined_times = 0, success = 0;
    for(i = 0; i < 3; i++) {
        int time;
        switch (to->sa_family)
        {
        case PF_INET:
            time = ping4(sockfd, (struct sockaddr_in*)to);
            if (time > 0) {
                combined_times += time;
                success += 1;
            }
            break;
        
        default:
            printf("%d is an unrecognised family\n",to->sa_family);
            return PING_ERROR_UNSUPPORTED_FAMILY;
            break;
        }
    }

    if (success > 1) {
        return combined_times/success;
    }
    return -2;    
}