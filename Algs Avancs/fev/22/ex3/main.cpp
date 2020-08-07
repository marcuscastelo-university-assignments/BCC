#include <iostream>
#include <map>


using namespace std;

int main(int argc, char const *argv[])
{
    map<long, long> m;

    unsigned n;
    cin >> n;   

    long d, count = 0;
    for (unsigned i = 0; i < n; i++)
    {
        cin >> d;
        if (!m[d]){
            m[d]++;
            count++;
        }
    }
    
    cout << count << endl;

    return 0;
}
