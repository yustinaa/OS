#include "MinMaxWrapper_th.h"
#include <vector>
#include <thread>
#include <chrono>
using namespace std;

void MinMaxThread(MinMaxParams* params) {
    if (!params || !params->array) return;

    vector<int>& a = *params->array;
    int min_v = a[0];
    int max_v = a[0];

    for (size_t i = 0; i < a.size(); ++i) {
        int val = a[i];
        if (val < min_v) min_v = val;
        if (val > max_v) max_v = val;
        this_thread::sleep_for(chrono::milliseconds(7));
    }

    params->min = min_v;
    params->max = max_v;
}
