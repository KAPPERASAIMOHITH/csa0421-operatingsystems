#include <windows.h>
#include <stdio.h>

#define SHARED_MEMORY_SIZE 1024

int main() {
    // Create a named shared memory object
    HANDLE hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // Use paging file
        NULL,                    // Default security
        PAGE_READWRITE,          // Read/write access
        0,                       // Maximum object size (high-order DWORD)
        SHARED_MEMORY_SIZE,      // Maximum object size (low-order DWORD)
        "SharedMemoryExample");  // Name of mapping object

    if (hMapFile == NULL) {
        printf("Could not create file mapping object (%d).\n", GetLastError());
        return 1;
    }

    // Map the shared memory object into the address space of the current process
    LPVOID pBuf = MapViewOfFile(
        hMapFile,               // Handle to map object
        FILE_MAP_ALL_ACCESS,    // Read/write permission
        0,
        0,
        SHARED_MEMORY_SIZE);

    if (pBuf == NULL) {
        printf("Could not map view of file (%d).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    // Write data to the shared memory
    printf("Enter some data to write to shared memory: ");
    fgets((char*)pBuf, SHARED_MEMORY_SIZE, stdin);

    printf("Data written to shared memory: %s\n", (char*)pBuf);

    // Keep the writer program running for a while to ensure reader can read
    printf("Writer is keeping the shared memory open for 30 seconds...\n");
    Sleep(30000); // Sleep for 30 seconds

    // Unmap the shared memory object
    UnmapViewOfFile(pBuf);

    // Close the handle to the shared memory object
    CloseHandle(hMapFile);

    return 0;
}

