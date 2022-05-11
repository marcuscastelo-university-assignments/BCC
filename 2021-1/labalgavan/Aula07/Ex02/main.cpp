#include <iostream>
#include <vector>

using namespace std;

int N, G;
int maxCapacity;

struct product
{
    int p, w;
};
vector<product> products;
vector<int> capacities;

using mrow = vector<int>;
vector<mrow> dpMatrix;

void solveAllDP()
{
    dpMatrix.clear();
    dpMatrix.reserve(N + 1);

    for (int i = 0; i < N + 1; i++)
        dpMatrix.push_back(mrow(maxCapacity + 1, -1));

    for (int i = 0; i < maxCapacity + 1; i++)
        dpMatrix[0][i] = 0;

    for (int i = 0; i < N + 1; i++)
        dpMatrix[i][0] = 0;

    for (int item = 1; item < N+1; item++)
    {
        for (int capacity = 1; capacity < maxCapacity + 1; capacity++)
        {
            int bestValUntilNow = dpMatrix[item-1][capacity];

            if (products[item-1].w > capacity) {
                dpMatrix[item][capacity] = bestValUntilNow;
                continue;
            }

            //Supondo que a pessoa pegue, inicialmente, apenas este item:
            int thisItemVal = products[item-1].p;
            int remainingCapacity = capacity - products[item-1].w;

            //Com o espaço restante (com certeza já calculado), olhe na dp pela melhor solução (mas não pode pegar o mesmo item de novo, então subtrai um).
            int dpSolutionToRemainingSpace = dpMatrix[item-1][remainingCapacity];

            int valueConsideringThisItemIsPickedAndTheRemainingPicksAreOptimal = thisItemVal + dpSolutionToRemainingSpace;

            dpMatrix[item][capacity] = max(bestValUntilNow, valueConsideringThisItemIsPickedAndTheRemainingPicksAreOptimal);
        }   
    }
}

void solve()
{
    solveAllDP();
    int familySum = 0;

    for (int i = 0; i < G; i++)
        familySum += dpMatrix[N][capacities[i]];

    cout << familySum << endl;
}

void testcase()
{
    cin >> N;

    maxCapacity = 0;
    products.clear();
    capacities.clear();

    products.reserve(N);

    int p, w;
    for (int i = 0; i < N; i++)
    {
        cin >> p >> w;
        products.push_back({p,w});
    }

    cin >> G;

    capacities.reserve(G);

    int mw;
    for (int i = 0; i < G; i++)
    {
        cin >> mw;
        capacities.push_back(mw);
        if (mw > maxCapacity)
            maxCapacity = mw;
    }

    solve();
}

int main(int argc, char const *argv[])
{
    int T;
    cin >> T;

    for (int i = 0; i < T; i++)
        testcase();

    return 0;
}
