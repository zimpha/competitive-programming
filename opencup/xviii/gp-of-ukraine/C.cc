#include <cstdio>

const int N = 1e4 + 10;

char s[N], t[20];

int main() {
  int n;
  scanf("%d%s", &n, s);
  int ret = 0;
  for (int len = 1, w = 3; len <= n && len <= 8; ++len, w *= 3) {
    for (int mask = 0; mask < w; ++mask) {
      for (int i = 0, x = mask; i < len; ++i, x /= 3) {
        t[i] = 'a' + x % 3;
      }
      int cnt = 0;
      for (int i = 0, j = 0; i < n; ++i) {
        if (s[i] == t[j]) ++j;
        if (j == len) j = 0, ++cnt;
      }
      if (cnt * len * cnt > ret) {
        ret = cnt * len * cnt;
      }
    }
  }
  printf("%d\n", ret);
  return 0;
}
