#include <iostream>
#include <vector>

using namespace std;

#define MAX_N 600
#define MAX_K 300

int N, K;
int distances[MAX_N + 1];

struct Walk
{
    int start;
    int end;
    int distance;
};

Walk groups[MAX_K + 1];

int sumDist(int startSite, int endSite)
{
    int sum = 0;
    for (int i = startSite + 1; i <= endSite; i++)
        sum += distances[i];
    return sum;
}

void initialize()
{
    cin >> N >> K;

    for (int i = 0; i < N + 1; i++)
        cin >> distances[i];

    for (int i = 0; i < K + 1; i++)
    {
        groups[i] = (Walk){
            i - 1,
            i,
            distances[i]};
    }

    groups[K] = (Walk){
        K-1,
        N,
        sumDist(K-1, N)};
}

void debugPrintCurrentGroups() {
    cout << "[DEBUG] Groups:" << endl;
    for (int i = 0; i < K+1; i++)
    {
        Walk &walk = groups[i];
        cout << i << ": {" << walk.start << " -> " << walk.end << ", D= " << walk.distance << "}" << endl;
    }
    cout<< endl;
    
}

Walk &getWalk(int walkId)
{
    return groups[walkId];
}

bool canGive(int walkId)
{
    Walk &walk = getWalk(walkId);
    return (walk.end - walk.start) > 1;
}

int give(int walkId)
{
    if (walkId == 0)
        return -1;

    if (!canGive(walkId))
        throw 20;

    Walk &left = getWalk(walkId - 1);
    Walk &right = getWalk(walkId);

    left.end++;
    right.start++;

    right.distance -= distances[left.end];
    left.distance += distances[left.end];

    return max(left.distance, right.distance); //Returns the new maxCost with this move (Optimization)
} 

void ungive(int walkId)
{
    if (walkId == 0)
        return;

    if (!canGive(walkId-1))
        throw 30;

    Walk &left = getWalk(walkId - 1);
    Walk &right = getWalk(walkId);

    right.distance += distances[left.end];
    left.distance -= distances[left.end];

    left.end--;
    right.start--;
}

int minCost = 0x7FFFFFFF;
int calcCost()
{
    int cost = 0;
    for (int i = 0; i < K + 1; i++)
    {
        if (groups[i].distance > cost)
            cost = groups[i].distance;

        if (cost > minCost) break; //Optimization
    }
    return cost;
}

void solve(int currWalk, bool ignoreCostCalc = false)
{
    // debugPrintCurrentGroups();

    //Optimization
    if (!ignoreCostCalc) {
        int currCost = calcCost();
        if (currCost < minCost) {
            minCost = currCost;
        }
    }

    if (currWalk == 0) return;
    int givenCounter = 0;
    while (canGive(currWalk))
    {
        givenCounter++;
        int giveCost = give(currWalk); //Optimization
        solve(currWalk-1, giveCost >= minCost);
    }

    for (int i = 0; i < givenCounter; i++)
        ungive(currWalk);  
}

int main(int argc, char const *argv[])
{
    initialize();
    solve(K);

    cout << minCost << endl;

    return 0;
}
