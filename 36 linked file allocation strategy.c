#include <stdio.h>
#include <stdlib.h> // For memory allocation

#define MAX_RECORDS 100
#define MAX_BLOCK_SIZE 100 // Adjust for your record size

// Structure to represent a file block
struct Block {
  int data[MAX_BLOCK_SIZE]; // Array to store records
  struct Block *next; // Pointer to the next block
};

// Structure to represent a file
struct File {
  char name[50];
  int num_records;
  struct Block *head; // Pointer to the first block of the file
  struct Block *tail; // Pointer to the last block of the file
};

// Function to create a new block
struct Block *create_block() {
  struct Block *new_block = (struct Block *)malloc(sizeof(struct Block));
  if (new_block == NULL) {
    printf("Memory allocation failed\n");
    return NULL;
  }

  for (int i = 0; i < MAX_BLOCK_SIZE; i++) {
    new_block->data[i] = 0; // Initialize data to 0 (optional)
  }
  new_block->next = NULL;
  return new_block;
}

// Function to simulate writing a record to a file
int write_record(struct File *file, int record_num, int data) {
  if (record_num < 1 || record_num > file->num_records) {
    printf("Invalid record number\n");
    return -1;
  }

  int block_num = (record_num - 1) / MAX_BLOCK_SIZE;
  int record_offset = (record_num - 1) % MAX_BLOCK_SIZE;

  // Traverse to the corresponding block
  struct Block *current = file->head;
  for (int i = 0; i < block_num; i++) {
    if (current == NULL) {
      printf("Error: File not long enough for record %d\n", record_num);
      return -1;
    }
    current = current->next;
  }

  // If record is at the end of the file and needs a new block
  if (current == NULL || record_offset == MAX_BLOCK_SIZE - 1) {
    struct Block *new_block = create_block();
    if (new_block == NULL) {
      return -1;
    }
    if (current == NULL) { // First block
      file->head = file->tail = new_block;
    } else {
      current->next = new_block;
      file->tail = new_block;
    }
    current = new_block;
  }

  current->data[record_offset] = data;
  file->num_records = record_num > file->num_records ? record_num : file->num_records;
  return 0;
}

// Function to simulate reading a record from a file
int read_record(struct File *file, int record_num) {
  if (record_num < 1 || record_num > file->num_records) {
    printf("Invalid record number\n");
    return -1;
  }

  int block_num = (record_num - 1) / MAX_BLOCK_SIZE;
  int record_offset = (record_num - 1) % MAX_BLOCK_SIZE;

  // Traverse to the corresponding block
  struct Block *current = file->head;
  for (int i = 0; i < block_num; i++) {
    if (current == NULL) {
      printf("Error: File not long enough for record %d\n", record_num);
      return -1;
    }
    current = current->next;
  }

  if (current == NULL) {
    printf("Error: File not long enough for record %d\n", record_num);
    return -1;
  }

  return current->data[record_offset];
}

int main() {
  struct File files[MAX_RECORDS];
  int num_files = 0;

  int choice;
  do {
    printf("\nMenu:\n");
    printf("1. Create File\n");
    printf("2. Write Record\n");
    printf("3. Read Record\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        if (num_files == MAX_RECORDS) {
          printf("Maximum number of files reached\n");
        } else {
          printf("Enter file name: ");
          scanf("%s", files[num_files].name);
          files[num_files].num_records = 0;
          files[num_files].head = NULL;
          files[num_files].tail = NULL;
          printf("File '%s' created\n", files[num_files].name);
          num_files++;
        }
        break;
      case 2:
        if (num_files == 0) {
          printf("No files created yet\n");
        } else {
          printf("Enter file name: ");
          char filename[50];
          scanf("%s", filename);

          int file_index = -1;
          for (int i = 0; i < num_files; i++) {
            if (strcmp(files[i].name, filename) == 0) {
              file_index = i;
              break;
            }
          }

          if (file_index == -1) {
            printf("File '%s' not found\n", filename);
          } else {
            int record_num, data;
            printf("Enter record number: ");
            scanf("%d", &record_num);
            printf("Enter data to write: ");
            scanf("%d", &data);

            if (write_record(&files[file_index], record_num, data) == -1) {
              printf("Error writing record\n");
            } else {
              printf("Record written successfully\n");
            }
          }
        }
        break;
      case 3:
        if (num_files == 0) {
          printf("No files created yet\n");
        } else {
          printf("Enter file name: ");
          char filename[50];
          scanf("%s", filename);

          int file_index = -1;
          for (int i = 0; i < num_files; i++) {
            if (strcmp(files[i].name, filename) == 0) {
              file_index = i;
              break;
            }
          }

          if (file_index == -1) {
            printf("File '%s' not found\n", filename);
          } else {
            int record_num;
            printf("Enter record number: ");
            scanf("%d", &record_num);

            int data = read_record(&files[file_index], record_num);
            if (data == -1) {
              printf("Error reading record\n");
            } else {
              printf("Record %d: %d\n", record_num, data);
            }
          }
        }
        break;
      case 4:
        printf("Exiting...\n");
        break;
    }
  } while (choice != 4);

  // Free allocated memory for blocks (optional, replace with a function)
  for (int i = 0; i < num_files; i++) {
    struct Block *current = files[i].head;
    while (current != NULL) {
      struct Block *temp = current;
      current = current->next;
      free(temp);
    }
  }

  return 0;
}

    

