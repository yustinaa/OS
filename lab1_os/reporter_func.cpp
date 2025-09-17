#include "reporter_func.h"
#include <fstream>
#include <iostream>

bool generateReport(const std::string& binFile, const std::string& reportFile, double pay) {
    std::ifstream in(binFile, std::ios::binary);
    std::ofstream out(reportFile);
    if (!in || !out) return false;

    out << "Номер\tИмя\tЧасы\tЗарплата\n";

    employee e;
    while (in.read(reinterpret_cast<char*>(&e), sizeof(employee))) {
        double salary = e.hours * pay;
        out << e.num << "\t" << e.name << "\t"
            << e.hours << "\t" << salary << "\n";
    }

    return true;
}
