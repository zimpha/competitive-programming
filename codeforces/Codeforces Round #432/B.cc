#include <cstdio>
#include <algorithm>

const int N = 2e6 + 10;

using int64 = long long;

int64 cnt[N], sum[N];

int main() {
  int n, x, y;
  scanf("%d%d%d", &n, &x, &y);
  for (int i = 0; i < n; ++i) {
    int v;
    scanf("%d", &v);
    cnt[v] += 1;
    sum[v] += v;
  }
  for (int i = 1; i < N; ++i) {
    cnt[i] += cnt[i - 1];
    sum[i] += sum[i - 1];
  }
  int64 ret = (int64)n * x;
  int delta = x / y + 1;
  for (int g = 2; g <= 1000000; ++g) {
    int64 now = 0;
    for (int i = g; i < N; i += g) {
      int l = i - g, r = i, m = r - delta;
      m = std::max(l, std::min(m, r));
      now += x * (cnt[m] - cnt[l]);
      now += r * (cnt[r] - cnt[m]) * y - (sum[r] - sum[m]) * y;
    }
    ret = std::min(ret, now);
  }
  printf("%lld\n", ret);
  return 0;
}