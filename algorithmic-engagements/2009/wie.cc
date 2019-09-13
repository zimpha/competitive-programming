#include <cstdio>
#include <cassert>
#include <limits>
#include <algorithm>

using uint64 = unsigned long long;
using uint32 = unsigned int;

const int N = 2048;

struct RMQ {
  int q[N], val[N];
  int head, tail, n;

  void init() {
    head = n = 0;
    tail = -1;
  }

  void append(int x) {
    val[n] = x;
    while (head <= tail && val[q[tail]] >= x) --tail;
    q[++tail] = n++;
  }

  int query(int l) {
    while (head <= tail && q[head] < l) ++head;
    assert(head <= tail);
    return val[q[head]];
  }
} rmq_i[N], rmq_j[N];

int from[2][N], dp[N][N];
int t[N], n;

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &t[i]);
    rmq_i[i].init();
    rmq_j[i].init();
  }
  for (int i = 0; i < n; ++i) {
    if (i + 1 < n) rmq_i[i].append(t[i] + t[i + 1]);
    if (i) rmq_j[i].append(t[i] + t[i - 1]);
    dp[i][i] = t[i];
    from[1][i] = i;
  }
  for (int l = 2; l <= n; ++l) {
    int u = l & 1, v = u ^ 1;
    for (int i = 0; i + l <= n; ++i) {
      int j = i + l - 1, &k = from[v][i];
      for (k = from[u][i]; k <= j && dp[i][k - 1] <= dp[k + 1][j]; ++k);
      --k;
      int best = std::min(dp[i][j - 1] + t[j], dp[i + 1][j] + t[i]);
      best = std::min(best, rmq_j[j].query(j - k - 1));
      best = std::min(best, rmq_i[i].query(k - i));
      if (j + 1 < n) rmq_i[i].append(best + t[j + 1]);
      if (i) rmq_j[j].append(best + t[i - 1]);
      dp[i][j] = best;
    }
  }
  printf("%d\n", dp[0][n - 1]);
  return 0;
}
