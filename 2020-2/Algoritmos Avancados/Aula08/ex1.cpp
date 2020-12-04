#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Doll {
    int h, w;
    bool operator<(const Doll& other) const {
        return w < other.w || (w == other.w && h >= other.h);
    }

    bool fitsIn(const Doll& other) const {
        return w < other.w && h < other.h;
    }
};

vector<Doll> dolls;
vector<bool> explored;

int solve(int from) {
    int paths = 0;

    for (int base = 0; base < (int) dolls.size(); base++)
    {
        if (explored[base]) continue;
        for (int curr = base; curr < (int) dolls.size();)
        {
            if (explored[curr]) break;

            explored[curr] = true;
            for (int next = curr+1; next < (int) dolls.size(); next++)
            {
                if (explored[next]) continue;
                if (dolls[curr].fitsIn(dolls[next])) {
                    curr = next;
                    break;
                }
            }   
        }
        paths++;
    }
        

    return paths;
}

int main(int argc, char const *argv[])
{
    int t, m;
    cin >> t;

    Doll tmpDoll;
    while (t--) {
        cin >> m;

        dolls.clear();
        dolls.reserve(m);
        explored.clear();
        explored.reserve(m);

        while (m--) {
            cin >> tmpDoll.w >> tmpDoll.h;
            dolls.push_back(tmpDoll);
            explored.push_back(false);
        }

        sort(dolls.begin(), dolls.end());    

        int r = solve(0);
        cout << r << endl;
    }
    return 0;
}
