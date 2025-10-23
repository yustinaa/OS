#pragma once
#include <vector>
#include <stdexcept>
using namespace std;

vector<long long> fibonacci(int n) {
    if (n <= 0)
    {
        throw invalid_argument("n must be positive number");
    }
    vector<long long> f(n);
    f[0] = 0;
    if (n > 1)
    {
        f[1] = 1;
    }
    for (int i = 2; i < n; ++i)
    {
        f[i] = f[i - 1] + f[i - 2];
    }
    return f;
}
