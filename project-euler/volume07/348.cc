#include <bits/stdc++.h>

using LL = long long;

bool is_pal(int n) {
  int r = 0;
  for (int m = n; m; m /= 10) {
    r = r * 10 + m % 10;
  }
  return r == n;
}

LL run() {
  const int n = 1000000000;
  std::map<int, int> cnt;
  for (int i = 2; i * i <= n; ++i) {
    for (int j = 2; j * j * j + i * i <= n; ++j) {
      int val = i * i + j * j * j;
      if (is_pal(val)) cnt[val]++;
    }
  }
  int ret = 0, k = 0;
  for (auto &&x: cnt) if (x.second == 4) {
    ret += x.first;
    if (++k == 5) break;
  }
  return ret;
}

int main() {
  std::cout << run() << std::endl;
  return 0;
}

