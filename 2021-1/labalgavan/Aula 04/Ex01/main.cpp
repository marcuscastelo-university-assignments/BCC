#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 12;
const int MAX_X = 100;

vector<int> list_def(MAX_N+1, 0);
vector<int> frequency_def(MAX_X+1, 0);

vector<int> list(MAX_N+1, 0);
vector<int> frequency(MAX_X+1, 0);
struct sum {
    int value;
    vector<int> history;
};

void operator+=(vector<sum>& a, const vector<sum> &b) {
    a.insert(a.end(), b.begin(), b.end());
}

ostream& operator<<(ostream& s, const vector<int>& vec) {
    if (vec.size() > 0)
        s << vec[0];
    for (size_t i = 1; i < vec.size(); i++)
        s << "+" << vec[i];    

    return s;
}

int n, t;
vector<sum> rec(int i, sum currentSum) {
    int remaining = t - currentSum.value;
    if (remaining == 0) return { currentSum };
    if (remaining < 0) throw 20;

    int dig = list[i];
    if (dig == 0) return { currentSum }; //Useless sums below this

    vector<sum> possibleSums;
    if (remaining > 0) { 
        if (remaining - dig >= 0 && frequency[dig] > 0) {
            frequency[dig]--;

            sum deeperSum = currentSum;
            deeperSum.value += dig;
            deeperSum.history.push_back(dig);

            possibleSums += rec(i, deeperSum);
            frequency[dig]++;
        }

        for (int j = i+1; j < n; j++)
        {
            int deeperDig = list[j];
            if (deeperDig == 0) break;

            if (remaining - deeperDig < 0) continue;
            if (frequency[deeperDig] == 0) continue;

            frequency[deeperDig]--;

            sum deeperSum = currentSum;
            deeperSum.value += deeperDig;
            deeperSum.history.push_back(deeperDig);
            possibleSums += rec(j, deeperSum);

            frequency[deeperDig]++;
        }
    }

    return possibleSums;
}

void testcase() {
    list = list_def;
    frequency = frequency_def;
    
    int tmp;
    int k = 0;
    for (int i = 0; i < n; i++) {
        cin >> tmp;

        if (frequency[tmp] == 0)
            list[k++] = tmp;

        frequency[tmp]++;
    }
    n = k;

    cout << "Sums of " << t << ":" << endl;

    vector<sum> sums;
    for (int i = 0; i < n; i++)
    {
        int dig = list[i];
        if (dig == 0) break; //Ignore 0 sums
        if (dig > t) continue;

        frequency[dig]--;
        sums += rec(i, {dig, {dig}});
        frequency[dig]++;
    }
    
    if (sums.empty()) cout << "NONE" << endl;
    else for (auto& s: sums) {
        cout << s.history;
        cout << endl;
    }
}

int main(int argc, char const *argv[])
{
    while (true)
    {
        cin >> t >> n;
        if (n == 0) break;

        testcase();
    }
    
    return 0;
}
