#include <cstdio>
#include <vector>

const int N = 100;

int a[N][N];

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> cnt(2000);
  for (int i = 0; i < n * n; ++i) {
    int x;
    scanf("%d", &x);
    cnt[x]++;
  }
  if (n & 1) {
    int odd = 0;
    for (int i = 0; i < 2000; ++i) if (cnt[i] & 1) {
      ++odd;
      a[n / 2][n / 2] = i;
      cnt[i]--;
    }
    if (odd != 1) {
      puts("No");
      return 0;
    }
    std::vector<int> s;
    for (int i = 0; i < 2000; ++i) if (cnt[i] % 4 == 2) {
      s.push_back(i);
      cnt[i] -= 2;
    }
    if (s.size() % 2 == 1) {
      puts("No");
      return 0;
    }
    for (int i = 0; i < 2000; ++i) {
      while (cnt[i] && s.size() < n - 1) {
        s.push_back(i);
        s.push_back(i);
        cnt[i] -= 4;
      }
    }
    if (s.size() != n - 1) {
      puts("No");
      return 0;
    }
    for (int i = 0; i < n / 2; ++i) {
      a[i][n / 2] = a[n - 1 - i][n / 2] = s[i];
      a[n / 2][i] = a[n / 2][n - 1 - i] = s[i + n / 2];
    }
  } else {
    for (int i = 0; i < 2000; ++i) if (cnt[i] % 4 != 0) {
      puts("No");
      return 0;
    }
  }
  int x = 0, y = 0;
  for (int i = 0; i < 2000; ++i) {
    while (cnt[i]) {
      a[x][y] = a[x][n - 1 - y] = a[n - 1 - x][y] = a[n - 1 - x][n - 1 - y] = i;
      ++y;
      if (y == n / 2) ++x, y = 0;
      cnt[i] -= 4;
    }
  }
  puts("Yes");
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      printf("%d ", a[i][j]);
    }
    puts("");
  }
  return 0;
}
