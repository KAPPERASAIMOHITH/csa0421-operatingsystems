#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hPipe;
    char buffer[100];
    DWORD dwBytesRead;

    // Wait for a moment to allow the named pipe to be created
    Sleep(2000); // 2-second delay

    // Connect to the named pipe
    hPipe = CreateFile(
        "\\\\.\\pipe\\MyNamedPipe", // Pipe name
        GENERIC_READ,               // Read access
        0,                          // No sharing
        NULL,                       // Default security attributes
        OPEN_EXISTING,              // Opens existing pipe
        0,                          // Default attributes
        NULL);                      // No template file

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Error: Could not open pipe. Error code: %d\n", GetLastError());
        return 1;
    }

    // Read from the pipe
    if (!ReadFile(
        hPipe,        // Pipe handle
        buffer,       // Buffer to receive data
        sizeof(buffer), // Buffer size
        &dwBytesRead,  // Bytes read
        NULL)) {       // Not overlapped
        printf("Error: Failed to read from pipe. Error code: %d\n", GetLastError());
        CloseHandle(hPipe);
        return 1;
    }

    // Close the pipe handle
    CloseHandle(hPipe);

    printf("Received message: %s\n", buffer);

    return 0;
}

