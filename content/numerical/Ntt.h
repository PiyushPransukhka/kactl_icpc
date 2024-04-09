/**
 * Author: koderkushy
 * Date: 2024-04-08
 * License: CC0
 * Source: self
 * Description: Performs NTT on a.
 * Inputs must be in [0, mod).
 * Time: O(N \log N)
 * Status: tested
 */

#pragma once

template<typename Ntt>
auto ntt (std::vector<ll> &a, const bool invert = false) {
    static const auto ntt = Ntt();
    static constexpr auto mod = Ntt::getmod();
    static constexpr auto depth = Ntt::depth;
    const int N = size(a);
    assert(__builtin_popcount(N) == 1 and __builtin_ctz(N) <= depth);
    for (int i = 1, j = 0; i < N; i++) {
        int b = N >> 1;
        while (b & j) j ^= b, b >>= 1;
        j ^= b;
        if (j > i) std::swap(a[i], a[j]);
    }
    const auto &buf = invert? ntt.ib: ntt.b;
    for (int L = 1; L != N; L <<= 1)
        for (int s = 0; s != N; s += 2*L)
            for (int i = s; i != s + L; ++i) {
                auto x = a[i], y = a[i + L] * buf[i-s + L] % mod;
                a[i] = x + y - (x + y >= mod ? mod: 0);
                a[i + L] = x - y + (x < y ? mod: 0);
            }
    if (invert) {
        const int ninv = minv(N, mod);
        for (auto &v: a) v = v * ninv % mod;
    }
}

template<typename Ntt>
auto conv (std::vector<ll> a, std::vector<ll> b, int MAX = -1){
    static constexpr auto mod = Ntt::getmod();
    if (MAX == 0) return vector<ll>{};
    if (MAX == -1)
        MAX = max(1ul, size(a) + size(b) - 1);
    a.resize(min(int(size(a)), MAX));
    b.resize(min(int(size(b)), MAX));
    const int n = size(a) + size(b);
    int m = 1 << 32 - __builtin_clz(max(1, n - 1));

    a.resize(m), ntt<Ntt>(a);
    b.resize(m), ntt<Ntt>(b);

    for (int i = 0; i < m; i++)
        a[i] = a[i] * b[i] % mod;

    ntt<Ntt>(a, 1), a.resize(MAX);
    return a;
}
