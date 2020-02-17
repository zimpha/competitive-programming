#include <cstdio>
#include <cstring>

using int64 = long long;

int64 choose(int n, int k) {
  if (n < k) return 0;
  if (k == 0) return 1;
  if (k == 1) return n * 9;
  if (k == 2) return n * (n - 1) / 2 * 9 * 9;
  return n * (n - 1) * (n - 2) / 6 * 9 * 9 * 9;
}

const int N = 100 + 10;

char s[N];
int n, k;

int main() {
  scanf("%s%d", s, &k);
  n = strlen(s);
  int64 ret = 0, cnt = 0;
  for (int i = 0; i < n; ++i) {
    int o = s[i] - '0';
    for (int d = 0; d < o; ++d) {
      int t_cnt = cnt + (d != 0);
      if (t_cnt <= k) {
        ret += choose(n - i - 1, k - t_cnt);
      }
    }
    cnt += (o != 0);
  }
  ret += cnt == k;
  printf("%lld\n", ret);
  return 0;
}
