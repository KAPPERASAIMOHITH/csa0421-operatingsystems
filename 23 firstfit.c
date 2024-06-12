#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

typedef struct {
    int id;
    int size;
    int allocated;
} Block;

void first_fit(Block blocks[], int num_blocks, int request_size) {
    int i;

    // Find the first available block
    for (i = 0; i < num_blocks; i++) {
        if (!blocks[i].allocated && blocks[i].size >= request_size) {
            // Allocate the process to the first available block
            printf("Process of size %d is allocated to block %d.\n", request_size, blocks[i].id);
            blocks[i].allocated = 1;
            return;
        }
    }

    // If no suitable block is found
    printf("No suitable block available for process of size %d.\n", request_size);
}

int main() {
    Block blocks[MAX_BLOCKS];
    int num_blocks, num_requests, i;

    // Input number of memory blocks
    printf("Enter the number of memory blocks: ");
    scanf("%d", &num_blocks);

    // Input details for each memory block
    for (i = 0; i < num_blocks; i++) {
        printf("Enter size of block %d: ", i + 1);
        scanf("%d", &blocks[i].size);
        blocks[i].id = i + 1;
        blocks[i].allocated = 0;
    }

    // Input number of memory allocation requests
    printf("Enter the number of memory allocation requests: ");
    scanf("%d", &num_requests);

    // Input memory allocation requests and allocate using first fit algorithm
    for (i = 0; i < num_requests; i++) {
        int request_size;
        printf("Enter size of allocation request %d: ", i + 1);
        scanf("%d", &request_size);
        first_fit(blocks, num_blocks, request_size);
    }

    return 0;
}

