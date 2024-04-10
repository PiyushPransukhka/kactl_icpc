/**
 * Author: koderkushy
 * Date: 2024-04-08
 * License: CC0
 * Source: me
 * Description: Lazy segment tree. Pass Node and Lazy classes and fill out F, L, A.
 * DO NOT MESS with order of member declaration.
 * Time: O(\log N).
 * Status: stress-tested
 */
#pragma once

template<typename Node, typename Lazy>
class LazySegtree {
    const int sz, N;
    const Node id;
    const Lazy null;
    vector<Node> a; vector<Lazy> b;
    Node F(Node, Node);
    Lazy L(Lazy, Lazy);
    Node A(Node, Lazy);

    inline void on_all (int i, Lazy u)
        { a[i] = A(a[i], u); if(i < N) b[i] = L(b[i], u); }
    inline void push (int i)
        { on_all(i<<1, b[i]), on_all(i<<1|1, b[i]), b[i] = null; }
    void pull (int x) {
        static int C[30], i = 0;
        for (; x /= 2; C[++i] = x);
        for (; i; i--) push(C[i]);
    }

public:
    LazySegtree (const vector<Node>& x, Node id, Lazy null)
    : sz(x.size()), id(id), null(null),
      N(1 << 32-__builtin_clz(max(1, sz-1))),
      a(2*N, id), b(N, null) {
        copy(begin(x), end(x), begin(a) + N);
        for (int i = N; --i; )
            a[i] = F(a[2*i], a[2*i + 1]);
    }

    void set (int i, const Node x) {
        pull(i += N), a[i] = x;
        while (i /= 2)
            a[i] = F(a[2*i], a[2*i + 1]);
    }

    Node qu (int l, int r) {
        if (l == r) return id;
        pull(l += N), pull((r += N) - 1);
        Node x = id, y = id;
        for (; l < r; l /= 2, r /= 2) {
            if (l&1) x = F(x, a[l++]);
            if (r&1) y = F(a[--r], y);
        }
        return F(x, y);
    }

    void apply (int l, int r, const Lazy u) {
        if (l == r) return;
        pull(l += N), pull((r += N) - 1);
        for (int L = l, R = r; L < R; L /= 2, R /= 2) {
            if (L&1) on_all(L++, u);
            if (R&1) on_all(--R, u);
        }
        l >>= __builtin_ctz(l), --r >>= __builtin_ctz(r+1);
        while (l /= 2) a[l] = F(a[2*l], a[2*l + 1]);
        while (r /= 2) a[r] = F(a[2*r], a[2*r + 1]);
    }
};
