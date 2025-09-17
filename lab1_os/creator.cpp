#include "employee.h"
#include <iostream>
#include <fstream> 
#include <cstdlib>  
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "�������������: Creator <��� �����> <���-�� �������>\n";
        return 1;
    }

    const char* filename = argv[1];
    int n = atoi(argv[2]);// ���������� �������

    ofstream out(filename, ios::binary);
    if (!out) {
        cout << "�� ������� ������� ����!\n";
        return 1;
    }

    employee e;
    for (int i = 0; i < n; i++) {
        cout << "��������� " << i + 1 << endl;
        cout << "������� ����������������� �����: ";
        cin >> e.num;
        cout << "������� ���: ";
        cin >> e.name;
        cout << "������� ���������� ������������ �����: ";
        cin >> e.hours;

        out.write((char*)&e, sizeof(employee)); // ������ ��������� � ��� ����
    }

    out.close();
    return 0;
}
