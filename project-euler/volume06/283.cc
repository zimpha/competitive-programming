//http://forumgeom.fau.edu/FG2007volume7/FG200718.pdf
#include <bits/stdc++.h>

using LL = long long;

const int N = 20000000 + 10;
int mp[N], pl[N];

void sieve() {
  int m = 0;
  for (int i = 2; i < N; ++i) {
    if (!mp[i]) mp[i] = i, pl[m++] = i;
    for (int j = 0; j < m && pl[j] * i < N; ++j) {
      mp[pl[j] * i] = pl[j];
      if (i % pl[j] == 0) break;
    }
  }
}

std::vector<LL> divisor;
int fac[100], cnt[100], sz;

void dfs(int d, LL now, LL total) {
  if (d == sz) {
    if (now * now <= total) divisor.push_back(now);
    return;
  }
  for (int i = 0; i <= cnt[d]; ++i) {
    dfs(d + 1, now, total);
    now *= fac[d];
  }
}

std::set<std::pair<LL, std::pair<LL, LL>>> S;

LL solve(int m, int u, int v) {
  sz = 0;
  for (int n = m * m * 4; n > 1; n /= mp[n]) {
    fac[sz++] = mp[n];
  }
  for (int n = u * u + v * v; n > 1; n /= mp[n]) {
    fac[sz++] = mp[n];
  } 
  std::sort(fac, fac + sz);
  cnt[0] = 1;
  int t = 0;
  for (int i = 1; i < sz; ++i) {
    if (fac[i] == fac[i - 1]) ++cnt[t];
    else fac[++t] = fac[i], cnt[t] = 1;
  }
  sz = t + 1;
  divisor.clear();
  LL total = 4ll * m * m * (u * u + v * v), ret = 0;
  dfs(0, 1, total);
  for (auto &&d1: divisor) {
    LL d2 = total / d1;
    if ((d1 + 2 * m * u) % v == 0 && (d2 + 2 * m * u) % v == 0) {
      LL a = (d1 + 2 * m * u) / v + 2 * m * v / u;
      LL b = (d2 + 2 * m * u) / v + 2 * m * v / u;
      LL c = (d1 + d2 + 4 * m * u) / v;
      if (a > b) std::swap(a, b);
      if (a > c) std::swap(a, c);
      if (b > c) std::swap(b, c);
      if (!S.count({a, {b, c}})) {
        ret += a + b + c;
        S.insert({a, {b, c}});
        //std::cout << a << ' ' << b << ' ' << c << std::endl;
      }
    }
  }
  return ret;
}

LL run(int ratio) {
  LL ret = 0;
  S.clear();
  for (int m = 1; m <= ratio; ++m) {
    for (int u = 1; u <= m * 2; ++u) if (m * 2 % u == 0) {
      for (int v = 1; v <= int(u * sqrt(3)); ++v) {
        if (std::__gcd(u, v) == 1) {
          ret += solve(m, u, v);
        }
      }
    }
  }
  return ret;
}

int main() {
  sieve();
  std::cout << run(1) << std::endl;
  std::cout << run(100) << std::endl;
  std::cout << run(200) << std::endl;
  std::cout << run(1000) << std::endl;
  return 0;
}
