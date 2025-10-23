#pragma once
#include <iostream>
#include <vector>
using namespace std;

bool is_palind(const vector<int>& a) {
    int left = 0;
    int right = a.size() - 1;

    while (left < right) {
        if (a[left] != a[right])
        {
            return false;
        }
        left++;
        right--;
    }

    return true;
}


