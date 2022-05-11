#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define LEN(x) (x.length())
#define text (*text_p)
#define pattern (*pattern_p)

string *text_p, *pattern_p;

vector<int> generate_lps() {
    //LPS is a intermediate vector that stores the "already-granted" prefix at the current position 
    vector<int> lps;    
    unsigned pattern_length = LEN(pattern);

    unsigned len = 0;
    lps.assign(pattern_length, 0); //lps[0] is always 0; the others will be replaced

    #define j len
    for (unsigned i = 1; i < pattern_length; i++)
    {
        if (pattern[i] == pattern[j]) {
            len++;
            lps[i] = len;
        } else {
            if (len > 0) { //Try to match with previous lps
                len = lps[j-1];
                i--;
            } else { //Not able to match with above trials
                lps[i] = len; //At this point len is 0
            }
        }
    }
    #undef j

    return lps;
}

vector<unsigned> match_patterns_kmp(unsigned max_matches_until_return = (unsigned)(-1)) {
    vector<unsigned> matches;
    vector<int> lps = generate_lps();

    unsigned i = 0, j = 0; //Text and Pattern indexes
    while (i < LEN(text) && matches.size() < max_matches_until_return)
    {
        if (pattern[j] == text[i]) {
            i++; j++;
        } 

        if (j == LEN(pattern)) {
            matches.push_back(i-j);
            j = lps[j-1];
        } else if (i < LEN(text) && pattern[j] != text[i]) { 
            // Do not match lps[0..lps[j-1]] characters, 
            // they will match anyway 
            if (j != 0) 
                j = lps[j - 1]; 
            else
                i++;
        } 
    }
    return matches;
}

//For the enourmous input in just one line, I really don't know any buffer size that would fit (not even vscode could count how much characters there was in the line, just like this big line I'm writing right now. I don't know why I'm still here. Btw, spotify ads are anoying as hell, maybe I'll pay for premium membership IDK)
string *improved_getline() {
    char *str;
    scanf("%m[^\r\n]", &str);
    char c;
    do { c = getchar(); } while (c != '\n' && c != EOF);
    return new string(str);    
}

int main(int argc, char const *argv[])
{   

    text_p = improved_getline();
    pattern_p = improved_getline();



    auto matches = match_patterns_kmp();
    if (matches.size() > 0)
        for (auto match: matches)
            cout << "O padrao foi encontrado na posicao " << match << endl;
    else
        cout << "O padrao nao foi encontrado" << endl;
    return 0;
}
