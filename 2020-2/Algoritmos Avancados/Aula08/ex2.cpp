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

int calcVecSum() {
    int sum = 0;
    for (int i = 0; i < (int) weights.size(); i++)
        sum += weights[i];
    return sum;    
}

struct State {
    int index, accumSum;
    bool operator<(const State& other) const {
        return accumSum < other.accumSum;
    }
};

bool isThereAnySubsequenceThatSums(int desiredSum) {
    priority_queue<State> states;
    int firstI = 0;
    states.push({firstI, 0});
    
    while (!states.empty())
    {
        State s = states.top();
        states.pop();

        
        if (s.accumSum == desiredSum) return true;

        if (s.index >= (int) weights.size()) continue; //Stop creating states if reached vector end
        
        states.push({s.index+1, s.accumSum});
        
        if (s.accumSum + weights[s.index] <= desiredSum)
            states.push({s.index+1, s.accumSum + weights[s.index]});
    }

    return false;   
}

bool solve() {
    int weightsSum = calcVecSum();
    if (weightsSum % 2 == 1) return false;
    int sideSum = weightsSum / 2;

    return isThereAnySubsequenceThatSums(sideSum);    
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
        
        bool r = solve();       
        cout << (r?"YES":"NO") << endl; 
    }
    
    return 0;
}