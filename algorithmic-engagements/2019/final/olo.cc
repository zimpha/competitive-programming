#include <cmath>
#include <cstdio>
#include <tuple>
#include <vector>
#include <map>
#include <algorithm>

using int64 = long long;
using line = std::tuple<int, int, int64>;

std::map<line, std::vector<std::pair<int, int>>> mp;

int64 gcd(int64 a, int64 b) {
  return b ? gcd(b, a % b) : a;
}

void add(int x1, int y1, int x2, int y2) {
  int a = y2 - y1;
  int b = x1 - x2;
  int64 c = (int64)y1 * (x2 - x1) - (int64)x1 * (y2 - y1);
  int g = gcd(std::abs(a), std::abs(b));
  g = gcd(g, std::abs(c));
  a /= g, b /= g, c /= g;
  if (a < 0 || (a == 0 && b < 0)) a = -a, b = -b, c = -c;
  mp[{a, b, c}].emplace_back(x1, y1);
  mp[{a, b, c}].emplace_back(x2, y2);
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int x1, y1, x2, y2, x3, y3;
    scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3);
    add(x1, y1, x2, y2);
    add(x2, y2, x3, y3);
    add(x3, y3, x1, y1);
  }
  double ret = 0;
  for (auto &e: mp) {
    auto &u = e.second;
    std::sort(u.begin(), u.end());
    for (size_t i = 0; i < u.size(); i += 2) {
      ret += hypot(u[i].first - u[i + 1].first, u[i].second - u[i + 1].second);
    }
  }
  printf("%.10f\n", ret);
  return 0;
}
