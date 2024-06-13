#include <stdio.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>  // Included for O_RDONLY flag

int search_file(const char* filename, const char* pattern) {
  int handle, bytes_read;
  char buffer[256];

  handle = open(filename, O_RDONLY);  // Use O_RDONLY for read-only access
  if (handle == -1) {
    perror("open");
    return 1;
  }

  while ((bytes_read = read(handle, buffer, sizeof(buffer) - 1)) > 0) {
    buffer[bytes_read] = '\0'; // Ensure null termination

    // Search for the pattern within the read buffer
    if (strstr(buffer, pattern) != NULL) {
      printf("%s: %s\n", filename, buffer);
      close(handle);
      return 0; // Found a match, exit
    }
  }

  if (bytes_read == -1) {
    perror("read");
    return 1;
  }

  close(handle);
  return 1; // No match found
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    printf("Usage: %s <pattern> <filename>\n", argv[0]);
    return 1;
  }

  const char* pattern = argv[1];
  const char* filename = argv[2];

  // Search the file for the pattern
  if (search_file(filename, pattern) == 0) {
    printf("Pattern '%s' found in '%s'\n", pattern, filename);
  } else {
    printf("Pattern '%s' not found in '%s'\n", pattern, filename);
  }

  return 0;
}

