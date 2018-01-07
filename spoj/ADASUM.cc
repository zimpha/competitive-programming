#include <cstdio>
#include <cstring>

using int64 = long long;

const int N = 2e6 + 10, mod = 1e9 + 7;

char s[N];
int pw[N];

int main() {
  scanf("%s", s);
  int n = strlen(s);
  pw[0] = 1;
  for (int i = 1; i <= n; ++i) {
    pw[i] = pw[i - 1] * 10ll % mod;
  }
  for (int i = 1; i <= n; ++i) {
    pw[i] = (pw[i - 1] + pw[i]) % mod;
  }
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    ret += (int64)(i + 1) * (s[i] - '0') * pw[n - i - 1] % mod;
    ret %= mod;
  }
  printf("%d\n", ret);
  return 0;
}
