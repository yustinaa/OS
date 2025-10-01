#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include "lab2_os1.h"
#include <vector>
#include <windows.h>
#include "core.h"
#include "utils.h"
#include "wrappers/MinMaxWrapper.h"
#include "wrappers/AverageWrapper.h"

int main() {
    int n;
    cout << "Enter size: ";
    cin >> n;

    if (n <= 0) {
        cerr << "Invalid array size!" << endl;
        return 1;
    }

    vector<int> array(n);
    cout << "Enter array elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }

    MinMaxParams min_max_p;
    min_max_p.array = &array;

    AverageParams avg_p;
    avg_p.array = &array;

    HANDLE hMinMax = CreateThread(nullptr, 0, MinMaxThread, &min_max_p, 0, nullptr);
    HANDLE hAverage = CreateThread(nullptr, 0, AverageThread, &avg_p, 0, nullptr);

    if (!hMinMax || !hAverage) {
        cerr << "Error creating threads!" << endl;
        return 1;
    }

    WaitForSingleObject(hMinMax, INFINITE);
    WaitForSingleObject(hAverage, INFINITE);

    CloseHandle(hMinMax);
    CloseHandle(hAverage);

    replace_min_max_av(array, avg_p.average);

    cout << "Average: " << avg_p.average << endl;
    cout << "Min: " << min_max_p.min << ", Max: " << min_max_p.max << endl;

    cout << "Modified array: ";
    for (size_t i = 0; i < array.size(); ++i)
    {
        int val = array[i];
        cout << val << " ";
    }

    return 0;
}
