#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main (void) {
    string input;
    cin >> input;

    int depth;
    cin >> depth;

    vector<vector<char>*> words;
    for (int i = 0; i < depth; i++) {
        words.push_back (new vector<char>());
    }

    int direction = 0; // 0 down, 1 up
    int index = 0;
    for (auto it = input.begin(); it != input.end(); it++) {
        words[index]->push_back(*it);
        
        if (direction == 0) {
            if (index == 0) {
                direction = 1;
                index = 1;
            } else {
                index--;
            }
        } else {
            if (index == depth - 1) {
                direction = 0;
                index--;
            } else {
                index++;
            }
        }
        cout << "Index is " << index << "\n";
    }    

    // print
    for (int i = 0; i < depth; i++) {
        for (auto it = words[i]->begin(); it != words[i]->end(); it++) {
            cout << *it;
        }
        cout << "\n";
    }

    return 0;
}
