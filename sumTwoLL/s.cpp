#include <iostream>

using namespace std;

class Node {
public:
    Node () = delete;  
    Node (int val) : next(NULL), value(val) {}

    void insert (int value) {
        Node * current = this;
        while (current->next != NULL) {
            current = current->next;
        }

        current->next = new Node (value);
        return;
    }

    void show (void) {
        Node * current = this;
        while (current != NULL) {
            cout << current->value << " ";
            current = current->next;
        }
        cout << endl;
        return;
    }

    Node * next;
    int value;
};

void merge (Node * n, Node * n2) {
    int first = 0;
    int second = 0;
    while (n != NULL) {
        first += n->value;
        if (n->next != NULL) {
            first *= 10;
        }
        n = n->next;
    }

    while (n2 != NULL) {
        second += n2->value;
        if (n2->next != NULL) {
            second *= 10;
        }
        n2 = n2->next;
    }

    int total = first + second;

    cout << total << "\n";
    return;
}

int main (void) {

    Node n(5);

    n.insert(1);
    n.insert(8);
    n.insert(5);
    n.insert(4);
    n.insert(1);
    n.insert(9);
    n.show();

    Node n2(4);

    n2.insert(6);
    n2.insert(5);
    n2.insert(2);
    n2.insert(2);
    n2.insert(9);
    n2.insert(1);
    n2.insert(2);
    n2.show();

    merge (&n, &n2);
  
    return 0;
} 
