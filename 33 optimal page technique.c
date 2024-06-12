#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_REFERENCES 30

void printFrames(int frames[], int frameCount) {
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == -1)
            printf(" - ");
        else
            printf(" %d ", frames[i]);
    }
    printf("\n");
}

int predict(int refStr[], int refLen, int frames[], int frameCount, int currentIndex) {
    int result = -1, farthest = currentIndex;
    for (int i = 0; i < frameCount; i++) {
        int j;
        for (j = currentIndex; j < refLen; j++) {
            if (frames[i] == refStr[j]) {
                if (j > farthest) {
                    farthest = j;
                    result = i;
                }
                break;
            }
        }
        if (j == refLen) {
            return i;
        }
    }
    return (result == -1) ? 0 : result;
}

int isInFrames(int frames[], int frameCount, int page) {
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == page)
            return 1;
    }
    return 0;
}

void optimalPageReplacement(int refStr[], int refLen, int frameCount) {
    int frames[MAX_FRAMES];
    int pageFaults = 0;
    for (int i = 0; i < frameCount; i++)
        frames[i] = -1;

    for (int i = 0; i < refLen; i++) {
        printf("Processing page: %d\n", refStr[i]);
        if (!isInFrames(frames, frameCount, refStr[i])) {
            pageFaults++;
            if (i < frameCount) {
                frames[i] = refStr[i];
            } else {
                int j = predict(refStr, refLen, frames, frameCount, i + 1);
                frames[j] = refStr[i];
            }
            printf("Page fault! Frames: ");
            printFrames(frames, frameCount);
        } else {
            printf("Page hit! Frames: ");
            printFrames(frames, frameCount);
        }
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
}

int main() {
    int refStr[MAX_REFERENCES];
    int refLen, frameCount;

    printf("Enter number of frames: ");
    scanf("%d", &frameCount);

    printf("Enter the length of the page reference string: ");
    scanf("%d", &refLen);

    printf("Enter the page reference string:\n");
    for (int i = 0; i < refLen; i++) {
        scanf("%d", &refStr[i]);
    }

    optimalPageReplacement(refStr, refLen, frameCount);

    return 0;
}

