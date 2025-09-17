#include "employee.h"
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <conio.h>

using namespace std;

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    string binF, reportF;
    int n;
    double pay;

    cout << "������� ��� ��������� �����: ";
    cin >> binF;
    cout << "������� ���������� �������: ";
    cin >> n;

    // ��������� ��������� ������ ��� � �������
    string cmdCreator = "Creator.exe " + binF + " " + to_string(n);
    char cmdLine[256];
    strcpy_s(cmdLine, cmdCreator.c_str());

    // ��� � �������: ��������� STARTUPINFO
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFOA));
    si.cb = sizeof(STARTUPINFOA);

    // ��������� ������� ��� � �������
    if (!CreateProcessA(NULL, cmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        cout << "������ ������� Creator\n";
        cout << "Press any key to finish.\n";
        _getch();
        return 1;
    }

    // ���� ���������� ��� � �������
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    // ������� ���������� �����
    ifstream fin(binF, ios::binary);
    employee emp;
    cout << "\n���������� ��������� �����:\n";
    while (fin.read((char*)&emp, sizeof(employee))) {
        cout << emp.num << " " << emp.name << " " << emp.hours << endl;
    }
    fin.close();

    cout << "\n������� ��� ����� ������: ";
    cin >> reportF;
    cout << "������� ������ �� ���: ";
    cin >> pay;

    // ��������� Reporter ����������
    string cmdReporter = "Reporter.exe " + binF + " " + reportF + " " + to_string(pay);
    char cmdR[256];
    strcpy_s(cmdR, cmdReporter.c_str());

    ZeroMemory(&si, sizeof(STARTUPINFOA));
    si.cb = sizeof(STARTUPINFOA);

    if (!CreateProcessA(NULL, cmdR, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        cout << "������ ������� Reporter\n";
        cout << "Press any key to finish.\n";
        _getch();
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    ifstream frep(reportF);
    cout << "\n���������� ������:\n";
    string line;
    while (getline(frep, line)) {
        cout << line << endl;
    }
    frep.close();

    cout << "Press any key to finish.\n";
    _getch();
    return 0;
}