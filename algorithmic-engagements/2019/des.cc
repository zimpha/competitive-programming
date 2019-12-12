#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>

const int N = 50, M = 4e6;

using uint64 = unsigned long long;
using uint = unsigned int;

int next[N][N], prev[N][N];
uint suf_prod[N][N];
int a[N], n;

struct Node {
  uint64 mask;
  uint64 ways;
  int inv;
} dp[2][M];

void update(Node &now, int inv, uint64 ways) {
  if (now.inv == -1 || inv < now.inv) {
    now.inv = inv;
    now.ways = 0;
  }
  if (inv == now.inv) now.ways += ways;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 0; i < n; ++i) {
    suf_prod[i][n + 1] = 1;
    for (int x = n; x >= 0; --x) {
      int y = n + 1, z = 0;
      for (int j = i; j < n; ++j) {
        if (a[j] > x && a[j] < y) y = a[j];
        if (a[j] < x && a[j] > z) z = a[j];
      }
      next[i][x] = y; prev[i][x] = z;
      suf_prod[i][x] = suf_prod[i][y] * (y - x);
    }
  }
  suf_prod[n][0] = n + 1;
  Node* f = dp[0], *g = dp[1];
  f[0] = (Node){0, 1, 0};
  for (int i = 0; i < n; ++i) {
    int l = prev[i][a[i]], r = next[i][a[i]];
    uint maskr = suf_prod[i][r];
    uint maski = suf_prod[i][a[i]];
    uint maskl = suf_prod[i][l];
    memset(g, -1, sizeof(*g) * suf_prod[i + 1][0]);
    for (uint state = 0; state < suf_prod[i][0]; ++state) {
      const auto &val = f[state];
      // ---l---i---r--- -> state1, state2, state3, state4
      uint state1 = state / maskl;
      uint state2 = state / maski % (a[i] - l);
      uint state3 = state / maskr % (r - a[i]);
      uint state4 = state % maskr;
      uint64 mask1 = val.mask & ((uint64(1) << l) - 1);
      uint64 mask3 = val.mask >> r << r;
      int k = state2 + state3;
      // not choose
      uint next_state = state4 + k * maskr + state1 * suf_prod[i + 1][l];
      g[next_state].mask = mask1 | (((uint64(1) << k) - 1) << l) | mask3;
      update(g[next_state], val.inv, val.ways);
      // choose
      next_state += maskr;
      g[next_state].mask = mask1 | (((uint64(1) << (k + 1)) - 1) << l) | mask3;
      int cnt = __builtin_popcountll(val.mask >> a[i]);
      update(g[next_state], val.inv + cnt, val.ways);
    }
    std::swap(f, g);
  }
  for (int i = 1; i <= n; ++i) {
    assert(__builtin_popcountll(f[i].mask) == i);
    printf("%d %lld\n", f[i].inv, f[i].ways);
  }
  return 0;
}
