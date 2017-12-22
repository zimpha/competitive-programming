#include <bits/stdc++.h>
using namespace std;

char s[10000];

void sol() {
  scanf("%s", s);
  int n = strlen(s);
  if (n >= 10) {
    puts("YES");
    return;
  }
  for (int i = 1; i < n; ++ i) {
    for (int j = i + 1; j < n; ++ j) {
      for (int k = j + 1; k < n; ++ k) {
        string a(s, s + i);
        string b(s + i, s + j);
        string c(s + j, s + k);
        string d(s + k, s + n);
        if (a != b && a != c && a != d && b != c && b != d && c != d) {
          puts("YES");
          return;
        }
      }
    }
  }
  puts("NO");
}

int main() {
  int T; scanf("%d", &T);
  while (T --) sol();
  return 0;
}
