#include <cstdio>

char s[1000];

int main() {
  int n;
  scanf("%d%s", &n, s);
  for (int i = 0; i + 3 <= n; ++i) {
    if (s[i] == 'j' && s[i + 1] == 'o' && s[i + 2] == 'i') {
      s[i] = 'J';
      s[i + 1] = 'O';
      s[i + 2] = 'I';
    }
  }
  puts(s);
  return 0;
}
