#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int SZ = 100000000, MN = 10000;
int pi[SZ], pl[SZ], m;
void sieve() {
  m = 0; for (int i = 2; i < SZ; ++ i) pi[i] = 1;
  for (int i = 2; i < SZ; ++i) {
    if (pi[i]) pl[m++] = i;
    for (int j = 0; j < m && pl[j] * i < SZ; ++j) {
      pi[pl[j] * i] = 0;
      if (i % pl[j] == 0) break;
    }
  }
  for (int i = 2; i < SZ; ++ i) pi[i] += pi[i - 1];
}
inline LL sqr(LL x) {return x * x;}
inline LL cub(LL x) {return x * x * x;}
map<LL, LL> cache;
LL phi(LL x, LL a) {
  if (a == 1 || !x) return (x + 1) / 2;
  LL &r = cache[(x << 10) + a]; if (r) return r;
  return r = phi(x, a - 1) - phi(x / pl[a - 1], a - 1);
}
LL getPi(LL n) {
  if (n < SZ) return pi[n];
  LL a = getPi(pow(n, .25));
  LL b = getPi(sqrt(n));
  LL c = getPi(pow(n, 1./3));
  LL r = phi(n, a) + (b + a - 2) * (b - a + 1) / 2;
  for (int i = a + 1; i <= b; ++i) {
    LL w = n / pl[i - 1];
    r -= getPi(w);
    if (i <= c) {
      int upp = getPi(sqrt(w));
      for (int j = i; j <= upp; ++j) r += j - 1 - getPi(w / pl[j - 1]);
    }
  }
  return r;
}

LL run(LL n) {
  LL ret = 0;
  for (int i = 0; i < m; ++i) {
    LL r = 1;
    for (int j = 0; j < 7; ++j) r *= pl[i];
    if (r <= n) ++ret;
    else break;
  }
  for (int i = 0; cub(pl[i]) < n; ++i) {
    LL x = n / cub(pl[i]);
    ret += getPi(x);
    if (pl[i] <= x) --ret;
  }
  for (int i = 0, a = pl[i]; cub(a) < n; a = pl[++i]) {
    for (int j = i + 1, b = pl[j]; sqr(b) * a < n; b = pl[++j]) {
      LL c = n / (a * b);
      ret += getPi(c) - getPi(b);
    }
  }
  return ret;
}

int main() {
  sieve();
  cout << run(100) << endl;
  cout << run(1000) << endl;
  cout << run(1000000) << endl;
  cout << run(1000000000000ll) << endl;
  return 0;
}
