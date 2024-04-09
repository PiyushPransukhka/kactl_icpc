/**
 * Author: koderkushy
 * Date: 2024-04-08
 * License: CC0
 * Source: self
 * Description: First $MAX$ coeffs of $\sqrt{p(x)}$.
 * Status: tested
 */

#pragma once

template<int mod>
auto has_sqrt (const vector<ll>& p) {
    size_t l = 0;
    while (l < size(p) and p[l] == 0) l++;
    if (l == size(p)) return l;
    return (l%2 or mpow(p[l], mod-1>>1, mod) != 1) ? -1: l;
}

template<typename Ntt>
auto sqrt (vector<ll> p, int MAX = -1) {
    static constexpr auto mod = Ntt::getmod();
    static constexpr auto i2 = minv(2, mod);
    if (MAX == -1) MAX = size(p);
    auto l = has_sqrt<mod>(p);
    if (l == size(p))
        return vector<ll>(MAX);
    assert(l != -1);
    p.erase(begin(p), begin(p) + l);
    vector<ll> g(1, msqrt(p[0], mod));
    for (size_t n = 1; n < MAX - l/2; n <<= 1) {
        auto ig = inverse<Ntt>(g, n<<1);
        vector fp(begin(p), begin(p) + min(n<<1, size(p)));
        fp.resize(n<<1), fp = conv<Ntt>(ig, fp);
        g.resize(max(size(fp), size(g)));
        for (size_t k = 0; k < size(g); ++k)
            g[k] += fp[k];
        for (auto& x: g) x = x * i2 % mod;
    }
    vector<ll> res(l/2, 0);
    res.insert(end(res), begin(g), begin(g) + MAX-l/2);
    return res;
}