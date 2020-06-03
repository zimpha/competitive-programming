#include <cstdio>

using int64 = long long;

int cnt[2][1 << 20];

int main() {
  int n;
  scanf("%d", &n);
  int s = 0;
  cnt[0][s]++;
  int64 ret = 0;
  for (int i = 1; i <= n; ++i) {
    int x;
    scanf("%d", &x);
    s ^= x;
    ret += cnt[i & 1][s];
    cnt[i & 1][s]++;
  }
  printf("%lld\n", ret);
  return 0;
}
