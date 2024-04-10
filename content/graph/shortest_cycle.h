/**
 * Author: piyush_pransukhka
 * Date: 2024-04-09
 * License: CC0
 * Source: self
 * Description: Shortest cycle
 * Time: O(V \cdot (V + E))
 * Status: tested
 */

vector<vector<int>> adj;

int shortest_cycle(int n){
       int ans=1e9;
       for(int i=0;i<n;i++){
           vector<int> dis(n,-1);
           vector<int> par(n,-1);
           queue<int> q;
           q.push(i);
           dis[i]=0;

           while(!q.empty()){
               int v=q.front();
               q.pop();

               for(auto u : adj[v]){
                    if(dis[u]==-1){
                        dis[u]=dis[v]+1;
                        q.push(u);
                        par[u]=v;
                    }

                    else if(par[v]!=u && par[v]!=u){
                           ans=min(ans,dis[u]+dis[v]+1);    
                    } 
               }
           }
       }

       if(ans==1e9)
          ans=-1;

       return ans;
}
