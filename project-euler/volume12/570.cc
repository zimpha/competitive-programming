#include <bits/stdc++.h>

using LL = long long;

const int N = 100000000;

int phi[N + 1], G[N + 1];
int mp[N + 1], p[N], pcnt;

void sieve() {
  for (int i = 0; i <= N; ++i) phi[i] = i;
  int m = 0, v;
  for (int i = 2; i <= N; ++i) {
    if (phi[i] == i) p[m++] = i, phi[i] = i - 1, mp[i] = i;
    for (int j = 0; j < m && p[j] * i <= N; ++ j) {
      v = p[j];
      mp[i * v] = v;
      phi[i * v] = phi[i] * (v - !!(i % v));
      if (i % v == 0) break;
    }
  }
  pcnt = m;
}

LL pm(LL a, LL n, LL m) {
  LL r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % m;
    a = a * a % m;
  }
  return r;
}

std::vector<int> dv;
int fac[100], cnt[100], sz;

void dfs(int d, int n) {
  if (d == sz) {
    dv.push_back(n);
    return;
  }
  for (int i = 0; i <= cnt[d]; ++i) {
    dfs(d + 1, n);
    n *= fac[d];
  }
}

int h1[N], h2[N];

int get(int p) {
  p /= 6;
  int t = 3 * pm(4, p - 2, p) % p;
  int m = sqrt(p) + 10;
  LL pw = 1;
  for (int i = 0; i < m; ++i) {
    int v = pw;
    if (h1[v] == -1) h1[v] = i;
    else if(h2[v] == -1) h2[v] = i;
    pw = pw * t % p;
  }
  LL it = pm(t, p - 2, p), mul = pm(it, m, p);
  int ret = 0;
  pw = 1;
  for (int i = 0; i < m; ++i) {
    int x = -1, y = -1;
    int v = pw * 2 * t % p * t % p;
    if (h1[v] != -1) x = i * m + h1[v];
    if (h2[v] != -1) y = i * m + h2[v];
    if (x >= 3) {
      if (!ret || x < ret) ret = x;
    }
    if (y >= 3) {
      if (!ret || y < ret) ret = y;
    }
    pw = pw * mul % p;
  }
  pw = 1;
  for (int i = 0; i < m; ++i) {
    h1[pw] = h2[pw] = -1;
    pw = pw * t % p;
  }
  return ret;
}

std::pair<int, int> get_A(int m) {
  // A(n) = 3 * 4 ** (n - 1) - 2 * 3 ** (n - 1)
  LL p4 = 4, p3 = 3;
  int x = 0, y;
  if (m <= 100) {
    for (int n = 3; n <= m + 3; ++n) {
      p4 = p4 * 4 % m, p3 = p3 * 3 % m;
      if ((3 * p4 - 2 * p3) % m == 0) {
        x = n;
        break;
      }
    }
  } else {
    x = get(m);
  }
  if (x == 0) return {-1, -1};
  int p = phi[m];
  sz = 0;
  for (int n = p; n > 1; n /= mp[n]) {
    if (sz == 0) fac[sz] = mp[n], cnt[sz++] = 1;
    else if (mp[n] == fac[sz - 1]) cnt[sz - 1]++;
    else fac[sz] = mp[n], cnt[sz++] = 1;
  }
  dv.clear();
  dfs(0, 1);
  for (auto &&d : dv) {
    p4 = pm(4, x + d - 1, m);
    p3 = pm(3, x + d - 1, m);
    if ((3 * p4 - 2 * p3) % m == 0) {
      y = d;
      break;
    }
  }
  return {x, y};
}

std::pair<int, int> get_A2(int x, int y, int m) {
  // A(n) = 3 * 4 ** (n - 1) - 2 * 3 ** (n - 1)
  int u = 0, v = 0;
  LL m4 = pm(4, y, m), m3 = pm(3, y, m);
  LL p4 = pm(4, x - 1, m), p3 = pm(3, x - 1, m);
  for (int i = 0; i <= m; ++i) {
    LL n = x + i * y;
    if (n > N / 10) break;
    if ((3 * p4 - 2 * p3) % m == 0) {
      u = n;
      break;
    }
    p4 = p4 * m4 % m;
    p3 = p3 * m3 % m;
  }
  if (u == 0) return {-1, -1};
  p4 = pm(4, u - 1, m), p3 = pm(3, u - 1, m);
  for (LL k = 1; k <= m; k ++) {
    LL d = k * y;
    if (d > N / 10) break;
    p4 = p4 * m4 % m;
    p3 = p3 * m3 % m;
    if ((3 * p4 - 2 * p3) % m == 0) {
      v = d;
      break;
    }
  }
  if (v == 0) v = 1e9;
  return {u, v};
}

std::pair<int, int> get_B(int x, int y, int m) {
  // B(n) =(4 * n + 26) * 3 ** (n-1) + (9 * n - 69) * 2 ** (2*n-3)
  int u = 0, v = 0;
  LL p3 = pm(3, x - 1, m), p2 = pm(2, 2 * x - 3, m);
  LL m3 = pm(3, y, m), m2 = pm(4, y, m);
  for (int i = 0; i <= m; ++i) {
    LL n = x + i * y;
    if (n > N / 10) break;
    LL bn = (4 * n + 26) * p3 + (9 * n - 69) * p2;
    if (bn % m == 0) {
      if (u == 0) u = n;
      else if (v == 0) v = n - u;
      else break;
    }
    p3 = p3 * m3 % m;
    p2 = p2 * m2 % m;
  }
  if (u == 0) return {-1, -1};
  if (v == 0) v = 1e9;
  return {u, v};
}

LL run(int n) {
  LL ret = 0;
  int cnt = 0;
  for (int i = 1; i <= n; ++i) G[i] = 6;
  for (int i = 0; i < 200000 && i < pcnt; ++i) {
    LL m = 6 * p[i];
    if (m > 10 * n) break;
    auto ta = get_A(m);
    int ax = ta.first, ay = ta.second;
    if (ax == -1) continue;
    auto tb = get_B(ax, ay, m);
    int bx = tb.first, by = tb.second;
    if (bx == -1) continue;
    if (bx > n) continue;
    for (int j = bx; j <= n; j += by) G[j] *= p[i];
    while (true) {
      m *= p[i];
      if (m > n * 10) break;
      ta = get_A2(ax, ay, m);
      ax = ta.first, ay = ta.second;
      if (ax == -1) break;
      tb = get_B(ax, ay, m);
      bx = tb.first, by = tb.second;
      if (bx == -1) break;
      if (bx > n) break;
      for (int j = bx; j <= n; j += by) G[j] *= p[i];
    }
  }
  for (int i = 3; i <= n; ++i) ret += G[i];
  return ret;
}

int main() {
  sieve();
  memset(h1, -1, sizeof(h1));
  memset(h2, -1, sizeof(h2));
  std::cout << "end sieve" << std::endl;
  std::cout << run(10000000) << std::endl;
  return 0;
}
