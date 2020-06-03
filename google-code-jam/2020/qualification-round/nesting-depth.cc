#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>

const int N = 100 + 10;

char s[N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%s", s);
    int sum = 0;
    printf("Case #%d: ", cas);
    for (int i = 0; s[i]; ++i) {
      int o = s[i] - '0';
      while (sum < o) putchar('('), ++sum;
      while (sum > o) putchar(')'), --sum;
      putchar(s[i]);
    }
    while (sum > 0) putchar(')'), --sum;
    puts("");
  }
  return 0;
}
