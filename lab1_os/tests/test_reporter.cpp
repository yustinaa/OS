#include "pch.h"
#include "../Reporter/reporter_func.h"
#include <fstream>
#include <vector>
#include <string>
using namespace std;

TEST(ReporterTest, GenerateReport) {
    string binFile = "test_employees.bin";
    string reportFile = "test_report.txt";
    double pay = 100.0;

    vector<employee> employees = {
        {15434, "Darya", 15},
        {28765, "Petr", 20}
    };

    ofstream out(binFile, ios::binary);
    ASSERT_TRUE(out.is_open());
    for (const auto& e : employees) {
        out.write(reinterpret_cast<const char*>(&e), sizeof(employee));
    }
    out.close();

    bool success = generateReport(binFile, reportFile, pay);
    ASSERT_TRUE(success);

    ifstream in(reportFile);
    ASSERT_TRUE(in.is_open());

    string line;
    getline(in, line);
    EXPECT_EQ(line, "Номер\tИмя\tЧасы\tЗарплата");

    getline(in, line);
    EXPECT_EQ(line, "15434\tDarya\t15\t1500");

    getline(in, line);
    EXPECT_EQ(line, "28765\tPetr\t20\t2000");

    in.close();
}
