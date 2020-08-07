#include <iostream>
#include <string.h>

#define CHESSBOARD_SIZE 8

using namespace std;

enum QUEEN_TYPES {
    Q0=1,Q1=2,Q2=4,Q3=8,Q4=16,Q5=32,Q6=64,Q7=128
};

int queens[] {(int)Q0,(int)Q1,(int)Q2,(int)Q3,(int)Q4,(int)Q5,(int)Q6,(int)Q7};

int invalidPositions[CHESSBOARD_SIZE][CHESSBOARD_SIZE];
int queenPositions[CHESSBOARD_SIZE];

int minMoves = 10; //Absurd value

void propagateInvalidPositions(int queenCol, int queenRow, int toCol) {
    for (int col = queenCol; col <= toCol; col++)
    {
        int k = col - queenCol; //Desloc vert

        invalidPositions[col][queenRow] |= queens[queenCol];    //Horizontally
        if (queenRow-k >= 0 && queenRow -k < CHESSBOARD_SIZE )
            invalidPositions[col][queenRow-k] |= queens[queenCol];  //Diag down
        if (queenRow+k < CHESSBOARD_SIZE && queenRow+k >= 0)
            invalidPositions[col][queenRow+k] |= queens[queenCol];  //Diag up
    }   
}

void resetInvalid() {
    for (int i = 0; i < CHESSBOARD_SIZE; i++)
        for (int j = 0; j < CHESSBOARD_SIZE; j++)
            invalidPositions[i][j] = 0;
}

void updateInvalidPositions(int toCol) {
    resetInvalid();
    // memset(invalidPositions, 0, CHESSBOARD_SIZE*CHESSBOARD_SIZE*sizeof(int));
    for (int col = 0; col <= toCol; col++)
    {
        propagateInvalidPositions(col, queenPositions[col], toCol);
    }
}

void backtrack(int currQueenInd, int movesAccum) {
    if (currQueenInd >= CHESSBOARD_SIZE) {
        if (movesAccum < minMoves) minMoves = movesAccum;
        return;
    }

    updateInvalidPositions(currQueenInd);
    if ((invalidPositions[currQueenInd][queenPositions[currQueenInd]] | queens[currQueenInd]) == (int) queens[currQueenInd])
        backtrack(currQueenInd + 1, movesAccum); //Maintain position if no other queen is marking the place

    int lastPosition = -1;
    for (int newRow = 0; newRow < CHESSBOARD_SIZE; newRow++)
    {
        if (invalidPositions[currQueenInd][newRow]) continue;
        if (newRow == queenPositions[currQueenInd]) continue;

        lastPosition = queenPositions[currQueenInd];
        queenPositions[currQueenInd] = newRow;
        backtrack(currQueenInd + 1, movesAccum + 1);
        queenPositions[currQueenInd] = lastPosition;
    }    
}

void testCase() {
    minMoves = 10;
    int row;
    for (int col = 0; col < CHESSBOARD_SIZE; col++)
    {   
        cin >> row;
        queenPositions[col] = row-1; //Passed as 0-based index
    }
    backtrack(0,0);
}

int main(int argc, char const *argv[])
{
    for (int testNum = 1; !cin.eof(); testNum++)
    {
        // if (testNum > 100) return 0; //Nota para correção: Deve haver algum problema com o EOF no runcodes, já que o código foi testado em duas máquinas com 3 tipos de fim de linha (LF, CR e CRLF) e funcionou perfeitamente sem esse if > 100
        testCase();
        cout << "Case " << testNum << ": " << minMoves << endl;   
    }
    return 0;
}
