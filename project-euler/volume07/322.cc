#include <bits/stdc++.h>

long dp[70][2];

long dfs2(long d, long n, long m, bool e) {
  if (d < 0) return 1;
  if (dp[d][e] != -1) return dp[d][e];
  dp[d][e] = 0;
  int lower = m >> d & 1;
  int upper = e ? (n >> d & 1) : 1;
  for (int i = lower; i <= upper; ++i) {
    dp[d][e] += dfs2(d - 1, n, m, e & (i == (n >> d & 1)));
  }
  return dp[d][e];
}

bool check(long n, long m) {
  for (int i = 0; i <= 60; ++i) {
    if ((n >> i & 1) < (m >> i & 1)) return true;
  }
  return false;
}

long pw[30];
long dfs5(int d, long n, long m, bool e, long v) {
  if (d < 0) return check(v, m);
  int lower = m / pw[d] % 5;
  int now = n / pw[d] % 5;
  int upper = e ? now : 4;
  long ret = 0;
  for (int i = lower; i <= upper; ++i) {
    ret += dfs5(d - 1, n, m, e & (i == now), v * 5 + i);
  }
  return ret;
}

long run() {
  long n = 1000000000000000000ll - 1;
  long m = 1000000000000ll - 10;
  memset(dp, -1, sizeof(dp));
  long ret = dfs2(61, n, m, 1);
  pw[0] = 1;
  for (int i = 1; i < 30; ++i) pw[i] = pw[i - 1] * 5;
  ret += dfs5(27, n, m, 1, 0);
  return n - m - ret + 1;
}

int main() {
  std::cout << run() << std::endl;
  return 0;
}
