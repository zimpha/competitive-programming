#include <bits/stdc++.h>

const int M = 100000000;

int run(int n) {
  std::vector<int> phi(n + 1, 1), p;
  for (int i = 2; i <= n; ++i) {
    if (phi[i] == 1) {
      p.push_back(i);
      phi[i] = i - 1;
    }
    for (size_t j = 0; j < p.size() && i * p[j] <= n; ++j) {
      phi[i * p[j]] = phi[i] * (p[j] - !!(i % p[j]));
      if (i % p[j] == 0) break;
    }
  }
  std::vector<int> u(n + 1, 0), f(n + 1, 0);
  auto add = [&](int x, int v) {
    for (; x <= n; x += ~x & x + 1) u[x] = (u[x] + v) % M;
  };
  auto get = [&](int x, int r = 0) {
    for (; x >= 0; x -= ~x & x + 1) r = (r + u[x]) % M;
    return r;
  };
  f[6] = 1; add(phi[6], 1);
  for (int i = 7; i <= n; ++i) {
    f[i] = get(phi[i] - 1);
    f[i] = (f[i] + M - f[phi[i]]) % M;
    add(phi[i], f[i]);
    f[i] = (f[i] + f[i - 1]) % M;
  }
  return f[n];
}

int main() {
  std::cout << run(10) << std::endl;
  std::cout << run(100) << std::endl;
  std::cout << run(10000) << std::endl;
  std::cout << run(20000000) << std::endl;
  return 0;
}
