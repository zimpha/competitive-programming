#include <cstdio>
#include <vector>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> cnt(m);
  for (int i = 0, x; i < n; ++i) {
    scanf("%d", &x);
    cnt[x - 1]++;
  }
  int ret = 0;
  for (auto &x: cnt) {
    if (x > ret) ret = x;
  }
  printf("%d\n", ret);
  return 0;
}
