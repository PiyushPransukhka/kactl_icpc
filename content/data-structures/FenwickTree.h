/**
 * Author: Piyush Pransukhka
 * Date: 2024-12-22
 * License: CC0
 * Source: self
 * Description: Can be used for min/max operations for prefix queries.
 * Time: $O(\log N)$
 * Status: tested
 */

struct FenwickTree {
    vector<int> bit;  
    int n;
 
    FenwickTree(int n) {
      this->n = n;
      bit.assign(n, 0);
    }
 
    int sum(int r) {
      int ret = 0;
      for (; r >= 0; r = (r & (r + 1)) - 1) ret += bit[r];
      return ret;
    }
 
    void add(int idx, int delta) {
      for(; idx < n; idx = idx | (idx + 1)) bit[idx] += delta;
    }
    
    // First index having prefix sum >= v
    int lower_bound(int v){
      int sum = 0, pos = 0;
      for(int i=25; i>=0; i--){
        if(pos + (1 << i) - 1 < n and sum + bit[pos + (1 << i) - 1] < v){
          sum += bit[pos + (1 << i) - 1], pos += (1 << i);
        }
      }
      return pos;
    }
};
