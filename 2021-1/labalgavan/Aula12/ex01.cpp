#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

unsigned long long int n;

// Given an unsigned long long integer, this function finds the number, sum and product of its divisors.
void solve() {
    vector<unsigned long long int> divisors;
    for (unsigned long long int i = 1; i <= n; ++i) {
        if (n % i == 0) {
            divisors.push_back(i);
        }
    }
    sort(divisors.begin(), divisors.end());
    unsigned long long int sum = 0;
    unsigned long long int product = 1;
    for (unsigned long long int i = 0; i < divisors.size(); ++i) {
        sum += divisors[i];
        product *= divisors[i];
    }
    cout << divisors.size() % (1000000000 + 7) << " " << sum % (1000000000 + 7) << " " << product % (1000000000 + 7) << endl;
}

int main(int argc, char const *argv[])
{
    cin >> n;   
    solve();
    return 0;
}


