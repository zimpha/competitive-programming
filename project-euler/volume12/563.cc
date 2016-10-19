#include <bits/stdc++.h>

const int p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
const long upp = 1ll << 55;

std::vector<long> can;

void dfs(int d, long now) {
  if (d == 9) {
    can.push_back(now);
    return;
  }
  dfs(d + 1, now);
  while (now <= upp / p[d]) {
    now *= p[d];
    dfs(d + 1, now);
  }
}

int cnt[100];

int dfs_fac(int d, long p, long q) {
  if (p > q) return 0;
  if (d == 9) {
    return q * 10 <= p * 11;
  }
  int ret = 0;
  for (int i = 0; i <= cnt[d]; ++i) {
    ret += dfs_fac(d + 1, p, q);
    p *= ::p[d];
    q /= ::p[d];
  }
  return ret;
}

int calc(long n) {
  long m = n;
  for (int i = 0; i < 9; ++i) {
    cnt[i] = 0;
    while (m % p[i] == 0) {
      m /= p[i];
      cnt[i]++;
    }
  }
  return dfs_fac(0, 1, n);
}

long run(int n) {
  dfs(0, 1);
  std::sort(can.begin(), can.end());
  std::cout << can.size() << std::endl;
  std::vector<bool> mark(n + 1, 0);
  long ret = 0;
  int tot = 0;
  for (auto &&x: can) {
    int cnt = calc(x);
    if (cnt >= 2 && cnt <= n && !mark[cnt]) {
      ret += x;
      mark[cnt] = 1;
      ++tot;
      std::cout << "M(" << cnt << ") = " << x << std::endl;
    }
    if (tot == n - 1) break;
  }
  return ret;
}

int main() {
  std::cout << run(100) << std::endl;
  return 0;
}
