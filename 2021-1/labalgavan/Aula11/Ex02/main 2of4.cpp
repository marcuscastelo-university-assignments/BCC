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

struct PqItem {
    big accumDist, biggestW, dest;
    bool operator<(const PqItem& other) const { return accumDist >= other.accumDist; }
};

pair<vector<big>, vector<big>> dijkstra(big from, const vector<AdjVec> &graph)
{
    vector<big> distances(n + 1, INF);
    vector<big> biggestWeight(n + 1, 0);

    distances[1] = 0;

    priority_queue<PqItem> toVisit;

    toVisit.push({0, 0, 1});
    while (!toVisit.empty())
    {
        auto &top = toVisit.top();
        big u = top.dest;
        big biggestWTillNow = top.biggestW;
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
                biggestWeight[e.to] = max(biggestWTillNow, e.len);
                toVisit.push({-distances[e.to], max(biggestWTillNow, e.len), e.to});
            }
        }
    }

    return {distances, biggestWeight};
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

    auto res = dijkstra(1, graph);

    auto& dists = res.first;
    auto& biggests = res.second;

    big ans = dists[n] - biggests[n] + biggests[n]/2;
    cout << ans << endl;

    return 0;
}
