#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;
static int __tabs = -1;

using CoinComb = vector<int>;

template <>
struct std::hash<CoinComb>
{
    size_t operator()(const CoinComb &comb) const
    {
        size_t finalHash = 0;
        for (auto &item : comb)
            finalHash ^= hash<int>()(item);
        return finalHash;
    }
};

int N, X;
vector<int> coins;

template <typename T>
void dbg_printvec(const vector<T> &vec)
{
    cout << "{ ";
    for (auto &item : vec)
    {
        cout << item << " ";
    }
    cout << "}" << endl;
}

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

unordered_set<CoinComb> backtrack(int x)
{
    if (x == 0)
        return {{}}; //backtrack(0) != empty = {{}}.  i.e. one solution with no coins

    __tabs++;
    dbg_ptabs();
    cout << ":::backtrack(" << x << "):::" << endl;

    unordered_set<CoinComb> possibleWays;

    for (auto coin : coins)
    {
        int innerX = x - coin;
        if (innerX >= 0)
        {
            auto innerCombs = backtrack(innerX);
            if (innerCombs.size() == 0)
                continue; //This innerX is not possible backtrack(innerX) = empty

            for (auto &innerComb : innerCombs)
            {
                auto icCopy = innerComb;
                dbg_ptabs();
                cout << "coin=" << coin << "; backtrack(" << innerX << ") partial: ";
                addCoin(coin, icCopy);
                dbg_printvec(icCopy);
                possibleWays.insert(icCopy);
            }
        }
        else
            break;
    }

    dbg_ptabs();
    cout << "===backtrack(" << x << ")=== --> " << possibleWays.size() << " combinations" << endl;
    __tabs--;
    return possibleWays;
}

int solve(int x)
{
    return backtrack(x).size();
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

    cout << solve(X) << endl;
    return 0;
}