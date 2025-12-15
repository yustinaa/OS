#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include <conio.h>
#include "lab_os5.h"

using namespace std;

const string PIPE_NAME = "\\\\.\\pipe\\Tube";
string g_fileName;
SRWLOCK* locks;
int emp_count = 0;

DWORD WINAPI ClientHandler(LPVOID lpParam) 
{
    HANDLE hPipe = (HANDLE)lpParam;
    Request req;
    DWORD bytesRead, bytesWritten;

    while (true) 
    {
        if (!ReadFile(hPipe, &req, sizeof(req), &bytesRead, NULL) || bytesRead == 0) break;

        int recordIndex = -1;
        fstream file(g_fileName, ios::in | ios::binary);
        employee temp;
        int idx = 0;
        while (file.read((char*)&temp, sizeof(employee))) 
        {
            if (temp.num == req.id) 
            { recordIndex = idx;
            break; 
            }
            idx++;
        }
        file.close();

        bool found = (recordIndex != -1 && recordIndex < emp_count);
        WriteFile(hPipe, &found, sizeof(found), &bytesWritten, NULL);
        if (!found) continue;

        employee empData;
        if (req.cmd == 0)//чтение
        {
            AcquireSRWLockShared(&locks[recordIndex]);
            file.open(g_fileName, ios::in | ios::binary);
            file.seekg(recordIndex * sizeof(employee));
            file.read((char*)&empData, sizeof(employee));
            file.close();
            WriteFile(hPipe, &empData, sizeof(employee), &bytesWritten, NULL);
            int msg;
            ReadFile(hPipe, &msg, sizeof(msg), &bytesRead, NULL);
            ReleaseSRWLockShared(&locks[recordIndex]);
        }
        else if (req.cmd == 1)//изменение
        {
            AcquireSRWLockExclusive(&locks[recordIndex]);
            file.open(g_fileName, ios::in | ios::binary);
            file.seekg(recordIndex * sizeof(employee));
            file.read((char*)&empData, sizeof(employee));
            file.close();
            WriteFile(hPipe, &empData, sizeof(employee), &bytesWritten, NULL);
            if (ReadFile(hPipe, &empData, sizeof(employee), &bytesRead, NULL)) 
            {
                file.open(g_fileName, ios::in | ios::out | ios::binary);
                file.seekg(recordIndex * sizeof(employee));
                file.write((char*)&empData, sizeof(employee));
                file.close();
            }
            ReleaseSRWLockExclusive(&locks[recordIndex]);
        }
    }
    DisconnectNamedPipe(hPipe);
    CloseHandle(hPipe);
    return 0;
}

int main()
{
    cout << "Enter filename: ";
    cin >> g_fileName;
    cout << "Enter number of employees: ";
    cin >> emp_count;

    locks = new SRWLOCK[emp_count];
    fstream file(g_fileName, ios::out | ios::binary);
    for (int i = 0; i < emp_count; ++i) {
        InitializeSRWLock(&locks[i]);
        employee e;
        cout << "Emp #" << i + 1 << " (ID Name Hours): ";
        cin >> e.num >> e.name >> e.hours;
        file.write((char*)&e, sizeof(e));
    }
    file.close();

    int clientCount;
    cout << "Enter number of clients: "; cin >> clientCount;

    vector<HANDLE> hWaitEvents; //массив для ожидания
    for (int i = 0; i < clientCount; ++i) {
        STARTUPINFO si = { sizeof(si) };
        PROCESS_INFORMATION pi;
        char cmd[] = "Client.exe";
        if (CreateProcessA(NULL, cmd, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
            hWaitEvents.push_back(pi.hProcess);
            CloseHandle(pi.hThread);
        }
    }

    HANDLE hConnectEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    hWaitEvents.push_back(hConnectEvent);

    cout << "Server is running. To stop: Close ALL client windows.\n";



    while (true) 
    {
        HANDLE hPipe = CreateNamedPipe(PIPE_NAME.c_str(), PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
            PIPE_UNLIMITED_INSTANCES, 512, 512, 0, NULL);

        OVERLAPPED overlapped = { 0 };
        overlapped.hEvent = hConnectEvent;

        ConnectNamedPipe(hPipe, &overlapped);

        DWORD dwWait = WaitForMultipleObjects((DWORD)hWaitEvents.size(), hWaitEvents.data(), FALSE, INFINITE);

        if (dwWait == WAIT_OBJECT_0 + hWaitEvents.size() - 1) //сработало союытие канала
        {
            ResetEvent(hConnectEvent);
            HANDLE hThread = CreateThread(NULL, 0, ClientHandler, (LPVOID)hPipe, 0, NULL);
            if (hThread) CloseHandle(hThread);
        }
        else {
            bool anyAlive = false;
            for (size_t i = 0; i < hWaitEvents.size() - 1; i++) 
            {
                DWORD exCode;
                GetExitCodeProcess(hWaitEvents[i], &exCode);
                if (exCode == STILL_ACTIVE) anyAlive = true;
            }

            if (!anyAlive) {
                CloseHandle(hPipe);
                break;
            }
            CloseHandle(hPipe);
        }
    }

    cout << "\nAll clients finished. Final file content:\n";
    file.open(g_fileName, ios::in | ios::binary);
    employee e;
    while (file.read((char*)&e, sizeof(e))) {
        cout << "ID: " << e.num << "\tName: " << e.name << "\tHours: " << e.hours << endl;
    }
    file.close();

    for (size_t i = 0; i < hWaitEvents.size() - 1; i++)
    {
        CloseHandle(hWaitEvents[i]);
    }
    CloseHandle(hConnectEvent);
    delete[] locks;

    return 0;
}