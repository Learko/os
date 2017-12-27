#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "rw_pipe.h"

void *recv(void *pipe_name) {
    FILE *pipe;

    char buf[128];

    while (1) {
        pipe = fopen((char *)pipe_name, "r");

        fgets(buf, 128, pipe);

        printf("\rrecv >> %ssend >> ", buf);
        fflush(stdout);

        fclose(pipe);
    }
}

void *send(void *pipe_name) {
    FILE *pipe;

    char buf[128];

    while (1) {
        printf("send >> ");
        fgets(buf, 128, stdin);

        pipe = fopen((char *)pipe_name, "w");

        fputs(buf, pipe);
        fflush(pipe);

        fclose(pipe);
    }
}

void create_rw_pipe(char *send_pipe, char *recv_pipe) {
    pthread_t rt, wt;

    pthread_create(&rt, NULL, &recv, (void *)recv_pipe);
    pthread_create(&wt, NULL, &send, (void *)send_pipe);

    pthread_join(rt, NULL);
    pthread_join(wt, NULL);
}