/**
 * Author: kingmessi
 * Date: 2024-12-21
 * License: CC0
 * Source: self
 * Description: binary lifting, computes lca
 * Time: O(\log N) per query
 * Status: tested
 */

const int N = 2e5+5;
int depth[N],visited[N],up[N][20];
vi adj[N];vpii bkedge;


void dfs(int v) {
    visited[v]=true;
    rep(i,1,20)if(up[v][i-1]!=-1)up[v][i] = up[up[v][i-1]][i-1];
    for(int x : adj[v]) {
        if(!visited[x]) { 
            depth[x] = depth[up[x][0] = v]+1;
            dfs(x);
        }
        else if(x!=up[v][0] && depth[v]>depth[x])bkedge.pb({v,x});
    }
}

int jump(int x, int d) {
    rep(i,0,20){
        if((d >> i) & 1)
            {if(x==-1)break;x = up[x][i];}
    }return x;
}

int LCA(int a, int b) {
    if(depth[a] < depth[b]) swap(a, b);
    a = jump(a, depth[a] - depth[b]);
    if(a == b) return a;
    rrep(i,19,0){
        int aT = up[a][i], bT = up[b][i];
        if(aT != bT) a = aT, b = bT;
    }
    return up[a][0];
}