#include <iostream>
#include <stdio.h>
#include <cmath>
#include <chrono>

using namespace std;

typedef long long ll;

const double MIN_STEP_UNSOLVABLE = 1e-2;
const double F_PRECISION = 1e-8;
const double X_PRECISION = 1e-9;

ll p,q,r,s,t,u;
bool unsolvable;

ll fn, fp, fz;

double f(double x) {
    return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;
}

double find_first(int mult) {
    double step = 1/2.0;
    double x = 0;
    while (mult * f(x) < 0)
    {
        x = 0; step /= 2.0;

        if (step < MIN_STEP_UNSOLVABLE) {
            unsolvable = true; return 0;
        }

        while (mult * f(x) < 0)
        {
            if (x + step > 1) break;
            x += step;
        }
    }

    return x;
}

double find_zero(double neg, double pos) {
    if (unsolvable) return 0;
    double mid, fmid;
    while (true)
    {
        mid = (pos + neg) / 2.0;
        fmid = f(mid);
        if (std::abs (pos - neg) < X_PRECISION) break;
        if (std::abs( fmid ) < F_PRECISION) break;
        if (fmid < 0) neg = mid;
        else pos = mid;
    }
    if (mid < 0 || mid > 1 ) unsolvable = true;
    return mid;
}

double solve() {
    double neg = 0;//find_first(-1);
    double pos = 1;//find_first(1);
    double r;

    if (f(neg) * f(pos) > 0) unsolvable = true;

    else if (f(pos) >= f(neg)) r = find_zero(neg, pos);
    else r = find_zero(pos,neg);

    if (unsolvable) return 0;
    return r;

}

int main(int argc, char const *argv[])
{
    // int max = 50;

    while (cin >> p >> q >> r >> s >> t >> u) {

        unsolvable = false;
        double x = solve();
        if (unsolvable) cout << "No solution" << endl;
        else printf("%.4lf\n", x);

        // if (max-- <= 0) break;
    }

    return 0;
}
