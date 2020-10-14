#include <iostream>
#include <sstream>
#include <vector>
#include <string.h>
#include <math.h>

using namespace std;

#define MAX_C 5
#define MAX_S 10
#define MAX_CAP 2

int g_set = 0;
int C, S;
int SMasses[MAX_S];
vector<int> chamberUsage[MAX_C];
string g_output = "";

double calc_score() {
    double avg = 0;
    double chamberMasses[MAX_C];
    memset(chamberMasses, 0.0, sizeof(double) * MAX_C);
    for (int c = 0; c < C; c++)
        for (auto it = chamberUsage[c].begin(); it != chamberUsage[c].end(); it++)
        {
            avg += SMasses[*it];
            chamberMasses[c] += SMasses[*it];
        }

    avg /= C;
    double score = 0;

    for (int c = 0; c < C; c++)
        score += abs(chamberMasses[c] - avg);
    
    return score;
}

void update_output(double score) {
    stringstream ss;
    ss << "Set #" << g_set << endl;
    for (int c = 0; c < C; c++)
    {
        ss << " " << c << ": ";
        for (auto it = chamberUsage[c].begin(); it != chamberUsage[c].end(); it++)
            ss << SMasses[*it] << " ";
        ss << endl;        
    }
    ss << "IMBALANCE = " << score << endl;
    g_output = ss.str();
}

double best_score = 10000.0;
void trigger_check_for_best() {
    double score = calc_score();
    if (score < best_score) {
        best_score = score;
        update_output(score);
    }
}

void backtrack(int i) {
    if (i >= S) {
        trigger_check_for_best();
        return;
    }

    for (int c = 0; c < C; c++)
    {
        if (chamberUsage[c].size() >= MAX_CAP) continue;
        chamberUsage[c].push_back(i);
        backtrack(i + 1);
        chamberUsage[c].pop_back();
    }
}

void backtrack_init() {
    best_score = 10000;
    for (size_t i = 0; i < MAX_C; i++)
        chamberUsage[i].clear();
    
    backtrack(0);
}

int main(int argc, char const *argv[])
{
    while (cin >> C) {
        g_set++;
        cin >> S;
        for (int i = 0; i < S; i++)
            cin >> SMasses[i];        
        backtrack_init();
        cout << g_output;
    }
    return 0;
}
