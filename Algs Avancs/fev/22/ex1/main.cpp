#include <iostream>

using namespace std;

bool isValid(string s) {
    int depth = 0;
    for (auto c = s.begin(); c != s.end(); c++) {
        if (*c == '(') depth++;
        else if (*c == ')') depth--;
    
        if (depth < 0) return false;
    }
    return depth == 0;
}

int main(int argc, char const *argv[])
{
    string s;
    cin >> s;
    cout << (isValid(s) ? "YES" : "NO") << endl;

    return 0;
}