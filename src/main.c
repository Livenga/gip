#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "util.h"


/* src/network.c */
extern char *
get_ipv4(char *domain, char *service);


int
main(int argc, char *argv[]) {
  const struct option opts[] = {
    {"log", no_argument, 0, 'l'},
    {0, 0, 0, 0},
  };
  
  int i, opt, f_log;
  char *p_addr, *p_domain;


  f_log    = 0;
  while((opt = getopt_long(argc, argv, "l", opts, NULL)) > 0) {
    switch(opt) {
      case 'l':
        f_log = 1;
        break;
    }
  }

  p_domain = NULL;
  for(i = 1; i < argc; ++i) {
    if(argv[i][0] != '-') {
      p_domain = argv[i];
    }
  }
 
  if(p_domain == NULL) {
    fprintf(stderr, "* ドメイン名が指定されていません.\n");
    return EOF;
  }

  p_addr = get_ipv4(p_domain, NULL);


  if(p_addr != NULL) {
    printf("%s", p_addr);

    if(f_log) {
      write_log(p_domain, p_addr);
    }
  } else {
    fprintf(stderr, "* IPv4アドレスの取得に失敗.(%s)\n", p_domain);
    return EOF;
  }

  return 0;
}
