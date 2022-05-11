#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>

using ll = long long;
using namespace std;

int N;
ll X;
vector<ll> coins;
ll dp[1000001];

void solve()
{
    dp[0] = 1; 

    // c = { 1 }
    // { 2 3 5 }
    // dp[0] = 0
    // dp[1] = 0
    // dp[2] = 1                := 2
    // dp[3] = 1                := 3
    // dp[4] = 2                := 2 + 2
    // dp[5] = 2 + 2 + 1 = 5    := 2 + 3, 3 + 2, 5


    // { 1 }
    // dp[0] = 0 := null
    // dp[1] = 1 := 1
    // dp[2] = 2 := 1 + 1
    // dp[3] = 3 := 1 + 1 + 1


    for (ll x = 1; x <= X; x++)
    {
        for (int i = 0; i < N; i++)
        {
            ll ci = coins[i];
            if (ci > x) continue;
            
            dp[x] = (dp[x] + dp[x-ci]) % 1000000007;
        }
    }

    cout << dp[X] % 1000000007 << endl;
}

int main(int argc, char const *argv[])
{

    cin >> N >> X;
    ll tmp;
    for (int i = 0; i < N; i++)
    {
        cin >> tmp;
        // auto insit = upper_bound(coins.begin(), coins.end(), tmp);
        // coins.insert(insit, tmp);
        coins.push_back(tmp);
    }

    solve();

    return 0;
}
