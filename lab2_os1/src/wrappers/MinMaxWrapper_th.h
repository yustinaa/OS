#pragma once
#include <vector>

struct MinMaxParams {
    std::vector<int>* array;
    int min;
    int max;
};

void MinMaxThread(MinMaxParams* params);