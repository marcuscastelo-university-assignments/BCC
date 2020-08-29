#include <iostream>
#include <vector>
#include <set>

using namespace std;

#define MAX_N 12

int hi = 0;
set<vector<int>> sums;
vector<int> history;
int t, n;
bool backtrack(int vals[], int k, int sum) {

    if (k > n) return false;
    if (sum > t) return false;
    if (sum == t) {
        sums.insert(history);
        return true;
    }

    history.push_back(vals[k]);
    bool pegaPossible = backtrack(vals, k+1, sum + vals[k]); 
    history.pop_back();

    bool npegaPossible = backtrack(vals, k+1, sum);
    return pegaPossible || npegaPossible;

}

int main(int argc, char const *argv[])
{
    int vals[MAX_N];
    while (true) {
        cin >> t;
        cin >> n;
        if (n == 0) return 0;
        for (int i = 0; i < n; i++)
        {
            cin >> vals[i];
        }
        backtrack(vals, 0, 0);

        cout << "Sums of " << t << ":" << endl;
        if (sums.empty()) cout << "NONE" << endl;
        else {
            for (auto it = sums.rbegin(); it != sums.rend(); it++)
            {
                for (auto it2 = it->begin(); it2 != it->end(); it2++)
                {
                    cout << *it2;
                    if (it2+1 != it->end()) cout << "+";
                }
                cout << endl;
            }
        }

        sums.clear();
    }
    return 0;
}
