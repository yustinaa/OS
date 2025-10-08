#include "AverageWrapper.h"
#include "../core.h"
#include <iostream>
using namespace std;

DWORD WINAPI AverageThread(LPVOID lpParam) {
    AverageParams* params = static_cast<AverageParams*>(lpParam);
    if (!params || !params->array)
    {
        return  0;
    }

    double sum = 0.0;
    vector<int>& a = *params->array;
    for (size_t i = 0; i < a.size(); ++i) {
        int val = a[i];
        sum += val;
        Sleep(12);
    }

    params->average = sum/a.size();
    //cout << "Average: " << params->average << endl;
    return 0;
}
