#include <cstdio>

int main() {
  int cnt[10] = {};
  int n, k;
  scanf("%d%d", &k, &n);
  for (int i = 0; i < n; ++i) {
    int x;
    scanf("%d", &x);
    cnt[x / 1000]++;
  }
  int ret = 2;
  for (int i = 0; i < 10; ++i) if (cnt[i]) {
    ret += (cnt[i] + k - 1) / k;
  }
  printf("%d\n", ret);
  return 0;
}
