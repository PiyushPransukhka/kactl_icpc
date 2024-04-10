/**
 * Author: koderkushy
 * Date: 2024-04-08
 * License: CC0
 * Source: self
 * Description: Suffix automaton.
 * Status: tested
 */

#pragma once

template<size_t A_SZ = 26, char A_0 = 'a'>
struct SufAut {
    using map = array<int, A_SZ>;
    vector<int> len{0}, link{-1}, fst{-1};
    vector<bool> cln{0};
    vector<map> nx{{}};
    int l = 0;
    int push (int l, int sl, int fp, bool c, const map &adj) {
        len.push_back(l), link.push_back(sl);
        fst.push_back(fp), cln.push_back(c);
        nx.push_back(adj); return len.size() - 1;
    }
    void extend (const char c) {
        int cur = push(len[l]+1, -1, len[l], 0, {}), p = l;
        l = cur;
        while (~p and !nx[p][c - A_0])
            nx[p][c - A_0] = cur, p = link[p];
        if (p == -1) return void(link[cur] = 0);
        int q = nx[p][c - A_0];
        if (len[q] == len[p] + 1)
            return void (link[cur] = q);
        int cln = push(len[p] + 1, link[q], fst[q], true, nx[q]);
        while (~p and nx[p][c - A_0] == q)
            nx[p][c - A_0] = cln, p = link[p];
        link[q] = link[cur] = cln;
    } 
    int find (const string& s) {
        int u = 0;
        for (const auto c: s) {
            u = nx[u][c - A_0];
            if (!u) return -1;
        }
        return u;
    }
    vector<int> counts () {
        int n = size(len);
        vector c(n, 0);
        vector<vector<int>> inv(n);
        for (int i = 1; i < n; i++)
            inv[link[i]].push_back(i);
        auto dfs = [&](auto dfs, int u) -> void {
            c[u] = !cln[u];
            for (auto v: inv[u])
                dfs(dfs, v), c[u] += c[v];
        };
        dfs(dfs, 0); return c;
    }
};