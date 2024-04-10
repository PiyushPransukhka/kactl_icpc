/**
 * Author: piyush_pransukhka
 * Date: 2024-04-09
 * License: CC0
 * Source: self
 * Description: CRT
 * Status: tested
 */

#pragma once

struct Cng {
    ll a, m;
};

ll crt (vector<Cng> const& cngs) {
    ll M = 1;
    for (auto cng : cngs) M *= cng.m;

    ll z = 0;
    for (auto const& cng : cngs) {
        ll a_i = cng.a;
        ll M_i = M / cng.m;
        ll N_i = mod_inv(M_i, cng.m);
        z = (z + a_i * M_i % M * N_i) % M;
    }
    return z;
}

// NOTE : When $m_1, m_2, \dots$ are not coprime, we take $M = lcm(m_1, m_2,\dots)$ and break $a = a_i (mod m_i)$ into
// $a = a_i (mod p_j^n_j)$ for all prime factors $p_j$ of $m_i$ and then proceed similarly.