#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <sys/socket.h>

int network_init(char* host, int port);
/**
 * Converts a string into of IPv4/IPv6/Domain to a sockaddr structure
 * 
 * @param host The string to convert into a sockaddr structure
 * @param addr Pointer to a struct sockaddr structure
 * 
 * @returns 0 on sucess error codes on failure
 */
int char_to_addr(char* host, struct sockaddr* addr);

#endif