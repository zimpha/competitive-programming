#include <cstdio>
#include <vector>

int main() {
  int n, d;
  scanf("%d%d", &n, &d);
  std::vector<int> x(n), y(n), t(n);
  bool find = false;
  for (int i = 0; i < n && !find; ++i) {
    scanf("%d%d%d", &x[i], &y[i], &t[i]);
    for (int j = 0; j < i && !find; ++j) {
      if (t[i] == t[j]) continue;
      if (d * d == (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j])) {
        find = true;
      }
    }
  }
  if (find) puts("Yes");
  else puts("No");
  return 0;
}
