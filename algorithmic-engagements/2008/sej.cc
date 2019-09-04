#include <cstdio>
#include <cassert>
#include <vector>

using int64 = long long;

const int N = 1e6 + 10;

char s[N];
int fail[N], a[N];

int main() {
  int n, m;
  scanf("%d%d%s", &n, &m, s);
  fail[0] = -1;
  for (int i = 1, j = -1; i < m; ++i) {
    while (j >= 0 && s[j + 1] != s[i]) j = fail[j];
    fail[i] = s[j + 1] == s[i] ? ++j : j;
  }
  int cnt = 0;
  for (int i = 0, j = -1; i < m * 2 - 1; ++i) {
    char c = s[i < m ? i : i - m];
    while (j >= 0 && s[j + 1] != c) j = fail[j];
    if (s[j + 1] == c) ++j;
    if (j == m - 1) {
      j = fail[j];
      ++cnt;
    }
  }
  int period = m / cnt;
  for (int i = 0, x; i < n; ++i) {
    scanf("%d", &x);
    a[x % period]++;
  }
  int left = 0, right = 0;
  int64 best = 0;
  for (int k = 0; k < period; ++k) {
    if (k <= period / 2) left += a[k], best += (int64)a[k] * k;
    else right += a[k], best += (int64)a[k] * (period - k);
  }
  int64 sum = best;
  for (int i = 0, j = period / 2; i < period; ++i) {
    //printf("i=%d left=%d right=%d sum=%lld\n", i, left, right, sum);
    int nj = j + 1; if (nj >= period) nj = 0;
    left -= a[i]; right += a[i];
    sum -= left; sum += right;
    left += a[nj]; right -= a[nj];
    sum += (int64)a[nj] * (period / 2);
    sum -= (int64)a[nj] * (period - period / 2);
    if (sum < best) best = sum;
    j = nj;
  }
  printf("%lld\n", best);
  return 0;
}
