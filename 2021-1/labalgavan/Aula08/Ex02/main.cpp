#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct DPVal
{
    int i, score;
    bool operator<(const DPVal &other) const
    {
        return score < other.score;
    }
};

struct Elephant
{
    int W, S;
    bool operator<(const Elephant &other) const
    {
        return W < other.W && S > other.S;
    }
};

vector<int> dp;
vector<Elephant> elephants;

bool f(int a, int b)
{
    return elephants[a] < elephants[b];
}

int P(int i)
{
    if (dp[i] != -1)
        return dp[i];

    int maxLen = 0;
    for (int j = 0; j < (int)elephants.size(); j++)
        if (f(j, i))
            maxLen = max(P(j), maxLen);

    maxLen += 1;

    dp[i] = maxLen;
    return maxLen;
}

int main(int argc, char const *argv[])
{
    {
        int tmpW, tmpS;
        while (cin >> tmpW >> tmpS)
            elephants.push_back({tmpW, tmpS});
    }

    sort(elephants.begin(), elephants.end());

    dp = vector<int>(elephants.size(), -1);

    //P(0) = 1
    dp[0] = 1;

    int maxP = 0;
    for (size_t i = 0; i < elephants.size(); i++)
        maxP = max(maxP, P(i));

    cout << maxP << endl;

    return 0;
}
