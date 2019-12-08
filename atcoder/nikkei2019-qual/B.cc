#include <cstdio>

const int N = 100;

char a[N], b[N], c[N];

int main() {
  int n;
  scanf("%d", &n);
  scanf("%s%s%s", a, b, c);
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    if (a[i] != b[i] && a[i] != c[i] && b[i] != c[i]) ret += 2;
    else if (a[i] == b[i] && a[i] == c[i]) ret += 0;
    else ret += 1;
  }
  printf("%d\n", ret);
  return 0;
}
