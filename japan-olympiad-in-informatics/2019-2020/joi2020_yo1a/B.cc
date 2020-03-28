#include <cstdio>

int main() {
  int n;
  scanf("%d", &n);
  int ret = 0;
  for (int i = 0; i <= n; ++i) {
    char c = getchar();
    ret += (c == 'a') || (c == 'i') || (c == 'u') || (c == 'e') || (c == 'o');
  }
  printf("%d\n", ret);
  return 0;
}
