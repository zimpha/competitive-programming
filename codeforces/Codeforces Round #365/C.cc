#include <bits/stdc++.h>

void run() {
  int n;
  double u, v, w;
  std::cin >> n >> w >> v >> u;
  double l = 1e9, r = 0;
  for (int i = 0; i < n; ++i) {
    double x, y;
    std::cin >> x >> y;
    l = std::min(l, x - y / u * v);
    r = std::max(r, x - y / u * v);
  }
  printf("%.10f\n", w / u + r / v * (l < 0));
}

int main() {
  run();
  return 0;
}
