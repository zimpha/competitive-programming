#include <bits/stdc++.h>

const double PI = acos(-1.0);
const double eps = 1e-9;

struct vec {
  double a;
  int x, y, l;
  bool operator < (const vec &rhs) const {
    return a < rhs.a;
  }
};

const int N = 140;

long dp[2][N][N][N];

long run(int n) {
  std::vector<vec> v;
  for (int x = -n; x <= n; ++x) {
    for (int y = -n; y <= n; ++y) {
      for (int k = 1; k <= n; ++k) {
        if (x * x + y * y == k * k) {
          double a = atan2(y, x);
          if (a < 0) a += PI * 2;
          v.push_back((vec){a, x, y, k});
        }
      }
    }
  }
  std::sort(v.begin(), v.end());
  memset(dp, 0, sizeof(dp));
  dp[0][70][70][0] = 1;
  int sz = 0;
  for (size_t i = 0, j; i < v.size(); i = j) {
    int t = sz & 1; ++sz;
    for (j = i; j < v.size(); ++j) {
      if (fabs(v[i].a - v[j].a) > eps) break;
    }
    memcpy(dp[t ^ 1], dp[t], sizeof(dp[t]));
    for (int x = 0; x < N; ++x) for (int y = 0; y < N; ++y) {
      for (int d = 0; d <= n; ++d) if (dp[t][x][y][d]) {
        for (int k = i; k < j; ++k) {
          int xx = x + v[k].x, yy = y + v[k].y, dd = d + v[k].l;
          if (2 * abs(xx - 70) <= n && 2 * abs(yy - 70) <= n && dd <= n) {
            dp[t ^ 1][xx][yy][dd] += dp[t][x][y][d];
          }
        }
      }
    }
  }
  long ret = 0, ext = 0;
  for (int i = 1; i <= n; ++i) ret += dp[sz & 1][70][70][i];
  for (auto &&x: v) ext += x.l * 2 <= n;
  return ret - ext / 2;
}

int main() {
  std::cout << run(4) << std::endl;
  std::cout << run(30) << std::endl;
  std::cout << run(60) << std::endl;
  std::cout << run(120) << std::endl;
  return 0;
}
