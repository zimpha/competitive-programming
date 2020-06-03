/*
 * Q_i < i
 *   + A_{Q_i} > A_i: lower_bound in convex
 *   + A_{Q_i} < A_i: straight
 * Q_i > i:
 *   + A_i < A_{Q_i}: lower_bound in convex
 *   +
 *
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 2e5 + 10;

int64 x[N], y[N];
int a[N], q[N], np;
int n;

int64 gcd(int64 a, int64 b) {
  return b ? gcd(b, a % b) : a;
}

int64 ccw(int64 xa, int64 ya, int64 xb, int64 yb, int64 xc, int64 yc) {
  return (xb - xa) * (yc - ya) - (yb - ya) * (xc - xa);
}

std::pair<int64, int64> solve(int i) {
  if (q[i] < i) {
    if (a[q[i]] > a[i]) {
      auto p = std::lower_bound(y, y + np, a[i]) - y;;
      if (p == 0) return {-1, -1};
      --p;
      return {a[q[i]] - y[p], q[i] - p};
    } else {
      return {a[i] - a[q[i]], i - q[i]};
    }
  } else {
    if (a[i] < a[q[i]]) {
      auto p = std::lower_bound(y, y + np, a[i]) - y;;
      if (p == 0) return {a[q[i]] - a[i], q[i] - i};
      --p;
      if (ccw(x[p], y[p], i, a[i], q[i], a[q[i]]) >= 0) return {a[q[i]] - y[p], q[i] - x[p]};
      else return {a[q[i]] - a[i], q[i] - i};
    } else {
      int best = -1;
      for (int j = q[i] + 1; j < n; ++j) if (a[j] > a[i]) {
        if (best == -1 || ccw(q[i], a[q[i]], j, a[j], best, a[best]) > 0) best = j;
      }
      if (best == -1) return {-1, -1};
      else return {best - q[i], a[best] - a[q[i]]};
    }
  }
}

int main() {
  freopen("falling.in", "r", stdin);
  freopen("falling.out", "w", stdout);
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &q[i]);
    --q[i];
  }
  int m = std::max_element(a, a + n) - a;
  for (int i = 0; i <= m; ++i) {
    while (np >= 2 && ccw(x[np - 2], y[np - 2], x[np - 1], y[np - 1], i, a[i]) >= 0) --np;
    x[np] = i; y[np] = a[i]; ++np;
  }
  //for (int i = 0; i < np; ++i) printf("(%lld %lld)\n", x[i], y[i]);
  for (int i = 0; i < n; ++i) {
    auto ret = solve(i);
    if (ret.first == -1) puts("-1");
    else {
      auto g = gcd(ret.first, ret.second);
      printf("%lld/%lld\n", ret.first / g, ret.second / g);
    }
  }
  return 0;
}
