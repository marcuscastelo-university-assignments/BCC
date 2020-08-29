#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

char field[3][3];
bool finished;
vector<char> steps;
vector<char> solution_steps;

bool is_solvable(char field[3][3]) {
    int f[9];

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (field[i][j] == 'x')
                f[i*3+j] = 0;
            else
                f[i*3+j] = field[i][j] - '0';
        }
    }
    
    int sum = 0;

    for (int i = 0; i < 9; i++) {
        for (int j = i+1; j < 9; j++) {
            if (f[i] == 0 || f[j] == 0)
                continue;

            if (f[i] > f[j])
                sum++;
        }
    }

    return sum % 2 == 0;
}

pair<int,int> find_pos(char field[3][3], char c) {
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (field[i][j] == c)
                return make_pair(i, j);
        }
    }   
    cout << "DEU MUITA MERDA!! ";
    return make_pair(-1,-1);
}

int calcHeu(char field[3][3]) {
    static char f[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','0'}};
    int result = 0;

    for (int i = 1; i < 9; i++) {
        char c = i + '0';

        auto pos1 = find_pos(field, c);
        auto pos2 = find_pos(f, c);

        result += abs(pos1.first - pos2.first);
        result += abs(pos1.second - pos2.second);
    }

    return result;
}

bool hasFinished() {
    static char f[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', 'x'}};

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (field[i][j] != f[i][j])
                return false;
        }
        
    }
    return true;
}

void solve(int limit, char prev_move) {
    if (hasFinished()) {
        finished = true;
        solution_steps = steps;
        return;
    }

    auto blankSpace = find_pos(field, 'x');

    // up
    if (blankSpace.first > 0 && prev_move != 'd') {
        swap(field[blankSpace.first][blankSpace.second], field[blankSpace.first-1][blankSpace.second]);

        int h = calcHeu(field);

        if (h + (int)steps.size() + 1 <= limit && !finished) {
            steps.push_back('u');
            solve(limit, 'u');
            steps.pop_back();
        }

        swap(field[blankSpace.first][blankSpace.second], field[blankSpace.first-1][blankSpace.second]);
    }

    // down
    if (blankSpace.first < 2 && prev_move != 'u') {
        swap(field[blankSpace.first][blankSpace.second], field[blankSpace.first+1][blankSpace.second]);

        int h = calcHeu(field);

        if (h + (int)steps.size() + 1 <= limit && !finished) {
            steps.push_back('d');
            solve(limit, 'd');
            steps.pop_back();
        }

        swap(field[blankSpace.first][blankSpace.second], field[blankSpace.first+1][blankSpace.second]);
    }

    // left
    if (blankSpace.second > 0 && prev_move != 'r') {
        swap(field[blankSpace.first][blankSpace.second], field[blankSpace.first][blankSpace.second-1]);

        int h = calcHeu(field);

        if (h + (int)steps.size() + 1 <= limit && !finished) {
            steps.push_back('l');
            solve(limit, 'l');
            steps.pop_back();
        }

        swap(field[blankSpace.first][blankSpace.second], field[blankSpace.first][blankSpace.second-1]);
    }

    // right
    if (blankSpace.second < 2 && prev_move != 'l') {
        swap(field[blankSpace.first][blankSpace.second], field[blankSpace.first][blankSpace.second+1]);

        int h = calcHeu(field);

        if (h + (int)steps.size() + 1 <= limit && !finished) {
            steps.push_back('r');
            solve(limit, 'r');
            steps.pop_back();
        }

        swap(field[blankSpace.first][blankSpace.second], field[blankSpace.first][blankSpace.second+1]);
    }
}

int main(void) {
    int n;

    cin >> n;

    for (int a = 0; a < n; a++) {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cin >> field[i][j];
            }
        }
        
        if (!is_solvable(field)) {
            cout << "unsolvable" << endl;
            if (n) cout << endl;
            continue;
        }

        int heu = calcHeu(field);
        finished = false;
        steps.clear();

        while (true) {
            solve(heu, ' ');

            if (!finished) {
                heu += 10;
                continue;
            }

            for (int i = 0; i < (int)solution_steps.size(); i++)
                cout << solution_steps[i];
            cout << endl;
            break;
        }

    }

    return 0;
}
