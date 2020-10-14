#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct marriage {
    int target, idx;
};


bool map_has(const map<int, marriage>& _map, int key) {
    return _map.find(key) != _map.end();
}

int get_index(const vector<int>& vec, int item) {
    for (unsigned i = 1; i < vec.size(); i++)
        if (vec[i] == item) return i;
    return -1;
    
}

int n;
vector<vector<int>> womanPrefs;
vector<vector<int>> manPrefs;

map<int, marriage> womanMarriages;
map<int, marriage> manMarriages;

void marry_no_update(int m, int w, int m2wIdx) {
    int w2mIdx = get_index(womanPrefs[w], m);
    manMarriages[m] = {w, m2wIdx};
    womanMarriages[w] = {m, w2mIdx};
}

//Assuming those two would like to marry
void marry(int m, int w, int m2wIdx) {
    if (map_has(manMarriages, m)) { //if man is married
        int divorcedW = manMarriages[m].target;
        womanMarriages.erase(divorcedW);
    }

    if (map_has(womanMarriages, w)) { //if target woman is married
        int divorcedW = manMarriages[m].target;
        womanMarriages.erase(divorcedW);
    }

    marry_no_update(m, w, m2wIdx);
}

bool want_to_marry(int m, int w, int m2wIdx) {
    bool isManMarried = map_has(manMarriages, m);
    bool isWomanMarried = map_has(womanMarriages, w);

    bool mWants = !isManMarried || m2wIdx < manMarriages[m].idx;

    if (!mWants) return false;
    int w2mIdx = get_index(womanPrefs[w], m);

    bool wWants = !isWomanMarried || w2mIdx < womanMarriages[w].idx;

    return wWants; //wWants and mWants (if above forces AND)
}

void marry_all() {
    for (int m = 1; m <= n; m++)
    {
        int wIdx = 1, targetW = -1; //Tries best woman

        do {
            targetW = manPrefs[m][wIdx];

            //TODO: remove debug
            if (wIdx >= n) exit(666);
        } while (!want_to_marry(m, targetW, wIdx++));
        
        marry(m, targetW, wIdx);
    }
}

void print_marriages() {
    for (int m = 1; m <= n; m++)
    {
        //TODO: remove debug
        if (!map_has(manMarriages, m)) exit(55);

        printf("%d %d\n", m, manMarriages[m].target);
    }   
}

int main(int argc, char const *argv[])
{   
    int t, inp;
    cin >> t;

    for (int i = 0; i < t; i++)
    {
        womanMarriages.clear();
        manMarriages.clear();

        womanPrefs.clear();
        manPrefs.clear();

        //0 unused indexes
        womanPrefs.push_back(vector<int>());
        manPrefs.push_back(vector<int>());

        cin >> n;
        for (int j = 1; j <= n; j++)
        {
            cin >> inp;
            womanPrefs.push_back(vector<int>());
            womanPrefs[j].push_back(-1); //unused
            for (int k = 0; k < n; k++)
            {
                cin >> inp;
                womanPrefs[j].push_back(inp);
            }            
        }
        for (int j = 1; j <= n; j++)
        {
            cin >> inp;
            manPrefs.push_back(vector<int>());
            manPrefs[j].push_back(-1); //unused
            for (int k = 0; k < n; k++)
            {
                cin >> inp;
                manPrefs[j].push_back(inp);
            }
        }

        marry_all();
        print_marriages();
    }
    
    return 0;
}
