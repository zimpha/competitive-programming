#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> x(n), y(n);
  std::vector<int> a(n), b(n);
  std::vector<std::pair<int, int>> tar(n);
  for (int i = 0; i < n; ++i) scanf("%d%d", &x[i], &y[i]);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &a[i], &b[i]);
    tar[i] = {a[i], b[i]};
  }
  std::sort(tar.begin(), tar.end());
  for (int i = 0; i < n; ++i) {
    int tx = x[0] + a[i], ty = y[0] + b[i];
    std::vector<std::pair<int, int>> tmp(n);
    for (int j = 0; j < n; ++j) {
      tmp[j].first = tx - x[j];
      tmp[j].second = ty - y[j];
    }
    std::sort(tmp.begin(), tmp.end());
    if (tmp == tar) {
      printf("%d %d\n", tx, ty);
      break;
    }
  }
  return 0;
}