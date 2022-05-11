#include <iostream>
#include <vector>
using namespace std;

#define CHECKER_SIZE 10

enum class Piece
{
    None = 0,
    White,
    Black,
    WhiteEmpty,
    BlackEmpty
};

Piece board[CHECKER_SIZE][CHECKER_SIZE] = {};
vector<pair<int, int>> validPiecePositions;

void clearBoard()
{
    for (int i = 0; i < CHECKER_SIZE; i++)
    {
        for (int j = 0; j < CHECKER_SIZE; j++)
        {
            board[i][j] = Piece::None;
        }
    }
    validPiecePositions.clear();
}

void inputBoard()
{
    char positionPieceChar;
    for (int i = 0; i < CHECKER_SIZE; i++)
    {
        for (int j = 0; j < CHECKER_SIZE; j++)
        {
            cin >> positionPieceChar;
            if (positionPieceChar == 'W')
            {
                board[i][j] = Piece::White;
                validPiecePositions.push_back(make_pair(i, j));
            }
            else if (positionPieceChar == 'B')
            {
                board[i][j] = Piece::Black;
                validPiecePositions.push_back(make_pair(i, j));
            }
            else if (positionPieceChar == '#')
            {
                board[i][j] = Piece::BlackEmpty;
            }
            else if (positionPieceChar == '.')
            {
                board[i][j] = Piece::WhiteEmpty;
            }
        }
    }
}

bool canCapture(int x1, int y1, int dx, int dy)
{

    int x2 = x1 + dx;
    int y2 = y1 + dy;

    int x3 = x2 + dx;
    int y3 = y2 + dy;

    if (x2 < 0 || x2 >= CHECKER_SIZE || y2 < 0 || y2 >= CHECKER_SIZE)
    {
        return false;
    }

    if (x3 < 0 || x3 >= CHECKER_SIZE || y3 < 0 || y3 >= CHECKER_SIZE)
    {
        return false;
    }

    if (board[x1][y1] == Piece::White)
    {
        return board[x2][y2] == Piece::Black && (board[x3][y3] == Piece::WhiteEmpty || board[x3][y3] == Piece::BlackEmpty);
    }

    else if (board[x1][y1] == Piece::Black)
    {
        return board[x2][y2] == Piece::White && (board[x3][y3] == Piece::BlackEmpty || board[x3][y3] == Piece::WhiteEmpty);
    }

    else
    {
        // cout << "Invalid piece at " << x1 << ", " << y1 << endl;
        // for (int i = 0; i < CHECKER_SIZE; i++)
        // {
        //     for (int j = 0; j < CHECKER_SIZE; j++)
        //     {
        //         cout << (int)board[i][j] << " ";
        //     }
        //     cout << endl;
        // }

        return false;
    }

    cout << "ERROR: This code should be unreacheable" << endl;
    throw logic_error("This code should be unreacheable");
}

int _tab = 0;
int getMaxCapturesForPosition(int row, int col)
{
    int maxCaptures = 0;
    _tab++;

    // for (int i = 0; i < _tab; i++)
    // {
    //     cout << " ";
    // }
    // cout << "Enter ( " << row << ", " << col << " ) " << endl;

    const static int dxs[4] = {-1, -1, 1, 1};
    const static int dys[4] = {-1, 1, -1, 1};

    for (int i = 0; i < 4; i++)
    {
        int dx = dxs[i];
        int dy = dys[i];

        // If can capture, analyze the next position
        if (canCapture(row, col, dx, dy))
        {
            int landingX = row + 2 * dx;
            int landingY = col + 2 * dy;

            int captureX = row + dx;
            int captureY = col + dy;

            Piece landingPiece = board[landingX][landingY];
            Piece capturePiece = board[captureX][captureY];
            Piece currentPiece = board[row][col];

            board[landingX][landingY] = currentPiece;
            if (currentPiece == Piece::White)
            {
                board[row][col] = Piece::WhiteEmpty;
            }
            else if (currentPiece == Piece::Black)
            {
                board[row][col] = Piece::BlackEmpty;
            }
            else
            {
                cout << "GETMAX: Invalid current piece at " << row << ", " << col << endl;
                return 0;
            }

            if (capturePiece == Piece::White)
            {
                board[captureX][captureY] = Piece::WhiteEmpty;
            }
            else if (capturePiece == Piece::Black)
            {
                board[captureX][captureY] = Piece::BlackEmpty;
            }
            else
            {
                cout << "GETMAX: Invalid captured piece at " << row << ", " << col << endl;
                return 0;
            }

            maxCaptures = max(maxCaptures, 1 + getMaxCapturesForPosition(landingX, landingY));

            board[row][col] = currentPiece;
            board[captureX][captureY] = capturePiece;
            board[landingX][landingY] = landingPiece;
        }
    }

    // for (int i = 0; i < _tab; i++)
    // {
    //     cout << " ";
    // }
    // cout << "( " << row << ", " << col << " ) : " << maxCaptures << endl;

    _tab--;
    return maxCaptures;
}

int getMaxCaptures()
{
    int maxCaptures = 0;
    for (auto &position : validPiecePositions)
    {
        maxCaptures = max(maxCaptures, getMaxCapturesForPosition(position.first, position.second));
    }
    return maxCaptures;
}

void testCase()
{
    inputBoard();
    cout << getMaxCaptures() << endl;
}

int main(int argc, char const *argv[])
{

    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        testCase();
    }

    return 0;
}
