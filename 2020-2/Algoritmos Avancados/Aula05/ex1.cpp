#include <iostream>
#include <vector>

using namespace std;

vector<int> vec;

void printVec(int a, int b) {
    for (int i = a; i <= b; i++) {
        cout << vec[i] << " ";
    }
}

int solve(int start, int end, int d) {
    if (start >= end) return 0;

    int mid = (start + end) / 2;
    
    int inversions_left = solve(start, mid, d+1);
    int inversions_right = solve(mid+1, end, d+1);
    int total_inversions = inversions_left + inversions_right;

    int a = start, b = mid+1;
    
    int k = start;
    int *i = nullptr;

    vector<int> oldVec = vec;

    int size_left = mid - start + 1;
    
    while (true) {
        int val = 0;
        if (a <= mid) val += 1;
        if (b <= end) val += 2;

        if (val == 0) break;

        i = ( (val == 2) || 
              ( (val == 3) && (oldVec[a] > oldVec[b]) ) )? 
                ({total_inversions+=size_left; &b;}) : 
                ({size_left--; &a;});

        vec[k++] = oldVec[(*i)++];
    }

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

        cout << solve(0, vec.size()-1, 0) << endl;
    }
    return 0;
}
