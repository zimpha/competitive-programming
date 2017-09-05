#include <bits/stdc++.h>

void run() {
  int a, b;
  std::cin >> a >> b;
  int n;
  std::cin >> n;
  double res = 1e9;
  for (int i = 0; i < n; ++i) {
    int x, y, v;
    std::cin >> x >> y >> v;
    double dis = hypot(x - a, y - b) / v;
    res = std::min(res, dis);
  }
  printf("%.10f\n", res);
}

int main() {
  run();
  return 0;
}
