#include <cstdio>

const int N = 20;

char s[N][N], t[N][N];
int n, m;

const int dx[] = {0, 0, 0, 1, -1};
const int dy[] = {0, 1, -1, 0, 0};

void turn(int x, int y) {
  for (int i = 0; i < 5; ++i) {
    int xx = x + dx[i];
    int yy = y + dy[i];
    if (xx >= 0 && xx < n && yy >= 0 && yy < m) {
      t[xx][yy] = 'X' + '.' - t[xx][yy];
    }
  }
}

int check(int mask) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      t[i][j] = s[i][j];
    }
  }
  int ret = 0;
  for (int j = 0; j < m; ++j) {
    if (mask >> j & 1) {
      turn(0, j);
      ++ret;
    }
  }
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (t[i - 1][j] == '.') {
        turn(i, j);
        ++ret;
      }
    }
  }
  for (int j = 0; j < m; ++j) {
    if (t[n - 1][j] == '.') return -1;
  }
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
      scanf("%s", s[i]);
    }
    int best = -1;
    for (int mask = 0; mask < (1 << m); ++mask) {
      int now = check(mask);
      if (now != -1 && (best == -1 || now < best)) {
        best = now;
      }
    }
    printf("Case #%d: %d\n", cas, best);
  }
  return 0;
}
