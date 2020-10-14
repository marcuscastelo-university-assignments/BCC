#include <iostream>
#include <unordered_map>
#include <math.h>

using namespace std;

unordered_map<long, bool> forbidden;

int curr[4];
int start[4];
int target[4];

long hashn(int *vec) {
    return
        10000 +
        vec[0] * 1000 +
        vec[1] * 100 + 
        vec[2] * 10 + 
        vec[3];
}

bool is_forbidden(int *vec) {
    return forbidden[hashn(vec)];
}

void set_forbidden(int *vec, bool b) {
    forbidden[hashn(vec)] = b;
}

int delta_calc(int c, int t) {
    int loop_left = abs( (t-10) - c ) % 10;
    int loop_right = abs( (t+10) - c) % 10;
    int no_loop = abs(t - c);

    if (loop_left <= loop_right && loop_left <= no_loop) return -1;
    if (loop_right <= loop_left && loop_right <= no_loop) return 1;
    if (t > c) return 1; else return -1;
}
int solve(int moves);
int inner_solve(int i, int delta, int moves) {
    int bkp = curr[i], ret = -1;
    curr[i] = (curr[i] + delta) % 10;
    if (!is_forbidden(curr) && curr[i] != start[i])
        ret = solve(moves + 1);
    curr[i] = bkp;

    return ret;
}

int solve(int moves) {
    int ret = -2;

    if (moves > 100) return -1;

    for (int i = 0; i < 4; i++)
    {
        if (curr[i] == target[i]) continue;
        int delta = delta_calc(curr[i], target[i]);
        ret = inner_solve(i, delta, moves);
        if (ret != -1) return ret;
        ret = inner_solve(i, -delta, moves);
        if (ret != -1) return ret;
    }

    if (ret == -2) return moves;
    return -1;
}

int main(int argc, char const *argv[])
{
    int n;
    cin >> n;    

    for (int k = 0; k < n; k++)
    {   
        forbidden.clear();

        for (int i = 0; i < 4; i++){
            cin >> curr[i];
            start[i] = curr[i];
        }
        for (int i = 0; i < 4; i++)
            cin >> target[i];
        int qtd_forb, temp_forb[4];
        cin >> qtd_forb;
        for (int j = 0; j < qtd_forb; j++)
        {
            for (int i = 0; i < 4; i++)
                cin >> temp_forb[i]; 
            
            set_forbidden(temp_forb, true);
        }

        solve(0);
    }
    

    return 0;
}
