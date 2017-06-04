#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 1000000 + 10;
LL x[MAXN], y[MAXN];
int n, m;

int main() {
  scanf("%d%d", &n, &m);
  LL ret = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      int s; scanf("%d", &s);
      x[i] += s * 2;
      y[j] += s * 2;
      ret += s * 2;
    }
  }
  LL w = ret / 2;
  int r, c;
  LL tmp = 0;
  for (r = 1; r <= n; ++r) {
    tmp += x[r];
    if (tmp >= w) break;
  }
  tmp = 0;
  for (c = 1; c <= m; ++c) {
    tmp += y[c];
    if (tmp >= w) break;
  }
  for (int i = 1; i <= n; ++i) {
    ret += x[i] * abs(i - r);
  }
  for (int i = 1; i <= m; ++i) {
    ret += y[i] * abs(i - c);
  }
  printf("%d %d %lld\n", r, c, ret);
  return 0;
}
