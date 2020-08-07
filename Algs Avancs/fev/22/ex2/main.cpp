#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

map<int,int> teamPosition;
map<int,int> elemenTeam;

int nextTeamPos = 1;

struct node {
    unsigned team;
    queue<int> friends;
};

vector<node> teamQueue;

void dequeue() {
    node *n = &teamQueue[nextTeamPos];

    int elem = n->friends.front();
    n->friends.pop();

    if (n->friends.empty()) {
        teamPosition[n->team] = 0;
        nextTeamPos++;
    }

    cout << elem << endl;
}

void enqueue(int elem) {
    int myTeam = elemenTeam[elem];
    int myTeamPos = teamPosition[myTeam];

    if (myTeamPos == 0) { //Ninguém lá 
        node n;
        n.team = myTeam;
        n.friends.push(elem);
        teamQueue.push_back(n);
        teamPosition[myTeam] = teamQueue.size()-1;
        return;
    }

    node *n = &teamQueue[myTeamPos];
    n->friends.push(elem);
}

void processCommand(string command) {
    if (command == "STOP") return;
    if (command == "DEQUEUE") dequeue();
    else if (command == "ENQUEUE") {
        int elem;
        cin >> elem;
        enqueue(elem);
    }
}

int main(int argc, char const *argv[])
{
    //Remove index 0 for some reasons
    node _;

    int t, n, elem, scenario = 1;
    while (true) {
        teamQueue.push_back(_);
        cin >> t;

        if (t == 0) break;

        for (int i = 0; i < t; i++)
        {
            cin >> n;
            for (int u = 0; u < n; u++)
            {
                cin >> elem;
                elemenTeam[elem] = i;
            }
        }

        cout << "Scenario #" << scenario++ << endl;
        string command = "NONE";
        while (command != "STOP") {
            cin >> command;
            processCommand(command);
        }

        //Reset default values
        teamQueue.clear();
        elemenTeam.clear();
        teamPosition.clear();
        nextTeamPos = 1;
        cout << endl;

    }
    return 0;
}
