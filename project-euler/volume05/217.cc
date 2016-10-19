#include <bits/stdc++.h>

const int N = 50, M = 14348907;

int f[N][N * 9], g[N][N * 9];

int solve(int n) {
  memset(f, -1, sizeof(f));
  memset(g, 0, sizeof(g));
  f[0][0] = 0; g[0][0] = 1;
  int upp = n * 9, first_half = n / 2, second_half = (n + 1) / 2 + 1;
  for (int i = 0; i < n; ++i) {
    for (int x = 0; x <= upp; ++x) {
      if (f[i][x] == -1) continue;
      for (int d = !i; d <= 9; ++d) {
        int y = x;
        if (i + 1 <= first_half) y += d;
        if (i + 1 >= second_half) y -= d;
        if (y < 0 || y > upp) continue;
        if (f[i + 1][y] == -1) f[i + 1][y] = 0;
        f[i + 1][y] += (f[i][x] * 10 + d * g[i][x]) % M;
        g[i + 1][y] += g[i][x];
        f[i + 1][y] %= M;
        g[i + 1][y] %= M;
      }
    }
  }
  return f[n][0];
}

int brute(int n) {
  int x = 1, ret = 0;
  for (int i = 0; i < n; ++i) x *= 10;
  for (int a = x / 10; a < x; ++a) {
    int m = a, u = 0, v = 0;
    int first_half = n / 2, second_half = (n + 1) / 2 + 1;
    for (int i = 0; i < n; ++i) {
      int o = m % 10;
      if (i + 1 <= first_half) u += o;
      if (i + 1 >= second_half) v += o;
      m /= 10;
    }
    if (u == v) ret += a;
  }
  return ret % M;
}

int run(int n) {
  int ret = 0;
  for (int i = 1; i <= n; ++i) {
    ret += solve(i);
    ret %= M;
  }
  return ret;
}

int main() {
  assert(run(1) == 45);
  assert(run(2) == 540);
  assert(run(5) == 334795890 % M);
  std::cout << run(47) << std::endl;
  return 0;
}
