#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char global_str[256] = "";


typedef enum { out_cr, want_cr, claim_cr } pstate;
static pstate *flags;
static int turn = 0;
int num_threads;

typedef struct {
    int tid;
    char chr;
} thread_arg;


// Eisenberg & McGuire algorithm
void acquire(int i) {
    // printf("try acquire: %i\n", i);

    int index;
    do {
        flags[i] = want_cr;

        index = turn;
        while (index != i) {
            if (flags[index] != out_cr) {
                index = turn;
            }
            else {
                index = (index + 1) % num_threads;
            }
        }

        flags[i] = claim_cr;

        index = 0;
        while (index < num_threads && (index == i || flags[index] != claim_cr)) {
            ++index;
        }

    } while (!(index >= num_threads && (turn == i || flags[turn] == out_cr)));

    turn = i;

    // printf("acquireed: %i\n", i);
}

void release(int i) {
    // printf("try release: %i\n", i);

    int index = (turn + 1) % num_threads;
    while (flags[index] == out_cr) {
        index = (index + 1) % num_threads;
    }

    turn = index;
    flags[i] = out_cr;

    // printf("released: %i\n", i);
}


void strcat_slow(char *dst, char *src, int tid) {
    acquire(tid);
    strcat(dst, src);
    release(tid);

    struct timespec time = {0, 100000000l}; // 0s 100ms
    nanosleep(&time, NULL);
}

void *add_char_to_str(void *arg) {
    thread_arg *t_arg = (thread_arg *)arg;

    char c = t_arg->chr;
    char tid = t_arg->tid;

    for (int i = 0; i < 10; ++i) {
        strcat_slow(global_str, (char []){c, '\0'}, tid);
    }

    return NULL;
}



int main(int argc, char *argv[]) {
    num_threads = (argc == 2 ? atoi(argv[1]) : sysconf(_SC_NPROCESSORS_ONLN) + 1);

    pthread_t *threads = (pthread_t *)calloc(num_threads, sizeof(pthread_t));
    thread_arg *t_args = (thread_arg *)calloc(num_threads, sizeof(thread_arg));

    flags = (pstate *)calloc(num_threads, sizeof(pstate));

    for (int i = 0; i < num_threads; ++i) {
        t_args[i].tid = i;
        t_args[i].chr = 'a' + i;

        pthread_create(&threads[i], NULL, add_char_to_str, (void *)(&t_args[i]));
    }

    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }


    printf("str: %s\n", global_str);


    return EXIT_SUCCESS;
}