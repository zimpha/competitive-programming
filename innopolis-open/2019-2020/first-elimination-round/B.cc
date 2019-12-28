#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 1e5 + 10;

int cnt[N][26];
char s[N];

int main() {
  int n;
  scanf("%d", &n);
  int len = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%s", s);
    len = std::max<int>(len, strlen(s));
    for (int j = 0; s[j]; ++j) cnt[j][s[j] - 'a']++;
  }
  int ret = 0;
  for (int i = 0; i < len; ++i) {
    int mx = 0, sum = 0;
    for (int j = 0; j < 26; ++j) {
      sum += cnt[i][j];
      mx = std::max(mx, cnt[i][j]);
    }
    ret += sum - mx;
  }
  printf("%d\n", ret);
  return 0;
}
