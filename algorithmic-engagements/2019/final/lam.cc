#include <cstdio>
#include <cstring>

using int64 = long long;

const int N = 3e5 + 10, C = 16;

char s[N];
int64 table[C][C], cnt[C];

int main() {
  scanf("%s", s);
  memset(table, 0, sizeof(table));
  memset(cnt, 0, sizeof(cnt));
  for (int i = 0; s[i]; ++i) {
    int o = s[i] - 'a';
    for (int j = 0; j < C; ++j) table[j][o] += cnt[j];
    cnt[o]++;
  }
  int64 ret = 0;
  for (int mask = 0; mask < (1 << C); ++mask) {
    int64 sum = 0;
    for (int i = 0; i < C; ++i) {
      for (int j = 0; j < C; ++j) {
        if ((mask >> i & 1) && (~mask >> j & 1)) sum += table[i][j];
      }
    }
    if (sum > ret) ret = sum;
  }
  printf("%lld\n", ret);
  return 0;
}
