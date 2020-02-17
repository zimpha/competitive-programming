#include <cstdio>
#include <vector>
#include <map>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int64> ret(n);
    int64 sum = 0;
    std::vector<std::map<int, int>> mps(5);
    for (int i = 0, x; i < n; ++i) {
      scanf("%d", &x);
      std::vector<std::pair<int, int>> u = {{x, x}};
      for (int j = 0; j < 5 && !u.empty(); ++j) {
        std::vector<std::pair<int, int>> v;
        for (auto &e: u) {
          int rest = e.second;
          for (auto it = mps[j].upper_bound(e.first); it != mps[j].end() && rest; ) {
            int rm = std::min(rest, it->second);
            rest -= rm, it->second -= rm;
            v.emplace_back(it->first, rm);
            sum -= rm;
            if (it->second == 0) it = mps[j].erase(it);
          }
          mps[j][e.first] += e.second;
          sum += e.second;
        }
        u.swap(v);
      }
      ret[i] = sum;
    }
    for (int i = 0; i < n; ++i) {
      if (i) putchar(' ');
      printf("%lld", ret[i]);
    }
    puts("");
  }
  return 0;
}
