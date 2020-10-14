#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;

int n, solution_count = 0;
unordered_map<int, bool> forbidden; 

bool is_forbidden(int i, int j) {
    return forbidden[i*n+j];
}

void set_forbidden(int i, int j, bool b) {
    forbidden[i*n+j] = b;
}

bool is_invalid(int i, int j) {
    return i < 0 || i >= n || j < 0 || j >= n;
}

void backtrack(int i, int j) {
    if (is_forbidden(i, j) || is_invalid(i, j)) return;

    if (i == n-1 && j == n-1) {
        solution_count++;
        return;
    }

    set_forbidden(i, j, true);
        backtrack(i, j+1);
        backtrack(i, j-1);
        backtrack(i+1, j);
        backtrack(i-1, j);
    set_forbidden(i, j, false);
}

int main(int argc, char const *argv[])
{
    int wall;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> wall;
            if (wall == 1) forbidden[i*n+j] = true;
        }
    }
    backtrack(0,0);
    cout << solution_count << endl;
    
    return 0;
}
