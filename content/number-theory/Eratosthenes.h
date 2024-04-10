/**
 * Author: koderkushy
 * Date: 2024-04-08
 * License: CC0
 * Description: Prime sieve for generating all primes up to a certain limit.
 * Status: Tested
 */
#pragma once

constexpr size_t MX_PR = 1 << 20;
vector<int> primes;
bitset<MX_PR> ispr;
auto primes_init () {
    ispr[0] = ispr[1] = 1;
    primes.reserve(int(MX_PR / log(MX_PR)));
    for (uint64_t i = 2; i*i < MX_PR; ++i) if (!ispr[i])
        for (uint64_t j = i*i; j < MX_PR; j += i)
            ispr[j] = 1;
    for (int i = 0; i != MX_PR; ++i)
        if (!ispr[i]) primes.push_back(i);
}

vector<int> lpf, mul, primes;
auto lpf_init (const int N = 1 << 24) {
    lpf = mul = vector(N, 0);
    primes.reserve(N / max(1, int(log(N))));
    for (int i = 2; i != N; ++i) {
        if (lpf[i] == 0)
            lpf[i] = i, mul[i] = 1,
            primes.push_back(i);
        for (int p: primes) {
            if (p > lpf[i] or p * i > N)
                break;
            lpf[p * i] = p;
            mul[p * i] = 1 + (p == lpf[i]? mul[i]: 0);
        }
    }
}