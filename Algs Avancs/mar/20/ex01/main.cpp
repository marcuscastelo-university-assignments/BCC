#include <iostream>
#include <queue>
#include <cmath>
#include <string.h>
using namespace std;

int currentSequenceAsInt, targetSequenceAsInt, forbidden[10000];

int dist[10000];
queue<int> nextNodes;

int readSequenceAsInt() {
    int sequenceAsInt = 0, tempInput;
    for (double i=3 ; i>=0 ; i--) {
        cin >> tempInput;
        sequenceAsInt += tempInput*(int)pow(10.0, i);
    }
    return sequenceAsInt;
}

int bfs() {
    memset(dist, -1, sizeof(dist));

    nextNodes = queue<int>();
    nextNodes.push(currentSequenceAsInt);
    dist[currentSequenceAsInt] = 0;

    while (!nextNodes.empty()) {

        int currNode = nextNodes.front(); 
        nextNodes.pop();

        int originalNode = currNode;
        for (int i = 0; i <= 3; i++) {
            int nextNode;
            
            int mul = (int) pow(10.0, i);

            if (originalNode % 10 == 0) 
                nextNode = currNode + (mul*9);
            else 
                nextNode = currNode-mul;

            if (!forbidden[nextNode] && dist[nextNode] == -1) {
                dist[nextNode] = dist[currNode] + 1;

                if (nextNode == targetSequenceAsInt) 
                    return dist[nextNode];

                nextNodes.push(nextNode);
            }
            
            if (originalNode % 10 == 9) 
                nextNode = currNode - (mul*9);
            else 
                nextNode = currNode + mul;
            
            if (!forbidden[nextNode] && dist[nextNode] == -1) {
                dist[nextNode] = dist[currNode] + 1;

                if (nextNode == targetSequenceAsInt) return dist[nextNode];

                nextNodes.push(nextNode);
            }
            originalNode /= 10;
        }
    }
    return -1;
}
 
int main(int argc, char const *argv[])
{
    int N, n;
    int tempInput;
    cin >> N;
    for (int i = 0; i < N; i++) {
        memset(forbidden, 0, sizeof(forbidden));
        currentSequenceAsInt = readSequenceAsInt();
        targetSequenceAsInt = readSequenceAsInt();
        cin >> n;
        while (n--) {
            tempInput = readSequenceAsInt();
            forbidden[tempInput] = 1;
        }
        if (currentSequenceAsInt == targetSequenceAsInt) {
            cout << "0" << endl;
            continue;
        }
        cout << bfs() << endl;
    }
    return 0;
}