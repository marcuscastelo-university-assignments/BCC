#include <iostream>
#include <unordered_set>
#include <math.h>
#include <queue>

using namespace std;

class Combination
{
    int d[4], depth;

    public:
        Combination(int d[4], int depth){
            for (int i = 0; i < 4; i++)
                this->d[i] = d[i];

            this->depth = depth;
        }

        Combination(const Combination &other) {
            for (int i = 0; i < 4; i++)
                this->d[i] = other.d[i];

            this->depth = other.depth;
            
        }

        Combination(const Combination &other, int depth_delta) {
            for (int i = 0; i < 4; i++)
                this->d[i] = other.d[i];
            
            this->depth = other.depth + depth_delta;
        }


        static Combination prompt() {
            int d[4];
            for (int i = 0; i < 4; i++)
                cin >> d[i];
            return Combination(d, 0);            
        }

        Combination turned(int pos, int delta) const {
            Combination c = Combination(*this, +1);
            c.d[pos] = (10 + c.d[pos] + delta) % 10;
            return c;
        }

        Combination copy() const {
            return Combination(*this);
        }

        void print() const {
            for (int i = 0; i < 4; i++)
                cout << d[i];
            cout << endl;            
        }

        int hash() const {
            return 
                10000 +
                1000 * d[0] +
                100 * d[1] +
                10 * d[2] +
                d[3];
        }

        friend int heuristic(const Combination& curr, const Combination &target);

        bool operator==(const Combination& other) const {
            for (int i = 0; i < 4; i++)
                if (d[i] != other.d[i]) return false;
            return true;
        }

        int heuristic(Combination& target) const {
            int difference = 0;
            for (int i = 0; i < 4; i++)
                difference += abs(this->d[i] - target.d[i]);
            return difference; 
        }

        int getDepth() const { return depth; }

};

Combination *g_target = nullptr;

bool operator<(const Combination& A, const Combination& B)  {
    return A.heuristic(*g_target) >= B.heuristic(*g_target);
}

typedef unordered_set<int> Forbidden;

bool isForbidden(Forbidden& forbidden, Combination& combination) {
    return forbidden.find(combination.hash()) != forbidden.end();
}

void fillNeighborCombinations(Forbidden& forbidden, priority_queue<Combination> &explorationQueue, const Combination& current) {
    for (int i = 0; i < 4; i++)
    {
        Combination tu = current.turned(i, +1);
        Combination td = current.turned(i, -1);
        if (!isForbidden(forbidden, tu)) explorationQueue.push(tu);
        if (!isForbidden(forbidden, td)) explorationQueue.push(td);
    }
}

int solve(priority_queue<Combination> &explorationQueue, const Combination &initial, Forbidden& forbidden) {
    explorationQueue.push(initial);

    while (!explorationQueue.empty())
    {
        const Combination current = explorationQueue.top();
        explorationQueue.pop();

        fillNeighborCombinations(forbidden, explorationQueue, current);
        
        if (current == *g_target) return current.getDepth();  

        forbidden.insert(current.hash());
    }

    return -1;
}

void testcase() {
    Combination initial = Combination::prompt();
    Combination current = initial.copy();
    Combination target = Combination::prompt();
    g_target = &target;

    int forbidden_count;
    cin >> forbidden_count;

    Forbidden forbidden;
    for (int i = 0; i < forbidden_count; i++)
    {
        Combination temp_combination = Combination::prompt();
        forbidden.insert(temp_combination.hash());
    }

    forbidden.insert(initial.hash());

    priority_queue<Combination> explorationQueue;
    int minimum_moves = solve(explorationQueue, current, forbidden);
    cout << minimum_moves << endl;
}

int main(int argc, char const *argv[])
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) testcase();
    return 0;
}
