/**
 * Author: piyush_pransukhka
 * Date: 2024-04-09
 * License: CC0
 * Source: self
 * Description: Primitive roots
 * g is a primitive root modulo n if and only if the smallest integer k for which $g^k = 1 (mod n)$ is equal to phi(n).
 * Primitive root modulo n exists if and only if:
 * - n is 1, 2, 4, or
 * - n is power of an odd prime number $(n = p^k)$, or
 * - n is twice power of an odd prime number $(n = 2 *(p^k))$
 * The number of primitive roots modulo n is equal to phi(phi(n)).
 * Status: tested
 */

int powmod (int a, int b, int p) {
    int res = 1;
    while (b)
        if (b & 1) {res = int (res * 1ll * a % p),  --b;}
        else {a = int (a * 1ll * a % p),  b >>= 1;}
    return res;
}
int find_primitive_root(int p) {
    vector<int> fact;
    int phi = phi(p); // find euler totient of p.
    int n = phi;
    for (int i=2; i*i<=n; ++i)
        if (n % i == 0) {
            fact.push_back(i);
            while (n % i == 0) n /= i;
        }
    if (n > 1) fact.push_back (n);
    for (int res=2; res<=p; ++res) {
        bool ok = true;
        for (size_t i=0; i<fact.size() && ok; ++i)
            ok &= powmod (res, phi / fact[i], p) != 1;
        if (ok)  return res;
    }
    return -1;
}