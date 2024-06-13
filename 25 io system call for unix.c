#include <windows.h>
#include <stdio.h>
#include <tchar.h>

int main() {
    // Open a file using CreateFile() function
    HANDLE hFile = CreateFile(
        _T("example.txt"),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        _tprintf(_T("Could not open file (error %d)\n"), GetLastError());
        return 1;
    }

    // Get file size using GetFileSize() function
    DWORD fileSize = GetFileSize(hFile, NULL);
    if (fileSize == INVALID_FILE_SIZE) {
        _tprintf(_T("Could not get file size (error %d)\n"), GetLastError());
        CloseHandle(hFile);
        return 1;
    }
    _tprintf(_T("File size: %lu bytes\n"), fileSize);

    // Move the file pointer using SetFilePointer() function
    DWORD offset = SetFilePointer(hFile, 0, NULL, FILE_END);
    if (offset == INVALID_SET_FILE_POINTER) {
        _tprintf(_T("Could not move file pointer (error %d)\n"), GetLastError());
        CloseHandle(hFile);
        return 1;
    }
    _tprintf(_T("File pointer moved to end: %lu\n"), offset);

    // Open a directory using FindFirstFile() and FindNextFile() functions
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(_T("*"), &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        _tprintf(_T("Could not open directory (error %d)\n"), GetLastError());
        CloseHandle(hFile);
        return 1;
    }

    do {
        _tprintf(_T("Directory entry: %s\n"), findFileData.cFileName);
    } while (FindNextFile(hFind, &findFileData) != 0);

    if (GetLastError() != ERROR_NO_MORE_FILES) {
        _tprintf(_T("Error reading directory (error %d)\n"), GetLastError());
    }

    // Close the directory handle
    FindClose(hFind);

    // Close the file handle
    CloseHandle(hFile);

    return 0;
}

