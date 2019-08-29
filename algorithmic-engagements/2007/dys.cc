#include <cstdio>

const int N = 1e5 + 10;

char s[N], t[N];

int main() {
  int n;
  scanf("%d%s%s", &n, s, t);
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    ret += s[i] != t[i];
  }
  printf("%d\n", ret);
  return 0;
}
