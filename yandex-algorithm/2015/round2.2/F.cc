#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>

const int N = 1e7 + 10;

char s[N], t[N];
int last[26];

int duval(char s[]) {
  int n = strlen(s), last = 0;
  for (int i = 0; i < n;) {
    int j = i, k = i + 1;
    for (; k < n && s[j] <= s[k]; ++k) j = (s[j] < s[k] ? i : (j + 1));
    for (last = i; i <= j;) i += k - j;
  }
  return n - last;
}

int main() {
  scanf("%s", s);
  int n = strlen(s);
  memset(last, -1, sizeof(last));
  for (int i = 0; i < n; ++i) last[s[i] - 'a'] = i;
  int bound = -1;
  for (int i = 0, j = 0, mx = -1; i < n && bound == -1; ++i) {
    while (j < s[i] - 'a') mx = std::max(mx, last[j++]);
    if (mx > i) bound = i;
  }
  if (bound == -1) {
    puts(s);
    return 0;
  }
  std::reverse(s + bound, s + n);
  int u = duval(s + bound);
  s[n] = 'z' + 1;
  s[n + 1] = 0;
  int v = duval(s + bound) - 1;
  std::reverse(s + bound, s + n);
  s[n] = 0;
  strcpy(t, s);
  std::reverse(s + bound, s + bound + u);
  std::reverse(t + bound, t + bound + v);
  if (strcmp(s, t) <= 0) puts(s);
  else puts(t);
  return 0;
}
