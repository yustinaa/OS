#include "core.h"
#include <algorithm>
using namespace std;

int find_min(const vector<int>& a)
{
    if (a.empty()) return 0; 
    int minVal = a[0];
    for (int val : a) {
        if (val < minVal) minVal = val;
    }
    return minVal; 
}
int find_max(const vector<int>& a) 
{
    if (a.empty()) return 0;
    int maxVal = a[0];
    for (int val : a) {
        if (val > maxVal) maxVal = val;
    }
    return maxVal;
}
double count_average(const vector<int>& a) 
{
    if (a.empty()) return 0;
    int sum=0;
    for (int val : a) {
        sum += val;
    }
    return static_cast<double>(sum) / a.size();
}
void replace_min_max_av(vector<int>& a, double avg) 
{
    int min = find_min(a);
    int max = find_max(a);
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] == min || a[i] == max)
        {
            a[i] = static_cast<int>(avg);
        }
    }

}
