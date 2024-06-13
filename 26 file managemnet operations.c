#include <stdio.h>
#include <io.h>
#include <fcntl.h>

#define BUFFER_SIZE 256

int main() {
  int choice, handle, bytes_read, bytes_written;
  char buffer[BUFFER_SIZE];

  // Get user choice
  printf("File Management Operations:\n");
  printf("1. Create a new file\n");
  printf("2. Read from a file\n");
  printf("3. Write to a file\n");
  printf("4. Exit\n");
  printf("Enter your choice: ");
  scanf("%d", &choice);

  switch (choice) {
    case 1:
      // Create a new file
      printf("Enter filename to create: ");
      scanf("%s", buffer);
      handle = open(buffer, O_RDWR | _O_CREAT);
      if (handle == -1) {
        perror("open");
        return 1;
      }
      printf("File created successfully!\n");
      close(handle);
      break;

    case 2:
      // Read from a file
      printf("Enter filename to read: ");
      scanf("%s", buffer);
      handle = open(buffer, O_RDONLY);
      if (handle == -1) {
        perror("open");
        return 1;
      }

      printf("Contents of the file:\n");
      while ((bytes_read = read(handle, buffer, BUFFER_SIZE)) > 0) {
        write(stdout, buffer, bytes_read);
      }

      if (bytes_read == -1) {
        perror("read");
        return 1;
      }
      printf("\n");
      close(handle);
      break;

    case 3:
      // Write to a file
      printf("Enter filename to write: ");
      scanf("%s", buffer);
      handle = open(buffer, O_WRONLY | O_CREAT);
      if (handle == -1) {
        perror("open");
        return 1;
      }

      printf("Enter data to write: ");
      fgets(buffer, BUFFER_SIZE, stdin);

      bytes_written = write(handle, buffer, strlen(buffer));
      if (bytes_written == -1) {
        perror("write");
        return 1;
      }

      printf("Data written successfully!\n");
      close(handle);
      break;

    case 4:
      printf("Exiting program.\n");
      break;

    default:
      printf("Invalid choice!\n");
  }

  return 0;
}

