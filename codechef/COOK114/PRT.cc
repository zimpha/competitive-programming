#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 3e5 + 10;
const int mod = 1e9 + 7;

using int64 = long long;

std::vector<int> edges[N];
int A[N], size[N], n, m;
int64 cnt[N];

void dfs(int u, int p = -1) {
  size[u] = edges[u].size() == 1;
  for (auto &v: edges[u]) if (v != p) {
    dfs(v, u);
    cnt[u] += (int64)size[u] * size[v];
    size[u] += size[v];
  }
  cnt[u] += (int64)size[u] * (m - size[u]);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &A[i]);
      cnt[i] = 0;
      edges[i].clear();
    }
    for (int i = 1; i < n; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      --u, --v;
      edges[u].push_back(v);
      edges[v].push_back(u);
    }
    m = 0;
    for (int i = 0; i < n; ++i) {
      m += edges[i].size() == 1;
    }
    dfs(0);
    std::sort(A, A + n);
    std::sort(cnt, cnt + n);
    int64 ret = 0;
    for (int i = 0; i < n; ++i) {
      ret += cnt[i] % mod * A[i] % mod;
    }
    printf("%lld\n", ret % mod);
  }
  return 0;
}
