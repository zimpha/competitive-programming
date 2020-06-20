#include <cstdio>
#include <vector>
#include <tuple>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<std::tuple<int, int, int>> p;
    for (int i = 0, x, y; i < n * 2; ++i) {
      scanf("%d%d", &x, &y);
      p.emplace_back(x, y, i < n);
    }
    std::sort(p.begin(), p.end());
    std::vector<std::tuple<int, int, int>> s;
    int ym = 200;
    for (auto &e: p) {
      if (s.empty() || std::get<2>(s.back()) == std::get<2>(e)) s.push_back(e);
      else {
        auto a = s.back(); s.pop_back();
        auto b = e;
        if (std::get<2>(a)) std::swap(a, b);
        puts("4");
        printf("%d %d\n", std::get<0>(a), std::get<1>(a));
        printf("%d %d\n", std::get<0>(a), ym);
        printf("%d %d\n", std::get<0>(b), ym);
        printf("%d %d\n", std::get<0>(b), std::get<1>(b));
        ++ym;
      }
    }
  }
  return 0;
}
