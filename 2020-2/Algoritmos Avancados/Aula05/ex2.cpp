#include <iostream>
#include <vector>

using namespace std;

typedef long long int Height;

vector<Height> heights;

int binary_search(Height target_height) {
    int lo = 0, hi = (int) heights.size() - 1;

    if (target_height <= heights[lo]) return lo;
    if (target_height >= heights[hi]) return hi;

    int i;
    while (true)
    {
        i = (lo + hi) / 2;
        if (heights[i] == target_height) return i;
        if (lo >= hi) return i;

        if (heights[i] > target_height) hi = i-1;
        if (heights[i] < target_height) lo = i+1;
    }

    return i;
}

pair<int,int> find_ladies_index(Height target_height) {
    int target_i = binary_search(target_height);

    if (target_i < 0 || (size_t) target_i >= heights.size()) cout << "DEBUG: binary_search returned outofbounds" << endl;

    int ts;
    size_t st;
    st = ts = target_i;

    while (ts >= 0 && heights[ts] >= target_height) ts--;
    while (st < heights.size() && heights[st] <= target_height) st++;

    return make_pair(ts, (st >= heights.size()) ? -1 : (int) st);
}

int main(int argc, char const *argv[])
{
    int n, q;
    Height temp_h;
    cin >> n;

    heights.reserve(n);
    while (n-- > 0) {
        cin >> temp_h;
        heights.push_back(temp_h);
    }

    cin >> q;
    while (q-- > 0)
    {
        cin >> temp_h;
        pair<int, int> ladies = find_ladies_index(temp_h);
        
        if (ladies.first < 0) cout << 'X';
        else cout << heights[ladies.first];

        cout << " ";

        if (ladies.second < 0) cout << 'X';
        else cout << heights[ladies.second];

        cout << endl;
    }
    

    return 0;
}
