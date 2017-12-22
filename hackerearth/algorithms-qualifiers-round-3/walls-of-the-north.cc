#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100000 + 10;
int f[MAXN], g[MAXN], h[MAXN], x[MAXN];
int n, m;

int uf[MAXN], ug[MAXN];

void addf(int x, int v) {
  for (; x >= 0; x -= ~x & x + 1) uf[x] = max(uf[x], v);
}
void addg(int x, int v) {
  for (; x <= m; x += ~x & x + 1) ug[x] = max(ug[x], v);
}
int getf(int x) {
  int r(0);
  for (; x <= m; x += ~x & x + 1) r = max(r, uf[x]);
  return r;
}
int getg(int x) {
  int r(0);
  for (; x >= 0; x -= ~x & x + 1) r = max(r, ug[x]);
  return r;
}

int sol() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++ i) {
    scanf("%d", h + i);
  }
  memcpy(x, h, sizeof(h[0]) * n);
  sort(x, x + n);
  m = unique(x, x + n) - x;
  for (int i = 0; i <= m; ++ i) uf[i] = ug[i] = 0;
  int ret(0);
  for (int i = 0; i < n; ++ i) {
    h[i] = lower_bound(x, x + m, h[i]) - x;
    f[i] = 1 + getf(h[i]);
    g[i] = 1 + getg(h[i]);
    addf(h[i], g[i]);
    addg(h[i], f[i]);
    ret = max(ret, max(f[i], g[i]));
  }
  return ret;
}

int main() {
  int T; scanf("%d", &T);
  while (T --) cout << sol() << endl;
  return 0;
}
