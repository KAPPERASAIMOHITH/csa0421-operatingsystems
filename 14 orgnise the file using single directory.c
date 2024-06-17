#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 50

// Structure to represent a file
typedef struct {
    char name[MAX_FILENAME_LENGTH];
} File;

// Function prototypes
void initializeFiles(File files[]);
void createFile(File files[], int *numFiles);
void deleteFile(File files[], int *numFiles);
void listFiles(File files[], int numFiles);

int main() {
    File files[MAX_FILES];
    int numFiles = 0;
    char choice;

    // Initialize files array
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

// Initialize files array
void initializeFiles(File files[]) {
    for (int i = 0; i < MAX_FILES; i++) {
        strcpy(files[i].name, "");
    }
}

// Create a file
void createFile(File files[], int *numFiles) {
    char filename[MAX_FILENAME_LENGTH];
    printf("Enter filename: ");
    scanf("%s", filename);

    // Check if filename already exists
    for (int i = 0; i < *numFiles; i++) {
        if (strcmp(files[i].name, filename) == 0) {
            printf("File '%s' already exists.\n", filename);
            return;
        }
    }

    // Check if maximum number of files reached
    if (*numFiles >= MAX_FILES) {
        printf("Maximum number of files reached. Cannot create more files.\n");
        return;
    }

    strcpy(files[*numFiles].name, filename);
    (*numFiles)++;
    printf("File '%s' created successfully.\n", filename);
}

// Delete a file
void deleteFile(File files[], int *numFiles) {
    char filename[MAX_FILENAME_LENGTH];
    printf("Enter filename to delete: ");
    scanf("%s", filename);

    int found = 0;
    for (int i = 0; i < *numFiles; i++) {
        if (strcmp(files[i].name, filename) == 0) {
            // Shift remaining files to fill the gap
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

// List files
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

