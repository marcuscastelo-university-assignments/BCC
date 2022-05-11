#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    int H;
    cin >> H;
    bool result = true;

    int lastH;
    cin >> lastH;
    for (int i = 1; i < H; i++)
    {
        int h;
        cin >> h;
        if (h < lastH) {
            result = false; // It's already decreasing, give up
            break;
        }
        else if (h > lastH) {
            lastH = h - 1; // Always subtract 1 if possible
        }
        else {
            lastH = h; // If equal, keep the same, if subtracted it would be a decreasing sequence
        }
    }

    if (result) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }

    return 0;
}
