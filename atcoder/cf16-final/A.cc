#include <cstdio>
#include <cstring>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      char s[10];
      scanf("%s", s);
      if (strcmp(s, "snuke") == 0) {
        printf("%c%d\n", 'A' + j, i + 1);
        return 0;
      }
    }
  }
  return 0;
}
