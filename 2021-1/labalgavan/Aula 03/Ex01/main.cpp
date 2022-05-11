#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = (3000*2999) + 1; //Worst case scenario (all n coolness value is n, which lead each one to allocate n-1 new elements, so n*(n-1) ) [plus one, since there is no 0 coolness]

int main(int argc, char const *argv[])
{
    int n;
    cin >> n;

    unsigned price = 0;
    vector<int> count(MAX_N, 0);

    int coolness;
    for (int i = 0; i < n; i++)
    {
        cin >> coolness;
        count[coolness]++;
    }

    for (int i = 1; i < MAX_N-1; i++)
    {
        if (count[i] > 1) {
            price += count[i] - 1;
            count[i+1] += count[i] - 1;
            count[i] = 1;
        } 
    }

    cout << price << endl;

    return 0;
}
