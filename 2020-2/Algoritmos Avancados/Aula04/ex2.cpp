#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

char field[3][3];
bool solution_found;
vector<char> steps;
vector<char> solution_steps;

int nr_of_inversions(int f[9]) {
    int result = 0;

    for (int i = 0; i < 9; i++) {
        for (int j = i+1; j < 9; j++) {
            if (f[i] == 0 || f[j] == 0)
                continue;

            if (f[i] > f[j])
                result++;
        }
    }

    return result;
}

bool is_solvable(char field[3][3]) {
    int f[9];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (field[i][j] == 'x')
                f[i*3+j] = 0;
            else
                f[i*3+j] = field[i][j] - '0';
        }
    }

    // field width is odd so the nr of
    // inversions should be even for the
    // puzzle to be solvable
    return nr_of_inversions(f) % 2 == 0;
}

pair<int,int> find_pos(char field[3][3], char c) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (field[i][j] == c)
                return make_pair(i, j);
        }
    }
    return make_pair(0,0);
}

// Manhattan distance
int heuristic(char field[3][3]) {
    static char f[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','0'}};
    int result = 0;

    for (int i = 1; i < 9; i++) {
        char c = i + '0';

        pair<int,int> pos1 = find_pos(field, c);
        pair<int,int> pos2 = find_pos(f, c);

        result += abs(pos1.first - pos2.first);
        result += abs(pos1.second - pos2.second);
    }

    return result;
}

bool is_goal_reached() {
    static char f[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', 'x'}};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (field[i][j] != f[i][j])
                return false;
        }
    }

    return true;
}

void find_solution(int limit, char prev_move) {
    if (is_goal_reached()) {
        solution_found = true;
        solution_steps = steps;
        return;
    }

    pair<int,int> blank = find_pos(field, 'x');

    // up
    if (blank.first > 0 && prev_move != 'd') {
        swap(field[blank.first][blank.second], field[blank.first-1][blank.second]);

        int h = heuristic(field);

        if (h + steps.size() + 1 <= (long unsigned) limit && !solution_found) {
            steps.push_back('u');
            find_solution(limit, 'u');
            steps.pop_back();
        }

        swap(field[blank.first][blank.second], field[blank.first-1][blank.second]);
    }

    // down
    if (blank.first < 2 && prev_move != 'u') {
        swap(field[blank.first][blank.second], field[blank.first+1][blank.second]);

        int h = heuristic(field);

        if (h + steps.size() + 1 <= (long unsigned) limit && !solution_found) {
            steps.push_back('d');
            find_solution(limit, 'd');
            steps.pop_back();
        }

        swap(field[blank.first][blank.second], field[blank.first+1][blank.second]);
    }

    // left
    if (blank.second > 0 && prev_move != 'r') {
        swap(field[blank.first][blank.second], field[blank.first][blank.second-1]);

        int h = heuristic(field);

        if (h + steps.size() + 1 <= (long unsigned) limit && !solution_found) {
            steps.push_back('l');
            find_solution(limit, 'l');
            steps.pop_back();
        }

        swap(field[blank.first][blank.second], field[blank.first][blank.second-1]);
    }

    // right
    if (blank.second < 2 && prev_move != 'l') {
        swap(field[blank.first][blank.second], field[blank.first][blank.second+1]);

        int h = heuristic(field);

        if (h + steps.size() + 1 <= (long unsigned) limit && !solution_found) {
            steps.push_back('r');
            find_solution(limit, 'r');
            steps.pop_back();
        }

        swap(field[blank.first][blank.second], field[blank.first][blank.second+1]);
    }
}

int main(void) {
    int N;

    cin >> N;

    while (N--) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) 
                cin >> field[i][j];

        if (!is_solvable(field)) {
            cout << "unsolvable" << endl;
            if (N)
                cout << endl;
            continue;
        }

        int h = heuristic(field);
        solution_found = false;
        steps.clear();

        while (true) {
            find_solution(h, ' ');

            if (solution_found) {
                for (long unsigned i = 0; i < solution_steps.size(); i++)
                    cout << solution_steps[i];
                
                cout << endl;
                break;
            } else {
                h += 10;
            }
        }

        if (N)
            cout << endl;
    }

    return 0;
}
