#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
pthread_mutex_t forks[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];
void think(int philosopher_number) {
    printf("Philosopher %d is thinking.\n", philosopher_number);
    sleep(rand() % 3 + 1); 
}
void eat(int philosopher_number) {
    printf("Philosopher %d is eating.\n", philosopher_number);
    sleep(rand() % 3 + 1);
}
void* philosopher(void* num) {
    int philosopher_number = *(int*)num;
    while(1) {
        think(philosopher_number);
        pthread_mutex_lock(&forks[philosopher_number]);
        printf("Philosopher %d picked up left fork.\n", philosopher_number);
        pthread_mutex_lock(&forks[(philosopher_number + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d picked up right fork.\n", philosopher_number);
        eat(philosopher_number);
        pthread_mutex_unlock(&forks[(philosopher_number + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d put down right fork.\n", philosopher_number);
        pthread_mutex_unlock(&forks[philosopher_number]);
        printf("Philosopher %d put down left fork.\n", philosopher_number);
    }
}
int main() {
    int i;
    int philosopher_numbers[NUM_PHILOSOPHERS];
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_numbers[i] = i;
        if (pthread_create(&philosophers[i], NULL, philosopher, &philosopher_numbers[i])) {
            fprintf(stderr, "Error creating thread for philosopher %d\n", i);
            return 1;
        }
    }
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        if (pthread_join(philosophers[i], NULL)) {
            fprintf(stderr, "Error joining thread for philosopher %d\n", i);
            return 2;
        }
    }
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}

