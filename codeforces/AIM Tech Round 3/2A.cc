#include <bits/stdc++.h>

void run() {
  int n, b, d;
  std::cin >> n >> b >> d;
  int ret = 0, now = 0;
  for (int i = 0; i < n; ++i) {
    int a;
    std::cin >> a;
    if (a > b) continue;
    now += a;
    if (now > d) {
      now = 0;
      ++ret;
    }
  }
  std::cout << ret << std::endl;
}

int main() {
  run();
  return 0;
}
