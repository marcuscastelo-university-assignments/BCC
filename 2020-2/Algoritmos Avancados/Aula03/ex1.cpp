#include <iostream>
#include <sstream>

using namespace std;

#define maxn 20

int N, n;
int durations[maxn];
int result[maxn];
int result_size = -1;

int best_sum = -1;
string best_sum_out;

string generate_output(int sum) {
    if (result_size == -1) return "Invalid state, result_size == -1";

    stringstream ss;

    for (int i = 0; i < result_size; i++)
    {
        ss << result[i] << " ";
    }

    ss << "sum:" << sum;
    return ss.str();    
}

bool backtrack(int last_picked_i, int sum, int count) {
    if (sum > N) return false;
    if (sum == N || count >= n) {
        result_size = count;
        best_sum_out = generate_output(sum);
        return true;
    }

    for (int i = last_picked_i+1; i < n; i++)
    {
        result[count] = durations[i];
        if (backtrack(i, sum + durations[i], count+1)) return true;
    }

    if (sum > best_sum) {
        result_size = count;
        best_sum_out = generate_output(sum);
        best_sum = sum;
    }

    return false;
}

void backtrack_init() {
    result_size = -1;
    best_sum = 0;
    backtrack(-1, 0, 0);
}



int main(int argc, char const *argv[])
{
    while (cin >> N)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> durations[i];
        backtrack_init();
        cout << best_sum_out << endl;
    }
    
    return 0;
}
