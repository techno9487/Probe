#ifndef _DNS_H_
#define _DNS_H_

int dns_query(char* domain,int family,struct addrinfo* result);

#endif