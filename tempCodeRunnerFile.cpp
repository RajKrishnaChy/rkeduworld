#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

using namespace std;

int main()
{
    // Create a semaphore with an initial value of 0
    HANDLE sem = CreateSemaphore(NULL, 0, 1, "my_semaphore");

    // Create the child process
    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    TCHAR* szCommandLine = _tcsdup(TEXT("child.exe"));

    if (!CreateProcess(NULL, szCommandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        cerr << "Error creating child process" << endl;
        return 1;
    }

    // Print "Hello"
    cout << "Hello" << endl;

    // Signal the semaphore
    ReleaseSemaphore(sem, 1, NULL);

    // Wait for the semaphore to be signaled
    WaitForSingleObject(sem, INFINITE);

    // Print "World"
    cout << "World" << endl;

    // Signal the semaphore
    ReleaseSemaphore(sem, 1, NULL);

    // Wait for the child process to exit
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Close the semaphore
    CloseHandle(sem);

    return 0;
}
