/**
 * Author: koderkushy
 * Date: 2024-04-08
 * License: CC0
 * Source: self
 * Description: Returns $p^{-1}(x)$ such that $p(x)p^{-1}(x) = 1+x^{MAX}q(x)$.
 * Ensure $p$ is not empty and $p_0 \neq 0$.
 * Status: tested
 */


#pragma once

template<typename Ntt>
auto inverse (vector<ll> p, int MAX = -1) {
    static constexpr auto mod = Ntt::getmod();
    if (MAX == -1)
        MAX = size(p);
    assert(size(p) and p[0]);
    vector<ll> b(1, minv(p[0], mod));
    for (size_t n = 1; n < MAX; n <<= 1) {
        vector x(begin(p), begin(p) + min(n<<1, size(p)));
        b.resize(n<<2), ntt<Ntt>(b);
        x.resize(n<<2), ntt<Ntt>(x);
        for (int i = 0; i != (n<<2); ++i)
            b[i] = b[i] * (2 + mod - b[i] * x[i] % mod) % mod;
        ntt<Ntt>(b, 1);
        b.resize(n<<1);
    }
    return b.resize(MAX), move(b);
}
