#include <cstdio>
#include <vector>

using int64 = long long;

std::vector<int64> solve(int k) {
  if (k == 1) return {0};
  if (k & 1) {
    auto u = solve(k - 1);
    for (auto &x: u) x = x * 2 + 1;
    u.push_back(0);
    return u;
  } else {
    auto u = solve(k / 2);
    int64 s = 0;
    for (auto &x: u) s |= x, x = x * 2 + 1;
    u.push_back(s * 2);
    return u;
  }
}

int main() {
  int k, s;
  scanf("%d%d", &k, &s);
  auto ret = solve(k);
  printf("%d\n", (int)ret.size());
  for (auto &x: ret) printf("%lld ", x);
  puts("");
  return 0;
}
