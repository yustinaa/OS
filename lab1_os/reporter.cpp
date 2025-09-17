#include "reporter_func.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "�������������: Reporter <�������� ����> <�����.txt> <������>\n";
        return 1;
    }

    string binFile = argv[1];
    string reportFile = argv[2];
    double pay = atof(argv[3]);

    if (!generateReport(binFile, reportFile, pay)) {
        cout << "������ ��� �������� ������!\n";
        return 1;
    }

    return 0;
}
