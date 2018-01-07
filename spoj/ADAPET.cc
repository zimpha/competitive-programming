#include <cstdio>
#include <cstring>

const int N = 5e5 + 10;

int fail[N];
char s[N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, k;
    scanf("%s%d", s, &k);
    n = strlen(s);
    fail[0] = -1;
    for (int i = 1, j = -1; i < n; ++i) {
      while (j >= 0 && s[i] != s[j + 1]) j = fail[j];
      fail[i] = (s[i] == s[j + 1] ? ++j : j); 
    }
    int d = n - 1 - fail[n - 1];
    printf("%lld\n", n + 1ll * (k - 1) * d);
  }
  return 0;
}
