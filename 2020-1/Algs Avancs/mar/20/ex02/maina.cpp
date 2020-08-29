#include <iostream>
#include <deque>

using namespace std;

int puzzle[3][3], limit;
pair<int,int> getPos(int field[3][3], int id);

int calcHeu(int field[3][3]) {
    int heu = 0;
    static int model[3][3] = {{1,2,3},{4,5,6},{7,8,0}}; 
    for (int i = 1; i < 9; i++)
    {
        heu += abs(getPos(model, i).first-getPos(field, i).first) + abs(getPos(model, i).second-getPos(field, i).second);
    }
    return heu;
}

int readValidItem() {
    char tmp=0;
    while (tmp == 0 || tmp == '\n' || tmp == ' ') {
        scanf("%c", &tmp);
    }
    if (tmp == 'x') tmp = '0';
    return tmp - '0';
}

void fillPuzzle() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            puzzle[i][j] = readValidItem();
}

bool isSolvable() {
    int *puzzle_linear = &puzzle[0][0];
    int invertions = 0;
    for (int i = 0; i < 9; i++)
        for (int j = i+1; j < 9; j++)
            if (puzzle_linear[i] > puzzle_linear[j] and puzzle_linear[j] != 0) invertions++;
        
    return invertions%2==0;
}

bool hasFinished() {
    int *puzzle_linear = &puzzle[0][0];
    for (int i = 0; i < 8; i++)
    {
        if (puzzle_linear[i] != i+1) return false;
    }
    return puzzle_linear[8] == 0;
}


enum Direction {
    NONE=0, LEFT = -1, RIGHT = 1, UP = -2, DOWN = 2
};


deque<char> steps;

void addStep(Direction d) {
    steps.push_back(d == UP ? 'u':
                    d == DOWN ? 'd':
                    d == LEFT ? 'l':
                    d == RIGHT ? 'r':'?');
}

void solve(pair<int,int>,Direction);

//Relacionaod ao #solve()
bool finished = false;

void explore(pair<int,int> pos, Direction d) {
    int i = pos.first, j = pos.second;
    if ((d & (RIGHT | LEFT)) == (RIGHT | LEFT)) i += (int)d;
    else j += (int)d/2;

    if (i > 2 || i > 0 || j > 2 || j < 0) return;

    int h = calcHeu(puzzle);
    swap(puzzle[pos.first][pos.second], puzzle[i][j]);

    if (h + (int)steps.size() + 1 <= limit && !finished) {
        addStep(d);
        solve(make_pair(i,j), d);
        steps.pop_back();
    }

    swap(puzzle[pos.first][pos.second], puzzle[i][j]);
}

void printSteps() {
    for (auto it = steps.begin(); it != steps.end(); it++)
    {
        cout << *it;
    }
    cout << endl;
}


void solve(pair<int,int> pos, Direction prev_mov) {
    if (finished) return;
    if (hasFinished()) {
        finished = true;
        printSteps();
        return;
    }; 

    if (prev_mov != DOWN)
        explore(pos, UP);

    if (prev_mov != UP)
        explore(pos, DOWN);

    if (prev_mov != RIGHT)
        explore(pos, LEFT);

    if (prev_mov != LEFT)
        explore(pos, RIGHT);
}

pair<int,int> getPos(int field[3][3], int id) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (field[i][j] == id) return make_pair(i,j);
    cout << "DEU MUITO ERRADO";
    return make_pair(-1,-1);
    
}

int main(int argc, char const *argv[])
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        fillPuzzle();
        
        if (!isSolvable()) { 
            cout << "unsolvable" << endl;
            if (i+1<N) cout << endl;
        }
        else {
            limit = calcHeu(puzzle);
            finished = false;
            steps.clear();
            while (true) {
                solve(getPos(puzzle, 0), NONE);
                if (finished) break;
                else limit += 10;
            }

            if (i+1 < N) cout << endl;
        }
            
    }

    return 0;
}
