/*
u have k lists of sorted integers.
Find the smallest range that includes at least one number from each of the k lists. 

For example, 
List 1: [4, 10, 15, 24, 26] 
List 2: [0, 9, 12, 20] 
List 3: [5, 18, 22, 30] 

The smallest range here would be [20, 24] as it contains 24 from list 1, 
20 from list 2, and 22 from list 3.
*/
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <climits>

using namespace std;

void solve (void);
bool pointerReachedEnd (void);

#define SIZE 1000

int pointers[SIZE];
int listLengths[SIZE];
vector<int> lists[SIZE];
int numLists = 0;

int main (void) {
    // Read in the inputs.
    string line;
    while (getline(cin, line)) {
        // Read a line into an iss

        istringstream iss (line);
        
        // Read the line
        int lineLength = 0;
        int var = 0;
        while (iss >> var) {
            // Push each character onto a list
            lists[numLists].push_back (var);
            lineLength++;
        }
        listLengths[numLists] = lineLength;
        numLists++;
    }
    
    solve ();
    
    return 0;
}

void solve (void) {
    // Initialise our pointer array
    for (int i = 0; i < SIZE; i++) {
        pointers[i] = 0;
    }
    
    int smallestDistance = INT_MAX;
    int smallAnswer = -1;
    int largeAnswer = -1;
    
    // Keep going until one of our pointers 
    // reaches the end of any list.
    
    // We'll need to know which list has our smallest number
    int smallestListNumber = -1;
    while (pointerReachedEnd () == false) {
        
        // Choose some numbers as our initial values
        int smallestValue = INT_MAX;
        int largestValue = INT_MIN;
        
        // Find the smallest and highest pointed to by our pointers
        for (int i = 0; i < numLists; i++) {

            if (lists[i][pointers[i]] < smallestValue) {
                smallestValue = lists[i][pointers[i]];
                smallestListNumber = i;
            }

            if (lists[i][pointers[i]] > largestValue) {
                largestValue = lists[i][pointers[i]];
            }
        }
        
        // We've chosen smallest and largest, 
        // Check if it's smaller than what we've seen before.
        if (largestValue - smallestValue < smallestDistance) {
            // If it is, it's a new best answer, record it.
            smallestDistance = largestValue - smallestValue;
            smallAnswer = smallestValue;
            largeAnswer = largestValue;
        }
        
        // Regardless of whether the answer is better, we need
        // to move the pointer @ smallest up.
        pointers[smallestListNumber]++;
    }
    
    // At this point we'll have reached the end, so just print the answer
    cout << "Smallest Distance: " << smallestDistance << endl;
    cout << smallAnswer << " -> " << largeAnswer << endl;
    
    return;
}

// Check if any of the indexes in 'pointers' has reached the end
// of their respective lists in 'lists'.
bool pointerReachedEnd (void) {
    for (int i = 0; i < numLists; i++) {
        if (pointers[i] == listLengths[i]) {
            return true;
        }
    }
    return false;
}
