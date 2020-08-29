#include <deque>
#include <iostream>
#include <string.h>

using namespace std;

int ND;
int lastDInd = 0;
char wordDict[100][201];
int maxDWordSize = 0;
string tempW;

deque<string> print;

bool doesWordExist(const char *word) {
    for (int i = 0; i < ND; i++)
        if (!strcmp(word, wordDict[i])) return true;
    return false;    
}

void backtrack(int start) {
    if (start > (int)tempW.size()) return;
    if (start == (int)tempW.size()) {
        for (auto it = print.begin(); it != print.end(); it++)
            std::cout << *it << " ";
        std::cout << endl;
        return;
    }
    for (int len = 1; len <= maxDWordSize; len++)
    {
        string str = tempW.substr(start, len);
        if (doesWordExist(str.c_str())) {
            print.push_back(str);
            backtrack(start+len);
            print.pop_back();
        }
    }
    
}


int main(int argc, char const *argv[])
{
    int NT;
    cin >> ND;
    for (int i = 0; i < ND; i++){
        cin >> tempW;
        strcpy(wordDict[lastDInd++], tempW.c_str());
        if ((int)tempW.size()+1 > maxDWordSize)
            maxDWordSize = (int)tempW.size()+1;
    }

    cin >> NT;
    for (int i = 0; i < NT; i++)
    {
        cin >> tempW;
        backtrack(0);
        if (i+1<NT)
            std::cout << endl;
    }
    
    
    return 0;
}
