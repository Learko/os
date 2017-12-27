#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10


pthread_t threads[N]; 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void *thread_id(void *id) {
    sleep(rand() % 5);
    pthread_mutex_lock(&mutex);

    printf("Hello from thread: %d\n", (int)id);

    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}


int main() {
    for (int i = 0; i < N; ++i) {
        // passing `i` causes warnings assotiated with `pointer to int` casts,
        // but size of `int` - 4bytes < size of `void *` - 4/8bytes,
        // so there is no error
        int err = pthread_create(&(threads[i]), NULL, thread_id, (void *)i);

        if (err) {
            fprintf(stderr, "Something went wrong. %d\n", err);
        }
    }

    for (int i = 0; i < N; ++i) {
        pthread_join(threads[i], NULL);
    }


    return EXIT_SUCCESS;
}
