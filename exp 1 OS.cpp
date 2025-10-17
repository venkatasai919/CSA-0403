#include <iostream>
#include <windows.h>
using namespace std;

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    cout << "Parent Process:" << endl;
    cout << "Process ID (PID): " << GetCurrentProcessId() << endl;

    if (CreateProcess(
            NULL,
            (LPSTR)"notepad.exe",
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si,
            &pi)
        ) {
        cout << "Child Process Created Successfully." << endl;
        cout << "Child Process ID: " << pi.dwProcessId << endl;
        cout << "Parent Process ID (PID): " << GetCurrentProcessId() << endl;
    } 
    else {
        cout << "CreateProcess failed. Error: " << GetLastError() << endl;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
