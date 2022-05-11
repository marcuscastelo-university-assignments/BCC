#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

using namespace std;

#define MAX_N 600
#define MAX_K 300

int N, K;
int points[MAX_N + 2];


bool __testRec(int P, int i, int k)
{
    if (k > K + 1 || i >= N + 2)
        return false;

    if (i == N + 1)
    {
        if (k == K + 1) return true;
        return false;
    }

    for (int j = i + 1; j < N + 1; j++)
    {
        if (points[j] - points[i] < P) 
            if (__testRec(P, j, k + 1)) {
                return true;
            }
    }
        
    return false;
}

bool test(int P)
{
    return __testRec(P, 0, 0);
}

int bb(int a, int b)
{
    if (a == b)
        return test(a) ? a : -1;

    int p = (b + a) / 2;

    bool pworks = test(p);
    if (pworks)
    {
        int lp = bb(a, p - 1);
        bool lpworks = lp != -1;
        return lpworks ? lp : p;
    }
    else
        return bb(p + 1, b);
}

void solve()
{
    int minCost = bb(0, points[N + 1]);
    if (minCost == -1)
    {
        cout << "This shouldn't happen, no P was found..." << endl;
    }
    else
        cout << minCost << endl;
}

void initialize()
{
    cin >> N >> K;

    points[0] = 0;
    int accumDist = 0;
    int tmp;
    for (int i = 1; i < N + 2; i++)
    {
        cin >> tmp;
        accumDist += tmp;
        points[i] = accumDist;
    }
}

int main(int argc, char const *argv[])
{
    initialize();
    solve();
}
