#include <cstdio>

const int N = 1e5 + 10;

char s[N];
int cnt[17][1 << 17];
int tot[17];

void add(int x, int v) {
  if (cnt[x][v] == 0) ++tot[x];
  cnt[x][v]++;
}

void del(int x, int v) {
  if (cnt[x][v] == 1) --tot[x];
  cnt[x][v]--;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  scanf("%s", s);
  for (int i = 0; i < n; ++i) {
    int v = 0;
    for (int j = 0; j < 17 && i + j < n; ++j) {
      v = v * 2 + s[i + j] - '0';
      add(j, v);
    }
  }
  for (int j = 0; j < 17; ++j) {
    if (tot[j] != (1 << (j + 1))) {
      printf("%d\n", j + 1);
      break;
    }
  }
  for (int i = 0, x; i < m; ++i) {
    scanf("%d", &x); --x;
    for (int a = x - 16; a <= x; ++a) if (a >= 0) {
      int v = 0;
      for (int b = 0; b < 17 && a + b < n; ++b) {
        v = v * 2 + s[a + b] - '0';
        if (a + b >= x) del(b, v);
      }
    }
    s[x] ^= '0' ^ '1';
    for (int a = x - 16; a <= x; ++a) if (a >= 0) {
      int v = 0;
      for (int b = 0; b < 17 && a + b < n; ++b) {
        v = v * 2 + s[a + b] - '0';
        if (a + b >= x) add(b, v);
      }
    }
    for (int j = 0; j < 17; ++j) {
      if (tot[j] != (1 << (j + 1))) {
        printf("%d\n", j + 1);
        break;
      }
    }
  }
  return 0;
}
