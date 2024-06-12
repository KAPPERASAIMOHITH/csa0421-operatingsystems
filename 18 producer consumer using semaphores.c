#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void *producer(void *param) {
    int item;

    while (1) {
        item = rand() % 100; // Produce an item
        sem_wait(&empty); // Wait if buffer is full
        pthread_mutex_lock(&mutex); // Acquire mutex lock

        // Add item to the buffer
        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Release mutex lock
        sem_post(&full); // Increment the count of full slots

        sleep(1); // Simulate time taken to produce an item
    }
}

void *consumer(void *param) {
    int item;

    while (1) {
        sem_wait(&full); // Wait if buffer is empty
        pthread_mutex_lock(&mutex); // Acquire mutex lock

        // Remove item from buffer
        item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Release mutex lock
        sem_post(&empty); // Increment the count of empty slots

        sleep(1); // Simulate time taken to consume an item
    }
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // Initially, buffer is empty
    sem_init(&full, 0, 0); // Initially, no item is present
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

