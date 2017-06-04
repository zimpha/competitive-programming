#include <cstdio>

const int N = 100000 + 10;

char s[N], t[N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    scanf("%s%s", s, t);
    int ret = 0;
    for (int i = 0; i + 1 < n; ++i) {
      if (s[i] != t[i]) {
        s[i] = '0' + '1' - s[i];
        s[i + 1] = '0' + '1' - s[i + 1];
        ++ret;
      }
    }
    if (s[n - 1] != t[n - 1]) ret = -1;
    printf("%d\n", ret);
  }
  return 0;
}
