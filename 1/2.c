#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10


typedef struct {
    int value;
    int result;
} thread_data;

typedef struct {
    pthread_t thread;
    thread_data data;
} future;

future futures[N];


void *sqr(void *data)
{
    thread_data *td = (thread_data *)data;
    td->result = td->value * td->value;

    return EXIT_SUCCESS;
}


int main()
{
    for (int i = 0; i < N; ++i) {
        futures[i].data.value = i;
        int err = pthread_create(&(futures[i].thread), NULL, sqr, (void *)&futures[i].data);

        if (err) {
            fprintf(stderr, "We are fucked. %d\n", err);
        }
    }

    for (int i = 0; i < N; ++i) {
        pthread_join(futures[i].thread, NULL);
        printf("Square of %d is %d\n", futures[i].data.value, futures[i].data.result);
    }


    return EXIT_SUCCESS;
}