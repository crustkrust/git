#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define BUFFER_SIZE 5


int buffer[BUFFER_SIZE];
int count = 0;
pthread_mutex_t mutex;
pthread_cond_t not_full, not_empty;


void* producer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        item = rand() % 100;
        pthread_mutex_lock(&mutex);
        while (count == BUFFER_SIZE)
            pthread_cond_wait(&not_full, &mutex);
        buffer[count++] = item;
        printf("Producer produced: %d\n", item);
        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mutex);
        //sleep(1);
    }
    return NULL;
}


void* consumer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        while (count == 0)
            pthread_cond_wait(&not_empty, &mutex);
        item = buffer[--count];
        printf("Consumer consumed: %d\n", item);
        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex);
        //sleep(1);
    }
    return NULL;
}


int main() {
    pthread_t prod_thread, cons_thread;


    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty, NULL);


    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);


    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);


    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);


    return 0;
}

