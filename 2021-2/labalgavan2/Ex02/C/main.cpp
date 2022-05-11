#include <iostream>
#include <vector>

using namespace std;

using Sequence = vector<int>;
using SequencePtr = Sequence*;

#define S4 0
#define S8 1
#define S15 2
#define S16 3
#define S23 4
#define S42 5
#define SIZE 6
#define SUNKNOWN -1

#define DEBUG 0
#define D(x) { if (DEBUG) { cout << x << endl; } }

int _numberOfItemsToRemove = 0;

int getIndex(int item) {
    if (item == 4) {
        return S4;
    } else if (item == 8) {
        return S8;
    } else if (item == 15) {
        return S15;
    } else if (item == 16) {
        return S16;
    } else if (item == 23) {
        return S23;
    } else if (item == 42) {
        return S42;
    } else {
        return SUNKNOWN;
    }
}
int n;

int maxCounter = 0;
int counters[SIZE] = {0};

bool Register(int item) {
    int index = getIndex(item);
    if (index == SUNKNOWN) {
        return false;
    }

    int counter = counters[index];

    for (int i = 0; i < index; i++) {
        if (counters[i] < counter + 1) {
            return false;
        }
    }

    counters[index]++;
    maxCounter = max(maxCounter, counters[index]);

    return true;
}

int main(int argc, char const *argv[])
{
    cin >> n;

    int item;
    for (int i = 0; i < n; ++i)
    {
        cin >> item;
        if (Register(item)) {
            D("Registered " << item);
        } else {
            D("Bad item " << item);
            // break;
            _numberOfItemsToRemove++;
        }
    }

    int S4C = counters[S4];
    int S8C = counters[S8];
    int S15C = counters[S15];
    int S16C = counters[S16];
    int S23C = counters[S23];
    int S42C = counters[S42];

    int pendingItems = S4C + S8C + S15C + S16C + S23C - ((SIZE-1) * S42C);
    _numberOfItemsToRemove += pendingItems;

    D("Number of items to remove: " << _numberOfItemsToRemove);
    cout << _numberOfItemsToRemove << endl;
    return 0;
}
