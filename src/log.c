#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "util.h"

#define GIP_LOG ".gip_history"

int
write_log(char *domain, char *ipaddr) {
  int ret_code;
  char *home, *log_path;
  size_t path_length;
  FILE *fp;

  if(domain == NULL || ipaddr == NULL) {
    return EOF;
  }

  home = getenv("HOME");
  if(home == NULL) {
    return EOF;
  }

  path_length = strlen(home) + strlen(GIP_LOG) + 2;
  log_path    = (char *)calloc(path_length, sizeof(char));
  sprintf(log_path, "%s/%s", home, GIP_LOG);

  if((fp = fopen(log_path, "a")) != NULL) {
    fprintf(fp, "[%s] %s : %s\n", get_datetime(), ipaddr, domain);

    fclose(fp);
    ret_code = 0;
  } else {
    eprintf(stderr, "fopen(3)", log_path);
    ret_code = -2;
  }

  memset((void *)log_path, '\0', sizeof(char) * path_length);
  free((void *)log_path);
  log_path = NULL;

  return ret_code;
}
