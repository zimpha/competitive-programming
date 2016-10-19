#include <bits/stdc++.h>

const int N = 100000000;

// a=u^2-v^2, b=2uv, c=u^2+v^2
long dfs1(long a, long b, long c, long d) {
  long v = a + c, u = b + d;
  long z = 2 * u * (u + v), ret = 0;
  if (z > N) return 0;
  if (v % 2 != u % 2) ret += N / z;
  return ret + dfs1(a, b, v, u) + dfs1(v, u, c, d);
}

// a=u^2-v^2, b=2uv+v^2, c=u^2+v^2+uv
long dfs2(long a, long b, long c, long d) {
  long v = a + c, u = b + d;
  long z = u * (2 * u + 3 * v) + v * v, ret = 0;
  if (z > N) return 0;
  if ((u - v) % 3) ret += N / z;
  return ret + dfs2(a, b, v, u) + dfs2(v, u, c, d);
}

// a=u^2-v^2, b=2uv+u^2, c=u^2+v^2+uv
long dfs3(long a, long b, long c, long d) {
  long v = a + c, u = b + d;
  long z = 3 * u * (u + v), ret = 0;
  if (z > N) return 0;
  if ((u - v) % 3) ret += N / z;
  return ret + dfs3(a, b, v, u) + dfs3(v, u, c, d);
}

// a=2uv+v^2, b=2uv+u^2, c=u^2+v^2+uv
long dfs4(long a, long b, long c, long d) {
  long v = a + c, u = b + d;
  long z = 2 * u * u + 2 * v * v + 5 * u * v, ret = 0;
  if (z > N) return 0;
  if ((u - v) % 3) ret += N / z;
  return ret + dfs4(a, b, v, u) + dfs4(v, u, c, d);
}

int main() {
  long ret = 0;
  ret += dfs1(0, 1, 1, 1); // 90
  ret += dfs2(0, 1, 1, 1); // 120
  ret += dfs3(0, 1, 1, 1) + dfs4(0, 1, 1, 1); // 60
  std::cout << ret + N / 3 << std::endl;
  return 0;
}
