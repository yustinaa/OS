#include <iostream>
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

int main() {
    try {
        int n;
        cout << "Enter n: ";
        if (!(cin >> n))
        {
            throw invalid_argument("n must be integer");
        }

        vector<long long> result = fibonacci(n);

        cout << "First " << n << " Fibonacci numbers:\n";
        for (auto v : result)
            cout << v << " ";
        cout << endl;
    }
    catch (const exception& e) {
        cerr << "error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
