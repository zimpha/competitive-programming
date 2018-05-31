#include <cstdio>

using int64 = long long;

void mul(int n, int sgn, int64 cnt[]) {
  if (n == 0) return;
  int64 p = 1;
  for (; p * 10 <= n; p *= 10) {
    for (int i = 1; i <= 9; ++i) cnt[i] += sgn * p;
  }
  int o = n / p;
  for (int i = 1; i < o; ++i) {
    cnt[i] += sgn * p;
  }
  cnt[o] += (n - o * p + 1) * sgn;
}

void solve(int n, int sgn, int64 cnt[]) {
  if (n == 0) return;
  for (int i = 1, j; i <= n; i = j + 1) {
    j = n / (n / i);
    mul(j, sgn * (n / i), cnt);
    mul(i - 1, -sgn * (n / i), cnt);
  }
}

int main() {
  int l, r;
  scanf("%d%d", &l, &r);
  int64 cnt[10] = {};
  solve(r, 1, cnt);
  solve(l - 1, -1, cnt);
  for (int i = 1; i <= 9; ++i) {
    printf("%lld\n", cnt[i]);
  }
  return 0;
}
