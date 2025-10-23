#include "list.h"

int main() {
    myList a;
    int n;
    cout << "Enter size of a list: ";
    if (!(cin >> n))
    {
        throw invalid_argument("n must be integer");
    }
    cout << "Enter elements of a list: ";
    int x;
    for(int i=0; i<n; i++)
    {
        if (!(cin >> x))
        {
            throw invalid_argument("element must be integer");
        }
        a.add_el(x);
    }

    cout << "Original list: ";
    a.show();

    a.reverse();
    cout << "Reversed list: ";
    a.show();

    return 0;
}
