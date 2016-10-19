#include <bits/stdc++.h>

const int N = 100000000;

long dfs1(long a, long b, long c, long d) {
  long u = a + c, v = b + d, ret = 0;
  long z = 2 * u * u + 3 * u * v + v * v;
  if (z > N) return 0;
  if (v % 2 == 1 && v < u * 2) ret += N / z;
  return ret + dfs1(a, b, u, v) + dfs1(u, v, c, d);
}

long dfs2(long a, long b, long c, long d) {
  long u = a + c, v = b + d, ret = 0;
  long z = v * v + 3 * u * u + 4 * u * v;
  if (z > N * 2) return 0;
  if (v < u * 3 && u % 2 == 1 && v % 2 == 1 && v % 3 != 0) ret += N * 2 / z;
  return ret + dfs2(a, b, u, v) + dfs2(u, v, c, d);
}

long dfs3(long a, long b, long c, long d) {
  long u = a + c, v = b + d, ret = 0;
  long z = v * v + 3 * u * u + 4 * u * v;
  if (z > N) return 0;
  if (v < u * 3 && v % 2 != u % 2 && v % 3 != 0) ret += N / z;
  return ret + dfs3(a, b, u, v) + dfs3(u, v, c, d);
}

int main() {
  long ret = N / 3;
  ret += dfs1(0, 1, 1, 1) + dfs2(0, 1, 1, 1) + dfs3(0, 1, 1, 1);
  std::cout << ret << std::endl;
  return 0;
}
