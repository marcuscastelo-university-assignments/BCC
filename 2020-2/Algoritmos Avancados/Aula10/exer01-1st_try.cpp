#include <string>
#include <vector>
#include <iostream>

using namespace std;

string txt;
string pat;
vector<int> lps;
void makeLPS() {
    int n = (int)pat.size();
    int j = 0, i = 1;
    lps.reserve(n);
    lps.assign(n, -1);

    lps[0] = 0;
    while (i < n) {
        if (pat[i++] != pat[j++]) {
            j = lps[j-1];
            if (j > 0) i--; //If not zero yet, try again for extended pattern
        } else lps[i] = j;
    }       
}

int KMP() {
    int patterns_found = 0;
    int i = 0, j = 0;
    int tl = txt.length();

    int pl = pat.length();

    for (;i < tl; i++) {
        if (txt[i] == pat[j]) {
            if (j < pl-1) j++;
            else if (j == pl - 1) patterns_found++;
            else j = lps[j-1];
        } else {
            if (j > 0) j = lps[j-1];
            else i++;
        }
    }
    
    return patterns_found;   
}

int solve() {
    makeLPS();
    return KMP();
}

int main(int argc, char const *argv[])
{
    cin >> txt >> pat;
    // cout << solve() << endl;
    makeLPS();

    ;

    return 0;
}
