#include <cstdio>
#include <cstring>

const int N = 1e5 + 10;

char s[N], next[N];
int cnt[N];

int main() {
  int k;
  scanf("%d%s", &k, s);
  int n = strlen(s);
  for (int i = n - 1; i >= 0; --i) {
    cnt[i] = cnt[i + 1] + (s[i] == 's');
    if (s[i] == 's') next[i] = next[i + 1];
    else next[i] = s[i];
  }
  for (int i = 0; i < n; ++i) {
    if (s[i] == 's' && k) {
      if (next[i] < 's') --k;
      else if (k <= cnt[i + 1]) putchar('s');
      else --k;
    } else {
      putchar(s[i]);
    }
  }
  puts("");
  return 0;
}
