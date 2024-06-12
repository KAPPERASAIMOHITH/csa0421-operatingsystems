#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10
#define NUM_INCREMENTS 1000

int counter = 0;  // Shared counter
pthread_mutex_t mutex;  // Mutex lock

void* increment_counter(void* param) {
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        // Lock the mutex before accessing the counter
        pthread_mutex_lock(&mutex);
        counter++;  // Critical section
        // Unlock the mutex after accessing the counter
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    
    // Initialize the mutex
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        printf("Mutex initialization failed\n");
        return 1;
    }

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, increment_counter, NULL) != 0) {
            printf("Error creating thread %d\n", i);
            return 1;
        }
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    // Print the final counter value
    printf("Final counter value: %d\n", counter);

    return 0;
}

