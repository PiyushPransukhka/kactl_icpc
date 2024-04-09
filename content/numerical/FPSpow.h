/**
 * Author: koderkushy
 * Date: 2024-04-08
 * License: CC0
 * Source: self
 * Description: First coeffs of (p(x))^e.
 * Status: tested
 */

#pragma once

template<typename Ntt>
auto pow (vector<ll> p, int64_t e, int MAX = -1) {
    static constexpr auto mod = Ntt::getmod();
    if (MAX == -1) MAX = size(p);
    if (p.empty()) return vector<ll>(MAX, 0);
    if (e == 0) {
        vector v(MAX, 0ll);
        return v[0] = 1, v;
    }
    size_t sh = 0;
    while (sh < size(p) and p[sh] == 0) sh++;
    if (sh == size(p) or (sh and (e >= MAX or e*sh >= MAX)))
        return vector<ll>(MAX, 0);
    auto trim_l = MAX - e*sh;
    const auto ld_pow_e = mpow(p[sh], e, mod),
               inv_ld = minv(p[sh], mod),
               e_mod = e % mod;
    vector res(begin(p) + sh, end(p));
    for (auto &x: res)  x = x*inv_ld % mod;
    res = natural_log<Ntt>(res, trim_l);
    for (auto &x: res)  x = x*e_mod % mod;
    res = exp<Ntt>(res, trim_l);
    for (auto &x: res)  x = x*ld_pow_e % mod;
    if (e*sh) res.insert(begin(res), e*sh, 0);
    return move(res);
}
