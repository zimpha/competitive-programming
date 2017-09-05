#include <bits/stdc++.h>

void run() {
  int n;
  std::cin >> n;
  std::vector<int> c(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> c[i];
  }
  std::vector<std::string> str, rts;
  for (int i = 0; i < n; ++i) {
    std::string s;
    std::cin >> s;
    str.push_back(s);
    std::reverse(s.begin(), s.end());
    rts.push_back(s);
  }
  std::vector<long long> f(n), g(n);
  f[0] = 0, g[0] = c[0];
  for (int i = 1; i < n; ++i) {
    f[i] = g[i] = 1ll << 60;
    if (str[i - 1] <= str[i]) f[i] = std::min(f[i], f[i - 1]);
    if (rts[i - 1] <= str[i]) f[i] = std::min(f[i], g[i - 1]);
    if (str[i - 1] <= rts[i]) g[i] = std::min(g[i], f[i - 1] + c[i]);
    if (rts[i - 1] <= rts[i]) g[i] = std::min(g[i], g[i - 1] + c[i]);
  }
  long long ret = std::min(f.back(), g.back());
  if (ret == 1ll << 60) ret = -1;
  std::cout << ret << std::endl;
}

int main() {
  run();
  return 0;
}
