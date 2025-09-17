#include "employee.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "�������������: Reporter <�������� ����> <�����.txt> <������>\n";
        return 1;
    }

    const char* binfile = argv[1];
    const char* reportfile = argv[2];
    double pay = atof(argv[3]); // ������ �� ���

    ifstream in(binfile, ios::binary);
    ofstream out(reportfile);

    if (!in || !out) {
        cout << "������ �������� ������!\n";
        return 1;
    }

    out << "����� �� ����� \"" << binfile << "\"\n";
    out << "�����\t���\t����\t��������\n";

    employee e;
    while (in.read((char*)&e, sizeof(employee))) {
        double salary = e.hours * pay;
        out << e.num << "\t" << e.name << "\t"
            << e.hours << "\t" << salary << "\n";
    }

    in.close();
    out.close();
    return 0;
}
