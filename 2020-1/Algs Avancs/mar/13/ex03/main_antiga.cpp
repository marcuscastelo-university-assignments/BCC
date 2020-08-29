#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

#define MAX_N 50
int n;

int maxK = 0;

vector<int> ballsPeg[MAX_N];

bool isPlaceable(int k, int at) {
    if (ballsPeg[at].empty()) return true;
    double r = sqrt(ballsPeg[at].front() + k);
    return (r == (int)r);
}

void backtrack(int k) {
    cout << maxK << endl;
    bool end = true;
    for (int i = 0; i < n; i++)
    {
        if (isPlaceable(k, i)) {
            end = false;
            ballsPeg[i].push_back(k);
            backtrack(k+1);
            ballsPeg[i].pop_back();
        }
    }

    if (end) {
        if (k > maxK)
            maxK = k;
    }
    
}

void clearPegs() {
    for (int i = 0; i < n; i++) ballsPeg[i].clear();
}

int main(int argc, char const *argv[])
{
    int t;

    cin >> t;

    for (int i = 0; i < t; i++)
    {
        cin >> n;
        backtrack(1);
        clearPegs();
    }
    

    return 0;
}
