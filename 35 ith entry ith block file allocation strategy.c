#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 10
#define MAX_FILES 5

typedef struct {
    int blockPointers[MAX_BLOCKS];
} IndexBlock;

typedef struct {
    char fileName[20];
    int fileSize;
    IndexBlock* indexBlock;
} File;

File files[MAX_FILES];
int fileCount = 0;

void createFile(char* fileName, int fileSize) {
    if (fileCount < MAX_FILES) {
        File newFile;
        strcpy(newFile.fileName, fileName);
        newFile.fileSize = fileSize;
        newFile.indexBlock = (IndexBlock*) malloc(sizeof(IndexBlock));
        for (int i = 0; i < fileSize; i++) {
            newFile.indexBlock->blockPointers[i] = i + 1; // assign block numbers starting from 1
        }
        files[fileCount] = newFile;
        fileCount++;
        printf("File created: %s, Size: %d blocks\n", fileName, fileSize);
    } else {
        printf("Maximum number of files reached.\n");
    }
}

void displayFileAllocation() {
    for (int i = 0; i < fileCount; i++) {
        printf("File: %s, Size: %d blocks\n", files[i].fileName, files[i].fileSize);
        printf("Block Pointers: ");
        for (int j = 0; j < files[i].fileSize; j++) {
            printf("%d ", files[i].indexBlock->blockPointers[j]);
        }
        printf("\n");
    }
}

int main() {
    createFile("file1", 3);
    createFile("file2", 2);
    createFile("file3", 4);
    displayFileAllocation();
    return 0;
}
