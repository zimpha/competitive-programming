#include <cstdio>
#include <vector>

using int64 = long long;

int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  std::vector<int> col(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &col[i]);
    --col[i];
  }
  std::vector<int> u(m), v(m);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &u[i], &v[i]);
    --u[i], --v[i];
  }
  std::vector<std::vector<int64>> ways(n, std::vector<int64>(1 << k));
  for (int i = 0; i < n; ++i) {
    ways[i][1 << col[i]] = 1;
  }
  for (int l = 1; l < k; ++l) {
    for (int mask = 0; mask < (1 << k); ++mask) {
      if (__builtin_popcount(mask) != l) continue;
      for (int i = 0; i < m; ++i) {
        int a = u[i], b = v[i];
        if ((~mask >> col[b] & 1) && ways[a][mask]) {
          ways[b][mask | (1 << col[b])] += ways[a][mask];
        }
        if ((~mask >> col[a] & 1) && ways[b][mask]) {
          ways[a][mask | (1 << col[a])] += ways[b][mask];
        }
      }
    }
  }
  int64 ret = 0;
  for (int i = 0; i < n; ++i) {
    for (int mask = 0; mask < (1 << k); ++mask) {
      ret += ways[i][mask];
    }
  }
  printf("%lld\n", ret - n);
  return 0;
}
