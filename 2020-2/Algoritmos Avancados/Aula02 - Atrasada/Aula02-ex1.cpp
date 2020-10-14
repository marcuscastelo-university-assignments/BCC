//Uva 11264 - Coin Collector

#include <iostream>
#include <string.h>

#define llu long long unsigned

int n;
llu coin_types[1000];

using namespace std;

//BANK LOGIC
int find_next_idx(llu money_target, int curr_idx) {
    for (; curr_idx > 0; curr_idx--) {
        if (coin_types[curr_idx] <= money_target) return curr_idx;
    }

    return 0;   
}

llu g_number_of_coins_used = 0;
int _last_coin_idx = -1;
void _withdraw_recursive(llu X, int coin_idx) {
    if (X == 0) return;

    if (_last_coin_idx != coin_idx) g_number_of_coins_used++;
    _last_coin_idx = coin_idx;

    llu subtract_value = coin_types[coin_idx];

    if (subtract_value > X) {
        cout << "DEBUG: THIS SHOULD NOT HAPPEN SUB > X @_withdraw_recursive" << endl;
        return;
    }

    llu newX = X - subtract_value;
    _withdraw_recursive(newX, find_next_idx(newX, coin_idx));
}

void withdraw(llu X) {
    if (X == 0) return;
    g_number_of_coins_used = 0;
    _last_coin_idx = -1;
    _withdraw_recursive(X, find_next_idx(X, n-1));
}


//PROBLEM LOGIC

llu guess_good_choice_upper(int coin_idx) {
    return 2 * coin_types[coin_idx] - 1;
}

llu guess_good_choice_lower(int coin_idx) {
    return coin_types[coin_idx+1] - 1;
}

void calc_and_update_coin_count(llu &max_number_of_coins, int money) {
    withdraw(money);
    if (max_number_of_coins < g_number_of_coins_used)
        max_number_of_coins = g_number_of_coins_used;
}

llu calc_max_coin_count() {
    llu max_number_of_coins = 0;
    calc_and_update_coin_count(max_number_of_coins, guess_good_choice_upper(n-1));
    for (int i = n-2; i > 0; i--)
    {
        llu money_u = guess_good_choice_upper(i);
        llu money_d = guess_good_choice_lower(i);
        calc_and_update_coin_count(max_number_of_coins, money_u);
        calc_and_update_coin_count(max_number_of_coins, money_d);
    }

    return max_number_of_coins;
}


int main(int argc, char const *argv[])
{
    int T;
    cin >> T;

    for (int i = 0; i < T; i++)
    {
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> coin_types[j];
        cout << calc_max_coin_count() << endl;
    }
    
    
    return 0;
}