#pragma once

#include "../number-theory/Modpowmine.h"
#include "../numerical/NttInfo.h"

template<typename Ntt>
auto butterfly (std::vector<ll> &a, const bool invert = false) {
    static const auto ntt = Ntt();
    static constexpr auto mod = Ntt::getmod();
    static constexpr auto depth = Ntt::depth;

    const int& N = a.size();
    assert(__builtin_popcount(N) == 1 and __builtin_ctz(N) <= depth);

    for(int i = 1, j = 0; i < N; i++){
        int b = N >> 1;
        while(b & j) j ^= b, b >>= 1;
        j ^= b;
        if(j > i) std::swap(a[i], a[j]);
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
auto conv (std::vector<ll>& a, std::vector<ll> b, const size_t MAX = 0u){
    static constexpr auto mod = Ntt::getmod();
    a.resize(max(a.size(), MAX));
    b.resize(max(b.size(), MAX));

    const int n = (a.size() + b.size()); 
    int m = 1 << 32 - __builtin_clz(n - 1);

    a.resize(m), butterfly<Ntt>(a);
    b.resize(m), butterfly<Ntt>(b);

    for (int i = 0; i < m; i++)
        a[i] = a[i] * b[i] % mod;

    butterfly<Ntt>(a, 1), a.resize(n-1);

    if (MAX) a.resize(MAX);
}
