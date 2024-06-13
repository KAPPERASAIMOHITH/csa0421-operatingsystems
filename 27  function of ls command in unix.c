#include <stdio.h>
#include <windows.h>

void list_directory(const char* path, int show_hidden) {
  WIN32_FIND_DATA find_data;
  HANDLE dir_handle = FindFirstFile(path, &find_data);

  if (dir_handle == INVALID_HANDLE_VALUE) {
    perror("FindFirstFile");
    return;
  }

  do {
    // Skip current and parent directories
    if (strcmp(find_data.cFileName, ".") == 0 ||
        strcmp(find_data.cFileName, "..") == 0) {
      continue;
    }

    // Check for hidden files based on show_hidden flag
    if (!show_hidden && (find_data.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)) {
      continue;
    }

    // Print filename with basic formatting
    printf("%s\t", find_data.cFileName);
  } while (FindNextFile(dir_handle, &find_data) != 0);

  FindClose(dir_handle);
  printf("\n");
}

int main(int argc, char* argv[]) {
  int show_hidden = 0; // Default: don't show hidden files

  // Optional argument: -a to show hidden files
  if (argc > 1 && strcmp(argv[1], "-a") == 0) {
    show_hidden = 1;
  }

  // Default path: current directory
  char path[MAX_PATH];
  GetCurrentDirectory(MAX_PATH, path);

  // List directory contents
  list_directory(path, show_hidden);

  return 0;
}

