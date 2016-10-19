#include <bits/stdc++.h>

using LL = long long;

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

struct point {
  LL x, y, d;
  point() {}
  point(LL x, LL y, LL d): x(x), y(y), d(d) {}
  point(int o) {
    if (o) x = 0, y = 1, d = 1;
    else x = 0, y = 1, d = 3;
  }
  point operator + (const point &rhs) const {
    LL tx = rhs.x, ty = rhs.y, td = rhs.d;
    for (int i = 0; i < d; ++i) {
      td = (td + 1) % 4;
      std::swap(tx, ty);
      ty = -ty;
    }
    return point(x + tx, y + ty, td);
  }
};

void brute(int n, int m) {
  std::vector<bool> s;
  s.push_back(1);
  for (int i = 0; i < n; ++i) {
    int x = s.size();
    s.push_back(1);
    for (int j = 0; j < x; ++j) {
      if (j == x / 2) s.push_back(!s[j]);
      else s.push_back(s[j]);
    }
  }
  int x = 0, y = 0, d = 0;
  for (int i = 0; i < m; ++i) {
    x += dx[d];
    y += dy[d];
    if (s[i]) d = (d + 1) % 4;
    else d = (d + 3) % 4;
  }
  std::cout << x << ' ' << y << std::endl;
}

point f[100], g[100];
LL step[100];

point solve(int n, LL m, bool o) {
  if (step[n - 1] + 1 == m) return f[n - 1] + point(o);
  if (m <= step[n - 1]) return solve(n - 1, m, 1);
  return f[n - 1] + point(o) + solve(n - 1, m - step[n - 1] - 1, 0);
}

void run(int n, LL m) {
  f[0] = point(1), g[0] = point(0);
  step[0] = 1;
  for (int i = 1; i <= n; ++i) {
    f[i] = f[i - 1] + point(1) + g[i - 1];
    g[i] = f[i - 1] + point(0) + g[i - 1];
    step[i] = step[i - 1] * 2 + 1;
  }
  point res = solve(n, m, 1);
  std::cout << res.x << ',' << res.y << std::endl;
}

int main() {
  run(10, 500);
  run(50, 1000000000000ll);
  return 0;
}
