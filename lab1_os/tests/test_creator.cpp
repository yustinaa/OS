#include "pch.h"
#include "../Creator/creator_func.h"
#include <fstream>
#include <vector>
using namespace std;

TEST(TestCaseName, TestCreator) {
    string testFile = "test_employees.bin";
    vector<employee> employees = {
        {12344, "Darya", 15},
        {26542, "Petr", 17}
    };

    bool success = writeEmployeesToFile(testFile, employees);
    ASSERT_TRUE(success);

    ifstream in(testFile, ios::binary);
    ASSERT_TRUE(in.is_open());

    vector<employee> readEmployees;
    employee a;

    while (in.read(reinterpret_cast<char*>(&a), sizeof(employee))) {
        readEmployees.push_back(a);
    }
    in.close();

    ASSERT_EQ(readEmployees.size(), 2);

    EXPECT_EQ(readEmployees[0].num, 12344);
    EXPECT_STREQ(readEmployees[0].name, "Darya");
    EXPECT_DOUBLE_EQ(readEmployees[0].hours, 15);

    EXPECT_EQ(readEmployees[1].num, 223);
    EXPECT_STREQ(readEmployees[1].name, "Petr");
    EXPECT_DOUBLE_EQ(readEmployees[1].hours, 17);
}
