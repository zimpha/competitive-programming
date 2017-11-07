#include <cstdio>

int main() {
  int cnt = 0, p = 1;
  for (int i = 1; i <= 1000000; ++i) {
    p = p * 3ll % 1000000000;
    static bool mark[10];
    for (int x = 1; x <= 9; ++x) mark[x] = 0;
    for (int x = p; x; x /= 10) mark[x % 10] = 1;
    int s = 0;
    for (int x = 1; x <= 9; ++x) s += mark[x];
    cnt += (s == 9) * i;
  }
  printf("%d\n", cnt);
  return 0;
}
