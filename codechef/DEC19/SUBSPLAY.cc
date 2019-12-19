#include <cstdio>
#include <algorithm>

const int N = 1e5 + 10;

char s[N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d%s", &n, s);
    int ret = 0;
    int last[26];
    for (int i = 0; i < 26; ++i) last[i] = -1;
    for (int i = 0; i < n; ++i) {
      if (last[s[i] - 'a'] != -1) {
        ret = std::max(ret, last[s[i] - 'a'] + n - i);
      }
      last[s[i] - 'a'] = i;
    }
    printf("%d\n", ret);
  }
  return 0;
}
