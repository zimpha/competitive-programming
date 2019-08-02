#include <cmath>
#include <cstring>
#include <cassert>
#include <cstdio>
#include <vector>

const int N = 20000, D = 200, P = 100000, B = 1000001;

int f[N][D], p[P], rp[B], np;
bool mark[B];

int rec(int n, int d) {
  if (d == -1) return n >= 1;
  if (n < N && d < D && f[n][d] != -1) return f[n][d];
  int ret = 0, pr = p[d];
  if (pr >= n) ret = n;
  else if (d == 0) {
    for (int m = n; m; m /= 2) ++ret;
  } else if (pr * pr > n) {
    int b = rp[(int)sqrt(n)];
    assert(b < d);
    ret = rec(n, b);
    for (++b; b <= d; ++b) ret += n / p[b];
  } else if (pr > n / 2) {
    int b = rp[n / 2];
    assert(b < d);
    ret = rec(n, b) + d - b;
  } else {
    for (int m = n; m; m /= pr) {
      ret += rec(m, d - 1);
    }
  }
  if (n < N && d < D) f[n][d] = ret;
  return ret;
}

int count(int n, int b) {
  if (n <= 0) return 0;
  int v = sqrt(n);
  std::vector<int> s(v + 1, 1), l(v + 1, 1), w(v + 1);
  std::vector<int> mark(b + 1), p;
  for (int i = 1; i <= v; ++i) w[i] = n / i;
  for (int i = 2; i <= b; ++i) {
    if (!mark[i]) p.push_back(i);
    for (int j = 1, u = b / i; j <= u; ++j) {
      mark[j * i] = 1;
    }
  }
  for (auto x: p) {
    if (x <= v) {
      for (int i = x; i <= v; ++i) s[i] += s[i / x];
      for (int i = v; i >= 1; --i) {
        int u = w[i] / x;
        if (u <= v) l[i] += s[u];
        else l[i] += l[n / u];
      }
    } else {
      l[1] += n / x;
    }
  }
  return l[1];
}

int main() {
  int n, m, b;
  scanf("%d%d%d", &n, &m, &b);
  memset(f, -1, sizeof(f));
  np = 0;
  rp[1] = -1;
  for (int i = 2; i <= b; ++i) {
    if (!mark[i]) p[np++] = i;
    rp[i] = np - 1;
    for (int j = 1, u = b / i; j <= u; ++j) mark[j * i] = 1;
  }
  printf("%d\n", rec(n + m, rp[b]) - rec(n - 1, rp[b]));
  return 0;
}
