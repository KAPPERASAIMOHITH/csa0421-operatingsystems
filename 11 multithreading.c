#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


void *print_message1(void *ptr) {
    char *message;
    message = (char *) ptr;
    for(int i = 0; i < 5; i++) {
        printf("%s\n", message);
        sleep(1); 
    }
    return NULL;
}


void *print_message2(void *ptr) {
    char *message;
    message = (char *) ptr;
    for(int i = 0; i < 5; i++) {
        printf("%s\n", message);
        sleep(1); 
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    const char *message1 = "Thread 1 is running";
    const char *message2 = "Thread 2 is running";

    
    if(pthread_create(&thread1, NULL, print_message1, (void*) message1)) {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }

    
    if(pthread_create(&thread2, NULL, print_message2, (void*) message2)) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }

    
    if(pthread_join(thread1, NULL)) {
        fprintf(stderr, "Error joining thread 1\n");
        return 2;
    }

   
    if(pthread_join(thread2, NULL)) {
        fprintf(stderr, "Error joining thread 2\n");
        return 2;
    }

    printf("Threads have finished executing\n");

    return 0;
}

