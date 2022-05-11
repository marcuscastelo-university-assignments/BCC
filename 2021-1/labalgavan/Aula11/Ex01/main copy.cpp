#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
const int INF = 0x7FFFFFFF;

struct Travel {
    int to, len;
    bool operator<(const Travel& other) const { return len < other.len; }
};

using AdjVec = vector<Travel>;

int findMin(const vector<int> &distances, const vector<bool> &blacklist)
{
    int min = INF;
    int min_i = -1;
    for (size_t i = 0; i < distances.size(); i++)
        if (!blacklist[i] && distances[i] < min)
            min = distances[i], min_i = i;
    return min_i;
}

vector<int> dijkstra(int from, const vector<AdjVec> &graph)
{
    vector<int> distances(n + 1, INF);
    vector<bool> visited(n + 1, false);

    distances[1] = 0;
    for (int i = 0; i < n; i++)
    {
        int u = findMin(distances, visited);
        if (u == -1) {
            cout << "aaaa" << endl;
            break;
        }

        int d = distances[u];
        visited[u] = true;

        for (auto &e : graph[u])
        {
            if (d + e.len < distances[e.to])
                distances[e.to] = d + e.len;
        }
    }

    return distances;
}

int main(int argc, char const *argv[])
{
    cin >> n >> m;
    vector<AdjVec> graph(n + 1);
    int u, v, l;
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> l;
        graph[u].push_back({v, l});
    }

    auto dists = dijkstra(1, graph);
    for (int i = 1; i < (int)dists.size(); i++)
        cout << dists[i] << " ";
    cout << endl;

    return 0;
}
