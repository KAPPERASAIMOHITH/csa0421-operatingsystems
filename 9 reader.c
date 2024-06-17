#include <windows.h>
#include <stdio.h>

#define SHARED_MEMORY_SIZE 1024

int main() {
    // Wait a bit to ensure writer creates the shared memory
    Sleep(5000); // Sleep for 5 seconds

    // Open the named shared memory object
    HANDLE hMapFile = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,    // Read/write access
        FALSE,                  // Do not inherit the name
        "SharedMemoryExample"); // Name of mapping object

    if (hMapFile == NULL) {
        printf("Could not open file mapping object (%d).\n", GetLastError());
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

    // Read data from the shared memory
    printf("Data read from shared memory: %s\n", (char*)pBuf);

    // Unmap the shared memory object
    UnmapViewOfFile(pBuf);

    // Close the handle to the shared memory object
    CloseHandle(hMapFile);

    return 0;
}

