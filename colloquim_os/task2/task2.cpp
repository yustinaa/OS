#include "palindrom.h"
#include <stdexcept>

int main() {
    try {
        cout << "Enter a number: ";
        string numbers;
        cin >> numbers;

        for (char c : numbers) {
            if (!isdigit(c))
                throw invalid_argument("only numbers must be entered");
        }

        vector<int> a;
        for (char c : numbers)
            a.push_back(c - '0');

        if (is_palind(a))
            cout << "Number is a palindrome\n";
        else
            cout << "Number is not a palindrome\n";
    }
    catch (const exception& e) {
        cerr << "error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
