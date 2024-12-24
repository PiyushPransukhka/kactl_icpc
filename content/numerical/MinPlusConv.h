/**
 * Author: piyush_pransukhka
 * Date: 2024-12-23
 * License: CC0
 * Source: self
 * Description: Min-plus convolution for arbitrary + convex arrays.
 * B is convex : $b_{i+1} - b_{i} \leq b_{i+2} - b_{i+1}$
 * Given arrays a and b (1-indexed), finds array c such that
 * $\displaystyle c[k] = \min\nolimits_{k = i + j} a[i] + b[j]$,
 * Time: O((N + M) \log N)
 * Status: tested
 */

#define int long long

template <typename F>
vector<int> monotone_minima(int H, int W, F select) {
  vector<int> min_col(H);
  auto dfs = [&](auto& dfs, int x1, int x2, int y1, int y2) -> void {
    if (x1 == x2) return;
    int x = (x1 + x2) / 2;
    int best_y = y1;
    for (int y = y1 + 1; y < y2; ++y) {
      if (select(x, best_y, y)) best_y = y;
    }
    min_col[x] = best_y;
    dfs(dfs, x1, x, y1, best_y + 1);
    dfs(dfs, x + 1, x2, best_y, y2);
  };
  dfs(dfs, 0, H, 0, W);
  return min_col;
}

// B is convex
vector<int> min_plus_convolution(vector<int> A, vector<int> B) {
  int N = A.size(), M = B.size();
  for (int i = 0; i < M - 2; ++i) assert(B[i] + B[i + 2] >= 2 * B[i + 1]);
  auto select = [&](int i, int j, int k) -> bool {
    if (i < k) return false;
    if (i - j >= M) return true;
    return A[j] + B[i - j] >= A[k] + B[i - k];
  };
  vector<int> J = monotone_minima(N + M - 1, N, select);
  vector<int> C(N + M - 1);
  for (int i = 0; i < N + M - 1; ++i) {
    int j = J[i];
    C[i] = A[j] + B[i - j];
  }
  return C;
}