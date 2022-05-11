#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int end;

struct Road
{
    int to;
    int cost;
    bool operator<(const Road &other) const { return cost < other.cost; }
};

using AdjVec = vector<Road>;

vector<AdjVec> cityRoads;

const int INF = 0x7FFFFFFF;

int minElement(vector<int> &vec, vector<bool> &blacklist)
{
    int min = INF;
    for (size_t i = 0; i < vec.size(); i++)
        if (!blacklist[i] && vec[i] < min)
            min = vec[i];
    return min;
}

int n, m;
vector<bool> dijkstra(int from)
{
    vector<int> distances(n + 1, INF);
    vector<bool> visited(n + 1);

    distances[from] = 0;
    for (int i = 0; i < n; i++)
    {
        int u = minElement(distances, visited);
        if (u == INF) { __asm__("int 3"); break; }
        visited[u] = true;

        int d = distances[u];
        if (d == INF)
            continue;

        for (Road& road : cityRoads[u]) {
            if (visited[road.to]) continue;
            distances[road.to] = min(distances[road.to], d + road.cost);

        }
    }

    return visited;
}

int main(int argc, char const *argv[])
{
    cin >> n >> m;

    cityRoads = vector<AdjVec>(n + 1);

    int a, b, c;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> c;
        cityRoads[a].push_back({b, c});
        cityRoads[b].push_back({a, c});
    }

    return 0;
}
