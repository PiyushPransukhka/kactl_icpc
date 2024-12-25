/**
 * Author: piyush_pransukhka
 * Date: 2024-12-25
 * License: CC0
 * Source: self
 * Description: Stirling numbers of first kind. Finds $S(n, k)$ for a fixed n and for all $k = 0, 1, \dots n$.
 * Requires NTT. Take absolute values of $S(n, k)$ for use.
 * Time: O(N \log N)
 * Status: tested
 */

template<class T>
vector<T> power_table(T a, ll N) {
  vector<T> f(N, 1);
  for(int i=0;i<N-1;i++) f[i + 1] = a*f[i];
  return f;
}

template<class T>
vector<T> poly_taylor_shift(vector<T> a, T c) {
  ll N = a.size();
  vector<T> fac(N,1), invFac(N,1);
  for(int i=1;i<N;i++){
    fac[i]=fac[i-1]*T(i);
    invFac[i]=invFac[i-1]*inv(T(i));
  }
  for(int i=0;i<N;i++) a[i] *= fac[i];
  auto b = power_table<T>(c, N);
  for(int i=0;i<N;i++) b[i] *= invFac[i];
  reverse(all(a));
  auto f = conv(a, b);
  f.resize(N);
  reverse(all(f));
  for(int i=0;i<N;i++) f[i] *= invFac[i];
  return f;
}

template<class T>
vector<T> stirling_first(int n) {
  if (n == 0) return {1};
  if (n == 1) return {0, 1};
  auto f = stirling_first<T>(n / 2);
  auto g = poly_taylor_shift(f, T(-(n / 2)));
  f = conv(f, g);
  if (n & 1) {
    g = {-(n - 1), 1};
    f = conv(f, g);
  }
  return f;
}

// using mi = mint<998244353,5>
// auto ans = stirling_first<mi>(n);