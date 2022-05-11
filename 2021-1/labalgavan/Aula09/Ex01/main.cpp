#include <iostream>
#include <vector>

using namespace std;

const unsigned INF = 0x7FFFFFFF;

int main(int argc, char const *argv[])
{
    unsigned n, m;
    cin >> n >> m;

    vector<unsigned> dp(n+1, INF);

    vector<vector<unsigned>> connections(n+1);
    for (unsigned c = 0; c < m; c++)
    {
        unsigned a, b;
        cin >> a >> b;
        if (a==b) continue;
        if (a > b) {
            //Swap
            a = a + b;
            b = a - b;
            a = a - b;
        }
        connections[a].push_back(b);
    }
    
    dp[1] = 1;
    for (unsigned a = 1; a < n; a++)
        for (auto b : connections[a]) 
            dp[b] = min(dp[b], dp[a] + 1);

    if (dp[n] == INF) cout << "IMPOSSIBLE" << endl;
    else cout << dp[n] << endl;

    return 0;
}
