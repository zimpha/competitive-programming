#include <bits/stdc++.h>

const int M = 100000000, N = 40;

long dp3[N][N], dp2[N][N], dp1[N][N];
int n;

long solve1(int x, int y);
long solve2(int x, int y);
long solve3(int x, int y);

// type 1
long solve1(int x, int y) {
  if (x > y) std::swap(x, y);
  if (x == 0) return solve2(n, y);
  if (dp1[x][y] != -1) return dp1[x][y];
  long ret = solve1(x, y - 1) + solve1(x - 1, y);
  for (int i = 1; i <= n; ++i) {
    ret += solve3(x, i) * solve2(y, n - i) % M;
    ret += solve2(x, i) * solve3(y, n - i) % M;
  }
  ret %= M;
  return dp1[x][y] = ret;
}

// type 3
long solve2(int x, int y) {
  if (x > y) std::swap(x, y);
  if (x == 0 && y == 0) return 0;
  if (x == 0) return solve3(n, y);
  if (dp2[x][y] != -1) return dp2[x][y];
  long ret = solve2(x - 1, y) + solve2(x, y - 1);
  for (int i = 1; i < n; ++i) {
    ret += solve3(x, i) * solve3(y, n - i) % M;
  }
  ret %= M;
  return dp2[x][y] = ret;
}

// type 4
long solve3(int x, int y) {
  if (x > y) std::swap(x, y);
  if (x == 0) return 0;
  if (x == 1) return 1;
  if (dp3[x][y] != -1) return dp3[x][y];
  long ret = solve3(x - 1, y) + solve3(x, y - 1);
  ret %= M;
  return dp3[x][y] = ret;
}

long run(int n) {
  if (n == 1) return 2;
  memset(dp1, -1, sizeof(dp1));
  memset(dp2, -1, sizeof(dp2));
  memset(dp3, -1, sizeof(dp3));
  long ret = 0;
  ::n = n;
  for (int i = 1; i <= n; ++i) {
    ret += solve3(n - 1, i) * solve2(n - i, n) % M;
  }
  for (int i = 1; i <= n; ++i) {
    ret += solve2(n - 1, i) * solve3(n, n - i) % M;
  }
  ret += solve1(n - 1, n - 1);
  return ret % M;
}

int main() {
  std::cout << run(1) << std::endl;
  std::cout << run(2) << std::endl;
  std::cout << run(30) << std::endl;
  return 0;
}
