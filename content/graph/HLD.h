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

//euler,seg,hld combined
const int MX = 2e5+5;
template<int SZ, bool VALS_IN_EDGES> struct HLD { 
    int N; vi adj[SZ];
    int par[SZ], root[SZ], depth[SZ], sz[SZ], ti;
    int pos[SZ]; vi rpos; // rpos not used but could be useful
    void ae (int x, int y) { adj[x].pb(y), adj[y].pb(x); }
    void dfsSz (int x) { 
        sz[x] = 1; 
        for(auto& y : adj[x]) {
            par[y] = x; depth[y] = depth[x]+1;
            adj[y].erase(find(be(adj[y]),x)); /// remove parent from adj list
            dfsSz(y); sz[x] += sz[y];
            if (sz[y] > sz[adj[x][0]]) swap(y,adj[x][0]);
        }
    }
    void dfsHld (int x) {
        pos[x] = ti++; rpos.pb(x);
        for(auto y : adj[x]) {
            root[y] = (y == adj[x][0] ? root[x] : y);
            dfsHld(y); }
    }
    void init (int _N, int R = 0) { N = _N; 
        par[R] = depth[R] = ti = 0; dfsSz(R); 
        root[R] = R; dfsHld(R);
    }
    void clear () {
        rep(i,0,N+1){
            par[i]=0,root[i]=0,depth[i]=0,sz[i]=0,pos[i]=0;
            adj[i].clear();
        }
        ti=0;rpos.clear();
    }
    int lca (int x, int y) {
        for (; root[x] != root[y]; y = par[root[y]])
            if (depth[root[x]] > depth[root[y]]) swap(x,y);
        return depth[x] < depth[y] ? x : y;
    }
    int dist (int x, int y) { // # edges on path
        return depth[x]+depth[y]-2*depth[lca(x,y)]; }
    // [u, v)
    vector<pii> ascend (int u, int v) const {
      vector<pii> res;
      while (root[u] != root[v]) {
        res.emplace_back(pos[u], pos[root[u]]);
        u = par[root[u]];
      }
      if (u != v) res.emplace_back(pos[u], pos[v] + 1);
      return res;
    }
    // (u, v]
    vector<pii> descend (int u, int v) const {
      if (u == v) return {};
      if (root[u] == root[v]) return {{pos[u] + 1, pos[v]}};
      auto res = descend(u, par[root[v]]);
      res.emplace_back(pos[root[v]], pos[v]);
      return res;
    }
};
HLD<MX,0> hl;