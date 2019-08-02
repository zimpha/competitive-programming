#include <cstdio>

int main() {
  int n;
  scanf("%d", &n);
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    static char s[1000];
    scanf("%s", s);
    int cnt[256] = {0};
    for (int j = 0; s[j]; ++j) cnt[(int)s[j]]++;
    int count = 0;
    for (int j = 0; j < 256; ++j) count += !!cnt[j];
    if (count > ret) ret = count;
  }
  printf("%d\n", ret);
  return 0;
}
