
#pragma once

#include <iostream>

struct employee {
    int num;        // ID сотрудника
    char name[10];  // Имя
    double hours;   // Часы
};

struct Request {
    int id;
    int cmd; // 0 - read, 1 - modify
};

