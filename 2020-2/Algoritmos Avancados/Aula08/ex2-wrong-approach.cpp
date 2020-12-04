#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <algorithm>

const int MAX_N = 20;

using namespace std;

vector<int> weights;
int n;

typedef int SumBitmask;
typedef unordered_map<int, unordered_set<SumBitmask>> SumIndiciesMap;

struct State {
    int index;
    int usedIndiciesBitmask;

    State generateNext(int newUsedIndiciesBitmask) const {
        newUsedIndiciesBitmask |= (1 << index);

        int newIndex = index + 1;
        while (( (1 << newIndex) & newUsedIndiciesBitmask ) != 0) newIndex++;
        return {newIndex, usedIndiciesBitmask | newUsedIndiciesBitmask};
    }

    const bool operator<(const State& other) const {
        return index < other.index;
    }
};

unordered_set<SumBitmask> calcPossibleSumCombinationsOf(int fromIndex, int accumSum, int desiredSum, int forbiddenBitMask) {
    int innerSum = 0;
    unordered_set<SumBitmask> possibleCombinations;

    int iBitmask = 0;
    for (int i = fromIndex; i < (int) weights.size(); i++)
    {
        iBitmask = (1 << i);
        if ((iBitmask & forbiddenBitMask) != 0) continue;
        innerSum = accumSum + weights[i];

        if (innerSum > desiredSum) continue;
        if (innerSum == desiredSum) {
            possibleCombinations.insert(iBitmask);
        }

        else {
            unordered_set<SumBitmask> innerResults = calcPossibleSumCombinationsOf(i+1, innerSum, desiredSum, forbiddenBitMask | iBitmask);
            for (auto it = innerResults.begin(); it != innerResults.end(); it++)
            {
                possibleCombinations.insert(*it | iBitmask);
            }
        }
    }
        
    return possibleCombinations;
}

const unordered_set<SumBitmask>& getPossibleSumCombination(const State& currentState, int desiredSum, SumIndiciesMap& dpSumCombinations) {
    unordered_set<SumBitmask>* foundCombinations = nullptr;
    
    auto foundIt = dpSumCombinations.find(desiredSum);
    if (foundIt == dpSumCombinations.end()) {
        dpSumCombinations[desiredSum] = calcPossibleSumCombinationsOf(currentState.index + 1, 0, desiredSum, currentState.usedIndiciesBitmask);
        foundCombinations = &dpSumCombinations[desiredSum];
        
    } else foundCombinations = &foundIt->second;
    return *foundCombinations;
}

bool solve() {
    static int usedAllIndiciesBitmask = (1 << weights.size()) - 1;
    SumIndiciesMap dpSumCombinations;
    priority_queue<State> statesToExplore;
    statesToExplore.push({0, 0});

    while (!statesToExplore.empty())
    {
        State currentState = statesToExplore.top();
        statesToExplore.pop();

        if (currentState.usedIndiciesBitmask >= usedAllIndiciesBitmask) {
            return true;
        }

        int currentIndex = currentState.index;
        int currentIndexBitmask = (1 << currentIndex);
        int desiredSum = weights[currentIndex];

        const unordered_set<SumBitmask>& possibleSumCombinations = getPossibleSumCombination(currentState, desiredSum, dpSumCombinations);
        
        for (auto sumIt = possibleSumCombinations.begin(); sumIt != possibleSumCombinations.end(); sumIt++)
        {
            if ((*sumIt & currentIndexBitmask) != 0) continue;
            if ((*sumIt & currentState.usedIndiciesBitmask) != 0) continue;

            statesToExplore.push(currentState.generateNext(*sumIt));
        }
        
    }
    
    return false;

}

string bitmaskAsSum(int bitmask) {
    int sum = 0;
    stringstream ss;
    
    for (int i = 0; i < (int) weights.size(); i++)
    {
        int partial = ( (1 << i) & bitmask );
        if (partial != 0) {
            sum += weights[i];
            ss << weights[i] << " + ";
        }
    }    

    ss << " = " << sum << endl;
    return ss.str();
}

void printBitmaskAsSum(int bitmask) {
    cout << bitmaskAsSum(bitmask);
}

int main(int argc, char const *argv[])
{
    int m;
    cin >> m;
    while (getchar() != '\n');
    while (m--)
    {
        int num;
        string line;
        
        getline(cin, line);
        stringstream ss;
        ss << line;

        weights.clear();
        while (ss >> num)
            weights.push_back(num);
        n = weights.size();

        sort(weights.begin(), weights.end(), greater<int>());

        

        // auto p = calcPossibleSumCombinationsOf(0, 0, 10, 0);
        // for (auto it = p.begin(); it != p.end(); it++)
        // {
        //     printBitmaskAsSum(*it);
        // }    
        
        bool r = solve();       
        cout << (r?"YES":"NO") << endl; 
    }
    
    return 0;
}
