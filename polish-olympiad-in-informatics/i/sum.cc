#include <cstdio>
#include <cstring>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    char s[100];
    scanf("%s", s);
    while (true) {
      if (strlen(s) == 1 && (s[0] == '1' || s[0] == '4')) break;
      printf("%s ", s);
      int n = 0;
      for (int i = 0; s[i]; ++i) n += (s[i] - '0') * (s[i] - '0');
      sprintf(s, "%d", n);
    }
    printf("%s\n", s);
  }
  return 0;
}
