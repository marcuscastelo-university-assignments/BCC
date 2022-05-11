#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

using big = unsigned long long;
const big INF = numeric_limits<big>::max();

struct Road
{
    big to, cost;
    bool operator<(const Road &other) const { return cost >= other.cost; }
};

using AdjVec = vector<Road>;

int main(int argc, char const *argv[])
{
    big n, m;
    cin >> n >> m;
    vector<AdjVec> graph(n + 1);
    {
        big u, v, c;
        for (big i = 0; i < m; i++)
        {
            cin >> u >> v >> c;
            graph[u].push_back({v, c});
            graph[v].push_back({u, c});
        }
    }

    //Solve

    priority_queue<Road> roadsToExplore;
    vector<bool> visited(n+1);
    big visitedCount = 0;
    roadsToExplore.push({1, 0}); //Artificial road to first node.

    big totalCost = 0;

    while (!roadsToExplore.empty() && visitedCount != n)
    {
        Road r = roadsToExplore.top();
        roadsToExplore.pop();

        big u = r.to;

        //If this city already has a path to it, ignore it
        if (visited[u]) continue;

        visited[u] = true;
        visitedCount++;        
        
        //This road is the cheapest so far
        totalCost += r.cost;

        for (const Road &nextRoad: graph[u]) {
            roadsToExplore.push(nextRoad);
        }
    }

    if (visitedCount != n) cout << "IMPOSSIBLE" << endl;
    else cout << totalCost << endl;

    return 0;
}
