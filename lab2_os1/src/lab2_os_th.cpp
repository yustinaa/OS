#include "lab2_os1.h"
#include <vector>
#include <iostream>
#include <thread>
#include <stdexcept>
#include "core.h"
#include "wrappers/MinMaxWrapper_th.h"
#include "wrappers/AverageWrapper_th.h"

using namespace std;

int main() {
    try {
        int n;
        cout << "Enter size: ";
        if (!(cin >> n) || n <= 0) 
        {
            throw runtime_error("Invalid array size!");
        }

        vector<int> array(n);
        cout << "Enter array elements: ";
        for (int i = 0; i < n; ++i)
        {
            if (!(cin >> array[i])) {
                throw runtime_error("Invalid input!");
            }
        }

        MinMaxParams min_max_p;
        min_max_p.array = &array;

        AverageParams avg_p;
        avg_p.array = &array;

        thread tMinMax(MinMaxThread, &min_max_p);
        thread tAverage(AverageThread, &avg_p);

        tMinMax.join();
        tAverage.join();

        replace_min_max_av(array, avg_p.average);

        cout << "Average: " << avg_p.average << endl;
        cout << "Min: " << min_max_p.min << ", Max: " << min_max_p.max << endl;

        cout << "Modified array: ";
        for (int val : array) cout << val << " ";
        cout << endl;

        return 0;
    }
    catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
        return 1;
    }
}
