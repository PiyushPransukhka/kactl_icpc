/**
 * Author: koderkushy
 * Date: 2024-04-08
 * License: CC0
 * Source: self
 * Description: Centroid Decomposition.
 * Status: tested
 */

#pragma once

class CentroidTree {
public:
    CentroidTree (const vector<vector<int>>& Adj, int root = 0)
    : N(size(Adj)), adj(Adj), sub(N, 1), vis(N), par(N) {}

    void decompose (const int rt, const int p = -1) {
        auto [centroid, size] = get_centroid (rt);
        // solve here. Don't visit vis[u] = 1 vertices

        vis[centroid] = true, par[centroid] = p;
        for (auto v: adj[centroid])
            if (!vis[v]) decompose(v, centroid);
    }

private:
    int internal_dfs (int u, int p = -1) {
        for (auto v: adj[u]) if (!vis[v] and p != v)
            sub[u] += internal_dfs(v, u);
        return sub[u];
    }

    pii get_centroid (int rt) {
        internal_dfs(rt);
        const int size = sub[rt];
        int p = -1, c = rt;
        loop:;
        for (auto v: adj[c])
            if (!vis[v] and v != p and sub[v] > size / 2) {
                p = c, c = v;
                goto loop;
            }
        return {c, size};
    }

    const int N;
    vector<vector<int>> adj;
    vector<int> sub, par;
    vector<bool> vis;
};
