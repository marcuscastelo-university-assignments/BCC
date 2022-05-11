#include <iostream>
#include <vector>

using namespace std;

#define MAX_N 600
#define MAX_K 300

int N, K;
int distances[MAX_N + 1];

int groups[MAX_K + 1];

struct Walk
{
    int startingSite; //0 for start
    int notStopSites;
    int totalDistance;
};

class WalkManager
{
    int m_WalkCount;
    vector<Walk> m_Walks;

    void updateDistance(Walk &walk)
    {
        int dist = 0;
        for (int i = 0; i < walk.notStopSites; i++)
            dist += distances[walk.startingSite + i];
        walk.totalDistance = dist;
    }

    void expandLeft(Walk &walk, int count)
    {
        if (walk.notStopSites + count < 1)
            throw 31;
        if (walk.startingSite - count < 0)
            throw 32;

        walk.notStopSites += count;
        walk.startingSite += -count;
    }

    void expandRight(Walk &walk, int count)
    {
        if (walk.notStopSites + count < 1)
            throw 41;

        walk.notStopSites += count;
    }

public:
    WalkManager(int walkCount) : m_WalkCount(walkCount), m_Walks(walkCount)
    {
        if (walkCount > N + 1)
            throw 10;
        if (walkCount <= 0)
            throw 11;

        for (int i = 0; i < walkCount - 1; i++)
        {
            m_Walks[i].startingSite = i;
            m_Walks[i].notStopSites = 1;
            updateDistance(m_Walks[i]);
        }

        m_Walks[walkCount - 1].startingSite = walkCount - 1;
        m_Walks[walkCount - 1].notStopSites = N - walkCount + 2;
        updateDistance(m_Walks[walkCount - 1]);
    }

    bool tryResize(int walkId, int lr, int amount) {
        try
        {
            resize(walkId, lr, amount);
            return true;
        }
        catch(int e)
        {
            return false;
        }
        
    }

    void resize(int walkId, int lr, int amount)
    {
        if (amount == 0)
            return;
        Walk *walkA, *walkB, *walkC;

        walkB = &m_Walks[walkId];

        if (lr == -1)
        {
            if (walkId > 0)
            {
                walkA = &m_Walks[walkId - 1];
                expandRight(*walkA, -amount);
                updateDistance(*walkA);
            }
            expandLeft(*walkB, amount);
            updateDistance(*walkB);
        }
        else if (lr == 1)
        {
            if (walkId < m_WalkCount - 1)
            {
                walkC = &m_Walks[walkId + 1];
                expandLeft(*walkC, -amount);
                updateDistance(*walkC);
            }
            expandRight(*walkB, amount);
            updateDistance(*walkB);
        }
    }

    int getDistance(int walkId)
    {
        return m_Walks[walkId].totalDistance;
    }
};

WalkManager *walkManager;

void initialize()
{
    cin >> N >> K;

    for (int i = 0; i < N + 1; i++)
        cin >> distances[i];

    walkManager = new WalkManager(K + 1);
}

void solve() {

}

int main(int argc, char const *argv[])
{
    initialize();

    cout << endl;

    walkManager->tryResize(0, 1, 1);

    for (int i = 0; i < K + 1; i++)
    {

        cout << walkManager->getDistance(i) << endl;
    }
    return 0;
}
