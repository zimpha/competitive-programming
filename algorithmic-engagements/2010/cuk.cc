#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

const int64 inf = 1e18;
const int N = 531441 + 10;

struct Val {
  int64 a, b, v;
  bool operator < (const Val &rhs) const {
    return a < rhs.a;
  }
} X[N], Y[N];

int64 bit[N], val[N];

int main() {
  const int pw[] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 177147, 531441};
  int n;
  scanf("%d", &n);
  std::vector<int> w(n);
  for (int i = 0; i < n; ++i) scanf("%d", &w[i]);
  int x = n / 2, y = n - x;
  int xs = 0, ys = 0;
  for (int mask = 0; mask < pw[x]; ++mask) {
    int64 a = 0, b = 0, c = 0;
    for (int i = 0, m = mask; i < x; ++i, m /= 3) {
      if (m % 3 == 0) a += w[i];
      else if (m % 3 == 1) b += w[i];
      else c += w[i];
    }
    X[xs].a = a - b;
    X[xs].b = b - c;
    val[xs] = b - c;
    X[xs++].v = c - a;
  }
  for (int mask = 0; mask < pw[y]; ++mask) {
    int64 a = 0, b = 0, c = 0;
    for (int i = 0, m = mask; i < y; ++i, m /= 3) {
      if (m % 3 == 0) a += w[i + x];
      else if (m % 3 == 1) b += w[i + x];
      else c += w[i + x];
    }
    Y[ys].a = b - a;
    Y[ys].b = c - b;
    Y[ys++].v = c - a;
  }
  std::sort(X, X + xs); std::sort(Y, Y + ys);
  std::sort(val, val + xs);
  int m = std::unique(val, val + xs) - val;
  int64 ret = inf;
  for (int i = 0; i < m; ++i) bit[i] = inf;
  for (int i = 0, j = 0; i < ys; ++i) {
    while (j < xs && X[j].a <= Y[i].a) {
      int x = std::lower_bound(val, val + m, X[j].b) - val;
      for (; x < m; x += ~x & x + 1) bit[x] = std::min(bit[x], X[j].v);
      ++j;
    }
    int x = std::upper_bound(val, val + m, Y[i].b) - val - 1;
    int64 best = inf;
    for (; x >= 0; x -= ~x & x + 1) best = std::min(best, bit[x]);
    ret = std::min(ret, Y[i].v + best);
  }
  printf("%lld\n", ret);
  return 0;
}
