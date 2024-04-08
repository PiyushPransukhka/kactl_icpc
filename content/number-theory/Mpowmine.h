/**
 * Author: koderkushy
 * Date: 2024-04-08
 * License: CC0
 * Source: self
 * Description: modular exponentiation and inverse
 * Status: tested
 */

#pragma once

constexpr ll mpow (ll a, uint64_t p, int mod) {
    ll res = 1;
    while (p > 0) {
        if (p & 1) res = res * a % mod;
        a = a * a % mod, p >>= 1;
    }
    return res;
}

constexpr int minv (int a, int mod) {
    std::array x{1, 0};
    int _x0 {}, _x1{}, _a{}, _b{}, md = mod;
    while (mod)
        _x1 = x[0] - a / mod * x[1], _x0 = x[1],
        _a = mod, _b = a % mod,
        a = _a, mod = _b, x[0] = _x0, x[1] = _x1;
    return ((x[0] %= md) < 0 ? x[0] + md: x[0]);
}