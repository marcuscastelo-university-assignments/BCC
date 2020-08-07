#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

const int MAX_N = 1e5+1;

struct box {
    int id;
    long size;

    friend bool operator<(box const&, box const&);    
};

bool operator<(box const &a, const box &b){
    return a.size < b.size;
}

int main(int argc, char const *argv[])
{
    int totalpres, treepres, tired;
    
    //First line
    cin >> totalpres >> treepres >> tired;

    priority_queue<box> boxesUnderTree;

    vector<int> innerBoxIds[MAX_N];
    map<int, box> allBoxes;

    //Second line
    long tempSize;
    for (int i = 1; i <= totalpres; i++)
    {
        cin >> tempSize;
        allBoxes[i] = {i, tempSize};
    }

    //Third line
    long qi;
    int tempId;
    for (int i = 1; i <= totalpres; i++)
    {
        cin >> qi;
        for (int j = 0; j < qi; j++)
        {
            cin >> tempId;
            innerBoxIds[i].push_back(tempId);
        }
        
    }

    //Fourth line
    for (int i = 0; i < treepres; i++)
    {
        cin >> tempId;
        boxesUnderTree.push(allBoxes[tempId]);
    }

    //Solve

    int foundToys = 0;
    box b;
    while (!boxesUnderTree.empty() && tired-- > 0) {
        b = boxesUnderTree.top();
        boxesUnderTree.pop();

        if (innerBoxIds[b.id].empty()) foundToys++;
        else for (unsigned i = 0; i < innerBoxIds[b.id].size(); i++)
        {
            box removeme = allBoxes[innerBoxIds[b.id][i]];
            boxesUnderTree.push(removeme);
        }
        
    }
    
    cout << foundToys << endl;

    return 0;
}
