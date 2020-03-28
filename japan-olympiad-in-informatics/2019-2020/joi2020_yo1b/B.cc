#include <cstdio>
#include <algorithm>

char s[1000];

int main() {
  int n, a, b;
  scanf("%d%d%d", &n, &a, &b);
  scanf("%s", s);
  std::reverse(s + a - 1, s + b);
  puts(s);
  return 0;
}
