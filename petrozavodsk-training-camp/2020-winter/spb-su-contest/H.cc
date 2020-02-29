#include <cstdio>
#include <cmath>
#include <cassert>
#include <vector>
#include <algorithm>

const int N = 2e8;
const double pi = acos(-1.0);

int table[1000][1000];
int query[20000], n;
int sum[20000];

int gcd(int x, int y) {
  if (x < 1000 && y < 1000) {
    if (!table[x][y]) table[x][y] = y ? gcd(y, x % y) : x;
    return table[x][y];
  } else {
    return y ? gcd(y, x % y) : x;
  }
}

void prepare() {
  for (int x = 1; x * x * 2 <= N; ++x) {
    int bound = sqrt(N - x * x);
    for (int y = x + 1; y <= bound; y += 2) {
      if (gcd(x, y) != 1) continue;
      int u = y * y + x * x;
      auto p = std::lower_bound(query, query + n, u) - query;
      sum[p]++;
    }
  }
}

int main() {
  int m;
  scanf("%d", &m);
  std::vector<std::pair<int, int>> q(m);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &q[i].first, &q[i].second);
    for (int j = q[i].first; j <= q[i].second; ++j) query[n++] = j;
  }
  std::sort(query, query + n);
  n = std::unique(query, query + n) - query;
  prepare();
  for (int i = 0; i < n; ++i) sum[i + 1] += sum[i];
  for (int i = 0; i < m; ++i) {
    int l = std::lower_bound(query, query + n, q[i].first) - query;
    int r = std::lower_bound(query, query + n, q[i].second) - query;
    double best = 1e9;
    int best_x, best_y;
    for (int j = l; j <= r; ++j) {
      int g = gcd(query[j], 2 * sum[j]);
      int x = query[j] / g, y = 2 * sum[j] / g;
      //if (i == 2) printf("x=%d y=%d\n", x, y);
      double error = std::abs(pi - 1.0 * x / y);
      if (error < best) {
        best = error;
        best_x = x;
        best_y = y;
      }
    }
    printf("%d / %d\n", best_x, best_y);
  }
  return 0;
}
