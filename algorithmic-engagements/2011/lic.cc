#include <cstdio>

using int64 = long long;

const int N = 3e6 + 10;

int cnt[N];
int64 ret[N];

int main() {
  int n;
  scanf("%d", &n);
  int mx = 1;
  for (int i = 0, x; i < n; ++i) {
    scanf("%d", &x);
    cnt[x]++;
    if (x > mx) mx = x;
  }
  for (int g = mx; g >= 1; --g) {
    int64 x = cnt[g], &y = ret[g];
    for (int d = g + g; d <= mx; d += g) {
      y -= ret[d]; x += cnt[d];
    }
    y += x * (x - 1) / 2;
  }
  printf("%lld\n", ret[1]);
  return 0;
}
