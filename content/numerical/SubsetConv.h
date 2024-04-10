/**
 * Author: koderkushy
 * Date: 2024-04-08
 * License: CC0
 * Source: self
 * Description: Subset convolution.
 * Status: tested
 */

#pragma once

constexpr int MOD = 998244353;
auto sos (vector<ll>& a, const bool invert = false) {
    const size_t n = size(a);
    assert(__builtin_popcount(n) == 1);
    for (int i = 1; i < n; i <<= 1)
        for (int ms = 0; ms < n; ++ms)
            if ((ms & i) == 0)
                (a[ms | i] += (invert? MOD-a[ms]: a[ms])),
                a[ms | i] -= (a[ms | i] >= MOD ? MOD: 0);
}
void subset_conv (vector<ll>& a, const vector<ll>& b) {
    const int n = size(a);
    assert(__builtin_popcount(n) == 1 and size(b) == n);
    const int p = __builtin_ctz(n) + 1;
    vector a_cap(p, vector(n, ll()));
    vector b_cap(p, vector(n, ll()));
    vector c_cap(p, vector(n, ll()));
    for (int i = 0; i < n ; ++i)
        a_cap[__builtin_popcount(i)][i] = a[i],
        b_cap[__builtin_popcount(i)][i] = b[i];
    for (int i = 0; i < p; ++i)
        sos(a_cap[i]), sos(b_cap[i]);
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j <= i; ++j)
            for (int ms = 0; ms < n; ++ms)
                (c_cap[i][ms] += a_cap[j][ms] * b_cap[i - j][ms]) %= MOD;
        sos(c_cap[i], true);
    }
    for (int i = 0; i < n ; ++i)
        a[i] = c_cap[__builtin_popcount(i)][i];
}
