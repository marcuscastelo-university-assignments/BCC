#include <iostream>
#include <unordered_map>

using namespace std;

int digits[4];
int target[4];

unordered_map<int,bool> forbidden;

int sequenceToSum(int sequence[]) {
    int sum = 0;
    int mul = 1;
    for (int j = 3; j >= 0; j--)
    {
        mul = 1;
        for (int k = 0; k < j; k++) mul *= 10;            
        sum += mul * sequence[3-j];
    }
    return sum;
}

void turnLeft(int pos) {
    digits[pos] = (10+digits[pos]-1) % 10;
}

void turnRight(int pos) {
    digits[pos] = (digits[pos]+1) % 10;
}

int minMoves = 20e4;

bool isSequenceForbidden() {
    int sum = sequenceToSum(digits);
    return forbidden[sum];
}

bool isSequenceTarget() {
    for (int i = 0; i < 4; i++)
        if (digits[i] != target[i]) return false;
    return true;    
}

bool backtrack(int moves, int posMoved, int direction) {
    if (moves > minMoves) return false;
    if (isSequenceForbidden()) return false;
    if (isSequenceTarget()) {
        if (moves < minMoves) minMoves = moves;
        return true;
    }

    bool hasSolution = false;

    for (int pos = 0; pos < 4; pos++)
    {
        if (posMoved != pos) {
            turnRight(pos);
            hasSolution |= backtrack(moves+1, pos, 1);
            turnLeft(pos);

            hasSolution |= backtrack(moves, -1, 0);

            turnLeft(pos);
            hasSolution |= backtrack(moves+1, pos, -1);
            turnRight(pos);
        } else {
            if (direction != 1) {
                turnRight(pos);
                hasSolution |= backtrack(moves+1, pos, 1);
                turnLeft(pos);
            }
            backtrack(moves, -1, 0);
            if (direction != -1) {
                turnLeft(pos);
                hasSolution |= backtrack(moves+1, pos, -1);
                turnRight(pos);
            }
        }
    }
    return hasSolution;    
}

bool basicChecks() {
    if (forbidden[sequenceToSum(digits)]) return false;
    if (forbidden[sequenceToSum(target)]) return false;
    return true;
}

int main(int argc, char const *argv[])
{
//     isForbidden[6056] = true;
//     cout << isForbidden[56] << endl;
//     return 0;
    int n, N;
    cin >> N;
    for (int i = 0; i < 4; i++) cin >> digits[i]; //Si
    for (int i = 0; i < 4; i++) cin >> target[i]; //Ti
    cin >> n;
    int forbSum = 0, forbDig, mul;
    for (int i = 0; i < n; i++)
    {
        for (int j = 3; j >= 0; j--)
        {
            mul = 1;
            for (int k = 0; k < j; k++) mul *= 10;            
            cin >> forbDig;   
            forbSum += mul * forbDig;
        }
        forbidden[forbSum] = true;
        forbSum = 0; 
    }
    
    bool hasSolution = false;
    if (basicChecks() == true) {
        cout << "Calling backtrack" << endl;
        hasSolution |= backtrack(0, -1, 0);
    } else cout << "Failed on basics" << endl;
    cout << "HasSolution: " << hasSolution << endl;
    cout << "Result: " << minMoves << endl;

    return 0;
}
