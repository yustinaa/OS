#include "AverageWrapper.h"
#include "../core.h"
#include "../utils.h"
#include <iostream>
using namespace std;

DWORD WINAPI AverageThread(LPVOID lpParam) {
    AverageParams* params = static_cast<AverageParams*>(lpParam);
    if (!params || !params->array) return Constants::EXIT_CODE_OK;

    double sum = 0.0;
    vector<int>& a = *params->array;
    for (size_t i = 0; i < a.size(); ++i) {
        int val = a[i];
        sum += val;
        Sleep(Constants::SLEEP_AVG_MS);
    }

    params->average = sum/a.size();
    //cout << "Average: " << params->average << endl;
    return Constants::EXIT_CODE_OK;
}
