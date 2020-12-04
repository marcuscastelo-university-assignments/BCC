#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> from;
vector<int> to;
int n;

vector<int> pd;

int _hash(int fi, int ti) {
    return (fi + 1) * n + (ti + 1);
}

int solve(int fi, int ti) {
    if (fi < 0) return ti + 1;
    if (ti < 0) return fi + 1;

    int hash = _hash(fi, ti);
    if (pd[hash] != -1) return pd[hash];

    int cost;

    if (from[fi] == to[ti]) { //Nothing needs to be done
        cost = solve(fi - 1, ti - 1);
    } else {
        int insertion = solve(fi, ti - 1);
        int deletion = solve(fi - 1, ti);
        cost = 1 + min(insertion, deletion); //insertion or deletion
    }

    pd[hash] = cost;
    return cost;
    
}

int main(int argc, char const *argv[])
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        int inp;
        cin >> n;
        from.clear();
        to.clear();
        from.reserve(n);
        to.reserve(n);

        pd.clear();
        pd.assign((n+1)*n + 1, -1);

        for (int i = 0; i < n; i++) {
            cin >> inp;
            from.push_back(inp);
        }
        for (int i = 0; i < n; i++) {
            cin >> inp;
            to.push_back(inp);
        }
        cout << "Case " << t << ": " << solve(n-1, n-1) << endl;
        
    }
    return 0;
}
