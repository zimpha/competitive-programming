#include <bits/stdc++.h>

using LL = long long;

LL solve(LL u, LL v, LL upp) {
  LL x = u * u * v * v, y = (u + v) * (u + v);
  LL k = upp / u / u / y;
  return k * (k + 1) / 2 * (x + y * (u * u + v * v));
}

LL dfs(int a, int b, int c, int d, LL upp) {
  LL u = a + c, v = b + d;
  if (v > u || u * u > upp) return 0;
  LL ret = solve(u, v, upp);
  return ret + dfs(a, b, u, v, upp) + dfs(u, v, c, d, upp);
}

LL run(LL n) {
  //Descartes' theorem
  //ra = v^2g, rb = u^2g, rc = u^2v^2g/(u+v)^2, (u,v)=1
  return dfs(0, 1, 1, 0, n);
}

int main() {
  std::cout << run(5) << std::endl;
  std::cout << run(100) << std::endl;
  std::cout << run(1000000000) << std::endl;
  return 0;
}

