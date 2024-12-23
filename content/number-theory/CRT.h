/**
 * Author: piyush_pransukhka
 * Date: 2024-04-09
 * License: CC0
 * Source: self
 * Description: Solves system of equations $ x = a_{i} $ (mod ${m_i} $ ).
 * When $m_1, m_2,\dots$ are not coprime, we take $M = lcm(m_1, m_2, ,...)$ and we break $a = a_i$ (mod $m_i$) into
 * $a = a_i$ (mod ${p_j}^{n_j} $) for all prime factors $p_j$ of $m_i$.   and then proceed similarly.
 * The congruence with the highest prime power modulus will be the strongest congruence of all congruences based on the same 
 * prime number. Either it will give a contradiction with some other congruence, or it will imply already all other congruences.
 * If there are no contradictions, then the system of equation has a solution. We can ignore all congruences except the ones with
 * the  highest prime power moduli.
 * Status: tested
 */

struct Congruence {
    long long a, m;
};

long long chinese_remainder_theorem(vector<Congruence> const& congruences) {
    long long M = 1, solution = 0;
    for (auto const& congruence : congruences) {
        M *= congruence.m;
    }
    for (auto const& congruence : congruences) {
        long long a_i = congruence.a, M_i = M / congruence.m;
        long long N_i = mod_inv(M_i, congruence.m);
        solution = (solution + a_i * M_i % M * N_i) % M;
    }
    return solution;
}