#include <iostream>
#include "fibonacci.h"

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
