// hard mode
// input n c
// output for 13 4
// 1 5 8 11
// 2 6 9 12
// 3 7 10 13
// 4

// output for 15 4
// 1 5 9 13
// 2 6 10 14
// 3 7 11 15
// 4 8 12

// output for 17 4
// 1 6 11 16
// 2 7 12 17
// 3 8 13
// 4 9 14
// 5 10 15

// 1 6 11 15
// 2 7 12 16
// 3 8 13 17
// 4 9 14
// 5 10 

// 1 6 10 14
// 2 7 11 15
// 3 8 12 16
// 4 9 13 17
// 5 

/* WARNING THIS SHIT DOESN'T ACTUALLY WORK */


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
