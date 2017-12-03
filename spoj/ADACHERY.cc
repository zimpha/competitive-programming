#include <cstdio>
#include <vector>

const int N = 1e5 + 10;

std::vector<int> edges[N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> a(m), b(m), deg(n);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &a[i], &b[i]);
    if (a[i] > b[i]) std::swap(a[i], b[i]);
    deg[a[i]]++;
    deg[b[i]]++;
  }
  long long ret = 0;
  for (int i = 0; i < n; ++i) {
    ret += 1ll * deg[i] * (deg[i] - 1) / 2;
  }
  for (int i = 0; i < m; ++i) {
    if (deg[a[i]] < deg[b[i]]) edges[a[i]].push_back(b[i]);
    else edges[b[i]].push_back(a[i]);
  }
  std::vector<bool> mark(n, false);
  for (int a = 0; a < n; ++a) {
    for (auto &&b: edges[a]) mark[b] = true;
    for (auto &&b: edges[a]) {
      for (auto &&c: edges[b]) ret -= mark[c] * 3;
    }
    for (auto &&b: edges[a]) mark[b] = false;
  }
  printf("%lld\n", ret);
  return 0;
}
