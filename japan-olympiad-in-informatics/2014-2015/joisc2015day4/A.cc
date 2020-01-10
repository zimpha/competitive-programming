#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int K = 10000 + 10, N = 1e3 + 10;

int dsu[K][N], size[K][N];

int get(int dsu[], int x) {
  if (dsu[x] < 0) return x;
  else return get(dsu, dsu[x]);
}

int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  std::vector<int> a(m), b(m), c(m);
  std::vector<int> idx(m);
  for (int i = 0; i < m; ++i) {
    idx[i] = i;
    scanf("%d%d%d", &a[i], &b[i], &c[i]);
    --a[i], --b[i];
  }
  std::sort(idx.begin(), idx.end(), [&](int x, int y) {
    return c[x] > c[y];
  });
  for (int i = 0; i < k; ++i) {
    memset(dsu[i], -1, sizeof(*dsu[i]) * n);
  }
  std::vector<int> ret(m);
  for (auto &i: idx) {
    if (get(dsu[k - 1], a[i]) == get(dsu[k - 1], b[i])) continue;
    int l = 0, r = k - 1;
    while (l < r) {
      int m = (l + r - 1) >> 1;
      if (get(dsu[m], a[i]) != get(dsu[m], b[i])) r = m;
      else l = m + 1;
    }
    ret[i] = r + 1;
    int u = get(dsu[r], a[i]);
    int v = get(dsu[r], b[i]);
    if (-dsu[r][u] < -dsu[r][v]) std::swap(u, v);
    dsu[r][u] += dsu[r][v];
    dsu[r][v] = u;
  }
  for (int i = 0; i < m; ++i) printf("%d\n", ret[i]);
  return 0;
}
