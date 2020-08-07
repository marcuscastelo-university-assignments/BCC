#include <iostream>
#include <unordered_map>

using namespace std;

int digits[4];
int target[4];

bool visited[4][10];

unordered_map<string,bool> forbidden;
bool digitHasForbiddenNum[4][10];

string sequenceToStr(int sequence[]) {
    return 
        to_string(sequence[0]) 
        + to_string(sequence[1]) 
        + to_string(sequence[2]) 
        + to_string(sequence[3]);
}

void turnLeft(int pos) {
    digits[pos] = (10+digits[pos]-1) % 10;
}

void turnRight(int pos) {
    digits[pos] = (digits[pos]+1) % 10;
}

int minMoves = 20e4;

bool isSequenceForbidden() {
    string seq = sequenceToStr(digits);
    return forbidden[seq];
}

bool isSequenceTarget() {
    for (int i = 0; i < 4; i++)
        if (digits[i] != target[i]) return false;
    return true;    
}

void visit(int pos) {
    visited[pos][digits[pos]] = true;
}

void unvisit(int pos) {
    visited[pos][digits[pos]] = false;
}

bool isVisited(int pos) {
    return visited[pos][digits[pos]];
}

bool backtrack(int moves);

bool hasSomeForbidden(int pos, int from, int to) {
    if (from == to) {
        cout << "@hasSomeForbidden: NÃO PODE CHAMAR SENDO IGUAL";
        int a = 1/0;
    }
    bool someForbidden = false;
    for (int testNum = from+1; testNum != to; testNum = (testNum+1)%10)
    {
        if (digitHasForbiddenNum[pos][testNum]) {
            someForbidden = true;
            break;
        }
    }
    return someForbidden;
}

enum Direction {
    NONE_OK = 0, RIGHT_OK = 1, LEFT_OK = 2, STAY_OK = 4
};

Direction &operator|=(Direction &a, const Direction &b) {
    return a = (Direction)((int)a|(int)b);
}

Direction &operator|=(Direction &a, const int &b) {
    return a = (Direction)((int)a|b);
}

Direction direction[4];
bool backtrack(int moves) {
    if (isSequenceTarget()) {
        if (moves < minMoves) minMoves = moves;
        return true;
    }

    for (int i = 0; i < 4; i++)
    {
        
    }

    return false;
}

void setupPossibilities() {
    for (int pos = 0; pos < 4; pos++)
    {
        int targNum = target[pos];
        int currNum = digits[pos];
        
        direction[pos] = NONE_OK;

        if (targNum == currNum) {
            if (!digitHasForbiddenNum[pos][targNum]) {
                direction[pos] |= STAY_OK;
            }
        }

        if (!hasSomeForbidden(pos, currNum, targNum)) {
            direction[pos] |= RIGHT_OK;
        }

        if (!hasSomeForbidden(pos, targNum, currNum)) {
            direction[pos] |= LEFT_OK;
        }
    }
}

bool basicChecks() {
    if (forbidden[sequenceToStr(digits)]) return false;
    if (forbidden[sequenceToStr(target)]) return false;
    return true;
}

int main(int argc, char const *argv[])
{
    int n, N;
    cin >> N;
    for (int i = 0; i < 4; i++) cin >> digits[i]; //Si
    for (int i = 0; i < 4; i++) cin >> target[i]; //Ti
    cin >> n;
    string forbStr = "";
    int forbNum;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cin >> forbNum;   
            forbStr += to_string(forbNum);
            digitHasForbiddenNum[j][forbNum] = true;
        }
        forbidden[forbStr] = true;
        forbStr = ""; 
    }
    
    bool hasSolution = false;
    if (basicChecks() == true) {
        setupPossibilities();
        cout << "Calling backtrack" << endl;
        hasSolution |= backtrack(0, 0);
    } else cout << "Failed on basics" << endl;
    cout << "HasSolution: " << hasSolution << endl;
    cout << "Result: " << minMoves << endl;

    return 0;
}
