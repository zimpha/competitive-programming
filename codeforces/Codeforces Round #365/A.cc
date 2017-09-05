#include <bits/stdc++.h>

void run() {
  int n;
  std::cin >> n;
  int m = 0, c = 0;
  for (int i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    if (x > y) ++m;
    if (x < y) ++c;
  }
  if (m > c) puts("Mishka");
  if (m < c) puts("Chris");
  if (m == c) puts("Friendship is magic!^^");
}

int main() {
  run();
  return 0;
}
