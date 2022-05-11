#include <bits/stdc++.h>

using namespace std;
using big = unsigned long long;

#define MOD (1000000000 + 7)

void solve(big n)
{
    big sum = 0, product = 1, qtty = 0;
    const big sn = (big)sqrt(n);
    for (big i = 1; i <= sn; i++)
    {
        if (n % i == 0)
        {
            big reverso = n / i;
            if (i != reverso)
            {
                sum += reverso;
                product = ((reverso % MOD) * product) % MOD;
                qtty++;

                sum %= MOD;
                qtty %= MOD;
            }

            sum += i;
            product = ((i % MOD) * product) % MOD;
            qtty++;

            sum %= MOD;
            qtty %= MOD;
        }
    }

    cout << qtty << " " << sum << " " << product << endl;
}

int main(int argc, char const *argv[])
{
    big n;
    cin >> n;

    solve(n);

    return 0;
}
