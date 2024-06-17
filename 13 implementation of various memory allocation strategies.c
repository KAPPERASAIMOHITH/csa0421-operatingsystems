#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 1000 
#define BLOCK_COUNT 10    
typedef struct {
    int size;
    int is_free;
} Block;

Block memory[BLOCK_COUNT];
void initialize_memory() {
    for (int i = 0; i < BLOCK_COUNT; i++) {
        memory[i].size = (rand() % 100) + 10; 
        memory[i].is_free = 1; 
    }
}
void first_fit(int request_size) {
    for (int i = 0; i < BLOCK_COUNT; i++) {
        if (memory[i].is_free && memory[i].size >= request_size) {
            memory[i].is_free = 0;
            printf("Allocated %d bytes in block %d (First Fit)\n", request_size, i);
            return;
        }
    }
    printf("Failed to allocate %d bytes (First Fit)\n", request_size);
}


void best_fit(int request_size) {
    int best_index = -1;
    for (int i = 0; i < BLOCK_COUNT; i++) {
        if (memory[i].is_free && memory[i].size >= request_size) {
            if (best_index == -1 || memory[i].size < memory[best_index].size) {
                best_index = i;
            }
        }
    }
    if (best_index != -1) {
        memory[best_index].is_free = 0;
        printf("Allocated %d bytes in block %d (Best Fit)\n", request_size, best_index);
    } else {
        printf("Failed to allocate %d bytes (Best Fit)\n", request_size);
    }
}


void worst_fit(int request_size) {
    int worst_index = -1;
    for (int i = 0; i < BLOCK_COUNT; i++) {
        if (memory[i].is_free && memory[i].size >= request_size) {
            if (worst_index == -1 || memory[i].size > memory[worst_index].size) {
                worst_index = i;
            }
        }
    }
    if (worst_index != -1) {
        memory[worst_index].is_free = 0;
        printf("Allocated %d bytes in block %d (Worst Fit)\n", request_size, worst_index);
    } else {
        printf("Failed to allocate %d bytes (Worst Fit)\n", request_size);
    }
}


void print_memory_status() {
    printf("Memory Status:\n");
    for (int i = 0; i < BLOCK_COUNT; i++) {
        printf("Block %d: Size = %d, %s\n", i, memory[i].size, memory[i].is_free ? "Free" : "Allocated");
    }
}

int main() {
    initialize_memory();
    print_memory_status();

    int request_size;

    printf("\nRequesting memory (First Fit):\n");
    request_size = 50;
    first_fit(request_size);
    print_memory_status();

    printf("\nRequesting memory (Best Fit):\n");
    request_size = 30;
    best_fit(request_size);
    print_memory_status();

    printf("\nRequesting memory (Worst Fit):\n");
    request_size = 70;
    worst_fit(request_size);
    print_memory_status();

    return 0;
}

