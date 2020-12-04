#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct State {
    int current_value;
    int used_coins;

public:
    State subtract(int value) const{
        return {this->current_value - value, this->used_coins + 1};
    }
};

bool isPossible(int value, const vector<int>& coins) {
    return true;
}

int solve(const State& state, const vector<int>& coins, unordered_map<int, int>& dp) {

    if (dp.find(state.current_value) != dp.end()) 
        return dp[state.current_value];

    if (state.current_value == 0) {
        return state.used_coins;
    }

    int min_moves = 0x7FFFFFFF, temp;
    for (int i = 0; i < (int) coins.size(); i++)
    {
        if (coins[i] <= state.current_value) {
            temp = solve(state.subtract(coins[i]), coins, dp);
            min_moves = min(temp, min_moves);
        }
    }
    
    dp[state.current_value] = min_moves;
    return min_moves;
}

int solve(const vector<int>& coins, int value) {
    if (value % 2 == 1) {
        bool possible = false;
        for (int i = 0; i < (int)coins.size(); i++)
            if (coins[i] % 2 == 1) { possible = true; break; }
        if (!possible) return 0x7FFFFFFF;
    }
    unordered_map<int, int> dp;
    return solve({value, 0}, coins, dp);
}

int main(int argc, char const *argv[])
{
    int n, value, q, inp;
    cin >> n;
    vector<int> coins;

    while (n-- > 0)
    {
        cin >> value;
        cin >> q;

        coins.clear();
        coins.reserve(q);

        while (q-- > 0) {
            cin >> inp;
            coins.push_back(inp);
        } 

        sort(coins.begin(), coins.end(), greater<int>());

        int res = solve(coins, value);
        if (res == 0x7FFFFFFF) cout << "sem solucao" << endl;
        else cout << res << endl;        
    }
    

    return 0;
}
