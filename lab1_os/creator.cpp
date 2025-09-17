#include "employee.h"
#include "creator_func.h"
#include <iostream>
#include <fstream> 
#include <cstdlib>  
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "�������������: Creator <��� �����> <���-�� �������>\n";
        return 1;
    }

    const char* filen = argv[1];
    int n = atoi(argv[2]);

    vector<employee> employees(n);
    for (int i = 0; i < n; i++) {
        cout << "��������� " << i + 1 << endl;
        cout << "������� ����������������� �����: ";
        cin >> employees[i].num;
        cout << "������� ���: ";
        cin >> employees[i].name;
        cout << "������� ���������� ������������ �����: ";
        cin >> employees[i].hours;
    }

    if (!writeEmployeesToFile(filen, employees)) {
        cout << "������ ������ �����!\n";
        return 1;
    }

    return 0;
}
