#include <cstdio>
#include <cstring>

int main() {
  int cnt[2][2];
  memset(cnt, 0, sizeof(cnt));
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    cnt[x & 1][y & 1]++;
  }
  int turns = 0;
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      turns += cnt[i][j] / 2;
    }
  }
  if (turns & 1) puts("Alice");
  else puts("Bob");
  return 0;
}
