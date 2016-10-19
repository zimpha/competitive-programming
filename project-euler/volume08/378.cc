#include <bits/stdc++.h>

using LL = long long;

LL run(int n) {
  std::vector<int> mp(n + 2, 0), p;
  for (int i = 2; i <= n + 1; ++i) {
    if (!mp[i]) mp[i] = i, p.push_back(i);
    for (size_t j = 0; j < p.size() && p[j] * i <= n + 1; ++j) {
      mp[i * p[j]] = p[j];
      if (i % p[j] == 0) break;
    }
  }
  std::vector<LL> Tr(n + 1, 1);
  for (int i = 1; i <= n; ++i) {
    static int fac[100], s; s = 0;
    for (int m = i; m != 1; m /= mp[m]) fac[s++] = mp[m];
    for (int m = i + 1; m != 1; m /= mp[m]) fac[s++] = mp[m];
    std::sort(fac, fac + s);
    int cnt = 1;
    for (int j = 2; j < s; ++j) {
      if (fac[j] == fac[j - 1]) ++cnt;
      else Tr[i] *= (cnt + 1), cnt = 1;
    }
    Tr[i] *= (cnt + 1);
  }
  p.assign(n, 0);
  for (int i = 0; i < n; ++i) p[i] = i + 1;
  std::sort(p.begin(), p.end(), [&](int a, int b) {
    return Tr[a] > Tr[b];
  });
  std::vector<LL> u(n, 0), f(n, 0);
  const LL M = 1000000000000000000ll;
  auto add_mod = [](LL &x, LL y) {
    x += y;
    if (x >= M) x -= M;
  };
  auto add = [&](int x, LL v) {
    for (; x < n; x += ~x & x + 1) add_mod(u[x], v);
  };
  auto get = [&](int x) {
    LL r = 0;
    for (; x >= 0; x -= ~x & x + 1) add_mod(r, u[x]);
    return r;
  };
  for (int i = 0, j; i < n;) {
    for (j = i; j < n && Tr[p[i]] == Tr[p[j]]; ++j) {
      f[j] = get(p[j] - 1);
    }
    for (; i < j; ++i) add(p[i], 1);
  }
  u.assign(n, 0);
  LL ret = 0;
  for (int i = 0, j; i < n;) {
    for (j = i; j < n && Tr[p[i]] == Tr[p[j]]; ++j) {
      add_mod(ret, get(p[j] - 1));
    }
    for (; i < j; ++i) add(p[i], f[i]);
  }
  return ret;
}

int main() {
  std::cout << run(20) << std::endl;
  std::cout << run(100) << std::endl;
  std::cout << run(1000) << std::endl;
  std::cout << run(60000000) << std::endl;
  return 0;
}
