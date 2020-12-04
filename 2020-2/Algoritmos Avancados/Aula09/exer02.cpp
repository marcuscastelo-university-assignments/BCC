#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

string from;
string to;
int n;

vector<int> pd;

int _hash(int fi, int ti) {
    return (fi + 1) * n + (ti + 1);
}

int calcSingleCost(char c) {
    return c - 'a' + 1;
}

int calcSubstCost(char from, char to) {
    return abs(to - from);
}

int calcRemainingLettersCost(const string& vec, int i) {
    int sum = 0;
    while (i >= 0) sum += calcSingleCost(vec[i--]);
    return sum;
}

int solve(int fi, int ti) {
    int hash = _hash(fi, ti);
    if (pd[hash] != -1) return pd[hash];

    int cost;

    if (fi < 0) cost = calcRemainingLettersCost(to, ti);
    else if (ti < 0) cost = calcRemainingLettersCost(from, fi);
    else {
        int costAfterBothSlided = solve(fi - 1, ti - 1);

        if (from[fi] == to[ti]) { //Nothing needs to be done
            cost = costAfterBothSlided; //just ignoring is the same as substitution but with local cost 0 
        } else {

            int insertionCost = calcSingleCost(to[ti]);
            int deletionCost = calcSingleCost(from[fi]);
            int subsitionCost = calcSubstCost(from[fi], to[ti]);

            int costAfterInsertion = solve(fi, ti - 1);
            int costAfterDeletion = solve(fi - 1, ti);

            cost = min(min(insertionCost + costAfterInsertion, 
                    deletionCost + costAfterDeletion),
                    subsitionCost + costAfterBothSlided); //insertion or deletion
        }
    }

    pd[hash] = cost;
    return cost;
    
}

int main(int argc, char const *argv[])
{
    cin >> from >> to;
    n = max(from.size(), to.size());

    pd.assign(n*n + n + 1, -1);

    cout << solve(from.size()-1, to.size()-1) << endl;
        
    return 0;
}
