#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


static char 
_ipaddr[64];


char *
get_ipv4(char *domain, char *service) {
  int status;
  struct addrinfo hints, *res;
  struct sockaddr_in addrin;


  memset((void *)_ipaddr, '\0', sizeof(_ipaddr));
  memset((void *)&addrin, '\0', sizeof(struct sockaddr_in));
  memset((void *)&hints,  '\0', sizeof(struct addrinfo));

  hints.ai_family    = AF_INET;
  hints.ai_socktype  = SOCK_STREAM;
  hints.ai_protocol  = 0;
  hints.ai_addr      = NULL;
  hints.ai_canonname = NULL;
  hints.ai_next      = NULL;

  status = getaddrinfo(domain, service, &hints, &res);
  if(status != 0) {
    fprintf(stderr, "getaddrinfo(3): %s %s\n", domain, gai_strerror(status));
    return NULL;
  }


  struct addrinfo *ai_cur;
  for(ai_cur = res; ai_cur != NULL; ai_cur = ai_cur->ai_next) {
    if(sizeof(struct sockaddr_in) == ai_cur->ai_addrlen) {
      memcpy((void *)&addrin, (const void *)ai_cur->ai_addr, sizeof(struct sockaddr_in));
      strncpy((char *)_ipaddr, (const char *)inet_ntoa(addrin.sin_addr), 63);
    }
  }

  freeaddrinfo(res);

  return (char *)_ipaddr;
}
