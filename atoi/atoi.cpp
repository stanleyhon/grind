#include <iostream>
#include <string>

using namespace std;

int convert (char c) {
    if (c >= '0' && c <= '9') {
        cout << "Read the character " << c << " outputting: " << c - '0' << "\n";
        return (c - '0');
    } else {
	cout << "hit not between 0-9";
        return -1;
    }
} 

int main (void) {
    string input;
    cin >> input;

    bool first = true;
    int total = 0;
    for (auto it = input.begin(); it != input.end(); it++) {
        cout << "[" << *it << "]\n";
        if (first) {
            total = convert(*it);
            first = false;
            continue;
        }
        total = total * 10;
        total = total + convert(*it);
    }

    cout << total + 11;

    return 0;
}
