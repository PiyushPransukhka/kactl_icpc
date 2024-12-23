/**
 * Author: piyush_pransukhka
 * Date: 2024-12-23
 * License: CC0
 * Source: self
 * Description: Given arrays a and b (1-indexed), finds array c such that
 * $\displaystyle c[z] = \sum\nolimits_{z = gcd(x,y)} a[x] \cdot b[y]$,
 * Time: O(N \log N)
 * Status: tested
 */

const int MOD = 998244353;

void zeta(vector<ll>& a) {
  int n = a.size() - 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 2; j <= n / i; ++j) {
      a[i] += a[i * j];
      if (a[i] >= MOD) a[i] -= MOD;
    }
  }
}

void mobius(vector<ll>& a) {
  int n = a.size() - 1;
  for (int i = n; i >= 1; --i) {
    for (int j = 2; j <= n / i; ++j) {
      a[i] -= a[i * j];
      if (a[i] < 0) a[i] += MOD;
    }
  }
}

vector<ll> gcd_conv(vector<ll> a, vector<ll> b){
    zeta(a);
    zeta(b);

    int n = (int)a.size() - 1;
    vector<ll> c(n+1);
    for(int i=1;i<=n;i++){
        c[i]=(a[i]*b[i])%MOD;
    }

    mobius(c);
    return c;
}