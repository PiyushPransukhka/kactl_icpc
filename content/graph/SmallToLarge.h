/**
 * Author: kingmessi
 * Date: 2024-12-21
 * License: CC0
 * Source: self
 * Description: sack on tree
 * Time: O(N \log N)
 * Status: tested
 */

void add(int v, int p, int x){
    for(auto u: g[v])if(u != p && !big[u])add(u, v, x)
}
void dfs(int v, int p, bool keep){
    int mx = -1, bigChild = -1;
    for(auto u : g[v])if(u != p && sz[u] > mx)mx = sz[u], bigChild = u;
    for(auto u : g[v])if(u != p && u != bigChild)dfs(u, v, 0);
    if(bigChild != -1)dfs(bigChild, v, 1), big[bigChild] = 1;
    add(v, p, 1);//answer queries now
    if(bigChild != -1)big[bigChild] = 0;
    if(keep == 0)add(v, p, -1);
}