#include <bits/stdc++.h>

int run(int n, int m) {
  std::vector<int> p;
  std::vector<bool> mark(m + 1, 0);
  for (int i = 2; i <= m; ++i) if (!mark[i]) {
    p.push_back(i);
    for (int j = i; j <= m; j += i) mark[j] = 1;
  }
  m = p.size();
  std::vector<int> f;
  f.push_back(1);
  int ret = 1;
  for (int i = 0; i < m; ++i) {
    int val = 1;
    std::vector<int> g;
    for (; ;) {
      if (1ll * val * p[i] > n) break;
      val *= p[i];
      for (auto &e: f) {
        if (1ll * val * e > n) break;
        g.push_back(val * e);
      }
    }
    for (auto &e: g) f.push_back(e);
    std::sort(f.begin(), f.end());
    ret += g.size();
  }
  return ret;
}

int main() {
  std::cout << run(100000000, 5) << std::endl;
  std::cout << run(1000000000, 100) << std::endl;
  return 0;
}
