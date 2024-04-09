/**
 * Author: koderkushy
 * Date: 2024-04-08
 * License: CC0
 * Source: self
 * Description: First $MAX$ coeffs of $\log{p(x)}$. Ensure $p$ is not empty and $p_0 = 1$.
 * Status: tested
 */

#pragma once

template<int mod>
auto derivative (vector<ll> p) {
    assert(size(p));
    for (size_t i = 1; i != size(p); ++i)
        p[i - 1] = p[i] * i % mod;
    return p.pop_back(), move(p);
}

template<int mod>
auto integrate (vector<ll> p) {
    p.push_back(0);
    for (size_t i = size(p); --i; )
        p[i] = p[i - 1] * minv(i, mod) % mod;
    return p[0] = 0, move(p);
}

template<typename Ntt>
auto natural_log (vector<ll> p, int MAX = -1) {
    if (MAX == 0) return vector<ll>{};
    if (MAX == -1) MAX = size(p);
    assert(size(p) and p[0] == 1);
    auto inv = inverse<Ntt>(p, MAX);
    inv = conv<Ntt>(inv, derivative<Ntt::getmod()>(p), MAX - 1);
    return integrate<Ntt::getmod()>(inv);
}
