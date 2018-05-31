#include <cmath>
#include <cstdio>

int main() {
  int n, x;
  scanf("%d%d", &n, &x);
  int cnt = 1;
  for (int i = 1; i < n; ++i) {
    int u;
    scanf("%d", &u);
    cnt += u <= x;
  }
  printf("%d\n", int(log(cnt) / log(2)));
  return 0;
}
