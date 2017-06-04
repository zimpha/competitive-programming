#include <bits/stdc++.h>
using namespace std;

int main() {
  char s[100], t[100]; scanf("%s", s);
  int cnt[256];
  memset(cnt, 0, sizeof(cnt));
  for (int i = 0; s[i]; ++i) cnt[(int)s[i]] = 1;
  int n; scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%s", t);
    int r1 = 0, r2 = 0;
    for (int j = 0; s[j]; ++j) {
      r1 += t[j] == s[j];
      r2 += cnt[(int)t[j]];
    }
    r2 -= r1;
    printf("%d %d\n", r1, r2);
  }
  return 0;
}
