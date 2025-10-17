#include <stdio.h>
#include <windows.h>

int main() {
    HANDLE hMapFile;
    LPCTSTR pBuf;
    const char* message = "Hello from process 1!";

    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        256,
        "SharedMemoryExample"
    );

    if (hMapFile == NULL) {
        printf("Could not create file mapping object (%lu).\n", GetLastError());
        return 1;
    }

    pBuf = (LPTSTR) MapViewOfFile(
        hMapFile,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        256
    );

    if (pBuf == NULL) {
        printf("Could not map view of file (%lu).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    // Write to shared memory
    CopyMemory((PVOID)pBuf, message, strlen(message) + 1);
    printf("Process wrote to shared memory: %s\n", message);

    printf("Press Enter to read from shared memory...");
    getchar();

    // Read from shared memory
    printf("Process reads from shared memory: %s\n", pBuf);

    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}

