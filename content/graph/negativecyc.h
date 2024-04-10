/**
 * Author: piyush_pransukhka
 * Date: 2024-04-09
 * License: CC0
 * Source: self
 * Description: Negative cycle detection
 * Time: O(V \cdot E)
 * Status: tested
 */

vector<array<int,3>> edges;
bool negative_cycle(int n){
       vector<int> par(n,-1);
       vector<ll> d(n,1e18);
       int x;
       d[0]=0;
       bool any;
       for(int i=0;i<n;i++){
            any = false;
            for(auto [a,b,w] : edges){
                 if(d[b]>d[a]+w){
                     d[b]=d[a]+w,par[b]=a;
                     any=true,x=b;
                 }
            }
       }
       if(!any) return false;
       for(int i=0;i<n;i++){
          x=par[x];
       }
       vector<int> cyc={x}
       for(int i=par[x];i!=x;i=par[i]){
           cyc.push_back(i);
       }
       cyc.push_back(x);
       reverse(cyc.begin(),cyc.end());
       return true;
}