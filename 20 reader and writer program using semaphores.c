#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

sem_t rw_mutex;     // Semaphore for reader-writer mutual exclusion
sem_t mutex;        // Semaphore for protecting read_count
int read_count = 0; // Number of readers currently reading

void* reader(void* param) {
    int reader_id = *((int*)param);

    while (1) {
        // Reader tries to enter the critical section
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1) {
            sem_wait(&rw_mutex); // If this is the first reader, lock the resource for readers
        }
        sem_post(&mutex);

        // Reading section
        printf("Reader %d is reading.\n", reader_id);
        sleep(rand() % 3); // Simulate reading time

        // Reader leaves the critical section
        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&rw_mutex); // If this is the last reader, unlock the resource
        }
        sem_post(&mutex);

        sleep(rand() % 3); // Simulate time before next reading
    }
    return NULL;
}

void* writer(void* param) {
    int writer_id = *((int*)param);

    while (1) {
        // Writer tries to enter the critical section
        sem_wait(&rw_mutex);

        // Writing section
        printf("Writer %d is writing.\n", writer_id);
        sleep(rand() % 3); // Simulate writing time

        // Writer leaves the critical section
        sem_post(&rw_mutex);

        sleep(rand() % 3); // Simulate time before next writing
    }
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    // Initialize semaphores
    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);

    return 0;
}

