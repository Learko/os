#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char global_str[200] = "";
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void strcat_slow(char *dst, char *src) {
    pthread_mutex_lock(&mutex);
    strcat(dst, src);
    pthread_mutex_unlock(&mutex);

    struct timespec time = {0, 500000000l}; // 500ms
    nanosleep(&time, NULL);
}

void *add_char_to_str(void *c) {
    char cc = (char)c;

    for (int i = 0; i < 10; ++i) {
        strcat_slow(global_str, (char []){ cc, '\0' });
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    int num_threads = (argc == 2 ? atoi(argv[1]) : sysconf(_SC_NPROCESSORS_ONLN) + 1);

    pthread_t *threads = (pthread_t *)calloc(num_threads, sizeof(pthread_t)); 

    for (int i = 0; i < num_threads; ++i) {
        pthread_create(&threads[i], NULL, add_char_to_str, (void *)('a' + i));
    }

    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }


    printf("str: %s\n", global_str);


    return EXIT_SUCCESS;
}