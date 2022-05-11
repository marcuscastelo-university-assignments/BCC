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

static vector<int> referenceSequence { 4, 8, 15, 16, 23, 42 };

#define DEBUG 0
#define D(x) { if (DEBUG) { cout << x << endl; } }

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

using SequencePool = vector<SequencePtr>;
int n;
vector<SequencePool> sequencePools(SIZE);

int _numberOfIncompleteSequences = 0;
int _numberOfItemsToRemove = 0;

bool Register(int item) {
    D("Registering " << item);
    int index = getIndex(item);
    D("Index: " << index);
    if (index == SUNKNOWN) {
        return false;
    }

    SequencePool& sequencePool = sequencePools[index];

    if (sequencePool.size() == 0) {
        if (index == S4) {
            D("Creating new sequence for " << item);
            auto *newSeq = new Sequence();
            newSeq->reserve(SIZE);
            sequencePool.push_back(newSeq);
            _numberOfIncompleteSequences++;
        }
        else {
            D("No sequence for " << item);
            return false;
        }
    }

    int sequenceIndex = -1;

    for (auto it = sequencePool.begin(); it != sequencePool.end(); ++it) {
        Sequence* sequence = *it;
        if ((int)sequence->size() == n) {
            continue;
        }

        sequence->push_back(item);
        sequenceIndex = it - sequencePool.begin();
        break;
    }

    if (sequenceIndex == -1) {
        throw "No sequence found";
    }

    if (index < SIZE - 1) {
        int newIndex = index + 1;
        auto &newPool = sequencePools[newIndex];

        // Copy the sequence to the new pool (unless it's now complete)
        D("Copying sequence to new pool");
        newPool.push_back(sequencePool[sequenceIndex]);
        _numberOfIncompleteSequences++;
    }

    // Remove from old pool
    D("Removing sequence from old pool");
    sequencePool.erase(sequencePool.begin() + sequenceIndex);
    _numberOfIncompleteSequences--;

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

    D("Number of incomplete sequences: " << _numberOfIncompleteSequences);

    for (int i = 0; i < SIZE; ++i) {
        auto sequencePool = sequencePools[i];
        D("Sequence pool " << i << " has: " << sequencePool.size());
        for (auto sequence : sequencePool) {
            D("\tSequence has: " << sequence->size());
            if (sequence != nullptr)
                _numberOfItemsToRemove += (int)sequence->size();
        }
    }

    D("Number of items to remove: " << _numberOfItemsToRemove);
    cout << _numberOfItemsToRemove << endl;
    return 0;
}
