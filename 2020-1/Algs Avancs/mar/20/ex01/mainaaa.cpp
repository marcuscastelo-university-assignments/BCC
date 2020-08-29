#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct sequence {
    int digits[4];
};

sequence currentSequence;
sequence targetSequence;

vector<sequence> forbiddenSequencesPerDigNum[4][10];

int minMoves = 20e4;

bool isCurrSeqTarget() {
    for (int i = 0; i < 4; i++)
        if (currentSequence.digits[i] != targetSequence.digits[i]) return false;
    return true;
}

bool __pathBlocked[10];
bool *getBlockedPaths(int endPos) {
    for (int i = 0; i < 10; i++)
        __pathBlocked[i] = false;
    

    for (int pos = 0; pos <= endPos; pos++)
    {
        int posNum = currentSequence.digits[pos];
        auto sequences = &forbiddenSequencesPerDigNum[pos][posNum];
        for (auto it = sequences->begin(); it != sequences->end(); it++)
            __pathBlocked[it->digits[endPos]] = true;            
    }

    return __pathBlocked;
}

bool contains(bool *blockedPaths, int number) {
    for (int i = 0; i < 10; i++)
        if (blockedPaths[i] == number) return true;
    return false;
}

int calcTravelPossibleLength(bool *blockedPaths, int from, int to) {
    bool hasProblems1 = false;
    int count1 = 0;
    for (int i = from; i != to; i = (i+1)%10)
    {
        if (blockedPaths[i]) {
            hasProblems1 = true;
            break;
        }
        count1++;
    }

    bool hasProblems2 = false;
    int count2 = 0;
    for (int i = from; i != to; i = (10+i-1)%10)
    {
         if (blockedPaths[i]) {
            hasProblems2 = true;
            break;
        }
        count2++;
    }
    
    if (hasProblems1 && hasProblems2) return -1;
    if (hasProblems1) return count2;
    if (hasProblems2) return count1;
    return (count1<count2)?count1:count2;    
}

bool backtrack(int pos, int moves) {
    if (pos >= 4) {
        if (isCurrSeqTarget()) {
            if (minMoves < moves) minMoves = moves;
            return true;
        }
        return false;
    }

    bool hasSolution = false;

    hasSolution |= backtrack(pos+1, moves);
    bool *blockedNumbers = getBlockedPaths(pos);

    int currDig = currentSequence.digits[pos];
    for (int newDig = 0; newDig < 10; newDig++)
    {
        if (currDig == newDig) continue;
        if (contains(blockedNumbers, newDig)) continue;

        int pathLen = calcTravelPossibleLength(blockedNumbers, currDig, newDig);
        if (pathLen != -1) {
            currentSequence.digits[pos] = newDig;
            hasSolution |= backtrack(pos+1, moves+pathLen);
        }
    }
    return hasSolution;
}

int main(int argc, char const *argv[])
{
    int n, N;
    cin >> N;
    for (int i = 0; i < 4; i++) cin >> currentSequence.digits[i]; //Si
    for (int i = 0; i < 4; i++) cin >> targetSequence.digits[i]; //Ti
    cin >> n;
    int forbNum;
    sequence forbSeq;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cin >> forbNum;
            forbSeq.digits[j] = forbNum;
        }
        
        for (int j = 0; j < 4; j++)
        {
            int num = forbSeq.digits[j];
            forbiddenSequencesPerDigNum[j][num].push_back(forbSeq);
        }
    }
        
    
        bool hasSolution = false;
        cout << "Calling backtrack" << endl;
        hasSolution |= backtrack(0, 0);
        cout << "HasSolution: " << hasSolution << endl;
        cout << "Result: " << minMoves << endl;

    return 0;
}
