/**
 * Author: koderkushy
 * Date: 2024-04-08
 * License: CC0
 * Source: self
 * Description: Provides metadata to ntt.
 * Status: tested
 */

#pragma once

constexpr std::array primitive_roots {
    std::pair(998244353, 3),    // 23
    std::pair(1004535809, 3),   // 21
    std::pair(1012924417, 5),   // 21
    std::pair(1300234241, 3),   // 23
    std::pair(1484783617, 5)    // 23
};

template<int mod>
class Ntt {
public:

    static constexpr int depth = __builtin_ctz(mod - 1);
    static constexpr int root = []() {
            for (auto [m, root]: primitive_roots)
                if (m == mod) return root;
        }();
    static constexpr int w = mpow(root, mod - 1 >> depth, mod);
    static constexpr int iw = minv(w, mod);
    static constexpr int getmod () { return mod; }
    vector<ll> b, ib;

    Ntt () {
        const size_t SZ = 1 << 20;
        b = ib = vector<ll>(SZ);
        for (int l = 1, pw = 1 << depth-1; l != SZ; l <<= 1, pw >>= 1) {
            b[l] = ib[l] = 1;
            const auto wp = mpow(w, pw, mod), iwp = mpow(iw, pw, mod);
            for (int i = l+1; i < 2*l; ++i)
                b[i] = b[i-1] * wp % mod, ib[i] = ib[i-1] * iwp % mod;
        }
    }
};
