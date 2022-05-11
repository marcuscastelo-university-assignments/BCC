#include <iostream>
#include <vector>

using namespace std;

int n, r;
vector<string> words, rules;

void rec(const string& rule, string prefix, int ci) {
    if ((size_t)ci >= rule.length()){
        cout << prefix << endl;
        return;
    }

    char c = rule[ci];
    if (c == '0') {
        for (int i = 0; i <=9; i++)
            rec(rule, prefix+to_string(i), ci+1);  
    }
    else {
        for (auto& word : words) {
            rec(rule, prefix+word, ci+1);
        }
    }
}

void testcase() {
    string tmp;
    words.clear();
    words.reserve(n);
    for (int i = 0; i < n; i++){
        cin >> tmp;
        words.push_back(tmp);    
    }

    cin >> r;
    rules.clear();
    rules.reserve(r);
    for (int i = 0; i < r; i++)
    {
        cin >> tmp;
        rules.push_back(tmp);
    }
    
    cout << "--" << endl;
    for (auto& rule: rules) {
        rec(rule, "", 0);
    }    

}

int main(int argc, char const *argv[])
{
    while(cin >> n) testcase();


    return 0;
}
