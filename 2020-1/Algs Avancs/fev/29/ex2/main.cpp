#include <iostream>
#include <stack>
#include <queue>

using namespace std;

stack<int> s;
queue<int> q;
priority_queue<int> pq;

enum type {
    NONE = 0, QUEUE = 1, STACK = 2, PRIORITY_QUEUE = 4,
};

void clearData(int n) {
    while(!s.empty()) s.pop();
    while(!q.empty()) q.pop();
    while(!pq.empty()) pq.pop();
}

void push(int i) {
    s.push(i);
    q.push(i);
    pq.push(i);
}

void pop() {
    if (s.empty()) return;

    s.pop();
    q.pop();
    pq.pop();
}

type check(int returned) {
    if (s.empty()) return (type) NONE;

    int vs = s.top();
    int vq = q.front();
    int vpq = pq.top();

    int t = NONE;
    if (vs == returned) t |= STACK;
    if (vq == returned) t |= QUEUE;
    if (vpq == returned) t |= PRIORITY_QUEUE;
    return (type) t;
}

int main(int argc, char const *argv[])
{
    int n;
    char op;
    int val;
    while (cin >> n) {
        clearData(n);
        int t = STACK | QUEUE | PRIORITY_QUEUE;

        for (int i = 0; i < n; i++)
        {
            cin >> op;
            cin >> val;

            if (op == '1') push(val);
            else { t &= check(val); pop(); }
        }

        if (t == NONE) cout << "impossible";
        else if (t == STACK) cout << "stack";
        else if (t == QUEUE) cout << "queue";
        else if (t == PRIORITY_QUEUE) cout << "priority queue";
        else cout << "not sure";
        cout << endl;
    }
    return 0;
}
