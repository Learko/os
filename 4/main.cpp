#include <iostream>
#include <cstdint>
#include <pthread.h>

#include "queue.hpp"

auto q = queue<char>(5);


void *read(void *) {
    for (int i = 0; i < 5; ++i) {
        q.pop_front();
    }

    return 0;
}

void *write(void *c) {
    char cc = reinterpret_cast<char>(c);

    for (int i = 0; i < 5; ++i) {
        q.push_back(cc);
    }

    return 0;
}


int main() {
    const int n = 10;

    pthread_t *r = new pthread_t[n]();
    pthread_t *w = new pthread_t[n]();

    for (char i = 0; i < n; ++i) {
        pthread_create(&r[i], NULL, &read, NULL);
        pthread_create(&w[i], NULL, &write, (void *)('a' + i));
    }

    for (int i = 0; i < n; ++i) {
        pthread_join(r[i], NULL);
        pthread_join(w[i], NULL);
    }

    return 0;
}