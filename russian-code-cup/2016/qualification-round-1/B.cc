#include <bits/stdc++.h>
using namespace std;
typedef double flt;
typedef long long LL;
typedef pair<int, int> PII;

const int MAXN = 100000 + 10;
int a[MAXN], b[MAXN], n, h;
LL s[MAXN];

void add(int x, int v) {
  for (; x <= n; x += ~x & x + 1) b[x] += v;
}
int get(int x, int r = 0) {
  for (; x >= 0; x -= ~x & x + 1) r += b[x];
  return r;
}

void run() {
  scanf("%d%d", &n, &h);
  for (int i = 1; i <= n; ++i) scanf("%d", a + i);
  for (int i = 1; i <= n; ++i) b[i] = 0;
  for (int i = 1; i <= n; ++i) {
    int x; scanf("%d", &x);
    if (x) add(i, 1);
  }
  int ret = 0;
  if (get(1) == 0) ++ret, add(1, 1);
  for (int i = 1, len = 0, j = 1; i <= n; ++i) {
    s[i] = s[i - 1] + a[i];
    if (j < i) j = i, len = 0;
    while (j <= n && len < h) len += a[j++];
    int l = 1, r = i;
    while (l < r) {
      int m = (l + r + 1) >> 1;
      if (s[i] - s[m - 1] >= h) l = m;
      else r = m - 1;
    }
    //cerr << l << " " << j - 1 << endl;
    int cnt = get(i) - get(l - 1);
    if (cnt == 0) add(i, 1), ++ret;
    len -= a[i];
  }
  if (get(n) - get(n - 1) == 0) ++ret;
  printf("%d\n", ret);
}

int main() {
  int T; scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) run();
  return 0;
}
