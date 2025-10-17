#include <stdio.h>
#include <windows.h>

int main() {
    HANDLE hPipe;
    char buffer[100];
    DWORD dwWritten, dwRead;

    hPipe = CreateNamedPipe(
        "\\\\.\\pipe\\MyPipe",
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1,
        1024,
        1024,
        0,
        NULL
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Failed to create named pipe. Error: %lu\n", GetLastError());
        return 1;
    }

    printf("Waiting for a client to connect...\n");
    ConnectNamedPipe(hPipe, NULL);

    const char* msg = "Hello from server process!";
    WriteFile(hPipe, msg, strlen(msg) + 1, &dwWritten, NULL);
    printf("Server sent message: %s\n", msg);

    ReadFile(hPipe, buffer, sizeof(buffer), &dwRead, NULL);
    printf("Server received message: %s\n", buffer);

    DisconnectNamedPipe(hPipe);
    CloseHandle(hPipe);

    return 0;
}

