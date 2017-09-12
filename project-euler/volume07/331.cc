#include <cstdio>
#include <bitset>
#include <algorithm>
#include <vector>
#include <iostream>

using state = std::bitset<10000>;

const int N = 10000;

state a[N];
int n, m;

int main() {
  scanf("%d", &n);
  m = n * n;
  for (int e = 0; e < n * n; ++e) {
    a[e] = 0;
    int x = e / n;
    int y = e % n;
    if ((n - 1) * (n - 1) <= x * x + y * y && x * x + y * y < n * n) a[e][m] = 1;
    for (int i = 0; i < n; ++i) {
      a[e][x * n + i] = 1;
      a[e][i * n + y] = 1;
    }
  }
  int total = 0;
  for (int i = 0; i < m; ++i) total += a[i][m];
  int rk = 0;
  for (int r = 0; r < m; ++r) {
    int t = -1;
    for (int j = r; j < m && t == -1; ++j) {
      if (a[j][r]) t = j;
    }
    if (t == -1) continue;
    if (t != r) std::swap(a[t], a[r]);
    for (int j = 0; j < m; ++j) {
      if (a[j][r] && j != r) a[j] ^= a[r];
    }
    ++rk;
  }
  std::vector<int> all;
  for (int i = 0; i < m; ++i) {
    if (!a[i][i]) all.push_back(i);
  }
  int s = all.size();
  int ret = m;
  for (int mask = 0; mask < (1 << s); ++mask) {
    state x = 0;
    for (int i = 0; i < s; ++i) {
      if (mask >> i & 1) x[all[i]] = 1;
    }
    for (int i = 0; i < m; ++i) if (a[i][i]) {
      x[i] = a[i][m];
      for (int j = i + 1; j < m; ++j) {
        if (a[i][j]) x[i] = x[i] ^ x[j];
      }
    }
    int sum = 0;
    for (int i = 0; i < m; ++i) {
      sum += x[i];
    }
    if (sum < ret) ret = sum;
  }
  printf("%d %d %d %d\n", m, rk, ret, total);
  return 0;
}
