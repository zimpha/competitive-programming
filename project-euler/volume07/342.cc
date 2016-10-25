#include <bits/stdc++.h>

const int N = 10000000;

int p[N], mp[N];

void sieve() {
  for (int i = 2, m = 0; i < N; ++i) {
    if (!mp[i]) mp[i] = i, p[m++] = i;
    for (int j = 0; j < m && p[j] * i < N; ++j) {
      mp[i * p[j]] = p[j];
      if (i % p[j] == 0) break;
    }
  }
}

long run(long upp) {
  long m = pow(upp, 2.0 / 3), ret = 0;
  for (int i = 2; i <= m; ++i) {
    std::map<int, int> pf;
    std::set<int> p;
    for (int n = i; n != 1; n /= mp[n]) {
      pf[mp[n]] += 3;
      p.insert(mp[n]);
    }
    for (auto it = p.rbegin(); it != p.rend(); ++it) {
      if (pf[*it] <= 0) continue;
      pf[*it]++;
      for (int y = *it - 1; y != 1; y /= mp[y]) pf[mp[y]] -= 1;
    }
    long n = 1;
    bool flag = true;
    for (auto &&x: pf) {
      if (x.second < 0) flag = false;
      if (x.second & 1) flag = false;
      if (!flag) break;
      for (int j = 0; j < x.second; j += 2) n *= x.first;
    }
    if (flag && n < upp) ret += n;
  }
  return ret;
}

int main() {
  sieve();
  std::cout << run(10000000000ll) << std::endl;
  return 0;
}
