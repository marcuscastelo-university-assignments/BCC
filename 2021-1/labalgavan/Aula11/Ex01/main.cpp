#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#include <limits>

using big = unsigned long long int;

using namespace std;

big n, m;
const big INF = numeric_limits<big>::max();

struct Travel {
    big to, len;
    bool operator<(const Travel& other) const { return len < other.len; }
};

using AdjVec = vector<Travel>;

big findMin(const vector<big> &distances, const vector<bool> &blacklist)
{
    big min = INF;
    big min_i = INF;
    for (size_t i = 0; i < distances.size(); i++)
        if (!blacklist[i] && distances[i] < min)
            min = distances[i], min_i = i;
    return min_i;
}

vector<big> dijkstra(big from, const vector<AdjVec> &graph)
{
    vector<big> distances(n + 1, INF);

    distances[1] = 0;

    priority_queue<pair<long long,big>> toVisit;

    toVisit.push({-0,1});
    while (!toVisit.empty())
    {
        big u = toVisit.top().second;
        toVisit.pop();

        if (u == INF) {
            cout << "aaaa" << endl;
            break;
        }
        big d = distances[u];

        for (auto &e : graph[u])
        {
            if (d + e.len < distances[e.to]) {
                distances[e.to] = d + e.len;
                toVisit.push({-distances[e.to], e.to});
            }
        }
    }

    return distances;
}

int main(int argc, char const *argv[])
{
    cin >> n >> m;
    vector<AdjVec> graph(n + 1);
    big u, v, l;
    for (big i = 0; i < m; i++)
    {
        cin >> u >> v >> l;
        graph[u].push_back({v, l});
    }

    auto dists = dijkstra(1, graph);
    for (big i = 1; i < (big)dists.size(); i++)
        cout << dists[i] << " ";
    cout << endl;

    return 0;
}
