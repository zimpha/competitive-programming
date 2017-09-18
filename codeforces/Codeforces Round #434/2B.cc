#include <cstdio>
#include <vector>
#include <set>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> k(m), f(m);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &k[i], &f[i]);
  }
  std::set<int> valid;
  for (int d = 1; d <= 200; ++d) {
    bool flag = true;
    for (int i = 0; i < m && flag; ++i) {
      flag &= (f[i] - 1 == (k[i] - 1) / d);
    }
    if (flag) {
      valid.insert((n - 1) / d + 1);
    }
  }
  if (valid.size() == 1) printf("%d\n", *valid.begin());
  else puts("-1");
  return 0;
}
