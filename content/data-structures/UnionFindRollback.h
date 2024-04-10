/**
 * Author: kingmessi
 * Date: 2024-04-08
 * License: CC0
 * Source: self
 * Description: LCA
 * Inputs must be in [0, mod).
 * Time: O(log N) per query
 * Status: tested
 */

#pragma once

struct DSUrb {
    vi e; int comp;void init(int n) { e = vi(n,-1); comp = n;}
    int get(int x) { return e[x] < 0 ? x : get(e[x]); } 
    bool sameSet(int a, int b) { return get(a) == get(b); }
    int size(int x) { return -e[get(x)]; }
    vector<array<int,4>> mod;
    bool unite(int x, int y) { // union-by-rank
        x = get(x), y = get(y); 
        if (x == y) { mod.pb({-1,-1,-1,-1}); return 0; }
        comp --;
        if (e[x] > e[y]) swap(x,y);
        mod.pb({x,y,e[x],e[y]});
        e[x] += e[y]; e[y] = x; return 1;
    }
    void rollback() {
        auto a = mod.back(); mod.pop_back();
        if (a[0] != -1) e[a[0]] = a[2], e[a[1]] = a[3],comp++;
    }
};
 
template<int SZ> struct DynaCon { 
    DSUrb D; vpii seg[2*SZ]; vi ans;
    void init(int n){D.init(n);ans.resize(SZ);}
    void upd(int l, int r, pii p) {  // add edge p to all times in interval [l, r]
        for (l += SZ, r += SZ+1; l < r; l /= 2, r /= 2) {
            if (l&1) seg[l++].pb(p);
            if (r&1) seg[--r].pb(p);
        }
    }
    void process(int ind) {
        for(auto t : seg[ind]) D.unite(t.ff,t.ss);
        if (ind >= SZ) {
            ans[ind-SZ] = D.comp;
            // do stuff with D at time ind-SZ
        } else process(2*ind), process(2*ind+1);
        for(auto t : seg[ind]) D.rollback();
    }
};
 
DynaCon<300001> dy;