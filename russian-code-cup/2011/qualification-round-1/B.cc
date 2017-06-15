#include <cstdio>
#include <vector>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> c(n), t(n), p(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d%d", &c[i], &t[i], &p[i]);
  }
  std::vector<int> d(m);
  for (int i = 0; i < m; ++i) {
    scanf("%d", &d[i]);
  }
  int ret = -1;
  long long cost = 0;
  for (int i = 0; i < n; ++i) {
    long long now = c[i] * 100;
    for (auto &&T: d) {
      int k = (T + t[i] - 1) / t[i];
      if (T >= t[i]) now += k * p[i];
    }
    if (ret == -1 || now < cost) {
      ret = i;
      cost = now;
    }
  }
  printf("%d\n", ret + 1);
  return 0;
}
