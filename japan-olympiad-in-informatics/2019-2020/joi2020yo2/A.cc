#include <cstdio>
#include <algorithm>

const int N = 1000;

char S[N][N], T[N][N], buf[N][N];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%s", S[i]);
  for (int i = 0; i < n; ++i) scanf("%s", T[i]);
  int ret = n * n;
  for (int i = 0; i < 4; ++i) {
    int cnt = std::min(i, 4 - i);
    for (int x = 0; x < n; ++x) {
      for (int y = 0; y < n; ++y) {
        cnt += S[x][y] != T[x][y];
      }
    }
    ret = std::min(ret, cnt);
    for (int x = 0; x < n; ++x) for (int y = 0; y < n; ++y) buf[y][n - x - 1] = S[x][y];
    for (int x = 0; x < n; ++x) for (int y = 0; y < n; ++y) S[x][y] = buf[x][y];
  }
  printf("%d\n",ret);
  return 0;
}
