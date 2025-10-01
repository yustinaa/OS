#pragma once
#include <vector>
#include <windows.h>

struct AverageParams {
    std::vector<int>* array;
    double average;
};

DWORD WINAPI AverageThread(LPVOID lpParam);
