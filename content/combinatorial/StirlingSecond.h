/**
 * Author: piyush_pransukhka
 * Date: 2024-12-25
 * License: CC0
 * Source: self
 * Description: Stirling numbers of second kind. Finds $S(n, k)$ for a fixed n and for all $k = 0, 1, \dots n$.
 * Requires NTT.
 * Time: O(N \log N)
 * Status: tested
 */

template<class T>
vector<T> stirling_second(int n){
  vector<T> as(n + 1), bs(n + 1), invFac(n + 1, 1);
  for (int i = 1; i <= n; ++i)
    invFac[i] = invFac[i - 1] * inv(T(i));
  for (int i = 0; i <= n; ++i)
   as[i] = invFac[i] * T(((i & 1) ? -1 : +1));
  for (int i = 0; i <= n; ++i)
   bs[i] = invFac[i] * pow(T(i), n);
  
  auto ans = conv(as, bs); // conv_general in case of MOD other than 998244353.
  while(ans.size() > n + 1){
      ans.pop_back();
  }
  return ans;
}

// using mi = mint<998244353,5>
// auto ans = stirling_second<mi>(n);