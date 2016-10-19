#include <bits/stdc++.h>

const int e[10][2] = {{6, 7}, {1, 2}, {1, 3}, {1, 6}, {2, 3}, {2, 7}, {3, 4}, {4, 5}, {5, 6}, {5, 7}};
const int MOD = 1e8;

int col[10], binom[200][200];
int fA, fB;

bool check(int s) {
  for (int i = s; i < 10; ++i) {
    int u = e[i][0], v = e[i][1];
    if (col[u] == col[v]) return false;
  }
  return true;
}

void dfs(int d, int c, int tot) {
  if (d == 0) {
    std::set<int> s(col + 1, col + 8);
    if (s.size() != c) return;
    long long res = 1;
    for (int i = 2; i < c; ++i) {
      res = res * (tot - i) / (i - 1);
    }
    res %= MOD;
    if (check(0)) fA = (fA + res) % MOD;
    if (check(1)) fB = (fB + res) % MOD;
  } else if (d == 1 || d == 6) {
    dfs(d - 1, c, tot);
  } else {
    for (int i = 1; i <= c; ++i) {
      col[d] = i;
      dfs(d - 1, c, tot);
    }
  }
}

int run(int A, int B, int C) {
  col[1] = 1, col[6] = 2;
  fA = fB = 0;
  for (int i = 1; i <= C && i <= 7; ++i) {
    dfs(7, i, C);
  }
  int ret = binom[A + B][A];
  for (int i = 1; i <= A; ++i) {
    ret = 1ll * ret * fA % MOD;
  }
  for (int i = 1; i <= B; ++i) {
    ret = 1ll * ret * fB % MOD;
  }
  ret = 1ll * ret * C % MOD * (C - 1) % MOD;
  return ret;
}

int main() {
  for (int i = 0; i < 200; ++i) {
    binom[i][0] = binom[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]) % MOD;
    }
  }
  std::cout << run(1, 0, 3) << std::endl;
  std::cout << run(0, 2, 4) << std::endl;
  std::cout << run(2, 2, 3) << std::endl;
  std::cout << run(25, 75, 1984) << std::endl;
  return 0;
}
