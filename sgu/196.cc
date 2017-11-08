#include <cstdio>
#include <vector>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> d(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    d[--u]++;
    d[--v]++;
  }
  long long ret = 0;
  for (auto &&u: d) ret += 1ll * u * u;
  printf("%lld\n", ret);
  return 0;
}
