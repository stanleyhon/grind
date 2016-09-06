#include <iostream>
#include <list>

using namespace std;

int main () {
    list<int> input;

    int var = 0;
    while (cin >> var) {
        input.push_back(var);
    }

    bool first = true;
    int total = 0;
    int previous = 0;
    for (auto i = input.begin(); i != input.end(); i++) {
        if (first) {
            previous = *i;
            first = false;
            continue;
        }
        if (previous == *i) {
            total += previous;
        } else {
            previous = *i;
        }
    }

    cout << total;
    
    return 0;
}
        
         
