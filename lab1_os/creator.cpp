#include "employee.h"
#include "creator_func.h"
#include <iostream>
#include <fstream> 
#include <cstdlib>  
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Использование: Creator <имя файла> <кол-во записей>\n";
        return 1;
    }

    const char* filen = argv[1];
    int n = atoi(argv[2]);

    vector<employee> employees(n);
    for (int i = 0; i < n; i++) {
        cout << "Сотрудник " << i + 1 << endl;
        cout << "Введите идентификационный номер: ";
        cin >> employees[i].num;
        cout << "Введите имя: ";
        cin >> employees[i].name;
        cout << "Введите количество отработанных часов: ";
        cin >> employees[i].hours;
    }

    if (!writeEmployeesToFile(filen, employees)) {
        cout << "Ошибка записи файла!\n";
        return 1;
    }

    return 0;
}
