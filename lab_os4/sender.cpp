#include "sync_manager.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    if (argc < 3) {
        cerr << "»спользование: sender <файл> <sender_id>" << endl;
        return 1;
    }

    std::string filename = argv[1];
    int senderId = stoi(argv[2]);

    S_Manager ipc(filename, 10);

    if (S_Manager::signalReady(senderId)) {
        cout << "ѕроцесс Sender " << senderId << " готов к работе" << endl;
    }
    else {
        cerr << "ќшибка отправки сигнала готовности!" << endl;
    }

    bool running = true;
    while (running) {
        cout << "\n1 Ч отправить сообщение\n0 Ч выход\n";
        int cmd; 
        cin >> cmd;
        if (cmd == 1) {
            string msg;
            cout << "¬ведите сообщение: ";
            cin.ignore();
            getline(std::cin, msg);

            if (msg.length() >= 20) {
                cout << "—ообщение слишком длинное (макс. 19 символов)" << std::endl;
                continue;
            }

            ipc.writeMessage(msg);
            cout << "—ообщение отправлено" << std::endl;
        }
        else if (cmd == 0) {
            running = false;
        }
    }

    return 0;
}