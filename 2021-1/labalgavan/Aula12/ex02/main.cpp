#include <bits/stdc++.h>

using namespace std;
using big = unsigned long long;

big n;

//Uses sieve of erasthotenes to check if a number is prime

vector<bool> sieve;

void fillSieve(big n)
{
    sieve.assign(n + 1, true);
    sieve[0] = sieve[1] = false;
    for (size_t i = 2; i * i < sieve.size(); i++)
    {
        if (sieve[i])
        {
            for (size_t j = i * i; j < sieve.size(); j += i)
            {
                sieve[j] = false;
            }
        }
    }
}

big solve(vector<big> &A)
{
    big total = 0;
    for (size_t i = 0; i < A.size(); i++)
        for (size_t j = i + 1; j < A.size(); j++)
            total += sieve[__gcd(A[i], A[j])] ? 1 : 0;
    return total;
}

int main(int argc, char const *argv[])
{
    cin >> n;
    big pp = 0;
    vector<big> A(n);
    for (big i = 0; i < n; i++) {
        cin >> A[i];
        pp = max(pp, A[i]);
    }

    fillSieve(pp + 130);
    cout << solve(A);

    return 0;
}
