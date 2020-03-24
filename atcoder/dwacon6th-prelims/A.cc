#include <cstdio>
#include <cstring>

const int N = 60, M = 1e3 + 10;

char s[N][M], x[M];
int t[M];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%s%d", s[i], &t[i]);
  }
  scanf("%s", x);
  int ret = 0;
  for (int i = n - 1; i >= 0; --i) {
    if (strcmp(x, s[i]) == 0) break;
    ret += t[i];
  }
  printf("%d\n", ret);
  return 0;
}
