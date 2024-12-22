/**
 * Author: Piyush Pransukhka
 * Date: 2024-12-22
 * License: CC0
 * Source: self
 * Description: 2-d range queries and point updates (0-indexed)
 * Time: $O(\log N \log M)$. (Use persistent segment trees for $O(\log N)$.)
 * Status: tested
 */

template <typename T> 
struct BIT2D {
  const int n, m;
  vector<vector<T>> bit;

  BIT2D(int n, int m) : n(n), m(m), bit(n + 1, vector<T>(m + 1)) {}

  /** adds val to the point (r, c) */
  void add(int r, int c, T val) {
    r++, c++;
    for (; r <= n; r += r & -r) {
      for (int i = c; i <= m; i += i & -i) { bit[r][i] += val; }
    }
  }

  /** returns sum of points with row in [0, r] and column in [0, c] */
  T rect_sum(int r, int c) {
    r++, c++;
    T sum = 0;
    for (; r > 0; r -= r & -r) {
      for (int i = c; i > 0; i -= i & -i) { sum += bit[r][i]; }
    }
    return sum;
  }

  /** returns sum of points with row in [r1, r2] and column in [c1, c2] */
  T rect_sum(int r1, int c1, int r2, int c2) {
    return rect_sum(r2, c2) - rect_sum(r2, c1 - 1) - rect_sum(r1 - 1, c2) +
           rect_sum(r1 - 1, c1 - 1);
  }
};
