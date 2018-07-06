#ifndef _UTIL_H
#define _UTIL_H

/* src/util.c */
extern int
eprintf(FILE *strm, char *fn, char *param);
extern char *
get_datetime(void);

/* src/log.c */
extern int
write_log(char *domain, char *ipaddr);

#endif
