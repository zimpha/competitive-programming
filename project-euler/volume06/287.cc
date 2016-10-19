#include <bits/stdc++.h>

using LL = long long;

LL dis(LL x, LL y, LL c) {
  LL dx = x - c, dy = y - c;
  if (dx < 0) dx = -dx;
  if (dy < 0) dy = -dy;
  if (dx >= 1e9 || dy > 1e9) return 1ll << 60;
  return dx * dx + dy * dy;
}

bool ok(LL x, LL y, LL l, LL c, LL u) {
  int cnt = 0;
  if (dis(x, y, c) > u) ++cnt;
  if (dis(x + l, y, c) > u) ++cnt;
  if (dis(x, y + l, c) > u) ++cnt;
  if (dis(x + l, y + l, c) > u) ++cnt;
  return cnt % 4 == 0;
}

LL dfs(LL x, LL y, LL l, LL c, LL u) {
  if (ok(x, y, l - 1, c, u)) return 2;
  if (l == 2) return 9;
  LL ret = 1;
  l /= 2;
  ret += dfs(x, y, l, c, u);
  ret += dfs(x + l, y, l, c, u);
  ret += dfs(x, y + l, l, c, u);
  ret += dfs(x + l, y + l, l, c, u);
  return ret;
}

LL run(int n) {
  LL c = 1 << (n - 1), u = 1ll << (2 * n - 2);
  return dfs(0, 0, c, c, u) + dfs(c, 0, c, c, u) + dfs(0, c, c, c, u) + dfs(c, c, c, c, u) + 1;
}

int main() {
  std::cout << run(1) << std::endl;
  std::cout << run(2) << std::endl;
  std::cout << run(3) << std::endl;
  std::cout << run(4) << std::endl;
  std::cout << run(5) << std::endl;
  std::cout << run(6) << std::endl;
  std::cout << run(24) << std::endl;
  return 0;
}
