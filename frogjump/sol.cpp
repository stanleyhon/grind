#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<int> data;
map<int, set<int>*> sources;

void tryTarget (int target, int source);
void solve ();

int main (void)
{
    int input = 0;
    while (cin >> input) 
    {
        data.push_back(input);
    }

    for (auto i = data.begin(); i != data.end(); i++) 
    {
//        cout << *i << " ";
        sources[*i] = new set<int>();
    }

    solve ();

    return 0;
}


bool solve ()
{
    // Go to every stone
    for (auto i = data.begin(); i != data.end(); i++)
    {
        // Check if nobody could reach here.
        if (sources[*i]->empty())
        {
            // Base case
            if (*i == 0) 
            {
                sources[1]->insert(0);
            }
        }
        else
        {
            set<int> * temp = sources[*i];
            for (auto s = temp->begin(); s != temp->end(); s++)
            {
                int distanceTravelled = *i - *s;
                
                // try -1
                if (distanceTravelled - 1 > 0)
                {
                    tryTarget (*i + distanceTravelled - 1, *i);
                }
                
                // try same jump distance
                tryTarget (*i + distanceTravelled, *i);

                // Try jump distance + 1
                tryTarget (*i + distanceTravelled + 1, *i);
            }
        }

        // End case
        if (i == data.end() - 1)
        {
            // Lets see if anyone got here,
            if (sources[*i]->size() != 0)
            {
                cout << "Reachable!\n";
                return true;
            }
            else
            {
                cout << "Not Reachable!\n";
                return false;
            }
        }
    }

}

void tryTarget (int target, int source)
{
    if (sources.count(target) != 0)
    {
        cout << "Can jump from " << source << " to target " << target << "\n";
        sources[target]->insert(source); // We can reach the jump target from us
    }
}
