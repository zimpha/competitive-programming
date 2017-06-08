#include <cstdio>
#include <algorithm>

const int N = 100000 + 10;

using ll = long long;

ll sum[N];
int a[N], b[N], p[N];
int order[N], n;

bool cmp(int x, int y) {
  if (p[x] == 0) return false;
  if (p[y] == 0) return true;
  return 1ll * (a[x] - b[x]) * p[y] < 1ll * (a[y] - b[y]) * p[x];
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      scanf("%d%d%d", a + i, b + i, p + i);
      order[i] = i;
    }
    std::sort(order, order + n, cmp);
    sum[n] = 0;
    for (int i = n - 1; i >= 0; --i) {
      sum[i] = sum[i + 1] + b[order[i]];
    }
    double ret = 0;
    ll now = 0;
    for (int i = 0; i < n; ++i) {
      now += a[order[i]];
      ret += p[order[i]] / 1e7 * (now + sum[i + 1]);
    }
    printf("%.10f\n", ret);
  }
  return 0;
}
