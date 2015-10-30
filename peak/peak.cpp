#include <iostream>
#include <vector>

using namespace std;

void find_peak (vector<int> & v);

int main (void) {
    vector<int> v;
    int val;
    while (cin >> val) {
        v.push_back(val);
    }

    find_peak(v);

    return 0;
}

void find_peak (vector<int> & v) {
    int leftHand = 0;
    int rightHand = v.size() - 1;

    bool complete = false;
    while (complete == false) {
        int middle = (leftHand + rightHand) / 2;

        // perform the check on middle
        bool leftLower = false;
        bool rightLower = false; 
        if (leftHand >= 0) {
            if (v[leftHand] <= v[middle]) {
                leftLower = true;
            }
        } else {
            leftLower = true;
        }

        if (rightHand <= v.size() - 1) {
            if (v[rightHand] <= v[middle]) {
                rightLower = true;
            }
        } else {
            rightLower = true;
        }

        if (leftLower && rightLower) {
            cout << "Found a peak at index " << middle << 
                " | Left: " << v[leftHand] << 
                " | Middle: " << v[middle] <<
                " | Right: " << v[rightHand] << endl;
            complete = true;
        } else {
            // there is no guarantee there will be a peak on the smaller side,
            // but there is a guarantee there WILL BE a peak on the larger side,
            // so binary search on the larger side
            if (leftLower == true) {
                leftHand = middle;
            } else {
                rightHand = middle;
            }
        }
    }
    return;
}
