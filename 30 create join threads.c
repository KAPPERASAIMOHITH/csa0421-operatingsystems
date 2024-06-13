#include <stdio.h>
#include <pthread.h>

void *thread_function(void *arg) {
  int *number = (int *)arg;
  printf("Thread %d: Started with argument %d\n", (int)pthread_self(), *number);
  sleep(1); // Simulate some work
  printf("Thread %d: Exiting\n", (int)pthread_self());
  return NULL;
}

int main() {
  pthread_t thread1, thread2;
  int arg1 = 10, arg2 = 20;

  // (i) Thread creation
  printf("Main thread: Creating thread 1\n");
  if (pthread_create(&thread1, NULL, thread_function, &arg1) != 0) {
    perror("pthread_create");
    return 1;
  }

  printf("Main thread: Creating thread 2\n");
  if (pthread_create(&thread2, NULL, thread_function, &arg2) != 0) {
    perror("pthread_create");
    return 1;
  }

  // (ii) Join (wait for thread completion)
  printf("Main thread: Waiting for thread 1 to finish...\n");
  if (pthread_join(thread1, NULL) != 0) {
    perror("pthread_join");
    return 1;
  }

  printf("Main thread: Waiting for thread 2 to finish...\n");
  if (pthread_join(thread2, NULL) != 0) {
    perror("pthread_join");
    return 1;
  }

 
  printf("Main thread: All threads finished, exiting...\n");
  return 0;
}

