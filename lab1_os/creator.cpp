#include "employee.h"
#include <iostream>
#include <fstream> 
#include <cstdlib>  
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Использование: Creator <имя файла> <кол-во записей>\n";
        return 1;
    }

    const char* filename = argv[1];
    int n = atoi(argv[2]);// количество записей

    ofstream out(filename, ios::binary);
    if (!out) {
        cout << "Не удалось открыть файл!\n";
        return 1;
    }

    employee e;
    for (int i = 0; i < n; i++) {
        cout << "Сотрудник " << i + 1 << endl;
        cout << "Введите идентификационный номер: ";
        cin >> e.num;
        cout << "Введите имя: ";
        cin >> e.name;
        cout << "Введите количество отработанных часов: ";
        cin >> e.hours;

        out.write((char*)&e, sizeof(employee)); // запись структуры в бин файл
    }

    out.close();
    return 0;
}
