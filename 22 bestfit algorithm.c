#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

typedef struct {
    int id;
    int size;
    int allocated;
} Block;

void best_fit(Block blocks[], int num_blocks, int request_size) {
    int i, best_block_index = -1;

    // Find the best available block
    for (i = 0; i < num_blocks; i++) {
        if (!blocks[i].allocated && blocks[i].size >= request_size) {
            if (best_block_index == -1 || blocks[i].size < blocks[best_block_index].size) {
                best_block_index = i;
            }
        }
    }

    // Allocate the process to the best available block
    if (best_block_index != -1) {
        printf("Process of size %d is allocated to block %d.\n", request_size, blocks[best_block_index].id);
        blocks[best_block_index].allocated = 1;
    } else {
        printf("No suitable block available for process of size %d.\n", request_size);
    }
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

    // Input memory allocation requests and allocate using best fit algorithm
    for (i = 0; i < num_requests; i++) {
        int request_size;
        printf("Enter size of allocation request %d: ", i + 1);
        scanf("%d", &request_size);
        best_fit(blocks, num_blocks, request_size);
    }

    return 0;
}

