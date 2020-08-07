#include <iostream>

#include <string.h>

using namespace std;

#define MAX_N 100
#define MAX_M 1000
#define MAX_WORD_S 256

int n, m;
int currentRuleSize = 0;

char dict[MAX_WORD_S+1][MAX_N];

char currentPass[(MAX_WORD_S+1) * (MAX_WORD_S+1)];

void backtrack(char *rule, int k) {
    if (k >= currentRuleSize) {
        cout << currentPass << endl;
        return;
    }

    int len = strlen(currentPass);

    if (rule[k] == '0') {
        for (int i = 0; i <= 9; i++) {
            char s[] = {(char)((int)'0'+i),0};
            strcat(currentPass, s);
            backtrack(rule, k+1);   
            currentPass[len] = 0;
        }
    } else {
        for (int i = 0; i < n; i++) {
            char *word = dict[i];
            strcat(currentPass, word);
            backtrack(rule, k+1);
            currentPass[len] = 0;
        }
    }
}

int main(int argc, char const *argv[])
{
    //Start string size 0
    currentPass[0] = 0;


    char rule[256+1];

    while (cin >> n) {
        cout << "--" << endl;

        for (int i = 0; i < n; i++) cin >> dict[i];

        cin >> m;
        for (int i = 0; i < m; i++) {
            cin >> rule;
            currentRuleSize = strlen(rule);
            backtrack(rule, 0);
        }
    }


    return 0;
}
