#include <stdio.h>
#include <windows.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    HANDLE hFile;
    DWORD dwBytesWritten, dwBytesRead;
    char buffer[BUFFER_SIZE];
    char *filename = "example.txt";
    char *data_to_write = "Hello, this is a test string for file management in Windows.\n";

    // Creating and opening a file
    hFile = CreateFile(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Error opening file for writing. Error code: %d\n", GetLastError());
        return 1;
    }
    printf("File %s opened for writing.\n", filename);

    // Writing to the file
    if (!WriteFile(hFile, data_to_write, strlen(data_to_write), &dwBytesWritten, NULL)) {
        printf("Error writing to file. Error code: %d\n", GetLastError());
        CloseHandle(hFile);
        return 1;
    }
    printf("Written %lu bytes to file %s.\n", dwBytesWritten, filename);

    // Closing the file after writing
    if (!CloseHandle(hFile)) {
        printf("Error closing file after writing. Error code: %d\n", GetLastError());
        return 1;
    }
    printf("File %s closed after writing.\n", filename);

    // Opening the file for reading
    hFile = CreateFile(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Error opening file for reading. Error code: %d\n", GetLastError());
        return 1;
    }
    printf("File %s opened for reading.\n", filename);

    // Reading from the file
    if (!ReadFile(hFile, buffer, BUFFER_SIZE - 1, &dwBytesRead, NULL)) {
        printf("Error reading from file. Error code: %d\n", GetLastError());
        CloseHandle(hFile);
        return 1;
    }
    buffer[dwBytesRead] = '\0'; // Null-terminate the string
    printf("Read %lu bytes from file %s: \n%s", dwBytesRead, filename, buffer);

    // Closing the file after reading
    if (!CloseHandle(hFile)) {
        printf("Error closing file after reading. Error code: %d\n", GetLastError());
        return 1;
    }
    printf("File %s closed after reading.\n", filename);

    return 0;
}

