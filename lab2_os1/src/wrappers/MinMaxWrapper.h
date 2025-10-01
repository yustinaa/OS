#pragma once
#include <vector>
#include <windows.h>

struct MinMaxParams {
    std::vector<int>* array;
    int min;
    int max;
};

DWORD WINAPI MinMaxThread(LPVOID lpParam);
