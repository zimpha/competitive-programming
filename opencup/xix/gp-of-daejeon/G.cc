#include <cstdio>
#include <cassert>
#include <vector>

const int N = 10;

bool good[N][N];
int from[N], to[N], mask[N];
int n, k;
bool has_zero, has_all;

int dfs(int x, int y) {
  if (x == 0) {
    for (int z = 0; z < y; ++z) if (to[z] >> (y - 1) & 1) {
      if ((to[z] & to[y - 1]) != to[y - 1]) return 0;
      if ((from[z] & from[y - 1]) != from[z]) return 0;
    }
    for (int z = 0; z < y; ++z) if (to[y - 1] >> z & 1) {
      if ((to[z] & to[y - 1]) != to[z]) return 0;
      if ((from[z] & from[y - 1]) != from[y - 1]) return 0;
    }
  }
  if (x == 0 && y == k) {
    int a = (1 << k) - 1, b = 0;
    for (int i = 0; i < k; ++i) {
      if (to[i] + 1 == (1 << k)) continue;
      a &= to[i]; b |= to[i];
    }
    int ret = 1;
    if (!has_all && b + 1 != (1 << k)) ret *= 2;
    if (!has_zero && a != 0) ret *= 2;
    return ret;
  }
  int nx, ny;
  if (x < y) nx = y, ny = x;
  else if (y == x - 1) nx = 0, ny = x + 1;
  else nx = y + 1, ny = x;
  if (!good[x][y]) return dfs(nx, ny);
  int ret = dfs(nx, ny);
  int mask = (1 << std::min(x, y)) - 1;
  int to_y = to[y] & mask, to_x = to[x] & mask;
  int from_y = from[y] & mask, from_x = from[x] & mask;
  if ((to_x & to_y) == to_y && (from_x & from_y) == from_x) {
    to[x] ^= 1 << y; from[y] ^= 1 << x;
    ret += dfs(nx, ny);
    to[x] ^= 1 << y; from[y] ^= 1 << x;
  }
  return ret;
}

int main() {
  scanf("%d%d", &k, &n);
  for (int i = 0; i < k; ++i) {
    for (int j = 0; j < i; ++j) {
      good[i][j] = good[j][i] = 1;
    }
  }
  for (int i = 0, x; i < n; ++i) {
    scanf("%d", &x);
    if (x == 0) has_zero = 1;
    if (x + 1 == (1 << k)) has_all = 1;
    for (int a = 0; a < k; ++a) {
      for (int b = 0; b < k; ++b) {
        if ((x >> a & 1) && (~x >> b & 1)) good[a][b] = 0;
      }
    }
  }
  for (int i = 0; i < k; ++i) to[i] = from[i] = 1 << i;
  int ret = dfs(0, 1);
  if (n == 0) --ret;
  printf("%d\n", ret);
  return 0;
}
