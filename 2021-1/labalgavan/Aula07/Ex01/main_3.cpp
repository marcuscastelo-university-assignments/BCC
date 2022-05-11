#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <stdio.h>

#define __marucs_debug 1
#define D(x) {if (__marucs_debug){x fflush(stdout);}}

using namespace std;
static int __tabs = -1;

int N, X;
vector<int> coins;

void dbg_ptabs()
{
    for (int i = 0; i < __tabs; i++)
        cout << "\t";
}

void addCoin(int coin, vector<int> &coins)
{
    auto insit = lower_bound(coins.begin(), coins.end(), coin, less<int>());

    coins.insert(insit, coin);
}

int binarySearch(int l, int r, int c, int x)
{
    int best = -1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        // Check if x is present at mid
        if (m * c == x)
            return m;
        // If x greater, ignore left half
        if (m * c < x){
                best = m;
            l = m + 1;
        }
        // If x is smaller, ignore right half
        else {
            if (best == -1)
            best = m;
            r = m - 1;
        }
    }
 
    // if we reach here, then element was
    // not present
    return best;
}

int backtrack(int i, int x) {
    if (x == 0) return 1;
    if (x < 0) return 0;
    if (i == N) return 0;
    
    __tabs++;
    
    int ciMaxCoef = binarySearch(0, x/coins[i], coins[i], x);
    int ci = coins[i];

    dbg_ptabs();
    cout << ":::backtrack(i=" << i <<", x=" << x << ")::: mcic * ci == " << ciMaxCoef << " * " << ci << " == " << ciMaxCoef * ci << endl;

    int sum = 0, tmp;
    for (int cic = ciMaxCoef; cic >= 0; cic--)
    {
        if (x - (cic * ci) < 0) break;
        dbg_ptabs();
        std::cout << "Trying cic=" << cic << endl;
        tmp = backtrack(i+1, x - cic * ci);
        dbg_ptabs();
        std::cout << "Backtrack of cic=" << cic << " result (partial) = " << tmp << endl;
        sum += tmp;
    }

    __tabs--;
    return sum;
}

int main(int argc, char const *argv[])
{
    int tmp;
    cin >> N >> X;
    for (int i = 0; i < N; i++)
    {
        cin >> tmp;
        addCoin(tmp, coins);
    }

    cout << backtrack(0, X) << endl;
    return 0;
}
