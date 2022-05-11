#include <iostream>
#include <set>
#include <vector>
#include <sstream>

using namespace std;

#define MAX_WORD_LENGTH 400
#define MAX_N 20
vector<set<string, std::less<string>>> wordsPerSize(MAX_WORD_LENGTH);
int n;

vector<bool> visited(MAX_N);
void explore(vector<char> &matrix, int row, int col, vector<char> &word) {
    if (row < 0 || row >= n || col < 0 || col >= n) return;

    int index = row * n + col;
    if (visited[index]) return;

    char c = matrix[index];

    if (word.size() != 0) {
        char lc = word.back();
        if (lc >= c) return;
    }

    word.push_back(c);

    int drows[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dcols[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    for (int i = 0; i < 8; i++) {
        int newRow = row + drows[i];
        int newCol = col + dcols[i];

        visited[index] = true;
        explore(matrix, newRow, newCol, word);
        visited[index] = false;
    }

    if (word.size() >= 3)
        wordsPerSize[word.size() - 1].insert(string(word.begin(), word.end()));

    word.pop_back();
}

void findWords(vector<char> &matrix, int row, int col) {
    static vector<char> word;
    word.reserve(MAX_WORD_LENGTH);
    explore(matrix, row, col, word);
}

void testcase() {
    cin >> n;
    vector<char> a(n);
    for (int i = 0; i < n * n; ++i)
        cin >> a[i];

    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            findWords(a, row, col);
        }
    }

    for (int i = 0; i < MAX_WORD_LENGTH; ++i) {
        auto &words = wordsPerSize[i];
        if (words.size() == 0) continue;
        
        for (auto &word : words) {
            cout << word << endl;
        }
    }

}


int main(int argc, char const *argv[])
{
    int t;
    cin >> t;
    while (t--) {
        testcase();
    }
    return 0;
}
