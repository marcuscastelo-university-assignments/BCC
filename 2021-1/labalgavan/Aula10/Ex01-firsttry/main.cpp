#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 0x7FFFFFFF;

struct Road
{
    int to;
    int cost;
    int ID = -1;
    bool operator<(const Road &other) const { return cost < other.cost; }
};

struct Path {
    vector<Road> roads = {};
    int cost = 0;
    int to = INF;

    bool operator<(const Road &other) const { return cost < other.cost; }
    Path operator+(Road& road) const {
        Path other = *this;
        other.cost += road.cost;
        other.roads.push_back(road);
        other.to = road.to;
        return other;
    }
};

using AdjVec = vector<Road>;
vector<AdjVec> cityRoads;


Path* minElement(vector<Path*> &vec, vector<bool> &blacklist)
{
    Path* minElem = new Path{{},INF,INF};
    for (size_t i = 0; i < vec.size(); i++)
        if (vec[i] != nullptr && !blacklist[i] && vec[i]->cost < minElem->cost)
            minElem = vec[i];
    return minElem;
}

int n, m;
vector<Path*> dijkstra(int from)
{
    vector<Path*> paths(n + 1, nullptr);
    vector<bool> visited(n + 1);

    paths[from] = new Path;
    paths[from]->to = from;
    paths[from]->cost = 0;

    for (int i = 0; i < n; i++)
    {
        Path *path = minElement(paths, visited);
        if (path->to == INF) { 
            break; 
            } //Desconexo (impossível)
        
        int u = path->to;
        visited[u] = true;

        for (Road& road : cityRoads[u]) {
            if (visited[road.to]) continue;

            if (paths[road.to] == nullptr || path->cost + road.cost < paths[road.to]->cost) {
                paths[road.to] = new Path(*path + road);
            }
        }
    }

    return paths;
}

int main(int argc, char const *argv[])
{
    cin >> n >> m;

    cityRoads = vector<AdjVec>(n + 1);

    int a, b, c;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> c;
        cityRoads[a].push_back({b, c, i});
        cityRoads[b].push_back({a, c, i});
    }

    auto pathsFrom1 = dijkstra(1);


    return 0;
}
