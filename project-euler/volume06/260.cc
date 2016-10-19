#include <bits/stdc++.h>
using LL = long long;
const int N = 1024;
std::bitset<N> dp[N][N];

LL run(int n) {
  LL ret = 0;
  for (int x = 0; x <= n; ++x) {
    for (int y = 0; y <= n; ++y) {
      for (int z = 0; z <= n; ++z) {
        if (dp[x][y][z]) continue;
        if (x <= y && y <= z) ret += x + y + z;
        for (int i = x + 1; i <= n; ++i) dp[i][y][z] = 1;
        for (int i = y + 1; i <= n; ++i) dp[x][i][z] = 1;
        for (int i = z + 1; i <= n; ++i) dp[x][y][i] = 1;
        for (int i = 1; i + x <= n && i + y <= n; ++i) dp[x + i][y + i][z] = 1;
        for (int i = 1; i + x <= n && i + z <= n; ++i) dp[x + i][y][z + i] = 1;
        for (int i = 1; i + z <= n && i + y <= n; ++i) dp[x][y + i][z + i] = 1;
        for (int i = 1; i + x <= n && i + y <= n && i + z <= n; ++i) dp[x + i][y + i][z + i] = 1;
      }
    }
  }
  return ret;
}

int main() {
  std::cout << run(100) << std::endl;
  std::cout << run(1000) << std::endl;
  return 0;
}

