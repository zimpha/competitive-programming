#include <cstdio>

const int N = 1e5 + 10;

char s[N];
int cnt[26];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%s", s);
    for (int i = 0; i < 26; ++i) cnt[i] = 0;
    for (int i = 0; s[i]; ++i) cnt[s[i] - 'a']++;
    int ret = 0;
    for (int i = 0; i < 26; ++i) {
      if (cnt[i] > ret) ret = cnt[i];
    }
    printf("Case #%d: %d\n", cas, ret);
  }
  return 0;
}
