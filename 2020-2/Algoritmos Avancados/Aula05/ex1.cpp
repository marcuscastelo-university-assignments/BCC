#include <iostream>
#include <vector>

using namespace std;

vector<int> vec;

int solve(int start, int end) {
    if (start >= end) return 0;

    int mid = (start + end) / 2;
    
    int inversions_left = solve(start, mid);
    int inversions_right = solve(mid+1, end);
    int total_inversions = inversions_left + inversions_right;

    for (int i = mid+1; i <= end; i++)
        for (int j = start; j <= mid; j++)
            if (vec[j] > vec[i]) total_inversions++;

    return total_inversions;
}   

int main(int argc, char const *argv[])
{
    int tc, vq, inp;
    cin >> tc;
    while (tc-- > 0) {
        cin >> vq;

        vec.clear();
        vec.reserve(vq);
        
        while (vq-- > 0) {
            cin >> inp;
            vec.push_back(inp);
        }

        cout << solve(0, vec.size()-1) << endl;
    }
    return 0;
}
