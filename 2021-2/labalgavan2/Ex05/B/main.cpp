#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int n;
char s[131072];

void input_s() {
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
}

int calcMoves(int lo, int hi, char c) {
    int moves = 0;
    for (int i = lo; i < hi; i++) {
        if (s[i] != c) {
            moves++;
        }
    }
    return moves;
}

// Returns the number of moves required to make a c-good string.
int recur(int lo, int hi, char c) {
    if (lo == hi - 1) {
        return s[lo] == c ? 0 : 1;
    }

    int mid = lo + (hi - lo) / 2;

    int movesLeftC = calcMoves(lo, mid, c);
    int movesRightC = calcMoves(mid, hi, c);

    int movesLeftR = recur(lo, mid, c + 1);
    int movesRightR = recur(mid, hi, c + 1);

    return min(movesLeftC + movesRightR, movesLeftR + movesRightC);
}

int solve() {
   return recur(0, n, 'a');
}

void testcase() 
{
    cin >> n;
    input_s();
    cout << solve() << endl;
}

int main(int argc, char const *argv[])
{
    int t;
    cin >> t;
    while (t-->0)
        testcase();

    return 0;
}
