#pragma once
#include <vector>

struct AverageParams {
    std::vector<int>* array;
    double average;
};

void AverageThread(AverageParams* params);
