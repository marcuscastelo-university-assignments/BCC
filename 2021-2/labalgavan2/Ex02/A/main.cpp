#include <iostream>
#include <vector>
#include <algorithm>

#define DEBUG 0

#if DEBUG == 1
int _c;
#define D(x) { std::cout << x << std::endl; }
#define DC(x) { _c++; }
#else
#define DC(x)
#define D(x)
#endif

#define nullptr 0

// Events are defined as a pair of integers, where the first integer is the
// time which the event starts, and the second integer is the time which the event ends.
struct Event {
    int begin;
    int end;
};

using namespace std;

// We cannot overlap events
// This is a greedy algorithm, so we will always choose the event with the smallest end time
// to be the first event in the schedule.
// We will also always choose the event with the smallest begin time to be the first event
// in the schedule.
// This is because we want to minimize the amount of time we have to wait for the next event.
// We will also always choose the event with the smallest end time to be the first event
// in the schedule.
int calcMaxEvents(vector<Event> &events) {
    sort(events.begin(), events.end(), [](const Event &a, const Event &b) {
        return a.begin < b.begin;
    });

    sort(events.begin(), events.end(), [](const Event &a, const Event &b) {
        return a.end < b.end;
    });

    int maxEvents = 0;
    int currentEnd = 0;
    for (size_t i = 0; i < events.size(); i++) {
        if (events[i].begin >= currentEnd) {
            maxEvents++;
            currentEnd = events[i].end;
        }
    }

    return maxEvents;
}

int main(int argc, char const *argv[])
{
    int T, N;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> N;
        vector<Event> events;
        for (int j = 0; j < N; j++) {
            int begin, end;
            cin >> begin >> end;
            events.push_back({begin, end});
        }  

        if (DEBUG == 1) {
            cout << "Case #" << i + 1 << ": " << calcMaxEvents(events) << endl;
        } else {
            cout << calcMaxEvents(events) << endl;
        }
    }
    return 0;
}
