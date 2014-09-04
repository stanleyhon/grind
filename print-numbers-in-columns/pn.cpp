// easy mode.
// input n c
// output for 13 4
// 1 5 9 13
// 2 6 10 
// 3 7 11 
// 4 8 12

#include <iostream>
#include <cmath>

using namespace std;

int main (void) {

    double n = 0;
    double c = 0;

    cin >> n;
    cin >> c;

    cout << n << " " << c << endl;

    // this is how many things per column
    double numRows = ceil(n / c); // but then round up.

    int row = 0;
    int col = 0;
    while (row < numRows) {
        col = 0;
        while (col <= c) {
            if ((col * numRows + row + 1) > n) {
                col++;
                continue;
            }
            cout << (row + 1) + (col * numRows) << " ";
            col++;
        }
        cout << "\n";
        row++;
    }

    return 0;
}
