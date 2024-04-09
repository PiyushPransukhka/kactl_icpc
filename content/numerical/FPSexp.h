/**
 * Author: koderkushy
 * Date: 2024-04-08
 * License: CC0
 * Source: self
 * Description: First $MAX$ coeffs of $\exp{p(x)}$.
 * Ensure $p$ is not empty and $p_0 = 0$.
 * Status: tested
 */

#pragma once

template<typename Ntt>
auto exp (vector<ll> p, int MAX = -1) {
    static constexpr auto mod = Ntt::getmod();
    if (MAX == -1)
        MAX = size(p);
    assert(size(p) and p[0] == 0);
    vector<ll> b(1, 1);
    for (size_t n = 2; n < 2*MAX; n <<= 1) {
        auto a = natural_log<Ntt>(b, n);
        a[0] = (mod + a[0] - 1) % mod;
        for (auto& x: a)
            x = (x ? mod - x: 0);
        for (size_t i = 0; i < std::min(n, size(p)); i++)
            a[i] = (a[i] + p[i]) % mod;
        b = conv<Ntt>(b, a, n);
    }
    return b.resize(MAX), std::move(b);
}
