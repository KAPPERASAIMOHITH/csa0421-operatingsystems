#include <stdio.h>

#define MAX_RECORDS 100

// Structure to represent a file
struct File {
  char name[50];
  int num_records;
  int starting_block;
};

// Function to simulate reading a record
void read_record(struct File *file, int record_num) {
  if (record_num < 1 || record_num > file->num_records) {
    printf("Invalid record number\n");
    return;
  }

  // Simulate reading all previous records (for simplicity, just print a message)
  for (int i = 1; i < record_num; i++) {
    printf("Reading record %d...\n", i);
  }

  printf("Reading record %d from block %d\n", record_num, file->starting_block + record_num - 1);
}

int main() {
  struct File files[MAX_RECORDS];
  int num_files = 0;

  int choice;
  do {
    printf("\nMenu:\n");
    printf("1. Create File\n");
    printf("2. Read Record\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        if (num_files == MAX_RECORDS) {
          printf("Maximum number of files reached\n");
        } else {
          printf("Enter file name: ");
          scanf("%s", files[num_files].name);
          printf("Enter number of records: ");
          scanf("%d", &files[num_files].num_records);

          // Allocate a starting block (simulate disk allocation)
          files[num_files].starting_block = 100 + num_files; // Adjust block allocation logic if needed

          printf("File '%s' created with %d records\n", files[num_files].name, files[num_files].num_records);
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

          int found = 0;
          for (int i = 0; i < num_files; i++) {
            if (strcmp(files[i].name, filename) == 0) {
              int record_num;
              printf("Enter record number: ");
              scanf("%d", &record_num);
              read_record(&files[i], record_num);
              found = 1;
              break;
            }
          }

          if (!found) {
            printf("File '%s' not found\n", filename);
          }
        }
        break;
      case 3:
        printf("Exiting...\n");
        break;
      default:
        printf("Invalid choice\n");
    }
  } while (choice != 3);

  return 0;
}

