#include <pthread.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


typedef long long unsigned u64;


typedef struct {
    int n;
    int step;
    int shift;
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

    for (int i = ta->shift; i < ta->n; i += ta->step) {
        u64 t = fact(i);
        u64 num = t * t;
        u64 den = 2 << (i * i - 1);

        ta->res += (double)num / (double)den;
    }

    return EXIT_SUCCESS;
}


int main(int argc, char *argv[]) {
    int n = (argc > 1 ? atoi(argv[1]) : 6);
    int num_threads = (argc == 3 ? atoi(argv[2]) : sysconf(_SC_NPROCESSORS_ONLN) + 1);

    pthread_t *threads = (pthread_t *)calloc(num_threads, sizeof(pthread_t));
    thread_arg *thread_data = (thread_arg *)calloc(num_threads, sizeof(thread_arg));

    for (int i = 0; i < num_threads; ++i) {
        thread_data[i] = (thread_arg) { .n = n, .step = num_threads, .shift = i + 1, .res = 0 };
        pthread_create(&threads[i], NULL, seq_n, (void *)&thread_data[i]);
    }


    double res = 0;
    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
        res += thread_data[i].res;
    }

    printf("%f\n", res);

    return EXIT_SUCCESS;
}