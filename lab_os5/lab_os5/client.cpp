#include <iostream>
#include <windows.h>
#include <conio.h>
#include "lab_os5.h"


using namespace std;

const string PIPE_NAME = "\\\\.\\pipe\\Tube";


int main() {
    WaitNamedPipe(PIPE_NAME.c_str(), NMPWAIT_WAIT_FOREVER);

    HANDLE hPipe = CreateFile(PIPE_NAME.c_str(), GENERIC_READ | GENERIC_WRITE,
        0, NULL, OPEN_EXISTING, 0, NULL);

    if (hPipe == INVALID_HANDLE_VALUE) {
        cout << "Connection failed.\n";
        return 1;
    }

    while (true) {
        cout << "\n1. Modify\n2. Read\n3. Exit\n> ";
        int ch;
        cin >> ch;
        if (ch == 3) break;

        Request req;
        req.cmd = (ch == 1) ? 1 : 0;
        cout << "Enter ID: ";
        cin >> req.id;

        DWORD rw;
        WriteFile(hPipe, &req, sizeof(req), &rw, NULL);

        bool found;
        ReadFile(hPipe, &found, sizeof(found), &rw, NULL);
        if (!found) {
            cout << "Not found.\n";
            continue;
        }

        employee emp;
        ReadFile(hPipe, &emp, sizeof(emp), &rw, NULL);
        cout << "ID: " << emp.num << " Name: " << emp.name << " Hours: " << emp.hours << endl;

        if (req.cmd == 1) //изменить
        {
            cout << "New Name & Hours: ";
            cin >> emp.name >> emp.hours;
            WriteFile(hPipe, &emp, sizeof(emp), &rw, NULL);
            cout << "Updated.\n";
        }
        else
        { //чтение
            cout << "Press key to finish reading...";
            _getch();
            int msg = 1;
            WriteFile(hPipe, &msg, sizeof(msg), &rw, NULL); //освободить
        }
    }
    CloseHandle(hPipe);
    return 0;
}