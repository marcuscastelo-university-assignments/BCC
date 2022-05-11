#include <iostream>
#include <vector>
using namespace std;



int main(int argc, char const *argv[])
{
    //Input
    int n;
    cin >> n;

    vector<char> a(n);
    for (int i = 0; i < n; i++) { cin >> a[i]; a[i] -= '0'; }

    short f[10] = {-1}; //{-1, 0, 0, 0}
    for (int i = 1; i <= 9; i++) cin >> f[i];
    
    //Solve
    bool started = false;

    for (int i = 0; i < n; i++)
    {
        short dig = a[i];

        if (f[dig] == dig) {
            continue;
        }
        else if (f[dig] < dig) {
            if (started) break;
            else continue;
        }
        else {
            started = true;
            a[i] = f[dig];
        }
    }
    
    //Print
    for (int i = 0; i < n; i++) cout << (short)a[i];
    cout << endl;

    return 0;
}
