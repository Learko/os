#pragma once

#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


void rand_sleep() {
    std::uint64_t delay = random() % 100000000l;

    struct timespec time = { 0, delay }; // 0s 100ms
    nanosleep(&time, NULL);
}


template <class T> 
class queue {
public:
    queue(size_t _capacity) {
        data = new T[capacity];
        capacity = _capacity;
        length = 0;
        index = 0;

        pthread_mutex_init(&mutex, NULL);
        
        pthread_cond_init(&cond_r, NULL);
        pthread_cond_init(&cond_w, NULL);
    }

    size_t len() const noexcept { return length; }

    void push_back(T value) noexcept {
        rand_sleep();

        pthread_mutex_lock(&mutex);

        while (length == capacity) {
            pthread_cond_wait(&cond_w, &mutex);
        }

        rand_sleep();

        std::cout << "Push: " << value << std::endl;
        data[(index++) % capacity] = value;
        ++length;

        pthread_cond_signal(&cond_r);
        pthread_mutex_unlock(&mutex);
    }

    T pop_front() noexcept {
        rand_sleep();

        pthread_mutex_lock(&mutex);

        while (length == 0) {
            pthread_cond_wait(&cond_r, &mutex);
        }

        rand_sleep();

        T value = data[(index - (length--)) % capacity];
        std::cout << "Pop:  " << value << std::endl;

        pthread_cond_signal(&cond_w);
        pthread_mutex_unlock(&mutex);

        return value;
    }

private:
    T *data;
    size_t capacity;
    size_t length;
    size_t index;

    pthread_mutex_t mutex;
    pthread_cond_t cond_r;
    pthread_cond_t cond_w;
};