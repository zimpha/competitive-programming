#include <cstring>
#include <cstdio>

const int N = 1e7 + 10;

char s[N];

int main() {
  int n;
  scanf("%d ", &n);
  fgets(s, n * 2, stdin);
  bool r = true;
  for (int i = 0; i <= n * 2 - 1; ++i) {
    if (s[i] == 'A' || s[i] == 'C') {
      if (!r) {
        printf("%d\n", n - 1);
        return 0;
      }
      r = false;
    } else if (s[i] == 'B' || s[i] == 'D') {
      if (r) {
        printf("%d\n", n - 1);
        return 0;
      }
      r = true;
    }
  }
  printf("%d\n", r ? n : n - 1);
  return 0;
}
