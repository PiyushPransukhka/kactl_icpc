/**
 * Author: kingmessi
 * Date: 2024-12-21
 * License: CC0
 * Source: self
 * Description: trie
 * Time: O(N * bits)
 * Status: tested
 */

template<int SZ, int MXBIT> struct Trie {
    int nex[SZ][2], sz[SZ], num = 0; // num is last node in trie
    // change 2 to 26 for lowercase letters
    Trie() { memset(nex,0,sizeof nex); memset(sz,0,sizeof sz); }
    void ins(ll x, int a = 1) { // insert or delete
        int cur = 0; sz[cur] += a;
        rrep(i,MXBIT,0) {
            int t = (x>>i)&1;
            if (!nex[cur][t]) nex[cur][t] = ++num;
            sz[cur = nex[cur][t]] += a;
        }
    }
    ll test(ll x) { // compute max xor
        if (!sz[0]) return -INF; // no elements in trie
        int cur = 0;
        rrep(i,MXBIT,0) {
            int t = ((x>>i)&1)^1;
            if (!nex[cur][t] || !sz[nex[cur][t]]) t ^= 1;
            cur = nex[cur][t]; if (t) x ^= 1LL<<i;
        }
        return x;
    }
};