#include <cstdio>
#include <vector>

int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  std::vector<int> c(k), f(k);
  for (int i = 0; i < k; ++i) scanf("%d%d", &c[i], &f[i]);
  int best = -1;
  for (int mask = 0; mask < 32; ++mask) {
    std::vector<bool> mark(n);
    for (int i = 0; i < k; ++i) {
      if (mask >> (f[i] - 1) & 1) mark[c[i] - 1] = 1;
    }
    int sum = 0;
    for (int i = 0; i < n; ++i) sum += !mark[i];
    if (sum <= m) best = std::max(best, sum);
  }
  if (best == -1) puts("Round will be unrated");
  else printf("%d\n", best);
  return 0;
}
