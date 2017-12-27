#include <pthread.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


typedef long long unsigned u64;


typedef struct {
    int n;
    double res;
} thread_arg;


u64 fact(int n) {
    u64 res = n;

    for (int i = 2; i < n; ++i) {
        res *= i;
    }

    return res;
}

void *seq_n(void *arg) {
    thread_arg *ta = (thread_arg *)arg;

    u64 t = fact(ta->n);
    u64 num = t * t;
    u64 den = 2 << (ta->n * ta->n - 1);

    ta->res += (double)num / (double)den;

    return EXIT_SUCCESS;
}


int main(int argc, char *argv[]) {
    int n = (argc > 1 ? atoi(argv[1]) : 6);
    int num_threads = (argc == 3 ? atoi(argv[2]) : sysconf(_SC_NPROCESSORS_ONLN) + 1);

    pthread_t *threads = (pthread_t *)calloc(num_threads, sizeof(pthread_t)); 
    thread_arg *thread_data = (thread_arg *)calloc(num_threads, sizeof(thread_arg));

    for (int i = 1; i < n; ++i) {
        const int tid = (i - 1) % num_threads;

        if (threads[tid] != 0 && pthread_kill(threads[tid], 0) != ESRCH) {
            pthread_join(threads[tid], NULL);
        }

        thread_data[tid].n = i;

        pthread_create(&threads[tid], NULL, seq_n, (void *)&thread_data[tid]);

    }

    double res = 0;
    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i % num_threads], NULL);
        res += thread_data[i].res;
    }

    printf("%f\n", res);

    return EXIT_SUCCESS;
}