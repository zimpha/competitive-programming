#include <bits/stdc++.h>

void run() {
  int n;
  std::cin >> n;
  int sg = 0;
  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    sg ^= ~x & 1;
    if (sg) puts("1");
    else puts("2");
  }
}

int main() {
  run();
  return 0;
}
