#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIRECTORIES 100
#define MAX_FILES_PER_DIRECTORY 100
#define MAX_FILENAME_LENGTH 50
#define MAX_PATH_LENGTH 100

typedef struct {
    char name[MAX_FILENAME_LENGTH];
} File;

typedef struct {
    char name[MAX_FILENAME_LENGTH];
    File files[MAX_FILES_PER_DIRECTORY];
    int numFiles;
} Directory;

void initializeDirectory(Directory *directory, const char *name) {
    strcpy(directory->name, name);
    directory->numFiles = 0;
}

int findDirectory(Directory directories[], int numDirectories, const char *directoryName) {
    for (int i = 0; i < numDirectories; i++) {
        if (strcmp(directories[i].name, directoryName) == 0)
            return i;
    }
    return -1; // Directory not found
}

void createFile(Directory *directory) {
    if (directory->numFiles >= MAX_FILES_PER_DIRECTORY) {
        printf("Max files reached.\n");
        return;
    }
    printf("Enter filename: ");
    scanf("%s", directory->files[directory->numFiles++].name);
    printf("File created.\n");
}

void deleteFile(Directory *directory) {
    char filename[MAX_FILENAME_LENGTH];
    printf("Enter filename: ");
    scanf("%s", filename);
    for (int i = 0; i < directory->numFiles; i++) {
        if (strcmp(directory->files[i].name, filename) == 0) {
            for (int j = i; j < directory->numFiles - 1; j++)
                strcpy(directory->files[j].name, directory->files[j + 1].name);
            directory->numFiles--;
            printf("File deleted.\n");
            return;
        }
    }
    printf("File not found.\n");
}

void listFiles(Directory *directory) {
    for (int i = 0; i < directory->numFiles; i++)
        printf("%s\n", directory->files[i].name);
}

void createDirectory(Directory directories[], int *numDirectories) {
    if (*numDirectories >= MAX_DIRECTORIES) {
        printf("Max directories reached.\n");
        return;
    }
    printf("Enter directory name: ");
    scanf("%s", directories[*numDirectories].name);
    initializeDirectory(&directories[*numDirectories], directories[*numDirectories].name);
    (*numDirectories)++;
    printf("Directory created.\n");
}

void changeDirectory(Directory directories[], int numDirectories, char *currentDirectory) {
    char newDir[MAX_FILENAME_LENGTH];
    printf("Enter directory name: ");
    scanf("%s", newDir);
    if (findDirectory(directories, numDirectories, newDir) != -1) {
        strcpy(currentDirectory, newDir);
        printf("Changed to directory %s\n", currentDirectory);
    } else {
        printf("Directory not found.\n");
    }
}

int main() {
    Directory directories[MAX_DIRECTORIES];
    int numDirectories = 1;
    char currentDirectory[MAX_PATH_LENGTH] = "root";
    initializeDirectory(&directories[0], "root");

    char choice;
    do {
        printf("\nCurrent Directory: %s\n", currentDirectory);
        printf("1. Create a file\n2. Delete a file\n3. List files\n4. Create a directory\n5. Change directory\n6. Exit\nEnter your choice: ");
        scanf(" %c", &choice);

        int index = findDirectory(directories, numDirectories, currentDirectory);

        switch (choice) {
            case '1': createFile(&directories[index]); break;
            case '2': deleteFile(&directories[index]); break;
            case '3': listFiles(&directories[index]); break;
            case '4': createDirectory(directories, &numDirectories); break;
            case '5': changeDirectory(directories, numDirectories, currentDirectory); break;
            case '6': break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != '6');

    return 0;
}

