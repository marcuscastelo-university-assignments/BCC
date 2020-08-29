#include <iostream>
#include <unordered_map>

using namespace std;

int digits[4];
int target[4];

bool visited[4][10];

unordered_map<string,bool> forbidden;

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

bool backtrackRight(int pos, int moves) {
    bool hasSolution = false;
    turnRight(pos);
    if (!isVisited(pos)) {
        visit(pos);
        hasSolution |= backtrack(moves+1);
        unvisit(pos);
    }
    turnLeft(pos);
    return hasSolution;
}

bool backtrackLeft(int pos, int moves) {
    bool hasSolution = false;
    turnLeft(pos);
    if (!isVisited(pos)) {
        visit(pos);
        hasSolution |= backtrack(moves+1);
        unvisit(pos);
    }
    turnRight(pos);
    return hasSolution;
}

bool backtrack(int moves) {
    if (moves > minMoves) {
        // cout << "Maior que inf" << endl;
        return false;
    }
    if (isSequenceForbidden()) {
        // cout << "Sequencia é proibida, ignorando" << endl;
        return false;
    }
    if (isSequenceTarget()) {
        if (moves < minMoves) minMoves = moves;
        return true;
    }

    bool hasSolution = false;

    for (int pos = 0; pos < 4; pos++)
    {
        hasSolution |= backtrackLeft (pos, moves);
        hasSolution |= backtrackRight(pos, moves);
    }
    return hasSolution;    
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
    int forbDig;
    for (int i = 0; i < n; i++)
    {
        for (int j = 3; j >= 0; j--)
        {
            cin >> forbDig;   
            forbStr += to_string(forbDig);
        }
        forbidden[forbStr] = true;
        forbStr = ""; 
    }
    
    bool hasSolution = false;
    if (basicChecks() == true) {
        cout << "Calling backtrack" << endl;
        hasSolution |= backtrack(0);
    } else cout << "Failed on basics" << endl;
    cout << "HasSolution: " << hasSolution << endl;
    cout << "Result: " << minMoves << endl;

    return 0;
}
