#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

map<int,int> idToTime;

int main(int argc, char const *argv[])
{
    int gcdAccum = -1;
    int qnum, period;

    string dumpStr;
    cin >> dumpStr;

    if (dumpStr == "#") return 0;

    cin >> qnum;
    cin >> gcdAccum;

    idToTime[qnum] = gcdAccum;

    cin >> dumpStr;

    while (dumpStr != "#") {

        cin >> qnum;
        cin >> period;

        idToTime[qnum] = period;
        gcdAccum = __gcd(gcdAccum, period);
        
        cin >> dumpStr;
    }

    int itens;
    cin >> itens;

    int currTime = gcdAccum;
    while (1) {
        for (auto item = idToTime.begin(); item != idToTime.end(); item++)
        {
            if (itens <= 0) return 0;
            if (currTime % item->second == 0) {
                cout << item->first << endl;
                itens--;
            }
        }
        currTime += gcdAccum;
    }
    
    
    return 0;
}
