#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 50


typedef struct {
    char name[MAX_FILENAME_LENGTH];
} File;


void initializeFiles(File files[]);
void createFile(File files[], int *numFiles);
void deleteFile(File files[], int *numFiles);
void listFiles(File files[], int numFiles);

int main() {
    File files[MAX_FILES];
    int numFiles = 0;
    char choice;
    initializeFiles(files);

    do {
        printf("\n1. Create a file\n");
        printf("2. Delete a file\n");
        printf("3. List files\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                createFile(files, &numFiles);
                break;
            case '2':
                deleteFile(files, &numFiles);
                break;
            case '3':
                listFiles(files, numFiles);
                break;
            case '4':
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != '4');

    return 0;
}
void initializeFiles(File files[]) {
    for (int i = 0; i < MAX_FILES; i++) {
        strcpy(files[i].name, "");
    }
}
void createFile(File files[], int *numFiles) {
    char filename[MAX_FILENAME_LENGTH];
    printf("Enter filename: ");
    scanf("%s", filename);
    for (int i = 0; i < *numFiles; i++) {
        if (strcmp(files[i].name, filename) == 0) {
            printf("File '%s' already exists.\n", filename);
            return;
        }
    }
    if (*numFiles >= MAX_FILES) {
        printf("Maximum number of files reached. Cannot create more files.\n");
        return;
    }

    strcpy(files[*numFiles].name, filename);
    (*numFiles)++;
    printf("File '%s' created successfully.\n", filename);
}
void deleteFile(File files[], int *numFiles) {
    char filename[MAX_FILENAME_LENGTH];
    printf("Enter filename to delete: ");
    scanf("%s", filename);

    int found = 0;
    for (int i = 0; i < *numFiles; i++) {
        if (strcmp(files[i].name, filename) == 0) {
            for (int j = i; j < *numFiles - 1; j++) {
                strcpy(files[j].name, files[j + 1].name);
            }
            strcpy(files[*numFiles - 1].name, "");
            (*numFiles)--;
            printf("File '%s' deleted successfully.\n", filename);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("File '%s' not found.\n", filename);
    }
}
void listFiles(File files[], int numFiles) {
    if (numFiles == 0) {
        printf("No files found.\n");
    } else {
        printf("Files in directory:\n");
        for (int i = 0; i < numFiles; i++) {
            printf("%s\n", files[i].name);
        }
    }
}

