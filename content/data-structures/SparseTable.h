/**
 * Author: kingmessi
 * Date: 2024-12-23
 * License: CC0
 * Source: self
 * Description: Sparse table
 * Time: O(N \log N) build, O(1) per query, each times combine cost
 * Status: tested
 */

const int N=1e5+5; const int maxn=N;const int max_logn=20;
template<typename T>
struct SparseTable{
    int log[maxn];
    T dp[max_logn][maxn];
    T combine(T a,T b){return __gcd(a,b);}
    SparseTable(){
        log[1] = 0;
        for (int i = 2; i < maxn; i++)
            log[i] = log[i/2] + 1;
    }
    void build(vector<T> b)
    {
        int n=b.size();
        for (int i = 0; i < n; ++i){
            dp[0][i]=b[i];
        }
        for (int j = 1; j < max_logn; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                dp[j][i] = combine(dp[j - 1][i], dp[j - 1][i + (1 << (j - 1))]);
    }
    T query(int l,int r)
    {
        int j=log[r-l+1];
        return combine(dp[j][l],dp[j][r-(1<<j)+1]);
    }
};SparseTable<int> sp;