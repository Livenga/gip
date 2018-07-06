#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

static char _str_dt[32];


int
eprintf(FILE *strm, char *fn, char *param) {
  if(fn == NULL) {
    return fprintf(strm, "%s\n", strerror(errno));
  }

  if(param != NULL) {
    return fprintf(strm, "%s: %s %s\n", fn, param, strerror(errno));
  }

  return fprintf(strm, "%s: %s\n", fn, strerror(errno));
}


char *
get_datetime(void) {
  time_t t;
  struct tm *tm_ptr;


  memset((void *)_str_dt, '\0', sizeof(_str_dt));

  t = time(NULL);
  tm_ptr = localtime(&t);

  sprintf(_str_dt, "%04d-%02d-%02dT%02d:%02d:%02d",
      (1900 + tm_ptr->tm_year), (1 + tm_ptr->tm_mon), tm_ptr->tm_mday,
      tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec
      );

  return (char *)_str_dt;
}
