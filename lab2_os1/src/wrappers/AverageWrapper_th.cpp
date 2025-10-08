#include "AverageWrapper_th.h"
#include <vector>
#include <thread>
#include <chrono>
using namespace std;

void AverageThread(AverageParams* params) {
    if (!params || !params->array) return;

    double sum = 0.0;
    vector<int>& a = *params->array;

    for (size_t i = 0; i < a.size(); ++i) {
        sum += a[i];
        this_thread::sleep_for(chrono::milliseconds(12));
    }

    params->average = sum / a.size();
}
