#include <bits/stdc++.h>

long dp[20][11][11];

long solve1(int n) {
  memset(dp, 0, sizeof(dp));
  for (int i = 1; i < 10; ++i) {
    dp[1][10][i] = 1;
  }
  for (int i = 1; i < n; ++i) {
    for (int a = 0; a <= 10; ++a) {
      for (int b = 0; b < 10; ++b) {
        if (!dp[i][a][b]) continue;
        for (int c = 0; c < 10; ++c) {
          if (c != a) dp[i + 1][b][c] += dp[i][a][b];
        }
      }
    }
  }
  long ret = 0;
  for (int i = 0; i <= 10; ++i) {
    for (int j = 0; j <= 10; ++j) {
      ret += dp[n][i][j];
    }
  }
  return ret;
}

long solve3(std::string p, int n) {
  memset(dp, 0, sizeof(dp));
  dp[0][10][10] = 1;
  for (int i = 0; i < n; ++i) {
    int l = 0, r = 9;
    if (i < p.size()) l = r = p[i] - '0';
    for (int a = 0; a <= 10; ++a) {
      for (int b = 0; b <= 10; ++b) {
        if (!dp[i][a][b]) continue;
        for (int c = l; c <= r; ++c) {
          if (c != a) dp[i + 1][b][c] += dp[i][a][b];
        }
      }
    }
  }
  long ret = 0;
  for (int i = 0; i <= 10; ++i) {
    for (int j = 0; j <= 10; ++j) {
      ret += dp[n][i][j];
    }
  }
  return ret;
}

long solve2(std::string s) {
  int n = s.size();
  long ret = 0;
  std::string prefix;
  for (int i = 0; i < n; ++i) {
    for (char j = !i + '0'; j < s[i]; ++j) {
      ret += solve3(prefix + j, n);
    }
    prefix += s[i];
  }
  ret += solve3(prefix, n);
  return ret;
}

int main() {
  long ret = 0;
  for (int n = 4; n <= 15; ++n) {
    ret += solve1(n);
  }
  ret += solve2("2017201720172017");
  for (int i = 1000; i <= 2017; ++i) {
    int a = i / 1000, b = i / 100 % 10, c = i / 10 % 10, d = i % 10;
    if (a != c && b != d) --ret;
  }
  std::cout << ret << std::endl;
  return 0;
}
