#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;

// Semaphores for controlling access to shared resource and conditions
sem_t mutex;          // To protect the critical section (mutual exclusion)
sem_t not_full;       // Semaphore to track if the buffer is not full
sem_t not_empty;      // Semaphore to track if the buffer is not empty

void* producer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        item = rand() % 100;
        
        sem_wait(&not_full);      // Wait until buffer is not full
        sem_wait(&mutex);         // Lock the mutex to access the buffer

        buffer[count++] = item;
        printf("Producer produced: %d\n", item);

        sem_post(&mutex);         // Unlock the mutex
        sem_post(&not_empty);     // Signal that buffer is not empty

       
    }
    return NULL;
}

void* consumer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        sem_wait(&not_empty);     // Wait until buffer is not empty
        sem_wait(&mutex);         // Lock the mutex to access the buffer

        item = buffer[--count];
        printf("Consumer consumed: %d\n", item);

        sem_post(&mutex);         // Unlock the mutex
        sem_post(&not_full);      // Signal that buffer is not full


    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize semaphores
    sem_init(&mutex, 0, 1);       // Binary semaphore (1) for mutual exclusion
    sem_init(&not_full, 0, BUFFER_SIZE); // Semaphore for buffer size control (initially full)
    sem_init(&not_empty, 0, 0);   // Semaphore for empty buffer control (initially empty)

    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&not_full);
    sem_destroy(&not_empty);

    return 0;
}