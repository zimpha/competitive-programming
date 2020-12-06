#include <cstdio>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    printf("%c\n", (n % 2) ? 'B' : 'A');
  }
  return 0;
}
