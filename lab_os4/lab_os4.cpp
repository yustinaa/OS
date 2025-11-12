#include "sync_manager.h"
#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    string filename;
    int numRecords, numSenders;

    cout << "Введите имя бинарного файла: ";
    cin >> filename;
    cout << "Введите количество записей: ";
    cin >> numRecords;

    S_Manager ipc(filename, numRecords);

    cout << "Введите количество процессов Sender: ";
    cin >> numSenders;

    vector<PROCESS_INFORMATION> senderProcesses;

    for (int i = 0; i < numSenders; ++i) {
        STARTUPINFO si = { sizeof(si) };
        PROCESS_INFORMATION pi;

        string senderCommandLine = "sender.exe \"" + filename + "\" " + to_string(i);//путь к sender.exe

        cout << "Запуск: " << senderCommandLine << endl;

        if (CreateProcess(
            "sender.exe",                    
            const_cast<char*>(senderCommandLine.c_str()),
            NULL,                           
            NULL,                           
            FALSE,                          
            CREATE_NEW_CONSOLE,             
            NULL,                           
            NULL,                           
            &si,                            
            &pi                             
        )) 
        {
            senderProcesses.push_back(pi);
            cout << "Запущен процесс Sender " << i + 1 << " (ID: " << i << ")" << endl;
        }
        else {
            DWORD error = GetLastError();
            cerr << "Ошибка запуска процесса Sender " << i + 1 << "! Код: " << error << endl;
        }
    }

    if (senderProcesses.empty()) {
        std::cerr << "Не удалось запустить ни одного процесса Sender!" << endl;
        return 1;
    }

    cout << "Ожидание готовности процессов Sender..." << endl;

    if (S_Manager::waitAllSendersReady(numSenders)) {
        cout << "Все процессы Sender готовы к работе." << endl;
    }
    else {
        cerr << "Ошибка ожидания готовности процессов Sender!" << endl;
    }

    bool running = true;// осн цикл receiver
    while (running) {
        std::cout << "\n1 — читать сообщение\n0 — выход\n";
        int cmd;
        std::cin >> cmd;

        if (cmd == 1) {
            std::string msg;
            if (ipc.readMessage(msg)) {
                std::cout << "Прочитано: " << msg << std::endl;
            }
            else {
                std::cout << "Не удалось прочитать сообщение" << std::endl;
            }
        }
        else if (cmd == 0) {
            running = false;
        }
    }

    std::cout << "Завершение процессов Sender..." << std::endl;
    for (auto& pi : senderProcesses) {
        TerminateProcess(pi.hProcess, 0);
        WaitForSingleObject(pi.hProcess, 1000);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    std::cout << "Процесс Receiver завершен." << std::endl;
    return 0;
}