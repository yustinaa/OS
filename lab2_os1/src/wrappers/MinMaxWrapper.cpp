#include "MinMaxWrapper.h"
#include "../core.h"
#include <iostream>
using namespace std;

DWORD WINAPI MinMaxThread(LPVOID lpParam) {
    MinMaxParams* params = static_cast<MinMaxParams*>(lpParam);
    if (!params || !params->array) return 0;

    vector<int>& a = *params->array;
    int min_v = a[0];
    int max_v = a[0];

    for (size_t i = 0; i < a.size(); ++i) {
        int val = a[i];
        if (val < min_v)
        {
            min_v = val;
        }
        if (val > max_v)
        {
            max_v = val;
        }
        Sleep(7);
    }

    params->min = min_v;
    params->max = max_v;

    //cout << "Min: " << min_v << ", Max: " << max_v << endl;
    return 0;
}
