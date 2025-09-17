#include "employee.h"
#include <iostream>
#include <windows.h>
#include <iostream>
#include <fstream>
#include<string>
#include <locale.h>
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

    wstring cmdCreator = L"Creator.exe " + wstring(binF.begin(), binF.end()) + L" " + to_wstring(n);
    wchar_t cmdLine[256];
    wcscpy_s(cmdLine, 256, cmdCreator.c_str());

    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    if (!CreateProcess(NULL, cmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        cout << "������ ������� Creator\n";
        return 1;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

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

    wstring cmdReporter = L"Reporter.exe " + wstring(binF.begin(), binF.end()) + L" " + wstring(reportF.begin(), reportF.end()) + L" " + to_wstring(pay);
    wchar_t cmdR[256];
    wcscpy_s(cmdR, 256, cmdReporter.c_str());

    if (!CreateProcess(NULL, cmdR, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        cout << "������ ������� Reporter\n";
        return 1;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    ifstream frep(reportF);
    cout << "\n���������� ������:\n";
    string line;
    while (getline(frep, line)) {
        cout << line << endl;
    }
    frep.close();

    return 0;
}
