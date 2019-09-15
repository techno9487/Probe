#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <sys/socket.h>
/**
 * Init the network connection bettween the probe and the base daemon
 * @param host host of the server can be IPv4/IPv6/Domain
 * @param port the port the base server is hosted on
 */
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

/**
 * Shuts down the connection to the base server
 */
void network_close();

#endif