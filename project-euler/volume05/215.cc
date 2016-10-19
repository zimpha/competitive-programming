#include <bits/stdc++.h>

using LL = long long;

std::map<int, LL> dp[33];
int n, m;

void expand(int i, int d, int msk, int cur, LL val) {
  if (d == m) {
    dp[i][cur] += val;
    return;
  }
  int s = d * 2;
  int h = msk >> s & 3;
  if (h == 0) {
    expand(i, d + 1, msk, cur | (1 << s), val);
    expand(i, d + 1, msk, cur | (2 << s), val);
  } else {
    cur |= (h - 1) << s;
    expand(i, d + 1, msk, cur, val);
  }
}

bool check(int i, int msk) {
  if (!i) return true;
  for (int x = 0; x < m; ++x) {
    int h = msk >> (x * 2) & 3;
    if (i + h > n) return false;
    if (x) {
      int ph = msk >> (x * 2 - 2) & 3;
      if (h == ph && i + h != n) return false;
    }
  }
  return true;
}

LL run(int n, int m) {
  ::n = n, ::m = m;
  for (int i = 0; i <= n; ++i) dp[i].clear();
  dp[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (auto &&x: dp[i - 1]) {
      if (check(i - 1, x.first)) {
        expand(i, 0, x.first, 0, x.second);
      }
    }
  }
  return dp[n][0];
}

int main() {
  std::cout << run(9, 3) << std::endl;
  std::cout << run(32, 10) << std::endl;
  return 0;
}
