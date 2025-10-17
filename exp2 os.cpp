#include <iostream>
#include <windows.h>
using namespace std;

int main() {
    HANDLE source, dest;
    char buffer[1024];
    DWORD bytesRead, bytesWritten;

    source = CreateFile("source.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (source == INVALID_HANDLE_VALUE) {
        cout << "Cannot open source file. Error: " << GetLastError() << endl;
        return 1;
    }

    dest = CreateFile("destination.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (dest == INVALID_HANDLE_VALUE) {
        cout << "Cannot create destination file. Error: " << GetLastError() << endl;
        CloseHandle(source);
        return 1;
    }

    while (ReadFile(source, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead > 0) {
        WriteFile(dest, buffer, bytesRead, &bytesWritten, NULL);
    }

    cout << "File copied successfully." << endl;

    CloseHandle(source);
    CloseHandle(dest);
    return 0;
}

