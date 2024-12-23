/**
 * Author: piyush_pransukhka
 * Date: 2024-12-23
 * License: CC0
 * Source: self
 * Description: lehmer(n) gives the count of prime numbers <= n.
 * Highly optimised, works well for $n <= 10^{12}$ under 1.5 sec.
 * Time: $O(N ^ \frac{2}{3})$
 * Status: tested
 */

#define ll long long

const int MAXN=100;
const int MAXM=100010;
const int MAXP=10000010;
 
int prime_cnt[MAXP];
ll dp[MAXN][MAXM];
 
vector<int> primes;
bitset<MAXP> is_prime;
 
void sieve(){
   is_prime[2]=true;
   for(int i=3;i<MAXP;i+=2){
      is_prime[i]=true;
   }
   for(int i=3;i*i<MAXP;i+=2){
    for(int j=i*i;is_prime[i] && j<MAXP; j+=(i<<1)){
            is_prime[j]=false;
     }
   }
 
   for(int i=1;i<MAXP;i++){
      prime_cnt[i]=prime_cnt[i-1]+is_prime[i];
      if(is_prime[i]){
         primes.push_back(i);
      }
   }
}
 
void gen(){
    sieve();
    for(int i=0;i<MAXM;i++){
         dp[0][i]=i;
    }
    for(int n=1;n<MAXN;n++){
        for(int m=0;m<MAXM;m++){
             dp[n][m]=dp[n - 1][m]-dp[n - 1][m/primes[n-1]];
        }
    }
}
 
ll phi(ll m,ll n){
    if (n==0) return m;
    if (m<MAXM && n<MAXN) return dp[n][m];
    if ((ll)primes[n-1]*primes[n - 1]>=m && m<MAXP) 
        return prime_cnt[m]-n+1;
 
    return phi(m,n-1)-phi(m/primes[n - 1],n-1);
}
 
ll lehmer(ll m){
    if (m<MAXP) return prime_cnt[m];
 
    int s=sqrtl(0.5+m), y=cbrtl(0.5+m);
    int a=prime_cnt[y];
 
    ll res = phi(m,a)+a-1;
    for (int i=a;primes[i]<=s;i++){
        res=res-lehmer(m/primes[i])+lehmer(primes[i])-1;
    }
    return res;
}

// Call gen() in main
