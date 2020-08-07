#include <iostream>
#include <math.h>

#define MAX_N 50
int peg[MAX_N] = {0,};

bool checkSquare(int n) {
    int s = (int)sqrt(n);
    return (s)*(s)==n;
}

int usedPegs;
int N;
int maxNum = 0;
void backtrack(int currNum) {
    // std::cout << "i'm alive: " << maxNum << std::endl;
    if (currNum > maxNum) maxNum = currNum;

    int nextNum = currNum+1;
    for (int i = 0; i < usedPegs; i++)
    {
        if (peg[i] == 0 || checkSquare(peg[i]+nextNum)) {
            int bkp = peg[i];
            peg[i] = nextNum;
            backtrack(nextNum);
            peg[i] = bkp;
            // break;
        }
    }

    if (usedPegs < N) {
        peg[usedPegs] = nextNum;
        usedPegs++;
        backtrack(nextNum);
    } 
}

void testCase() {
    maxNum = 0;
    usedPegs = 1;
    peg[0]=1;
    for (int i = 0; i < MAX_N; i++) peg[i] = 0;
    std::cin >> N;
    backtrack(1);  
}

int main(int argc, char const *argv[])
{
    int T;
    std::cin >> T;
    for (int t = 0; t < T; t++) {
        testCase();
        std::cout << maxNum << std::endl;
    }
    
    return 0;
}
