#ifndef _RW_PIPE
#define _RW_PIPE

#define SWCR "swcr"
#define SRCW "srcw"

void *recv(void *);
void *send(void *);
void create_rw_pipe();

#endif