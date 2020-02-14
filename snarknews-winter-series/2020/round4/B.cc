#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

int main() {
  int n, m;
  scanf("%d", &n);
  std::vector<std::pair<int, int64>> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%lld%d", &a[i].second, &a[i].first);
  }
  scanf("%d", &m);
  std::vector<std::pair<int, int64>> b(m);
  for (int i = 0; i < m; ++i) {
    scanf("%lld%d", &b[i].second, &b[i].first);
  }
  int carry = 0;
  std::vector<std::pair<int, int64>> c;
  while (true) {
    while (!a.empty() && a.back().second == 0) a.pop_back();
    while (!b.empty() && b.back().second == 0) b.pop_back();
    if (a.empty() && b.empty()) break;
    int64 d1 = 0, n1 = -1, d2 = 0, n2 = -1;
    if (!a.empty()) d1 = a.back().first, n1 = a.back().second;
    if (!b.empty()) d2 = b.back().first, n2 = b.back().second;
    if (n1 == -1) n1 = n2;
    if (n2 == -1) n2 = n1;
    int64 m = std::min(n1, n2);
    if (!a.empty()) a.back().second -= m;
    if (!b.empty()) b.back().second -= m;
    c.emplace_back((d1 + d2 + carry) % 10, 1);
    carry = (d1 + d2 + carry) / 10;
    c.emplace_back((d1 + d2 + carry) % 10, m - 1);
  }
  std::vector<std::pair<int, int64>> ret;
  if (carry) ret.emplace_back(carry, 1);
  while (!c.empty()) {
    auto u = c.back(); c.pop_back();
    if (u.second == 0) continue;
    if (ret.empty()) ret.push_back(u);
    else if (ret.back().first == u.first) ret.back().second += u.second;
    else ret.push_back(u);
  }
  printf("%d\n", (int)ret.size());
  for (auto &e: ret) printf("%lld %d\n", e.second, e.first);
  return 0;
}
