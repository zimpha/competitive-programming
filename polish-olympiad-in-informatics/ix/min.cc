#include <cstdio>
#include <vector>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<char> s(n - 1);
  for (int i = 0; i < n  -1; ++i) {
    scanf(" %c", &s[i]);
  }
  for (int i = 0; i < n - 1; ++i) {
    if (s[i] == '-') putchar('-');
    else {
      if (s[i - 1] == '-') putchar('(');
      putchar('-');
      if (i == n - 2 || s[i + 1] == '-') putchar(')');
    }
  }
  puts("");
  return 0;
}
