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
        return W <= other.W && S > other.S;
    }
};

vector<Elephant> elephants;

bool f(int a, int b)
{
    return elephants[a].W < elephants[b].W && elephants[a].S > elephants[b].S;
}

int main(int argc, char const *argv[])
{

    //Input
    {
        int tmpW, tmpS;
        while (cin >> tmpS >> tmpW)
            elephants.insert(lower_bound(elephants.begin(), elephants.end(), Elephant{tmpW, tmpS}, std::less<Elephant>()), {tmpW, tmpS});
    }

    //Solve
    {
        vector<int> dp;
        dp = vector<int>(elephants.size(), -1);

        //P(0) = 1
        dp[0] = 1;

        int maxDP = 0;

        for (size_t i = 1; i < elephants.size(); i++)
        {
            int bestPastDP = 0;
            for (size_t j = 0; j < i; j++)
                if (f(j, i))
                    bestPastDP = max(bestPastDP, dp[j]);
            int lis_i = dp[i] = 1 + bestPastDP;
            maxDP = max(lis_i, maxDP);
        }

        cout << maxDP << endl;
    }

    return 0;
}
