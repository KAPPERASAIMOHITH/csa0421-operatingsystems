#include <stdio.h>

#define PAGE_FRAME_SIZE 3
#define PAGE_REFERENCE_SIZE 10

void fifo(int pageReference[], int pageFrameSize) {
    int pageFrames[PAGE_FRAME_SIZE];
    int pageFaults = 0;
    int front = 0;

    for (int i = 0; i < PAGE_REFERENCE_SIZE; i++) {
        int flag = 0;
        for (int j = 0; j < pageFrameSize; j++) {
            if (pageReference[i] == pageFrames[j]) {
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            pageFaults++;
            pageFrames[front] = pageReference[i];
            front = (front + 1) % pageFrameSize;
        }
    }

    printf("Page Faults: %d\n", pageFaults);
}

int main() {
    int pageReference[PAGE_REFERENCE_SIZE] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3};
    int pageFrameSize = PAGE_FRAME_SIZE;

    printf("Page Reference String: ");
    for (int i = 0; i < PAGE_REFERENCE_SIZE; i++) {
        printf("%d ", pageReference[i]);
    }
    printf("\n");

    printf("Page Frame Size: %d\n", pageFrameSize);

    fifo(pageReference, pageFrameSize);

    return 0;
}
