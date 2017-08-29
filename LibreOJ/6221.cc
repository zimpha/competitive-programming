#include <cstdio>
#include <vector>
#include <cmath>
#include <iostream>

using int64 = long long;

std::pair<int64, int64> dfs(int d, int64 now, int64 upp, const std::vector<int64> &p) {
  int64 cnt = 1, sum = now;
  for (int i = d; i < p.size(); ++i) {
    if (p[i] > upp / p[i]) break;
    int64 t_now = now, t_upp = upp;
    t_now *= p[i] * p[i];
    t_upp /= p[i] * p[i];
    while (true) {
      auto tmp = dfs(i + 1, t_now, t_upp, p);
      cnt += tmp.first;
      sum += tmp.second;
      if (t_upp < p[i]) break;
      t_now *= p[i];
      t_upp /= p[i];
    }
  }
  return {cnt, sum};
}

int main() {
  int64 n;
  std::cin >> n;
  const int m = static_cast<int>(sqrt(n));
  std::vector<int64> p, mark(m + 1);
  for (int i = 2; i <= m; ++i) if (!mark[i]) {
    p.push_back(i);
    for (int j = i + i; j <= m; j += i) mark[j] = true;
  }
  auto res = dfs(0, 1, n, p);
  std::cout << res.first << std::endl << res.second << std::endl;
  return 0;
}
